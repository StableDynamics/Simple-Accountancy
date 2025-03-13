///////////////////////////////////////////////////////////
//  BankFileImporter.cpp
//  Implementation of the Class BankFileImporter
//  Created on:      11-Mar-2025 22:05:24
//  Original author: matth
///////////////////////////////////////////////////////////

#include "BankFileImporter.h"

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Public functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BankFileImporter::BankFileImporter(){
}


BankFileImporter::BankFileImporter(const std::string& fname) {
	// Process file
	std::vector<std::vector<std::string>> content = importFile(fname);

	// Determine what Bank the statement is from
	determineBank(content);

	// Process content into LineValue objects
	processRawFStream(content, fname);

	// Housekeeping and variable assignment functions
	makeSureDataIsAscending();

	// Create reference wrapper for rawExpenses
	refreshRefs();

	// Create the AccountingPeriod
	accountingPeriod = AccountingPeriod(rawExpenses);
}


BankFileImporter::~BankFileImporter(){

}


/*
* Copy constructor
*/
BankFileImporter::BankFileImporter(const BankFileImporter& other)
	: bankName(other.bankName),
rawExpenses(other.rawExpenses),
accountingPeriod(other.accountingPeriod)
{
	refreshRefs();
}


/*
* Move constructor
*/
BankFileImporter::BankFileImporter(BankFileImporter&& other) noexcept
	: BankFileImporter() {
	swap(*this, other);
}


const std::string BankFileImporter::getBankName() const {

	return  enumToString(bankName, "Other");
}


const std::vector<std::reference_wrapper<LineValue>> BankFileImporter::getRawExpRef() const {
	return rawExpensesRef;
}


const AccountingPeriod& BankFileImporter::getAccountingPeriod() const {

	return  accountingPeriod;
}

// Overloaded operators
BankFileImporter& BankFileImporter::operator=(BankFileImporter other) {
	swap(*this, other);

	this->refreshRefs(); // Refresh references

	return *this;
}

// Friend Functions
void swap(BankFileImporter& first, BankFileImporter& second) {
	using std::swap; // Allows association to the std::swap function

	swap(first.bankName, second.bankName);
	swap(first.rawExpenses, second.rawExpenses); // rawExpensesRef is not copied as it'll contain garbage data so can be left blank
	second.refreshRefs();
	swap(first.accountingPeriod, second.accountingPeriod);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Private functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Process the file and create content from the data
*/
std::vector<std::vector<std::string>> BankFileImporter::importFile(const std::string& fname){
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
		// Close the file
		file.close();

		// Error
		std::stringstream errMsg;
		errMsg << "File could not be opened. Supplied address of file below:\n\n" << fname << "\n";
		std::string err = errMsg.str();
		throw std::runtime_error(err);
	}

	return content;
}

/*
* Work out what bank it is and assign its name
*/
void BankFileImporter::determineBank(const std::vector<std::vector<std::string>>& content) {
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
* Process the raw fstream and assign it to rawExpenses as a series of LineValue objects
*/
void BankFileImporter::processRawFStream(const std::vector<std::vector<std::string>>& content, const std::string& fname) {
	// Process raw data based on Bank
	switch (bankName)
	{
	case BankName::Nationwide_UK:
		nationwideUKProcessing(content, fname);
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

void BankFileImporter::nationwideUKProcessing(const std::vector<std::vector<std::string>>& content, const std::string& fname){
	LineValue lineValue;
	// Data starts on line 6 from Nationwide csvs
	size_t startLine = 5;

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
		lineValue.transactType = content[i][1].substr(1, content[i][1].size() - 2);
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
		rawExpenses.push_back(lineValue);
	}
}


void BankFileImporter::makeSureDataIsAscending(){
	// Determine if the data in expenses is in ascending order (oldest first) or not, if not then
	// rearrange it into ascending order
	if (rawExpenses.empty()) throw std::runtime_error("No data in rawExpenses vector");

	// Check and rearrange as required
	// ASSUMPTION: Data is in year order, then month order, then day order
	// Worth just using sort on data regardless of bank?
	if (rawExpenses.begin()->year >= std::prev(rawExpenses.end())->year)
	{
		if (rawExpenses.begin()->month >= std::prev(rawExpenses.end())->month)
		{
			if (rawExpenses.begin()->day >= std::prev(rawExpenses.end())->day)
			{
				if (rawExpenses.begin()->day == std::prev(rawExpenses.end())->day)
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
						std::reverse(rawExpenses.begin(), rawExpenses.end());
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
				std::reverse(rawExpenses.begin(), rawExpenses.end());
			}
		}
	}
}


/*
* Refreshes/creates the reference array to the rawExpenses
*/
void BankFileImporter::refreshRefs() {
	rawExpensesRef = { rawExpenses.begin(), rawExpenses.end() };
}