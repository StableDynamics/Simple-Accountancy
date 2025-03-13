///////////////////////////////////////////////////////////
//  IncomeOrExpense.h
//  Implementation of the Enumeration IncomeOrExpense
//  Created on:      03-Mar-2025 15:20:29
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(INCOMEOREXPENSE)
#define INCOMEOREXPENSE

#include <vector>
#include <string_view>

/**
 * is it an income or an expense?
 */
namespace IncomeOrExpense
{
	enum IncomeOrExpense
	{
		Income,
		Expense,
		maxIncomeOrExpense
	};

	const std::vector<std::string_view> incomeOrExpenseStrings3Len =
	{
		"Inc",
		"Exp"
	};

	const std::vector<std::string_view> incomeOrExpenseStringsOther =
	{
		"Income",
		"Expense"
	};
}

#endif // !defined(INCOMEOREXPENSE)
