///////////////////////////////////////////////////////////
//  BankStatement.cpp
//  Implementation of the Class BankStatement
//  Created on:      04-Mar-2025 14:33:13
//  Original author: matth
///////////////////////////////////////////////////////////

#include "BankStatement.h"

BankStatement::BankStatement(std::string fname) : bankName{ BankName::Nationwide_UK }, accountingPeriod{ "" }, avgIncome{ 0 }, avgExpenditure{ 0 }
{
	// Data vectors for the raw data from the file
	std::vector<std::vector<std::string>> content;
	std::vector<std::string> row;
	std::string line, word;

	// Blank line value object and associated blank data variables	
	int startLine{ 0 };
	LineValue lineValue = { 0, Month::January, 0, "", "", Currency::GBP, 0, 0, 0, IncomeOrExpense::Expense, ItemType::Bills };

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
	// ASSUMPTION: the first entry in content is unique to the bank
	if (content[0][0] == "\"Account Name:\"")
	{
		bankName = BankName::Nationwide_UK;
	}
	else
	{
		throw std::runtime_error("Bank not recognised");
	}

	// Process content into LineValue objects
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
			lineValue.day = std::stoi(content[i][0].substr(1,2));
			lineValue.month = enumFromString<Month::Month>(content[i][0].substr(4, 3), i, fname);
			lineValue.year = std::stoi(content[i][0].substr(8, 4));
			lineValue.description = content[i][2].substr(1, content[i][2].size() - 2);
			lineValue.description_ptr = static_cast<std::string_view>(lineValue.description);

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
			if (content[i][5].substr(1,1) == "-")
			{
				lineValue.balance = std::stod(content[i][5].substr(3, content[i][5].size() - 3));
			}else
				lineValue.balance = std::stod(content[i][5].substr(2, content[i][5].size() - 3));

			// This is where a discrimiator would sit in order to determine the line item type


			// Push lineValue back into the expenses vector
			expenses.push_back(lineValue);
		}
		break;

	case BankName::Natwest_UK:
		break;
	case BankName::Halifax_UK:
		break;
	case BankName::Tide_UK:
		break;
	default:
		break;
	}
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

/**
 * Determines the period that this accounting period is over based on the dates
 * supplied
 */
void BankStatement::determineAccountingPeriod(){

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