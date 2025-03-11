///////////////////////////////////////////////////////////
//  MonthlyTotals.h
//  Implementation of the Class MonthlyTotals
//  Created on:      10-Mar-2025 12:42:47
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(MONTHLYTOTALS)
#define MONTHLYTOTALS

#include <vector>
#include <numeric>
#include <array>
#include <functional>

#include "Month.h"
#include "itemType.h"
#include "LineValue.h"
#include "IncomeOrExpense.h"
#include "HelpfulFunctions.h"

class MonthlyTotals
{

public:
	MonthlyTotals();
	MonthlyTotals(const std::vector<LineValue>& expenses);
	virtual ~MonthlyTotals();

private:
	std::vector<int> yearsContained{ 0 };
	std::vector<std::vector<Month::Month>> monthsContained = { {} };
	// Arrangement of processedStatement, monthlyTotals, monthlyOccurances and monthlyAverages
	// year.month.currency.incomeOrExpense.type
	// Type explained below:
	// 0 - maxItemTypes = totals according to ItemType enum
	// end = Totals
	std::vector<
		std::vector<
			std::array<
				std::array<
					std::array<std::vector<std::reference_wrapper<const LineValue>>, static_cast<int>(ItemType::maxItemTypes) + 1>,
					static_cast<int>(IncomeOrExpense::maxIncomeOrExpense)>,
		static_cast<int>(Currency::maxCurrencies)>>> processedStatement = { {{{{{}}}}} }; // Processed LineValues into their categories
	std::vector<
		std::vector<
			std::array<
				std::array<
					std::array<double, static_cast<int>(ItemType::maxItemTypes) + 1>,
					static_cast<int>(IncomeOrExpense::maxIncomeOrExpense)>,
					static_cast<int>(Currency::maxCurrencies)>>> monthlyTotals = { {{{{}}}} }; // Total per type
	std::vector<
		std::vector<
			std::array<
				std::array<
					std::array<uint64_t, static_cast<int>(ItemType::maxItemTypes) + 1>,
					static_cast<int>(IncomeOrExpense::maxIncomeOrExpense)>,
					static_cast<int>(Currency::maxCurrencies)>>> monthlyOccurances = { {{{{}}}} }; // Times each type occurs
	std::vector<
		std::vector<
			std::array<
				std::array<
					std::array<double, static_cast<int>(ItemType::maxItemTypes) + 1>,
					static_cast<int>(IncomeOrExpense::maxIncomeOrExpense)>,
					static_cast<int>(Currency::maxCurrencies)>>> monthlyAverages = { {{{{}}}} }; // Average per type


	size_t returnTotalIndex();
	void determineItemType(const LineValue& expense, const size_t monthIdx, const size_t yearIdx);
	void checkArrays(const std::vector<LineValue>& expenses);
	void calculateAverages();

};
#endif // !defined(MONTHLYTOTALS)
