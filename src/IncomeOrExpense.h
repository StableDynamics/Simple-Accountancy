///////////////////////////////////////////////////////////
//  IncomeOrExpense.h
//  Implementation of the Enumeration IncomeOrExpense
//  Created on:      03-Mar-2025 15:20:29
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(INCOMEOREXPENSE)
#define INCOMEOREXPENSE

#include <array>
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

	inline constexpr std::array<std::string_view, static_cast<int>(IncomeOrExpense::maxIncomeOrExpense)> incomeOrExpenseStrings3Len =
	{
		"Inc",
		"Exp"
	};

	inline constexpr std::array<std::string_view, static_cast<int>(IncomeOrExpense::maxIncomeOrExpense)> incomeOrExpenseStringsOther =
	{
		"Income",
		"Expense"
	};
}

static_assert(IncomeOrExpense::incomeOrExpenseStrings3Len.size() == static_cast<int>(IncomeOrExpense::maxIncomeOrExpense), "IncomeOrExpense::incomeOrExpenseStrings3Len size mismatch");
static_assert(IncomeOrExpense::incomeOrExpenseStringsOther.size() == static_cast<int>(IncomeOrExpense::maxIncomeOrExpense), "IncomeOrExpense::incomeOrExpenseStringsOther size mismatch");

// namespace IncomeOrExpense

#endif // !defined(INCOMEOREXPENSE)
