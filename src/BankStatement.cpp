///////////////////////////////////////////////////////////
//  BankStatement.cpp
//  Implementation of the Class BankStatement
//  Created on:      04-Mar-2025 14:33:13
//  Original author: matth
///////////////////////////////////////////////////////////

#include "BankStatement.h"

#include <vector>
#include <string_view>

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Public functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BankStatement::BankStatement(){
}

BankStatement::BankStatement(const std::string& fname) : MonthlyTotals::MonthlyTotals(fname){
	calculateAvg();
}


BankStatement::~BankStatement(){

}


/**
 * Prints a high level summary of the contents of the bank statement including
 * bankName, monthly total income expenses arranged in years, and the averages
 * from the period
 */
void BankStatement::printStatementSummary(int strLen){
	// Input determines the length of strings used in account period
	// 0 (default) = 3Len strings
	// 1 = long strings
	// 2 = number strings
	if (strLen > 2) throw std::runtime_error("BankStatement::printStatementSummary(int strLen) called with wrong value. "
		"Acceptable values are 0 for 3Len strings, 1 for long strings, and 2 for number strings.");

	std::cout << "########### " << this->getBankName() << " ###########" << std::endl << std::endl;

	std::cout << "Accounting Period: " << (this->getAccountingPeriod()).getDescriptionString_sv(strLen) << std::endl << std::endl;

	// Setup config variables
	int width1{ 17 }; // padding size
	int width2{ 25 }; // padding size
	int curr{ 0 };
	size_t avgEndIdx = static_cast<size_t>(avgByType[0][0].size() - 1);

	// By currency
	//for (size_t i = 0; i < avgByType.size(); i++)
	//{
	//	if (!(avgByType[i][0][avgEndIdx] <= 0.00001 && avgByType[i][0][avgEndIdx] >= -0.00001) && !(avgByType[i][1][avgEndIdx] <= 0.00001 && avgByType[i][1][avgEndIdx] >= -0.00001)) // Making sure there is an income/expense per currency
	//	{
	//		std::cout << "### " << enumToString(static_cast<Currency::Currency>(i), "3Len") << " / " << enumToString(static_cast<Currency::Currency>(i), "Other") << " ###" <<
	//			"INCOME" << std::endl <<
	//			std::left << "|" << std::setw(width1) << "Type" << "|" << std::setw(width2) << "Average Value over Period" << "|" << std::endl <<
	//			std::left << "|" << std::setw(width1) << std::string(width1 - 2, '#') << "|" << std::setw(width2) << std::string(width2 - 2, '#') << "|" << std::endl;
	//		for (auto& iOrE : avgByType[i])
	//		{
	//			//std::cout << std::
	//		}
	//	}				
	//}
	

	
	// Depending on OS display a summary of the contents
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8); // Set console to UTF 8 on Windows
	setvbuf(stdout, nullptr, _IOFBF, 1000); // Changing buffer to stop VS from cutting up multi-byte characters
	std::vector<std::string> testVec = { "£" };
	std::string test = std::string(testVec[0]);
	char* str = test.data();
	std::cout << str << std::endl;
	/*SetConsoleOutputCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IONBF, 0);
	MBuf buf;*/
	//std::cout.rdbuf(&buf);
	std::cout << reinterpret_cast<const char *>(u8"Greek: αβγδ\n") << std::endl; // This works, now how to do it with an std::string?


	// set mode to allow utf16 so that it will print consistent unicode symbols
	//if (_setmode(_fileno(stdout), _O_U16TEXT) == -1) {
	//	throw std::runtime_error("Failed to set mode to UTF-16");
	//}
	//std::wcout << L"Hello, \u0444!\n";

	///*char tmpChar = '\u0444';

	//std::string s1{ "\u20AC1.00" };
	//std::u8string s2{ u8"\u20AC1.00" };*/
	//std::wstring s3{ L"\u00A31.00" };
	//const char temp[] = "\u00A31.00";
	//std::wstring s4{ std::begin(temp), std::end(temp) };
	//std::vector<std::wstring_view> wCurr{L"£",
	//	L"€",
	//	L"$"};
	//std::string str = std::string(Currency::currencyStringsOther[0]);
	//size_t strSz = str.size();
	//wchar_t wszBuf[512];
	//MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size() + 1, wszBuf, _countof(wszBuf)); // CP_ACP is not the best but CP_UTF8 fails for some reason

	///*std::cout << s1 << std::endl;
	//std::cout << reinterpret_cast<const char*>(s2.c_str());*/
	//std::wcout << s3 << std::endl;
	//std::wcout << s4 << std::endl;
	//std::wcout << L"£" << std::endl;
	//std::wcout << wCurr[0] << std::endl;
	//std::wcout << wszBuf << std::endl;
	////std::wcout << Currency::currencyStringsOther[0] << std::endl;

	///*std::cout << enumToString(Currency::GBP, "Other") << std::endl <<
	//	Currency::currencyStringsOther[0] << std::endl <<
	//	"£" << std::endl <<
	//	std::string("£") << std::endl <<
	//	(char)156 << std::endl <<
	//	(char)'\u0444' << std::endl <<
	//	tmpChar << std::endl << std::endl;*/

	//for (auto& currency : avgByType)
	//{
	//	if (!(currency[0][avgEndIdx] <= 0.00001 && currency[0][avgEndIdx] >= -0.00001) && !(currency[1][avgEndIdx] <= 0.00001 && currency[1][avgEndIdx] >= -0.00001)) // Making sure there is an income/expense per currency
	//	{
	//		std::cout << "### " << enumToString(static_cast<Currency::Currency>(curr), "3Len") << " / " << enumToString(static_cast<Currency::Currency>(curr), "Other") << " ###" << std::endl <<
	//			"INCOME" << std::endl <<
	//			std::left << "|" << std::setw(width1) << "Type" << "|" << std::setw(width2) << "Average Value over Period" << "|" << std::endl <<
	//			"|" << std::setw(width1) << std::string(width1 - 2, '#') << "|" << std::setw(width2) << std::string(width2 - 2, '#') << "|" << std::endl;
	//		for (auto& iOrE : currency)
	//		{
	//			//std::cout << std::
	//		}
	//	}
	//	curr += 1;
	//}

	//std::cout <<
	//	std::left << "|" << std::setw(width1) << "Type" << "|" << std::setw(width2) << "Average Value over Period" << "|" << std::endl <<
	//	std::left << "|" << std::setw(width1) << "Income" << "|" << std::right << std::setw(width2) << enumToString(;// << avgByType[0][avgEndIdx] << "|" << std::endl;
#endif
	
}

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Private functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * Calculates the averages per month
 */
void BankStatement::calculateAvg(){
	// loop through the monthlyTotals and calculate the average income
	int totalMonths{ 0 };


	const std::vector<std::vector<std::array<std::array<std::array<double, static_cast<int>(ItemType::maxItemTypes) + 1>,
		static_cast<int>(IncomeOrExpense::maxIncomeOrExpense)>, static_cast<int>(Currency::maxCurrencies)>>> monthlyTotals =  getMonthlyTotals();

	for (auto& year : monthlyTotals)
		for (auto& month : year) {
			totalMonths += 1;
			for (size_t i = 0; i < month.size(); i++)
				for (size_t j = 0; j < month[i].size(); j++) // Income or expense?
				{
					for (size_t k = 0; k < month[i][j].size(); k++) // Item type
					{
						avgByType[i][j][k] += month[i][j][k];
					}
				}
		}
	
	// Calculate Averages
	for (auto& currency : avgByType)
		for (auto& itemTypes : currency)
			for (auto& item : itemTypes)
				item = item / static_cast<double>(totalMonths);
}