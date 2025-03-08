///////////////////////////////////////////////////////////
//  BankStatement.cpp
//  Implementation of the Class BankStatement
//  Created on:      04-Mar-2025 14:33:13
//  Original author: matth
///////////////////////////////////////////////////////////

#include "BankStatement.h"

BankStatement::BankStatement(){
}

BankStatement::BankStatement(std::string& fname)
{
	// Data vectors for the raw data from the file
	std::vector<std::vector<std::string>> content;
	std::vector<std::string> row;
	std::string line, word;

	// Open file using fstream for reading into Internal buffer
	std::fstream file(fname, std::fstream::in);
	// Check to see if the file is open
	if (file.is_open())
		{
		// While there are lines to get from the file it will build up 'content' with the line 
		// data from the csv file
		while (std::getline(file, line))
			{
			// Row variable holds each row from the file temporarily, clear it to start
			row.clear();
			std::stringstream str(line);

			while (std::getline(str, word, ','))
			{
				// Add each word to the row
				row.push_back(word);
			}
			// Add the row to content
			content.push_back(row);
			}

		// Close the file
		file.close();
		}
	else
	{
		std::stringstream errMsg;
		errMsg << "File could not be opened. Supplied address of file below:\n\n" << fname << "\n";
		std::string err = errMsg.str();
		throw std::runtime_error(err);
	}

	// Determine what Bank the statement is from
	determineBank(content);

	// Process content into LineValue objects
	processRawData(content, fname);
	
	// Housekeeping and variable assignment functions
	makeSureDataIsAscending();
	accountingPeriod = AccountingPeriod(expenses);
}


BankStatement::~BankStatement(){

}


/**
 * Prints a high level summary of the contents of the bank statement including
 * bankName, monthly total income expenses arranged in years, and the averages
 * from the period
 */
void BankStatement::printSummary(){

}

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Private functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
*Workout the bankName from the raw data
*/
void BankStatement::determineBank(const std::vector<std::vector<std::string>>& content) {
	// ASSUMPTION: the way data is formatted in the csv is unique to every bank
	if (content[0][0] == "\"Account Name:\"")
	{
		bankName = BankName::Nationwide_UK;
	}
	else
	{
		throw std::runtime_error("Bank not recognised in BankStatement::BankStatement(std::string& fname) BankName member variable assignment");
	}
}

/*
* Process the raw data and assign it to expenses based on bank
*/
void BankStatement::processRawData(const std::vector<std::vector<std::string>>& content, const std::string& fname) {
	// Blank line value object and associated blank data variables	
	int startLine{ 0 };
	LineValue lineValue;
	
	// Process raw data based on Bank
	switch (bankName)
	{
	case BankName::Nationwide_UK:
		// Data starts on line 6 from Nationwide csvs
		startLine = 5;

		// Loop through the content and create LineValue objects
		// would be nice to take the column row from the csv and match it up
		// Hardcoded values are as such:
		// 0 - Date
		// 1 - Transaction Type
		// 2 - Description
		// 3 - Piad Out
		// 4 - Paid In
		// 5 - Balance
		for (size_t i = startLine; i < content.size(); i++)
		{
			lineValue.day = std::stoi(content[i][0].substr(1, 2));
			lineValue.month = enumFromString<Month::Month>(content[i][0].substr(4, 3), i, fname);
			lineValue.year = std::stoi(content[i][0].substr(8, 4));
			lineValue.description = content[i][2].substr(1, content[i][2].size() - 2);

			// Assign Paid in/Paid out
			// ASSUMPTION: csv file will not have 'information only' entries with no money values
			if (content[i][3] == "\"\"") // Paid out is blank
			{
				lineValue.paidOut = 0.0;
				lineValue.paidIn = std::stod(content[i][4].substr(2, content[i][4].size() - 3));
				lineValue.currency = enumFromString<Currency::Currency>(content[i][4].substr(1, 1), i, fname);
				lineValue.incomeOrExpense = IncomeOrExpense::Income;
			}
			else
			{
				lineValue.paidOut = std::stod(content[i][3].substr(2, content[i][3].size() - 3));
				lineValue.paidIn = 0.0;
				lineValue.currency = enumFromString<Currency::Currency>(content[i][3].substr(1, 1), i, fname);
				lineValue.incomeOrExpense = IncomeOrExpense::Expense;
			}

			// Is balance positive or negative?
			if (content[i][5].substr(1, 1) == "-")
			{
				lineValue.balance = std::stod(content[i][5].substr(3, content[i][5].size() - 3));
			}
			else
				lineValue.balance = std::stod(content[i][5].substr(2, content[i][5].size() - 3));

			// This is where a discrimiator would sit in order to determine the line item type
			lineValue.itemType = determineItemType(lineValue.description);

			// Push lineValue back into the expenses vector
			expenses.push_back(lineValue);
		}
		break;

	case BankName::Natwest_UK:
		// NatWest formats credit cards differently to current accounts in that the last entry is the balance
		// in the account at the end of the period
		break;
	case BankName::Halifax_UK:
		break;
	case BankName::Tide_UK:
		break;
	default:
		// Shouldn't be in here but if a bank has been added to the enum and hasn't been added to the switch
		// it'll tell the dev what's happening
		throw std::runtime_error("Bank not recognised in "
			"processRawData(const std::vector<std::vector<std::string>>& content, const std::string& fname) bankName processing switch");
		break;
	}
}

/**
 * Makes sure that the data in expenses is descending in date order
 */
void BankStatement::makeSureDataIsAscending() {
	// Determine if the data in expenses is in ascending order (oldest first) or not, if not then
	// rearrange it into ascending order
	if (expenses.empty()) throw std::runtime_error("No data in expenses vector");
	
	// Check and rearrange as required
	// ASSUMPTION: Data is in year order, then month order, then day order
	if (expenses.begin()->year >= std::prev(expenses.end())->year)
	{
		if (expenses.begin()->month >= std::prev(expenses.end())->month)
		{
			if (expenses.begin()->day >= std::prev(expenses.end())->day)
			{
				if (expenses.begin()->day == std::prev(expenses.end())->day)
				{
					// Most bank csvs don't have time info so if the statement only contains transactions from the same day assumptions
					// are made based on the bank
					// Could possibly speed this up by removing the break's but need more support for banks
					switch (bankName)
					{
					case BankName::Nationwide_UK:
						// Nationwide UK csvs are in ascending order so no need to rearrange
						break;
					case BankName::Natwest_UK:
						// Natwest UK csvs are in descending order so need to rearrange
						std::reverse(expenses.begin(), expenses.end());
						break;
					case BankName::Halifax_UK:
						// Currently unknown
						break;
					case BankName::Tide_UK:
						// Currently unknown
						break;
					case BankName::maxBanks:
						// Currently unknown
						break;
					default:
						// Shouldn't be in here but if a bank has been added to the enum and hasn't been added to the switch
						// it'll tell the dev what's happening
						throw std::runtime_error("Bank not recognised in BankStatement::makeSureDataIsAscending()");
						break;
					}
				}
				// Expense is in descending order and needs to be rearranged
				std::reverse(expenses.begin(), expenses.end());
			}
		}
	}
}

/**
 * Calculates the average monthly income
 */
void BankStatement::calculateAvgIncome(){

}


/**
 * Calculates the average monthly expenditure
 */
void BankStatement::calculateAvgExpenditure(){

}