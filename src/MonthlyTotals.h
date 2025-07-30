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

	// Getters
	const ProcessedStatement getProcessedStatement() const { return processedStatement; };

	const YrMtCrIEITTotal& getMonthlyTotals() const { return monthlyTotals; };

	const YrMtCrIEITOcc& getMonthlyOccurances() const { return monthlyOccurances; };

	const YrMtCrIEITAvg& getmonthlyAvgSnglTrnsct() const { return monthlyAvgSnglTrnsct; };

	const std::array<int, 2> getYearMonthAmounts() const;

	const std::vector<int>& getYearsContained() const { return yearsContained; };

	const std::vector<std::vector<Month::Month>>& getMonthsContained() const { return monthsContained; };

	// Experimental Database Alternative Start
	const StatementDatabase& getStatementDatabase() const { return statementDatabase; }; // Getter for the statement database

	const LineValueRefs& getLineValuesFromDatabase(int year, Month::Month month, Currency::Currency currency, IncomeOrExpense::IncomeOrExpense incomeOrExpense,
		ItemType::ItemType itemType, const std::string& subType) const;

	const std::map<std::string, LineValueRefs>& getLineValuesFromDatabase(int year, Month::Month month, Currency::Currency currency, IncomeOrExpense::IncomeOrExpense incomeOrExpense,
		ItemType::ItemType itemType) const;
	// Experimental Database Alternative End

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

	// Experimental Database Alternative Start
	StatementDatabase statementDatabase; // Database of LineValue objects arranged by Year, Month, Currency, Income/Expense, ItemType, and then Item Sub-Type
	void processStatementDatabase(const LineValueRefs expenses);
	// Experimental Database Alternative End

	void processStatement(const LineValueRefs expenses, int newOrRefresh = 0);
	size_t returnTotalIndex();
	void determineItemType(const LineValue& expense, const size_t monthIdx, const size_t yearIdx, int newOrRefresh = 0);
	void checkArrays(const LineValueRefs expenses);
	void calculateAverages();
	virtual void refreshRefs();

};
#endif // !defined(MONTHLYTOTALS)
