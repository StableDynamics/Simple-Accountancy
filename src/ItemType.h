///////////////////////////////////////////////////////////
//  ItemType.h
//  Implementation of the Enumeration ItemType
//  Created on:      03-Mar-2025 15:20:29
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(ITEMTYPE)
#define ITEMTYPE

#include <string_view>
#include <vector>

/**
 * What type of item is it?
 */
namespace ItemType
{
	enum ItemType
	{
		Other,
		Salary,
		Dividend,
		Pension,
		State_Assist,
		Rent,
		Bills,
		Bank_Fees,
		Loans,
		Savings,
		Interest,
		Shopping,
		Insurance,
		Subscriptions,
		Entertainment,
		maxItemTypes
	};

	const std::vector<std::string_view> itemTypeStrings3Len =
	{
		"Oth",
		"Sal",
		"Div",
		"Pen",
		"Sta",
		"Ren",
		"Bil",
		"Ban",
		"Loa",
		"Sav",
		"Int",
		"Sho",
		"Ins",
		"Sub",
		"Ent"
	};

	const std::vector<std::string_view> itemTypeStringsOther =
	{
		"Other",
		"Salary",
		"Dividend",
		"Pension",
		"State Assistance",
		"Rent",
		"Bills",
		"Bank Fees",
		"Loans",
		"Savings",
		"Interest",
		"Shopping",
		"Insurance",
		"Subscriptions",
		"Entertainment"
	};
}

#endif // !defined(ITEMTYPE)
