#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <type_traits>
#include <vector>
#include <map>

#include "Currencies.h"
#include "IncomeOrExpense.h"
#include "ItemType.h"
#include "Month.h"


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Forward declarations for classes and structs used in the project
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct LineValue;
class AccountingPeriod;


/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Type definitions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using LineValueRefs = std::vector<std::reference_wrapper<LineValue>>;	// Reference wrapper for LineValue objects
using ContentVec = std::vector<std::vector<std::string>>;				// Content vector for file import

using ProcessedStatement = std::vector<std::vector<std::array<std::array<std::array<std::vector<std::reference_wrapper<const LineValue>>,
	static_cast<int>(ItemType::maxItemTypes) + 1>, static_cast<int>(IncomeOrExpense::maxIncomeOrExpense)>,
	static_cast<int>(Currency::maxCurrencies)>>>;						// Processed statement of LineValue objects references in Year, Month, Currency, Income/Expense, ItemType (end idx itemType is the total)

using StatementDatabase = std::map<
							int, std::map<
								Month::Month, std::map<
									Currency::Currency, std::map<
										IncomeOrExpense::IncomeOrExpense, std::map<
											ItemType::ItemType, std::map<
												std::string, LineValueRefs>>>>>>;	// Database of LineValue objects arranged by Year, Month, Currency, Income/Expense, ItemType, and then Item Sub-Type

using YrMtCrIEITTotal = std::vector<std::vector<std::array<std::array<std::array<double, static_cast<int>(ItemType::maxItemTypes) + 1>,
	static_cast<int>(IncomeOrExpense::maxIncomeOrExpense)>, static_cast<int>(Currency::maxCurrencies)>>>;	// Vector of Year, Month, Currency, Income/Expense, ItemType (end idx itemType is the total) Totals

using YrMtCrIEITOcc = std::vector<std::vector<std::array<std::array<std::array<uint64_t, static_cast<int>(ItemType::maxItemTypes) + 1>,
	static_cast<int>(IncomeOrExpense::maxIncomeOrExpense)>, static_cast<int>(Currency::maxCurrencies)>>>;	// Vector of Year, Month, Currency, Income/Expense, ItemType (end idx itemType is the total) Occurances

using YrMtCrIEITAvg = std::vector<std::vector<std::array<std::array<std::array<double, static_cast<int>(ItemType::maxItemTypes) + 1>,
	static_cast<int>(IncomeOrExpense::maxIncomeOrExpense)>, static_cast<int>(Currency::maxCurrencies)>>>;	// Vector of Year, Month, Currency, Income/Expense, ItemType (end idx itemType is the total) Averages

using CrIEITAvg = std::array<std::array<std::array<double, static_cast<int>(ItemType::maxItemTypes) + 1>, static_cast<int>(IncomeOrExpense::maxIncomeOrExpense)>, 
	static_cast<int>(Currency::maxCurrencies)>;																// Stores monthly averages arranged by currency, and then income or expense, 
																											// and then individual array values are ItemTypes with the last element being the total

using AvgIEbyCr = std::array<double, static_cast<int>(Currency::maxCurrencies)>;							// Stores values comparing average monthly income to expenses for each currency