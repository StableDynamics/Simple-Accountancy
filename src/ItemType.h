///////////////////////////////////////////////////////////
//  ItemType.h
//  Implementation of the Enumeration ItemType
//  Created on:      03-Mar-2025 15:20:29
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(ITEMTYPE)
#define ITEMTYPE

#include <array>
#include <string_view>
#include <tuple>

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

	inline constexpr std::array enumData = {std::tuple<ItemType, std::string_view>{Other		, "Other"},
											std::tuple<ItemType, std::string_view>{Salary		, "Salary"},
											std::tuple<ItemType, std::string_view>{Dividend		, "Dividend"},
											std::tuple<ItemType, std::string_view>{Pension		, "Pension"},
											std::tuple<ItemType, std::string_view>{State_Assist	, "State Assitance"},
											std::tuple<ItemType, std::string_view>{Rent			, "Rent"},
											std::tuple<ItemType, std::string_view>{Bills		, "Bills"},
											std::tuple<ItemType, std::string_view>{Bank_Fees	, "Bank Fees"},
											std::tuple<ItemType, std::string_view>{Loans		, "Loans"},
											std::tuple<ItemType, std::string_view>{Savings		, "Savings"},
											std::tuple<ItemType, std::string_view>{Interest		, "Interest"},
											std::tuple<ItemType, std::string_view>{Shopping		, "Shopping"},
											std::tuple<ItemType, std::string_view>{Insurance	, "Insurance"},
											std::tuple<ItemType, std::string_view>{Subscriptions, "Subscriptions"},
											std::tuple<ItemType, std::string_view>{Entertainment, "Entertainment"} };

	static_assert(enumData.size() == static_cast<int>(maxItemTypes), "ItemTypes enumData array size mismatch");
}

#endif // !defined(ITEMTYPE)
