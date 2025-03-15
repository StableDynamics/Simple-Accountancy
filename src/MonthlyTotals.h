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
#include "BankFileImporter.h"

/*
* This class inherits the data from BankFileImporter and then processes the data to work out totals and averages per month per year
*/
class MonthlyTotals : public BankFileImporter
{

public:
	MonthlyTotals();
	MonthlyTotals(const std::string& fname);
	virtual ~MonthlyTotals();
	MonthlyTotals(const MonthlyTotals& other) = default; // Copy constructor
	MonthlyTotals(MonthlyTotals&& other) noexcept; // Move constructor

	const std::vector<std::vector<std::array<std::array<std::array<std::vector<std::reference_wrapper<const LineValue>>,
		static_cast<int>(ItemType::maxItemTypes) + 1>, static_cast<int>(IncomeOrExpense::maxIncomeOrExpense)>,
		static_cast<int>(Currency::maxCurrencies)>>> getProcessedStatement() const;

	const std::vector<std::vector<std::array<std::array<std::array<double, static_cast<int>(ItemType::maxItemTypes) + 1>,
		static_cast<int>(IncomeOrExpense::maxIncomeOrExpense)>, static_cast<int>(Currency::maxCurrencies)>>>& getMonthlyTotals() const;

	const std::vector<std::vector<std::array<std::array<std::array<uint64_t, static_cast<int>(ItemType::maxItemTypes) + 1>,
		static_cast<int>(IncomeOrExpense::maxIncomeOrExpense)>, static_cast<int>(Currency::maxCurrencies)>>>& getMonthlyOccurances() const;

	const std::vector<std::vector<std::array<std::array<std::array<double, static_cast<int>(ItemType::maxItemTypes) + 1>,
		static_cast<int>(IncomeOrExpense::maxIncomeOrExpense)>, static_cast<int>(Currency::maxCurrencies)>>>& getmonthlyAvgSnglTrnsct() const;

	const std::vector<size_t> getYearMonthAmounts();

	// Overloaded operators
	MonthlyTotals& operator=(MonthlyTotals other);

	// Friend functions
	friend void swap(MonthlyTotals& first, MonthlyTotals& second);

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
					static_cast<int>(Currency::maxCurrencies)>>> monthlyAvgSnglTrnsct = { {{{{}}}} }; // Average singular transaction per type


	void processStatement(const std::vector<std::reference_wrapper<LineValue>> expenses, int newOrRefresh = 0);
	size_t returnTotalIndex();
	void determineItemType(const LineValue& expense, const size_t monthIdx, const size_t yearIdx, int newOrRefresh = 0);
	void checkArrays(const std::vector<std::reference_wrapper<LineValue>> expenses);
	void calculateAverages();
	virtual void refreshRefs();

};
#endif // !defined(MONTHLYTOTALS)
