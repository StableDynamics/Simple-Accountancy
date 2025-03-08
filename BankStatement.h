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
#include <valarray>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <iterator>

#include "AccountingPeriod.h"

#include "HelpfulFunctions.h"
#include "LineValue.h"
#include "BankName.h"
#include "Month.h"
#include "Currency.h"
#include "IncomeOrExpense.h"
#include "ItemType.h"
#include "ItemTypeDiscriminator.h"

class AccountingPeriod; // Breaks circular includes

/**
 * This is the class that holds the processed data for the bank statement from the
 * csv file
 */
class BankStatement
{

public:
	BankStatement();
	BankStatement(std::string& fname);
	virtual ~BankStatement();
	// Maybe add copy constructor and assignment operator here?
	void printSummary();

private:
	BankName::BankName bankName{ BankName::maxBanks };
	std::vector<LineValue> expenses;
	AccountingPeriod accountingPeriod;
	double avgIncomeOverPeriod{ 0.0 };
	double avgExpenditureOverPeriod{ 0.0 };

	void processRawData(const std::vector<std::vector<std::string>>& content, const std::string& fname);
	void makeSureDataIsAscending();
	void calculateAvgIncome();
	void calculateAvgExpenditure();

};
#endif // !defined(BANKSTATEMENT)
