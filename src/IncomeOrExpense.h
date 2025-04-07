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
#include <tuple>

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

	inline constexpr std::array enumData = {std::tuple<IncomeOrExpense, std::string_view>{Income	, "Income"},
											std::tuple<IncomeOrExpense, std::string_view>{Expense	, "Expense"} };

	static_assert(enumData.size() == static_cast<int>(maxIncomeOrExpense), "IncomeOrExpense enumData array size mismatch");
}

// namespace IncomeOrExpense

#endif // !defined(INCOMEOREXPENSE)
