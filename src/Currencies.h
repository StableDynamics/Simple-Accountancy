///////////////////////////////////////////////////////////
//  Currency.h
//  Implementation of the Enumeration Currency
//  Created on:      05-Mar-2025 16:18:42
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(CURRENCIES)
#define CURRENCIES

#include <array>
#include <string_view>
#include <tuple>

/**
 * What currency is it?
 */
namespace Currency
{
	enum Currency
	{
		GBP,
		EUR,
		USD,
		maxCurrencies
	};

	// u8 string is to help windows display it properly in a terminal
	inline constexpr std::array enumData = {std::tuple<Currency, std::string_view, std::string_view, std::u8string_view>{GBP, "GBP", "£", u8"£"},
											std::tuple<Currency, std::string_view, std::string_view, std::u8string_view>{EUR, "EUR", "€", u8"€"},
											std::tuple<Currency, std::string_view, std::string_view, std::u8string_view>{USD, "USD", "$", u8"$"}, };

	static_assert(enumData.size() == static_cast<int>(maxCurrencies), "Currency enumData array size mismatch");
}

#endif // !defined(CURRENCIES)
