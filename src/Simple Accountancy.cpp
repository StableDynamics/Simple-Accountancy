
#include <iostream>
#include <string>
#include "BankStatement.h"
#include "HelpfulFunctions.h"
#include "ItemType.h"
#include "IncomeOrExpense.h"
#include "BankFileImporter.h"
#include "MonthlyTotals.h"

//#include <Windows.h>

//inline std::ostream& operator<<(std::ostream& os, const char8_t* str) {
//    return os << reinterpret_cast<const char*>(str);
//}

int main(int argc, char* argv[])
{
    //SetConsoleOutputCP(CP_UTF8); // Set console output to UTF-8 on Windows
    //SetConsoleCP(CP_UTF8); // Set console itself to UTF-8
    ////std::locale::global(std::locale("en_GB.UTF-8")); // Set locale globally to UTF-8

    //std::string str = "£";
    //std::vector<std::string> strVec = { str };
    //const char8_t* u8t = u8"£";
    //std::u8string u8String{ u8"£" };
    //std::vector<std::u8string> u8Vec = { u8String };
    //std::string u8Conv = fromu8String(u8String);
    //std::string u8VecConv = fromu8String(u8Vec[0]);
    //std::cout << str << std::endl;          // Doesn't work
    //std::cout << strVec[0] << std::endl;    // Doesn't work
    ////std::cout << u8t << std::endl;          // Does work - only works with overloaded operator<<
    //std::cout << u8Conv << std::endl;       // Does work, even without locale, might changed based on users OS settings
    //std::cout << u8VecConv << std::endl;    // Does work, even without locale, might changed based on users OS settings
    ////std::cout << u8"£" << std::endl;        // Does work - only works with overloaded operator<<
    //std::cout << "Â£" << std::endl;         // Does work, even without locale, might changed based on users OS settings


    // Program takes in the filename at launch in the format of "path\filename.csv"
    // Would be good to replace this with a file search if an argument has not been sipplied
    // Longer term would be to replace all of this with a GUI that allowed users to tailer analyses and compare results....
    // Error check inputs
    if (argc < 2)
    {
        std::cerr << "Program has not been supplied enough arguments. Have you given it the location"
            " of a file?" << std::endl;
        return -1;
    }

    // Error check enums - more of a development thing...
    try
    {
        enumErrorCheck<Month::Month>(Month::monthStrings3Len, Month::monthStringsOther, Month::maxMonths);
        enumErrorCheck<Currency::Currency>(Currency::currencyStrings3Len, Currency::currencyStringsOther, Currency::maxCurrencies);
		enumErrorCheck<IncomeOrExpense::IncomeOrExpense>(IncomeOrExpense::incomeOrExpenseStrings3Len, IncomeOrExpense::incomeOrExpenseStringsOther, IncomeOrExpense::maxIncomeOrExpense);
		enumErrorCheck<ItemType::ItemType>(ItemType::itemTypeStrings3Len, ItemType::itemTypeStringsOther, ItemType::maxItemTypes);
		enumErrorCheck<BankName::BankName>(BankName::bankNameStrings3Len, BankName::bankNameStringsOther, BankName::maxBanks);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }
	
	// Create vectors of class objects
    std::vector<BankFileImporter> bankFileImportersVec;
    std::vector<MonthlyTotals> monthlyTotalsVec;
	std::vector<BankStatement> bankStatementsVec;

    BankStatement temp;

    // Loop through all the files that were supplied
    for (size_t i = 1; i < argc; i++)
    {
        std::string fname{ argv[i] };

        // Create class objects for supplied file
        try
        {
            temp = BankStatement(fname);
            temp.printStatementSummary();

            bankStatementsVec.push_back(temp);
            
            bankFileImportersVec.emplace_back(fname);
            monthlyTotalsVec.emplace_back(fname);
			bankStatementsVec.emplace_back(fname);

            std::cout << "Created class from " << fname << "\n\n";
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            return -1;
        }
    }

	std::cout << "Finished processing all files\n\n";

	return 0;
}
