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

#include "LineValue.h"

/**
 * This is the class that holds the processed data for the bank statement from the
 * csv file
 */
class BankStatement
{

public:
	BankStatement();
	virtual ~BankStatement();
	void printSummary();

private:
	std::string bankName;
	std::vector<LineValue> expenses;
	std::string accountingPeriod;
	double avgIncome;
	double avgExpenditure;

	void determineAccountingPeriod();
	void calculateAvgIncome();
	void calculateAvgExpenditure();

};
#endif // !defined(BANKSTATEMENT)
