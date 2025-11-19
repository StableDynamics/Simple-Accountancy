///////////////////////////////////////////////////////////
//  BankName.h
//  Implementation of the Enumeration BankName
//  Created on:      05-Mar-2025 11:00:07
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(BANKNAME)
#define BANKNAME

#include <array>
#include <string_view>
#include <tuple>

/*
 * What bank is the statement from?
 */
namespace BankName
{
	enum BankName
	{
		Nationwide_UK_2024,
		Natwest_UK_2024,
		Natwest_UK_CC_2024, // NatWest Credit Card
		Halifax_UK_2025,
		Tide_UK_2024,
		maxBanks
	};

	inline constexpr std::array enumData = {std::tuple<BankName, std::string_view>{Nationwide_UK_2024	, "Nationwide UK"},
											std::tuple<BankName, std::string_view>{Natwest_UK_2024		, "NatWest UK"},
											std::tuple<BankName, std::string_view>{Natwest_UK_CC_2024	, "NatWest UK"},
											std::tuple<BankName, std::string_view>{Halifax_UK_2025		, "Halifax UK"},
											std::tuple<BankName, std::string_view>{Tide_UK_2024			, "Tide UK"}, };

	static_assert(enumData.size() == static_cast<int>(maxBanks), "BankName enumData array size mismatch");
}

#endif // !defined(BANKNAME)
