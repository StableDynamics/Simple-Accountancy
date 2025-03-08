
#include <iostream>
#include <string>
#include "BankStatement.h"
#include "HelpfulFunctions.h"
#include "ItemType.h"
#include "IncomeOrExpense.h"

int main(int argc, char* argv[])
{
    // Program takes in the filename at launch in the format of "path\filename.csv"
    // Would be good to replace this with a file search if an argument has not been sipplied
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
	
	// Create vector of bank statements
	std::vector<BankStatement> statements;

    // Loop through all the files that were supplied
    for (size_t i = 1; i < argc; i++)
    {
        std::string fname{ argv[i] };

        // Create AccountData class object for supplied file
        try
        {
            BankStatement statement(fname);

            std::cout << "Created class from " << fname << "\n\n";

			statements.push_back(statement);
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
