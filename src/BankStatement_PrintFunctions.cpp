
#include "BankStatement.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <tuple>

#include "HelpfulFunctions.h"
#include "OutputFormatting.h"

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <consoleapi2.h>
#include <WinNls.h>
#endif


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Public functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Prints a high level summary of the contents of the bank statement including
 * bankName, monthly total income expenses arranged in years, and the averages
 * from the period.
 * Functinality varies by OS due to needing to convert UTF8 strings
 */
void BankStatement::printStatementSummary(int strLen) const {
	std::string printDesc = "Statement Averages Summary";
	printPerriodStart(strLen, printDesc);

	// Setup config variables
	int width1{ 17 }; // padding size
	int width2{ 25 }; // padding size
	int currIdx{ 0 };
	size_t avgEndIdx = static_cast<size_t>(avgByType[0][0].size() - 1);

	// Depending on OS display a summary of the contents
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8); // Set console output to UTF-8 on Windows
	SetConsoleCP(CP_UTF8); // Set console itself to UTF-8
	//std::locale::global(std::locale("en_GB.UTF-8")); // Set locale globally to UTF-8, this might be needed for portability
#endif

	for (auto& currency : avgByType)
	{
		if (!(currency[0][avgEndIdx] <= 0.00001 && currency[0][avgEndIdx] >= -0.00001) || !(currency[1][avgEndIdx] <= 0.00001 && currency[1][avgEndIdx] >= -0.00001)) // Making sure there is an income/expense per currency by checking the total value at the end of the array
		{
			std::string currSym = enumToString(static_cast<Currency::Currency>(currIdx), "Other");
			std::string_view currSym_sv = currSym; // Saves a lot of copying
			std::cout << "##### " << enumToString(static_cast<Currency::Currency>(currIdx), "3Len") << " / " << currSym_sv << " #####" << std::endl << std::endl;
			std::stringstream tableHeader;
			tableHeader <<
				std::left << "|" << std::setw(width1) << "Type" << "|" << std::setw(width2) << "Average Value over Period" << "|" << std::endl <<
				"|" << std::setw(width1) << std::string(width1, '-') << "|" << std::setw(width2) << std::string(width2, '-') << "|" << std::endl;
			for (size_t i = 0; i < currency.size(); i++)
			{
				switch (static_cast<IncomeOrExpense::IncomeOrExpense>(i))
				{
				case IncomeOrExpense::Income:
					std::cout << "AVERAGE INCOME PER MONTH OVER PERIOD" << std::endl << std::endl;
					std::cout << tableHeader.str();
					break;
				case IncomeOrExpense::Expense:
					std::cout << "AVERAGE EXPENSE PER MONTH OVER PERIOD" << std::endl << std::endl;
					std::cout << tableHeader.str();
					break;
				default:
					// Has someone added an extra enum to IncomeOrExpense?
					std::stringstream errMsg;
					errMsg << "BankStatement::printStatementSummary(int strLen): Unrecognised IncomeOrExpense Index of " << i;
					std::string err = errMsg.str();
					throw std::runtime_error(err);
					break;
				}

				std::stringstream val;
				size_t j{ 0 };
#ifdef _WIN32
				width2 += 1; // Windows weirdness due to UTF8 shenanigans
#endif // _WIN32
				while (j < static_cast<size_t>(ItemType::maxItemTypes))
				{
					val << currSym_sv << TWODP(currency[i][j]);
					std::cout <<
						std::left << "|" << std::setw(width1) << enumToString(static_cast<ItemType::ItemType>(j), "Other") << "|" << std::right << std::setw(width2) << val.str() << "|" << std::endl;
					val.str(std::string()); val.clear(); // Clear and reset it
					j++;
				}
				val << currSym_sv << TWODP(currency[i][j]);
				std::cout <<
					std::left << "|" << std::setw(width1) << "Total" << "|" << std::right << std::setw(width2) << val.str() << "|" << std::endl << std::endl;
#ifdef _WIN32
				width2 -= 1; // Windows weirdness due to UTF8 shenanigans
#endif // _WIN32
			}
			// Income vs Expenditure
			std::cout << "Average Monthly Income vs Expenditure: ";
			if (avgIncVsExp[currIdx] < 0.0)
			{
				std::stringstream tot;
				tot << TWODP(avgIncVsExp[currIdx]);
				std::string total = tot.str();
				total.insert(1, std::string(currSym_sv));
				std::cout << total;
			}
			else
				std::cout << currSym_sv << TWODP(avgIncVsExp[currIdx]);
			std::cout << std::endl << std::endl;
		}
		currIdx += 1;
	}

	printPerriodEnd(strLen, printDesc);
}

/*
* Prints a month by month breakdown of the statement with various options for display type and string length.
* dispType values:
* 0 = (default) top level categories only
* 1 = top level categories, sub-categories, and individual line items
* 2 = top level categories and individual line items
*
* strLen Values:
* 0 (default) = 3Len strings
* 1 = long strings
* 2 = number strings
*/
void BankStatement::printPerMonthDetails(int dispType, int strLen) const {
	if (strLen > 2) throw std::runtime_error("BankStatement::printStatementSummary(int strLen) called with wrong value. "
		"Acceptable values are 0 for 3Len strings, 1 for long strings, and 2 for number strings.");
	if (dispType > 2) throw std::runtime_error("BankStatement::printPerMonthDetails(int dispType) called with wrong value. "
		"Acceptable values are 0 for Categories, 1 for Categories and Sub-Categories, and 2 for all details.");

	std::string printDesc = "Statement Month by Month Summary";
	printPerriodStart(strLen, printDesc);

	// Depending on OS display a month by month breakdown of the contents
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8); // Set console output to UTF-8 on Windows
	SetConsoleCP(CP_UTF8); // Set console itself to UTF-8
	//std::locale::global(std::locale("en_GB.UTF-8")); // Set locale globally to UTF-8, this might be needed for portability
#endif

	// Setup config variables
	std::string indent1 = "    "; // Indentation for the output
	int width1{ 15 }; // padding size
	int width2{ 20 }; // padding size
	int width3{ 25 }; // padding size
	int width4{ 25 }; // padding size
	size_t avgEndIdx = static_cast<size_t>(avgByType[0][0].size() - 1);

	// idx values
	int idxYear{ 0 }; // Year index
	int idxMonth{ 0 }; // Month index
	int idxCurrency{ 0 }; // Currency index
	int idxIncomeOrExpense{ 0 }; // Income or Expense index
	int idxItemType{ 0 }; // Item type index


	for (auto& year : getMonthlyTotals())
	{
		std::cout << "##### " << getYearsContained()[idxYear] << " #####" << std::endl;
		for (auto& month : year)
		{
			std::cout << indent1 << "##### " << enumToString(getMonthsContained()[idxYear][idxMonth]) << " #####" << std::endl;
			for (auto& currency : month)
			{
				if (!(currency[0][avgEndIdx] <= 0.00001 && currency[0][avgEndIdx] >= -0.00001) || !(currency[1][avgEndIdx] <= 0.00001 && currency[1][avgEndIdx] >= -0.00001)) // Making sure there is an income/expense per currency by checking the total value at the end of the array
				{
					std::string currSym = enumToString(static_cast<Currency::Currency>(idxCurrency), "Other");
					std::string_view currSym_sv = currSym; // Saves a lot of copying
					std::cout << indent1 << indent1 << "##### " << enumToString(static_cast<Currency::Currency>(idxCurrency), "3Len") << " / " << currSym_sv << " #####" << std::endl;
					for (auto& incomeOrExpense : currency)
					{
						switch (std::get<0>(IncomeOrExpense::enumData[idxIncomeOrExpense]))
						{
						case IncomeOrExpense::Income:
							std::cout << indent1 << indent1 << "##### Income #####" << std::endl;
							std::cout << indent1 << indent1 << indent1 << std::left << std::setw(width1) << "Total Income: " << std::setw(width2) << " " << std::setw(width3) << " " << std::setw(width4) << " " << currSym_sv << TWODP(incomeOrExpense.back()) << std::endl;
							break;
						case IncomeOrExpense::Expense:
							std::cout << indent1 << indent1 << "##### Expense #####" << std::endl;
							std::cout << indent1 << indent1 << indent1 << std::left << std::setw(width1) << "Total Expense: " << std::setw(width2) << " " << std::setw(width3) << " " << std::setw(width4) << " " << currSym_sv << incomeOrExpense.back() << std::endl;
							break;
						default:
							// Has someone added an extra enum to IncomeOrExpense?
							std::stringstream errMsg;
							errMsg << "BankStatement::printPerMonthDetails(int dispType, int strLen): Unrecognised IncomeOrExpense Index of " << idxIncomeOrExpense;
							std::string err = errMsg.str();
							throw std::runtime_error(err);
							break;
						}
						// Loop through the categories
						for (auto& itemType : incomeOrExpense)
						{
							if (idxItemType != static_cast<int>(ItemType::maxItemTypes)) // Make sure it doesn't trigger the last empty entry
							{
								std::stringstream cat;
								cat << std::get<1>(ItemType::enumData[idxItemType]) << ": ";
								std::cout << indent1 << indent1 << indent1 << std::left << std::setw(width1) << " " << std::setw(width2) << cat.str() << std::setw(width3) << " " << std::setw(width4) << " " << " | " << currSym_sv << TWODP(itemType) << std::endl;

								// Loop through sub-categories and items
								if ((dispType == 1 || dispType == 2) && itemType > 0.0000000001)
									printSubCategories(dispType, strLen, currSym_sv, indent1, width1, width2, width3, width4, idxYear,
										idxMonth, idxCurrency, idxIncomeOrExpense, idxItemType);

								cat.str(std::string()); cat.clear(); // Clear and reset the stringstream

								idxItemType += 1; // Increment item type index
							}
						}
						idxIncomeOrExpense += 1; // Increment IncomeOrExpense index
						idxItemType = 0; // Reset item type index for next loop
					}
					idxIncomeOrExpense = 0; // Reset currency index for next loop
					idxCurrency += 1; // Increment currency index
				}
			}
			std::cout << std::endl;
			idxCurrency = 0; // Reset currency index for next loop
			idxMonth += 1; // Increment month index
		}
		idxMonth = 0; // Reset month index for next loop
		idxYear += 1; // Increment year index
	}
	printPerriodEnd(strLen, printDesc);
}

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Private functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Prints the header at the start of the reporting sections
void BankStatement::printPerriodStart(int strLen, std::string printDesc) const {
	// Input determines the length of strings used in account period
	// 0 (default) = 3Len strings
	// 1 = long strings
	// 2 = number strings
	if (strLen > 2) throw std::runtime_error("BankStatement::printPerriodStart(int strLen) called with wrong value. "
		"Acceptable values are 0 for 3Len strings, 1 for long strings, and 2 for number strings.");

	std::cout << "########### " << printDesc << " for " << this->getBankName() << " ##########" << std::endl;
	std::cout << "### Accounting Period: " << (this->getAccountingPeriod()).getDescriptionString_sv(strLen) << std::endl;
	std::cout << "### Account Name: " << (this->getAccountName()) << std::endl << std::endl;
}

// Prints the header at the end of the reporting sections. strLen is to do with the displayed strig length and printDscr is a description of the summary being printed
void BankStatement::printPerriodEnd(int strLen, std::string printDesc) const {
	// Input determines the length of strings used in account period
	// 0 (default) = 3Len strings
	// 1 = long strings
	// 2 = number strings
	if (strLen > 2) throw std::runtime_error("BankStatement::printPerriodEnd(int strLen) called with wrong value. "
		"Acceptable values are 0 for 3Len strings, 1 for long strings, and 2 for number strings.");

	std::cout << "#### End of " << printDesc << " for " << this->getBankName() << " ####" << std::endl;
	std::cout << "#### Account Name: " << (this->getAccountName()) << std::endl;
	std::cout << "#### Accounting Period: " << (this->getAccountingPeriod()).getDescriptionString_sv(strLen) << std::endl;
	std::cout << "########## End of " << printDesc << " for " << this->getBankName() << " ##########" << std::endl << std::endl;
}


/*
*Splits a string into a vector of strings based on a maximum width
*/
std::vector<std::string> BankStatement::splitStrIntoStringsFromWidth(std::string const& inputStr, int const maxWidth) const {

	std::string word;
	std::string line;
	std::vector<std::string> lines;
	std::istringstream iss(inputStr);

	while (iss >> word) // split the string into words
	{
		if (line.length() + word.length() + 1 > maxWidth) // Check if adding the word exceeds the width
		{
			lines.emplace_back(line); // Store the current line
			line = word; // Start a new line with the current word
		}
		else
		{
			if (!line.empty()) line += " "; // Add a space before the word if line is not empty
			line += word; // Add the word to the current line
		}
	}

	// Assign Line to Lines
	if (!line.empty())
		lines.push_back(line);

	return lines;
}


/**
 * Prints out the sub-categories and the individual LineItems depending on the dispType value.
 */
void BankStatement::printSubCategories(int const dispType, int const strLen, std::string_view currSym_sv, std::string const indent1,
	int const width1, int const width2, int const width3, int const width4, int const idxYear, int const idxMonth,
	int const idxCurrency, int const idxIncomeOrExpense, int const idxItemType) const {
	double subCatTotal{ 0.0 }; // Total for the sub-category
	int idxSubCat{ 0 }; // Index for the sub-category

	// Sub-category printing variables
	std::vector<std::string> scLines;

	// Vectors to store the sub-category names and item strings
	std::vector<std::string> subCats;
	double itemVal{ 0.0 };
	std::vector<std::tuple<std::string, double>> items;

	// Extract keys using std::transform and a lambda function
	auto lineValueMap = getLineValuesFromDatabase(getYearsContained()[idxYear], getMonthsContained()[idxYear][idxMonth],
		std::get<0>(Currency::enumData[idxCurrency]), std::get<0>(IncomeOrExpense::enumData[idxIncomeOrExpense]),
		std::get<0>(ItemType::enumData[idxItemType]));

	std::transform(lineValueMap.begin(), lineValueMap.end(), back_inserter(subCats),
		[](const std::pair<std::string, LineValueRefs>& pair) { return pair.first; });

	// Loop through data and print it out
	for (auto& subCat : subCats)
	{
		for (auto& item : lineValueMap.find(subCat)->second)
		{
			switch (std::get<0>(IncomeOrExpense::enumData[idxIncomeOrExpense]))
			{
			case IncomeOrExpense::Income:
				subCatTotal += item.get().paidIn; // Add the paidIn value to the sub-category total
				itemVal = item.get().paidIn;
				break;
			case IncomeOrExpense::Expense:
				subCatTotal += item.get().paidOut; // Add the paidOut value to the sub-category total
				itemVal = item.get().paidOut;
				break;
			default:
				break;
			}

			// Collect the item strings if needed
			if (dispType == 2)
			{
				items.emplace_back(std::tuple<std::string, double>(item.get().description, itemVal));
			}

		}

		scLines = splitStrIntoStringsFromWidth(subCat, width3);

		for (size_t i = 0; i < scLines.size(); ++i)
		{
			std::cout << indent1 << indent1 << indent1
				<< std::left << std::setw(width1) << " "
				<< std::setw(width2) << " "
				<< std::setw(width3) << scLines[i];
			if (i == scLines.size() - 1) {
				std::cout << std::setw(width4) << " " << " | " << currSym_sv << TWODP(subCatTotal);
			}
			std::cout << std::endl;
		}

		if (dispType == 2) // Display the individual line items
		{
			std::vector<std::string> itemLines;
			for (auto& item : items)
			{
				itemLines = splitStrIntoStringsFromWidth(std::get<0>(item), width4);
				for (size_t i = 0; i < itemLines.size(); ++i)
				{
					std::cout << indent1 << indent1 << indent1
						<< std::left << std::setw(width1) << " "
						<< std::setw(width2) << " "
						<< std::setw(width3) << " "
						<< std::setw(width4) << itemLines[i];
					if (i == itemLines.size() - 1) {
						std::cout << " | " << currSym_sv << TWODP(std::get<1>(item));
					}
					std::cout << std::endl;
				}
			}
		}

		scLines.clear(); // Clear the lines vector for the next sub-category
		items.clear(); // Clear the items vector for the next sub-category
		subCatTotal = 0.0; // Reset sub-category total for next loop
		idxSubCat += 1; // Increment sub-category index
	}
}