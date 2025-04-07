///////////////////////////////////////////////////////////
//  BankStatement.h
//  Implementation of the Class BankStatement
//  Created on:      04-Mar-2025 14:33:13
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(BANKSTATEMENT)
#define BANKSTATEMENT

#include <array>
#include <string>

#include "MonthlyTotals.h"

#include "Currencies.h"
#include "IncomeOrExpense.h"
#include "ItemType.h"

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
	void printStatementSummary(int strLen = 0); // Held in BankStatement_WindowsStuff due to the need to convince windows to use UTF8

private:
	// Stores monthly averages arranged by currency, and then income or expense, and then individual array values are ItemTypes
	// currency.incomeOrExpense.type
	// Type explained below:
	// 0 - maxItemTypes = totals according to ItemType enum
	// end = Totals
	std::array<std::array<std::array<double, static_cast<int>(ItemType::maxItemTypes) + 1>, static_cast<int>(IncomeOrExpense::maxIncomeOrExpense)>, static_cast<int>(Currency::maxCurrencies)> avgByType = { {{}} };
	
	// Stores values comparing average monthly income to expenses for each currency 
	std::array<double, static_cast<int>(Currency::maxCurrencies)> avgIncVsExp = {};

	void calculateAvg();

};
#endif // !defined(BANKSTATEMENT)
