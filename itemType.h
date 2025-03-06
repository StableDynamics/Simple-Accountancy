///////////////////////////////////////////////////////////
//  ItemType.h
//  Implementation of the Enumeration ItemType
//  Created on:      03-Mar-2025 15:20:29
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(ITEMTYPE)
#define ITEMTYPE

#include <vector>
#include <string_view>

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
		Rent,
		Bills,
		Groceries,
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
		"Ren",
		"Bil",
		"Gro",
		"Ins",
		"Sub",
		"Ent"
	};

	const std::vector<std::string_view> itemTypeStringsOther =
	{
		"Other",
		"Salary",
		"Dividend",
		"Rent",
		"Bills",
		"Groceries",
		"Insurance",
		"Subscriptions",
		"Entertainment"
	};
}

#endif // !defined(ITEMTYPE)
