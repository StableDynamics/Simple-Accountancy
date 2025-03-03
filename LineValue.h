///////////////////////////////////////////////////////////
//  LineValue.h
//  Implementation of the Class LineValue
//  Created on:      03-Mar-2025 15:20:29
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(LINEVALUE)
#define LINEVALUE

#include "Month.h"
#include "IncomeOrExpense.h"
#include "ItemType.h"

/**
 * This struct contains the data from each line of the csv
 */
struct LineValue
{

private:
	int year;
	Month month;
	int day;
	double paidIn;
	double paidOut;
	double balance;
	IncomeOrExpense incomeOrExpense;
	ItemType itemType;

};
#endif // !defined(LINEVALUE)
