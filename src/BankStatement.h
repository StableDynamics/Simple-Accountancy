///////////////////////////////////////////////////////////
//  BankStatement.h
//  Implementation of the Class BankStatement
//  Created on:      04-Mar-2025 14:33:13
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(BANKSTATEMENT)
#define BANKSTATEMENT

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <iomanip>

#ifdef _WIN32
#include <Windows.h>
#include <cstdio>
#endif


#include "AccountingPeriod.h"
#include "MonthlyTotals.h"
#include "BankFileImporter.h"

#include "HelpfulFunctions.h"
#include "LineValue.h"
#include "BankName.h"
#include "Month.h"
#include "Currency.h"
#include "IncomeOrExpense.h"
#include "ItemType.h"
#include "ItemTypeDiscriminator.h"

/**
 * This class inherits from MonthlyTotals and is meant to contain more advanced 
 * analysis funcitons and display functions
 */
class BankStatement : public MonthlyTotals
{

public:
	BankStatement();
	BankStatement(const std::string& fname);
	virtual ~BankStatement();
	BankStatement(const BankStatement& other) = default; // Copy constructor
	// Maybe add copy constructor and assignment operator here?
	void printStatementSummary(int strLen = 0);

private:
	// Stores monthly averages arranged by currency, and then income or expense, and then individual array values are ItemTypes
	// currency.incomeOrExpense.type
	// Type explained below:
	// 0 - maxItemTypes = totals according to ItemType enum
	// end = Totals
	std::array<std::array<std::array<double, static_cast<int>(ItemType::maxItemTypes) + 1>, static_cast<int>(IncomeOrExpense::maxIncomeOrExpense)>, static_cast<int>(Currency::maxCurrencies)> avgByType = { {{}} };

	void calculateAvg();

};
#endif // !defined(BANKSTATEMENT)
