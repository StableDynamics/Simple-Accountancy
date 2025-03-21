#pragma warning(disable : 4091) // Windows.h contains a typedef for a struct called CURRENCY within the oaidl.h file which conflicts with the enum CURRENCY and its macro and it throws a C4091 warning

#include "BankStatement.h"

#include <iostream>
#include <iomanip>
#include <sstream>

#include "HelpfulFunctions.h"
#include "OutputFormatting.h"

#ifdef _WIN32
#include <Windows.h>
#include <string_view>
#include "TextConversion.h"
#endif

/**
 * Prints a high level summary of the contents of the bank statement including
 * bankName, monthly total income expenses arranged in years, and the averages
 * from the period.
 * Functinality varies by OS due to needing to convert UTF8 strings
 */
void BankStatement::printStatementSummary(int strLen) {
	// Input determines the length of strings used in account period
	// 0 (default) = 3Len strings
	// 1 = long strings
	// 2 = number strings
	if (strLen > 2) throw std::runtime_error("BankStatement::printStatementSummary(int strLen) called with wrong value. "
		"Acceptable values are 0 for 3Len strings, 1 for long strings, and 2 for number strings.");

	std::cout << "############### " << this->getBankName() << " ###############" << std::endl << std::endl;

	std::cout << "Accounting Period: " << (this->getAccountingPeriod()).getDescriptionString_sv(strLen) << std::endl << std::endl;

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
		if (!(currency[0][avgEndIdx] <= 0.00001 && currency[0][avgEndIdx] >= -0.00001) && !(currency[1][avgEndIdx] <= 0.00001 && currency[1][avgEndIdx] >= -0.00001)) // Making sure there is an income/expense per currency
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
					std::cout << "INCOME" << std::endl << std::endl;
					std::cout << tableHeader.str();
					break;
				case IncomeOrExpense::Expense:
					std::cout << "Expense" << std::endl << std::endl;
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
					val.str(std::string()); // Clear it
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
			std::cout << "Average Monthly Income vs Expenditure " << currSym_sv << ": ";
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
}