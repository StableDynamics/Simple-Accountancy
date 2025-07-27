
#include "BankStatement.h"

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

/**
 * Prints a high level summary of the contents of the bank statement including
 * bankName, monthly total income expenses arranged in years, and the averages
 * from the period.
 * Functinality varies by OS due to needing to convert UTF8 strings
 */
void BankStatement::printStatementSummary(int strLen) const{
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
void BankStatement::printPerMonthDetails(int dispType, int strLen) const{
	if (strLen > 2) throw std::runtime_error("BankStatement::printStatementSummary(int strLen) called with wrong value. "
		"Acceptable values are 0 for 3Len strings, 1 for long strings, and 2 for number strings.");
	if (dispType > 2) throw std::runtime_error("BankStatement::printPerMonthDetails(int dispType) called with wrong value. "
		"Acceptable values are 0 for 3Len strings, 1 for long strings, and 2 for number strings.");

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
	int width3{ 15 }; // padding size
	int width4{ 15 }; // padding size
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
								std::cout << indent1 << indent1 << indent1 << std::left << std::setw(width1) << " " << std::setw(width2) << cat.str() << std::setw(width3) << " " << std::setw(width4) << " " << currSym_sv << TWODP(itemType) << std::endl;
								switch (dispType)
								{
								case 0: // Top level categories only
									// No further processing needed, just print the category and value
									break;
								case 1: // Top level categories, sub-categories, and individual line items
								case 2: // Top level categories and individual line items
									break;
								default:
									// Shouldn't be in here, throw error
									std::stringstream errMsg;
									errMsg << "BankStatement::printPerMonthDetails(int dispType, int strLen): Unrecognised ItemType Index of " << idxItemType;
									std::string err = errMsg.str();
									throw std::runtime_error(err);
								}
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