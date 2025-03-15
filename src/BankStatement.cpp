///////////////////////////////////////////////////////////
//  BankStatement.cpp
//  Implementation of the Class BankStatement
//  Created on:      04-Mar-2025 14:33:13
//  Original author: matth
///////////////////////////////////////////////////////////

#include "BankStatement.h"

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
void BankStatement::printSummary(){

}

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Private functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * Calculates the averages per month
 */
void BankStatement::calculateAvg(){
	const std::vector<size_t> vectorSizes = getYearMonthAmounts();

	// loop through the monthlyTotals and calculate the average income
	int totalMonths{ 0 };


	const std::vector<std::vector<std::array<std::array<std::array<double, static_cast<int>(ItemType::maxItemTypes) + 1>,
		static_cast<int>(IncomeOrExpense::maxIncomeOrExpense)>, static_cast<int>(Currency::maxCurrencies)>>> monthlyTotals =  getMonthlyTotals();

	for (auto year : monthlyTotals)
		for (auto month : year) {
			totalMonths += 1;
			for (auto currency : month)
				for (size_t i = 0; i < currency.size(); i++) // Income or expense?
				{
					for (size_t j = 0; j < currency[i].size(); j++) // Item type
					{
						avgByType[i][j] += currency[i][j];
					}
				}
		}
	
	// Calculate Averages
	for (auto& itemTypes : avgByType)
		for (auto& item : itemTypes)
			item = item / static_cast<double>(totalMonths);
}