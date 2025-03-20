///////////////////////////////////////////////////////////
//  BankStatement.cpp
//  Implementation of the Class BankStatement
//  Created on:      04-Mar-2025 14:33:13
//  Original author: matth
///////////////////////////////////////////////////////////

#include "BankStatement.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <iomanip>

#include "AccountingPeriod.h"
#include "BankFileImporter.h"
#include "HelpfulFunctions.h"
#include "LineValue.h"
#include "BankName.h"
#include "Month.h"
#include "ItemTypeDiscriminator.h"

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