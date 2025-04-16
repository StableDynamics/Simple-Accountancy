///////////////////////////////////////////////////////////
//  BankFileImporter.cpp
//  Implementation of the Class BankFileImporter
//  Created on:      11-Mar-2025 22:05:24
//  Original author: matth
///////////////////////////////////////////////////////////

#include "BankFileImporter.h"

#include <fstream>
#include <stdexcept>
#include <string_view>
#include <type_traits>
#include <utility>

#include "Currencies.h"
#include "HelpfulFunctions.h"
#include "IncomeOrExpense.h"
#include "ItemTypeDiscriminator.h"
#include "Month.h"

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
* Move constructor
*/
BankFileImporter::BankFileImporter(BankFileImporter&& other) noexcept
	: BankFileImporter() {
	swap(*this, other);
}


const std::string BankFileImporter::getBankName() const {

	return  enumToString(bankName, "Other");
}


const std::string_view BankFileImporter::getAccountName() const {
	return accountName;
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
	first.BankFileImporter::refreshRefs(); second.BankFileImporter::refreshRefs();
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

	// Open file using fstream for reading into Internal buffer
	std::ifstream file(fname, std::ifstream::in);
	// Check to see if the file is open
	if (file.is_open())
	{
		// Define reference variables
		std::vector<std::string> row;
		std::string line, word;
		std::stringstream strStream;
		std::stringstream wordStream; // If anything has a comma in it as part of the text this stream accounts for that
		bool isCompound{ false }; // Flag to detect if the word is a compound word

		// While there are lines to get from the file it will build up 'content' with the line 
		// data from the csv file. Need to also make sure if the word starts with @ or if it doesn't and act accordingly
		while (std::getline(file, line))
		{
			// Row variable holds each row from the file temporarily, clear it to start
			row.clear();
			strStream.str(line);
			isCompound = false; // (Re)Set to false

			while (std::getline(strStream, word, ','))
			{
				if (word.front() == '\"' && word.back() != '\"') // If the word starts with a quote but doesn't end with one
				{
					isCompound = true; // Set the flag to true
					wordStream << word;
				}
				else if (word.back() == '\"' && isCompound) // If the word ends with a quote and is a compound word
				{
					wordStream << "," << word;
					row.emplace_back(wordStream.str());

					// Clear the stream
					wordStream.str(std::string());;	wordStream.clear();
					isCompound = false; // Reset the flag
				}
				else if (isCompound) // If the word is a compound word
				{
					wordStream << "," << word; // Add the comma and the word to the stream
				}
				else // Word is not a compound word
				{
					wordStream << word; // Add the word to the stream
					row.emplace_back(wordStream.str());

					// Clear the stream
					wordStream.str(std::string());;	wordStream.clear();
				}				
			}
			// Add the row to content, and reset strStream
			content.emplace_back(row);
			strStream.str(std::string()); strStream.clear();
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
* Refreshes/creates the reference array to the rawExpenses
*/
void BankFileImporter::refreshRefs() {
	rawExpensesRef = { rawExpenses.begin(), rawExpenses.end() };
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Bank Specific Functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Work out what bank it is and assign its name
*/
void BankFileImporter::determineBank(const std::vector<std::vector<std::string>>& content) {
	// ASSUMPTION: the way data is formatted in the csv is unique to every bank
	if (content[0][0] == "\"Account Name:\"") // Consistent with Nationwide statements from 2024 - Present
	{
		bankName = BankName::Nationwide_UK_2024;
	}
	else if (content[0][0] == "Date") // Consistent with Natwest statements from 2024 - Present
	{
		bankName = BankName::Natwest_UK_2024;
	}
	else if (content[0][0] == "\"Date\"") // Consistent with Tide statements from 2024 - Present
	{
		bankName = BankName::Tide_UK_2024;
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
	case BankName::Nationwide_UK_2024:
		nationwideUKProcessing(content, fname);
		break;
	case BankName::Natwest_UK_2024:
		// NatWest formats credit cards differently to current accounts in that the last entry is the balance
		// in the account at the end of the period
		natwestUKProcessing(content, fname);
		break;
	case BankName::Halifax_UK:
		break;
	case BankName::Tide_UK_2024:
		tideUKProcessing(content, fname);
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
	// Currently supports current account, savings account, and ISA statements with the format current in 2024 - Present
	// Reference variables
	LineValue lineValue;
	size_t startLine{};

	switch (bankName)
	{
	case BankName::Nationwide_UK_2024:
		// Using zero based indexing - data starts on line 5 from Nationwide csvs
		startLine = 5;

		// Account name for Nationwide is on line 0, element 1
		accountName = content[0][1].substr(1, content[0][1].size() - 2);

		// Loop through the content and create LineValue objects
		// would be nice to take the column row from the csv and match it up
		// Hardcoded values are as such:
		// 0 - Date
		// 1 - Transaction Type
		// 2 - Description
		// 3 - Paid Out
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
				lineValue.paidIn = std::stod(content[i][4].substr(2, content[i][4].size() - 2));
				lineValue.currency = enumFromString<Currency::Currency>(content[i][4].substr(1, 1), i, fname);
				lineValue.incomeOrExpense = IncomeOrExpense::Income;
			}
			else
			{
				lineValue.paidOut = std::stod(content[i][3].substr(2, content[i][3].size() - 2));
				lineValue.paidIn = 0.0;
				lineValue.currency = enumFromString<Currency::Currency>(content[i][3].substr(1, 1), i, fname);
				lineValue.incomeOrExpense = IncomeOrExpense::Expense;
			}

			// Is balance positive or negative?
			if (content[i][5].substr(1, 1) == "-")
			{
				lineValue.balance = std::stod(content[i][5].substr(3, content[i][5].size() - 2));
			}
			else
				lineValue.balance = std::stod(content[i][5].substr(2, content[i][5].size() - 2));

			// Determine the item type
			determineItemType(lineValue);

			// Push lineValue back into the expenses vector
			rawExpenses.push_back(lineValue);
		}
		break;
	default:
		break;
	}
}


void BankFileImporter::natwestUKProcessing(const std::vector<std::vector<std::string>>& content, const std::string& fname) {
	// Currently supports current account and credit card accounts with the format current in 2024 - Present
	// Reference variables
	LineValue lineValue;
	size_t startLine{};
	std::stringstream accName;

	// Credit card statements have an additional row at the end that contains the balance, work out if it is present 
	// and if it needs to be ignored
	int ignoreLastRow{ 0 };
	if (content[content.size() - 1][2].find("Balance") != std::string::npos)
		ignoreLastRow = 1; // Ignore the last row

	switch (bankName)
	{
	case BankName::Natwest_UK_2024:
		// Using zero based indexing - data starts on line 1 from Natwest csvs
		startLine = 1;

		// Account name for Natwest is on line 1, element 5 with account number on line 1 element 6
		accName << content[1][5].substr(0, content[1][5].size()) << ", " << content[1][6].substr(0, content[1][6].size());
		accountName = accName.str();

		// Loop through the content and create LineValue objects
		// would be nice to take the column row from the csv and match it up
		// Hardcoded values are as such:
		// 0 - Date
		// 1 - Transaction Type
		// 2 - Description (occassionally has compound words with " wrapping them)
		// 3 - Value (can be +ve or -ve)
		// 4 - Balance
		// 5 - Account Name
		// 6 - Account Number
		for (size_t i = startLine; i < content.size() - ignoreLastRow; i++)
		{
			lineValue.day = std::stoi(content[i][0].substr(0, 2));
			lineValue.month = enumFromString<Month::Month>(content[i][0].substr(3, 3), i, fname);
			lineValue.year = std::stoi(content[i][0].substr(7, 4));
			lineValue.transactType = content[i][1].substr(0, content[i][1].size());

			// Determine if there are " or not in the description string
			if (content[i][2][0] == '\"')
				lineValue.description = content[i][2].substr(1, content[i][2].size() - 1);
			else
				lineValue.description = content[i][2].substr(0, content[i][2].size());

			// Assign Paid in/Paid out
			// ASSUMPTION: csv file will not have 'information only' entries with no money values
			// ASSUMPTION: Natwest csvs wil only have GBP transactions due to the values being only numbers
			if (content[i][3][0] != '-') // Value is +ve
			{
				lineValue.paidOut = 0.0;
				lineValue.paidIn = std::stod(content[i][3].substr(0, content[i][3].size()));
				lineValue.currency = Currency::GBP;
				lineValue.incomeOrExpense = IncomeOrExpense::Income;
			}
			else // Value is -ve
			{
				lineValue.paidOut = std::stod(content[i][3].substr(1, content[i][3].size()));
				lineValue.paidIn = 0.0;
				lineValue.currency = Currency::GBP;
				lineValue.incomeOrExpense = IncomeOrExpense::Expense;
			}

			// Is balance positive or negative?
			if (content[i][4][0] == '-' && content[i][4] != "")
				lineValue.balance = std::stod(content[i][4].substr(1, content[i][4].size()));
			else if (content[i][4][0] != '-' && content[i][4] != "")
				lineValue.balance = std::stod(content[i][4].substr(0, content[i][4].size()));
			else
				lineValue.balance = 0.0;

			// Determine the item type
			determineItemType(lineValue);

			// Push lineValue back into the expenses vector
			rawExpenses.push_back(lineValue);
		}
		break;
	default:
		break;
	}
}


void BankFileImporter::tideUKProcessing(const std::vector<std::vector<std::string>>& content, const std::string& fname) {
	// Currently supports business current account statements with the format current in 2024 - Present
	// Reference variables
	LineValue lineValue;
	size_t startLine{};
	auto lastSlash = fname.find_last_of("\\");
	auto firstUnderscore = fname.find_first_of("_", lastSlash);

	switch (bankName)
	{
	case BankName::Tide_UK_2024:
		// Using zero based indexing - data starts on line 1 from Tide csvs
		startLine = 1;

		// Tide statements do not have an account name in them but the fname might do if it hasn't been altered
		if (firstUnderscore != std::string::npos)
			// ASSUMPTION: Default Tide formatting is always "Tide Account Type_DD_Mmm_YYYY_HH.MM.SS.csv"
			if (fname.substr(lastSlash, firstUnderscore - lastSlash).find("Tide") != std::string::npos)
				accountName = fname.substr(lastSlash + 1, firstUnderscore - lastSlash - 1);
			else
				accountName = "Tide Account";
		else
			accountName = "Tide Account";

		// Loop through the content and create LineValue objects
		// would be nice to take the column row from the csv and match it up
		// Hardcoded values are as such:
		// 0  - Date
		// 1  - Transaction ID
		// 2  - Description
		// 3  - Reference
		// 4  - From
		// 5  - To
		// 6  - Paid In
		// 7  - Paid Out
		// 8  - Category Name
		// 9  - Transaction Type
		// 10 - Status
		// 11 - Initiated By
		for (size_t i = startLine; i < content.size(); i++)
		{
			lineValue.day = std::stoi(content[i][0].substr(9, 2));
			lineValue.month = static_cast<Month::Month>(std::stoi(content[i][0].substr(6, 2)));
			lineValue.year = std::stoi(content[i][0].substr(1, 4));
			lineValue.transactType = content[i][9].substr(1, content[i][9].size() - 2);
			lineValue.description = content[i][2].substr(1, content[i][2].size() - 2);

			// Assign Paid in/Paid out
			// ASSUMPTION: csv file will not have 'information only' entries with no money values
			// ASSUMPTION: Tide csvs wil only have GBP transactions due to the values being only numbers
			if (content[i][7] == "\"\"") // Paid out is blank
			{
				lineValue.paidOut = 0.0;
				lineValue.paidIn = std::stod(content[i][6].substr(1, content[i][4].size() - 2));
				lineValue.currency = Currency::GBP;
				lineValue.incomeOrExpense = IncomeOrExpense::Income;
			}
			else
			{
				lineValue.paidOut = std::stod(content[i][7].substr(1, content[i][7].size() - 2));
				lineValue.paidIn = 0.0;
				lineValue.currency = Currency::GBP;
				lineValue.incomeOrExpense = IncomeOrExpense::Expense;
			}

			// Tide csvs do not have a value for balance
			lineValue.balance = 0.0;

			// Determine the item type
			determineItemType(lineValue);

			// Push lineValue back into the expenses vector
			rawExpenses.push_back(lineValue);
		}
		break;
	default:
		break;
	}
}


void BankFileImporter::makeSureDataIsAscending() {
	// Determine if the data in expenses is in ascending order (oldest first) or not, if not then
	// rearrange it into ascending order
	if (rawExpenses.empty()) throw std::runtime_error("No data in rawExpenses vector");

	// Check and rearrange as required
	// ASSUMPTION: Data is in year order, then month order, then day order
	// Worth just using sort on data regardless of bank?
	// Most bank csvs don't have time info so if the statement only contains transactions from the same day assumptions
	// are made based on the bank
	// Could possibly speed this up by removing the break's but need more support for banks
	switch (bankName)
	{
	case BankName::Nationwide_UK_2024:
		// Nationwide UK csvs are in ascending order so no need to rearrange
		break;
	case BankName::Natwest_UK_2024:
		// Natwest UK csvs are in descending order so need to rearrange
		std::reverse(rawExpenses.begin(), rawExpenses.end());
		break;
	case BankName::Halifax_UK:
		// Currently unknown
		break;
	case BankName::Tide_UK_2024:
		// Currently unknown
		break;
	case BankName::maxBanks:
		throw std::runtime_error("Bank name not modified from maxBanks and detected in BankStatement::makeSureDataIsAscending()");
		break;
	default:
		// Shouldn't be in here but if a bank has been added to the enum and hasn't been added to the switch
		// it'll tell the dev what's happening
		throw std::runtime_error("Bank not recognised in BankStatement::makeSureDataIsAscending()");
		break;
	}
}