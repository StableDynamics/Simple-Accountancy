///////////////////////////////////////////////////////////
//  LineValue.h
//  Implementation of the Class LineValue
//  Created on:      03-Mar-2025 15:20:29
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(LINEVALUE)
#define LINEVALUE

#include <string>

#include "Month.h"
#include "IncomeOrExpense.h"
#include "ItemType.h"
#include "Currency.h"

/**
 * This struct contains the data from each line of the csv
 */
struct LineValue
{

	int year;
	Month::Month month;
	int day;
	std::string description;
	Currency::Currency currency;
	double paidIn;
	double paidOut;
	double balance;
	IncomeOrExpense::IncomeOrExpense incomeOrExpense;
	ItemType::ItemType itemType;

};
#endif // !defined(LINEVALUE)
