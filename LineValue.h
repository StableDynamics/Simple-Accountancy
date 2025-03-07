///////////////////////////////////////////////////////////
//  LineValue.h
//  Implementation of the Class LineValue
//  Created on:      03-Mar-2025 15:20:29
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(LINEVALUE)
#define LINEVALUE

#include <string>
#include <string_view>

#include "Month.h"
#include "IncomeOrExpense.h"
#include "ItemType.h"
#include "Currency.h"

/**
 * This struct contains the data from each line of the csv, wondering if this should be a class instead...
 */
struct LineValue
{

	int year;												// Year of the transaction
	Month::Month month;										// Month of the transaction
	int day;												// Day of the transaction
	std::string description;								// Description of the transaction
	std::string_view description_ptr;						// Pointer to the description
	Currency::Currency currency;							// Currency of the transaction
	double paidIn;											// Amount paid in
	double paidOut;											// Amount paid out
	double balance;											// Balance after transaction
	IncomeOrExpense::IncomeOrExpense incomeOrExpense;		// Is it an income or an expense
	ItemType::ItemType itemType;							// What type of item is it?

};
#endif // !defined(LINEVALUE)
