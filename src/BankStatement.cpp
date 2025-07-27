///////////////////////////////////////////////////////////
//  BankStatement.cpp
//  Implementation of the Class BankStatement
//  Created on:      04-Mar-2025 14:33:13
//  Original author: matth
///////////////////////////////////////////////////////////

#include "BankStatement.h"

#include <stdexcept>
#include <iostream>
#include "IncomeOrExpense.h"

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


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Private functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * Calculates the averages per month
 */
void BankStatement::calculateAvg(){
	// loop through the monthlyTotals and calculate the average income
	int totalMonths{ 0 };


	const YrMtCrIEITTotal monthlyTotals =  getMonthlyTotals();

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

	// Calculate average Income vs Expenditure
	size_t curr{ 0 };
	for (auto& total : avgIncVsExp)
	{
		total = avgByType[curr][static_cast<size_t>(IncomeOrExpense::Income)].back() - avgByType[curr][static_cast<size_t>(IncomeOrExpense::Expense)].back();
		curr += 1;
	}
}

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
void BankStatement::printPerriodEnd(int strLen, std::string printDesc ) const {
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