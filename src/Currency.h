///////////////////////////////////////////////////////////
//  Currency.h
//  Implementation of the Enumeration Currency
//  Created on:      05-Mar-2025 16:18:42
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(CURRENCY)
#define CURRENCY

#include <array>
#include <string>
#include <string_view>
#include <vector>

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

	const std::vector<std::string_view> currencyStrings3Len =
	{
		"GBP",
		"EUR",
		"USD"
	};

	const std::vector<std::string_view> currencyStringsOther =
	{
		"£",
		"€",
		"$"
	};

#ifdef _WIN32 // Needed in order to have Windows consoles display things properly
	const std::vector<std::u8string> currencySymbolsu8 =
	{
		u8"£",
		u8"€",
		u8"$"
	};
#endif
}

#endif // !defined(CURRENCY)
