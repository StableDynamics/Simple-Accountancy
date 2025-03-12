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
	// Maybe add copy constructor and assignment operator here?
	void printSummary();

private:
	double avgIncomeOverPeriod{ 0.0 };
	double avgExpenditureOverPeriod{ 0.0 };

	void calculateAvgIncome();
	void calculateAvgExpenditure();

};
#endif // !defined(BANKSTATEMENT)
