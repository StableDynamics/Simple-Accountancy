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

#include "HelpfulFunctions.h"
#include "LineValue.h"
#include "BankName.h"
#include "Month.h"

/**
 * This is the class that holds the processed data for the bank statement from the
 * csv file
 */
class BankStatement
{

public:
	BankStatement(std::string fname);
	virtual ~BankStatement();
	void printSummary();

private:
	BankName bankName;
	std::vector<LineValue> expenses;
	std::string accountingPeriod;
	double avgIncome;
	double avgExpenditure;

	void determineAccountingPeriod();
	void calculateAvgIncome();
	void calculateAvgExpenditure();

};
#endif // !defined(BANKSTATEMENT)
