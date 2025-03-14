///////////////////////////////////////////////////////////
//  MonthlyTotals.cpp
//  Implementation of the Class MonthlyTotals
//  Created on:      10-Mar-2025 12:42:47
//  Original author: matth
///////////////////////////////////////////////////////////

#include "MonthlyTotals.h"

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Public functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MonthlyTotals::MonthlyTotals(){
}


MonthlyTotals::MonthlyTotals(const std::string& fname) : BankFileImporter::BankFileImporter(fname) {
	// Process statement
	const std::vector<std::reference_wrapper<LineValue>> expenses = processStatement();

	// Check array sizes are the same
	checkArrays(expenses);

	// Calculate averages
	calculateAverages();
}

MonthlyTotals::~MonthlyTotals(){

}


/*
* Copy constructor
*/
MonthlyTotals::MonthlyTotals(const MonthlyTotals& other)
	: yearsContained(other.yearsContained),
	monthsContained(other.monthsContained),
	monthlyTotals(other.monthlyTotals),
	monthlyOccurances(other.monthlyOccurances),
	monthlyAverages(other.monthlyAverages)
{
	refreshRefs();
}


/*
* Move constructor
*/
MonthlyTotals::MonthlyTotals(MonthlyTotals&& other) noexcept
	: MonthlyTotals() {
	swap(*this, other);
}


const std::vector<std::vector<std::array<std::array<std::array<std::vector<std::reference_wrapper<const LineValue>>,
	static_cast<int>(ItemType::maxItemTypes) + 1>, static_cast<int>(IncomeOrExpense::maxIncomeOrExpense)>,
	static_cast<int>(Currency::maxCurrencies)>>> MonthlyTotals::getProcessedStatement() const 
{
	return processedStatement;
}

const std::vector<std::vector<std::array<std::array<std::array<double, static_cast<int>(ItemType::maxItemTypes) + 1>,
	static_cast<int>(IncomeOrExpense::maxIncomeOrExpense)>, static_cast<int>(Currency::maxCurrencies)>>>& MonthlyTotals::getMonthlyTotals() const 
{
	return monthlyTotals;
}

const std::vector<std::vector<std::array<std::array<std::array<uint64_t, static_cast<int>(ItemType::maxItemTypes) + 1>,
	static_cast<int>(IncomeOrExpense::maxIncomeOrExpense)>, static_cast<int>(Currency::maxCurrencies)>>>& MonthlyTotals::getMonthlyOccurances() const 
{
	return monthlyOccurances;
}

const std::vector<std::vector<std::array<std::array<std::array<double, static_cast<int>(ItemType::maxItemTypes) + 1>,
	static_cast<int>(IncomeOrExpense::maxIncomeOrExpense)>, static_cast<int>(Currency::maxCurrencies)>>>& MonthlyTotals::getMonthlyAverages() const 
{
	return monthlyAverages;
}

const std::vector<size_t> MonthlyTotals::getYearMonthAmounts() {
	std::vector<size_t> yearMonth;
	for (auto val : monthsContained)
		yearMonth.push_back(static_cast<size_t>(val.size()));
	
	return yearMonth;
}


// Overloaded operators
MonthlyTotals& MonthlyTotals::operator=(MonthlyTotals other) {
	swap(*this, other);

	this->refreshRefs(); // Refresh references

	return *this;
}

// Friend Functions
void swap(MonthlyTotals& first, MonthlyTotals& second) {
	using std::swap; // Allows association to the std::swap function

	swap(static_cast<BankFileImporter&>(first), static_cast<BankFileImporter&>(second)); // Swap base class
	swap(first.yearsContained, second.yearsContained);
	swap(first.monthsContained, second.monthsContained);
	swap(first.monthlyTotals, second.monthlyTotals);
	swap(first.monthlyOccurances, second.monthlyOccurances);
	swap(first.monthlyAverages, second.monthlyAverages);
}


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Private functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Process the statement with a switch to work out if it's everything or just the references that need to be reprocessed
*/
const std::vector<std::reference_wrapper<LineValue>> MonthlyTotals::processStatement(int newOrRefresh) {
	if (newOrRefresh > 1) throw std::runtime_error("MonthlyTotals::processStatement(int newOrRefresh) called with wrong value. "
		"Acceptable values are 0 for new object and 1 for refresh of references.");
	// Function changes based on input newOrRefresh
	// 0 (default value) = new object things need to be assigned from scratch
	// 1 = move/copy of object and reference arrays need to be updated
	
	// Reference indexes
	size_t yearIdx{ 0 };
	size_t monthIdx{ 0 };
	std::vector<std::reference_wrapper<LineValue>> expenses = BankFileImporter::getRawExpRef();

	// Reference blank array
	auto blankProcessedYearArray = processedStatement[0];
	auto blankProcessedMonthArray = processedStatement[0][0];
	auto blankMonthlyTotalsYearArray = monthlyTotals[0];
	auto blankMonthlyOccurancesYearArray = monthlyOccurances[0];
	auto blankMonthlyTotalsMonthArray = monthlyTotals[0][0];
	auto blankMonthlyOccurancesMonthArray = monthlyOccurances[0][0];

	// Assign values from first entry
	yearsContained[0] = expenses[0].get().year;
	monthsContained[0].push_back(expenses[0].get().month);

	// Setup depending on newOrRefresh
	if (newOrRefresh == 0) {
		determineItemType(expenses[0], 0, 0);
	}
	else if (newOrRefresh == 1) {
		// Reset processedStatement
		processedStatement = { {{{{{}}}}} };
		blankProcessedYearArray = processedStatement[0];
		blankProcessedMonthArray = processedStatement[0][0];
		determineItemType(expenses[0], 0, 0, newOrRefresh);
	}

	// Loop through all data assigning valid data as we go
	for (size_t i = 1; i < expenses.size(); i++)
	{
		// Assign year
		auto foundYear = std::find(yearsContained.begin(), yearsContained.end(), expenses[i].get().year);
		if (foundYear == yearsContained.end())
		{
			switch (newOrRefresh)
			{
			case 0: // Runs into case 1 due to processedStatement and index increments applying to both
				yearsContained.push_back(expenses[i].get().year);

				// Create new year in monthly arrays
				monthlyTotals.push_back(blankMonthlyTotalsYearArray);
				monthlyOccurances.push_back(blankMonthlyOccurancesYearArray);
				monthlyAverages.push_back(blankMonthlyTotalsYearArray);
				monthsContained.push_back({ expenses[i].get().month });
				[[fallthrough]];
			case 1:
				processedStatement.push_back(blankProcessedYearArray);

				yearIdx += 1; // Increment Year
				monthIdx = 0; // Restart Month
				break;
			default:
				// Shouldn't get in here due to error check at start
				break;
			}
		}

		// Assign Month
		auto foundMonth = std::find(monthsContained[yearIdx].begin(), monthsContained[yearIdx].end(), expenses[i].get().month);
		if (foundMonth == monthsContained[yearIdx].end())
		{
			switch (newOrRefresh)
			{
			case 0: // Runs into case 1 due to processedStatement and index increments applying to both
				monthsContained[yearIdx].push_back(expenses[i].get().month);
				monthlyTotals[yearIdx].push_back(blankMonthlyTotalsMonthArray);
				monthlyAverages[yearIdx].push_back(blankMonthlyTotalsMonthArray);
				monthlyOccurances[yearIdx].push_back(blankMonthlyOccurancesMonthArray);
				[[fallthrough]];
			case 1:
				processedStatement[yearIdx].push_back(blankProcessedMonthArray);

				monthIdx += 1;
				break;
			default:
				// Shouldn't get in here due to error check at start
				break;
			}
		}

		// Assign values
		determineItemType(expenses[i], monthIdx, yearIdx, newOrRefresh);

		// Calculate Averages
		if (newOrRefresh == 0) calculateAverages();
	}

	return expenses;
}

/*
* As the arrays could change size if more item types are added this function returns an index to the poistion of the Total within
* the monthly arrays
*/
size_t MonthlyTotals::returnTotalIndex() {
	return static_cast<size_t>(monthlyTotals[0][0][0][0].size() - 1);
}

/*
* Determine the Line Item type and assign to the totalsByType array
*/
void MonthlyTotals::determineItemType(const LineValue& expense, const size_t monthIdx, const size_t yearIdx, int newOrRefresh) {
	if (newOrRefresh > 1) {
		std::string errMsg = "MonthlyTotals::determineItemType(const LineValue& expense, const size_t monthIdx, const size_t yearIdx, int newOrRefresh) "
			"called with wrong value. Acceptable values are 0 for new object and 1 for refresh of references.";
		throw std::runtime_error(errMsg);
	}
	// Function changes based on input newOrRefresh
	// 0 (default value) = new object things need to be assigned from scratch
	// 1 = move/copy of object and reference arrays need to be updated
	
	// Pull out indexes
	size_t currencyIdx = static_cast<size_t>(expense.currency);
	size_t iOrEIdx = static_cast<size_t>(expense.incomeOrExpense);
	size_t itemTypeIdx = static_cast<size_t>(expense.itemType);
	size_t totalIdx = returnTotalIndex();
	
	// Determine income vs expense
	// CONVENTION: all values should be positive
	switch (newOrRefresh)
	{
	case 0:
		switch (expense.incomeOrExpense)
		{
		case IncomeOrExpense::Income:
			if (expense.paidIn >= 0) // Section might not be needed but at least it makes sure that value is +ve just in case
			{
				monthlyTotals[yearIdx][monthIdx][currencyIdx][iOrEIdx][totalIdx] += expense.paidIn;
				monthlyTotals[yearIdx][monthIdx][currencyIdx][iOrEIdx][itemTypeIdx] += expense.paidIn;
			}
			else
			{
				monthlyTotals[yearIdx][monthIdx][currencyIdx][iOrEIdx][totalIdx] += (expense.paidIn * -1);
				monthlyTotals[yearIdx][monthIdx][currencyIdx][iOrEIdx][itemTypeIdx] += (expense.paidIn * -1);
			}
			break;
		case IncomeOrExpense::Expense:
			if (expense.paidOut >= 0)
			{
				monthlyTotals[yearIdx][monthIdx][currencyIdx][iOrEIdx][totalIdx] += expense.paidOut;
				monthlyTotals[yearIdx][monthIdx][currencyIdx][iOrEIdx][itemTypeIdx] += expense.paidOut;
			}
			else
			{
				monthlyTotals[yearIdx][monthIdx][currencyIdx][iOrEIdx][totalIdx] += (expense.paidOut * -1);
				monthlyTotals[yearIdx][monthIdx][currencyIdx][iOrEIdx][itemTypeIdx] += (expense.paidOut * -1);
			}
			break;
		default:
			// Shouldn't get in here
			throw std::runtime_error("MonthlyTotals::determineItemType: Value is neither income nor expense.");
		}
		// Increment monthlyOccurances
		monthlyOccurances[yearIdx][monthIdx][currencyIdx][iOrEIdx][totalIdx] += 1;
		monthlyOccurances[yearIdx][monthIdx][currencyIdx][iOrEIdx][itemTypeIdx] += 1;
		break;
	default:
		break;
	}
	
	// Setup references to original object
	processedStatement[yearIdx][monthIdx][currencyIdx][iOrEIdx][totalIdx].push_back(expense);
	processedStatement[yearIdx][monthIdx][currencyIdx][iOrEIdx][itemTypeIdx].push_back(expense);
}


/*
* Error check array sizes
*/
void MonthlyTotals::checkArrays(const std::vector<std::reference_wrapper<LineValue>> expenses) {
	std::stringstream errMsg;
	if (yearsContained.size() != monthsContained.size() || yearsContained.size() != monthlyTotals.size())
	{
		errMsg << "MonthlyTotals arrays do not have the same amount of years for statement beginning: " << expenses[0].get().lineValueSummary(1, 1);

		std::string err = errMsg.str();
		throw std::runtime_error(err);
	}
	else
	{
		for (size_t i = 0; i < yearsContained.size(); i++)
		{
			if (monthsContained[i].size() != monthlyTotals[i].size())
			{
				errMsg << "MonthlyTotals arrays do not have the same amount of months for " << yearsContained[i] << " for statement beginning: " <<
					expenses[0].get().lineValueSummary(1, 1);

				std::string err = errMsg.str();
				throw std::runtime_error(err);
			}
		}
	}
}

/*
* Calculate the average values for Income and Expenses by ItemType per month per year
*/
void MonthlyTotals::calculateAverages(){
	// Loop through the arrays and calculate the average monetary value per type
	for (size_t i = 0; i < yearsContained.size(); i++)
		for (size_t j = 0; j < monthsContained[i].size(); j++)
			for (size_t k = 0; k < static_cast<size_t>(Currency::maxCurrencies); k++)
				for (size_t l = 0; l < static_cast<size_t>(IncomeOrExpense::maxIncomeOrExpense); l++)
					for (size_t m = 0; m < static_cast<size_t>(ItemType::maxItemTypes) + 1; m++)
						monthlyAverages[i][j][k][l][m] = (monthlyOccurances[i][j][k][l][m] == 0) ? 0.0 : 
							monthlyTotals[i][j][k][l][m] / monthlyOccurances[i][j][k][l][m];
}


/*
* Refreshes the reference array for processedStatement
*/
void MonthlyTotals::refreshRefs() {
	processStatement(1);
}