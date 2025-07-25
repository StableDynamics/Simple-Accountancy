///////////////////////////////////////////////////////////
//  MonthlyTotals.h
//  Implementation of the Class MonthlyTotals
//  Created on:      10-Mar-2025 12:42:47
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(MONTHLYTOTALS)
#define MONTHLYTOTALS

#include <array>
#include <string>
#include <vector>

#include "BankFileImporter.h"
#include "ForwardDecls.h"
#include "Month.h"

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

	const ProcessedStatement getProcessedStatement() const;

	const YrMtCrIEITTotal& getMonthlyTotals() const;

	const YrMtCrIEITOcc& getMonthlyOccurances() const;

	const YrMtCrIEITAvg& getmonthlyAvgSnglTrnsct() const;

	const std::array<int, 2> getYearMonthAmounts();

	const std::vector<int>& getYearsContained() const;

	const std::vector<std::vector<Month::Month>>& getMonthsContained() const;

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
	ProcessedStatement processedStatement = { {{{{{}}}}} };		// Processed LineValues into their categories
	YrMtCrIEITTotal monthlyTotals = { {{{{}}}} };				// Total per type
	YrMtCrIEITOcc monthlyOccurances = { {{{{}}}} };				// Times each type occurs
	YrMtCrIEITAvg monthlyAvgSnglTrnsct = { {{{{}}}} };			// Average singular transaction per type


	void processStatement(const LineValueRefs expenses, int newOrRefresh = 0);
	size_t returnTotalIndex();
	void determineItemType(const LineValue& expense, const size_t monthIdx, const size_t yearIdx, int newOrRefresh = 0);
	void checkArrays(const LineValueRefs expenses);
	void calculateAverages();
	virtual void refreshRefs();

};
#endif // !defined(MONTHLYTOTALS)
