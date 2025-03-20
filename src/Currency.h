///////////////////////////////////////////////////////////
//  Currency.h
//  Implementation of the Enumeration Currency
//  Created on:      05-Mar-2025 16:18:42
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(CURRENCY)
#define CURRENCY

#include <vector>
#include <string_view>

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
}

#endif // !defined(CURRENCY)
