///////////////////////////////////////////////////////////
//  LineValue.h
//  Implementation of the Class LineValue
//  Created on:      03-Mar-2025 15:20:29
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(LINEVALUE)
#define LINEVALUE

#include <array>
#include <string>
#include <vector>

#include "Currencies.h"
#include "IncomeOrExpense.h"
#include "ItemType.h"
#include "Month.h"

/**
 * This struct contains the data from each line of the csv, wondering if this should be a class instead...
 * { 0, Month::January, 0, "", "", Currency::GBP, 0, 0, 0, IncomeOrExpense::Expense, ItemType::Bills }
 */
struct LineValue
{

	int year{ 0 };												// Year of the transaction
	Month::Month month{ Month::maxMonths };						// Month of the transaction
	int day{ 0 };												// Day of the transaction
	std::string transactType{};									// Type of transaction
	std::string description{};									// Description of the transaction
	Currency::Currency currency{ Currency::maxCurrencies };		// Currency of the transaction
	double paidIn{ 0.0 };										// Amount paid in
	double paidOut{ 0.0 };										// Amount paid out
	double balance{ 0.0 };										// Balance after transaction
	IncomeOrExpense::IncomeOrExpense incomeOrExpense
	{ IncomeOrExpense::maxIncomeOrExpense };					// Is it an income or an expense
	ItemType::ItemType itemType{ ItemType::maxItemTypes };		// What type of item is it?
	std::string catResult{};									// Contains the categorisation result - exact, partial, or no match
	std::array<int, static_cast<int>(ItemType::maxItemTypes)> 
		catResultTally{};										// Contains the categorisation results
	std::string subType{};										// User defined sub-type
	std::vector<std::string> subTypeVals{};						// Vector of the sub-type results

	std::string lineValueSummary(int threeOrOtherMonth, 
		int threeOrOtherCurrency) const;						// Prints summary of this LineValue

};
#endif // !defined(LINEVALUE)
