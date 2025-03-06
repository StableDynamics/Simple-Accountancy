///////////////////////////////////////////////////////////
//  Currency.h
//  Implementation of the Enumeration Currency
//  Created on:      05-Mar-2025 16:18:42
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(CURRENCY)
#define CURRENCY

#include <array>
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

	// Using sc suffix so std::array will infer that it is a string_view
	using namespace std::string_view_literals;
	constexpr std::array currencyStrings =
	{
		"GBP"sv,
		"EUR"sv,
		"USD"sv
	};

	constexpr std::array currencySymbols =
	{
		"£"sv,
		"€"sv,
		"$"sv
	};

	//Make sure we've defined all enums
	static_assert(currencyStrings.size() == maxCurrencies, "Missing Currency string");
	static_assert(currencySymbols.size() == maxCurrencies, "Missing Currency symbol");

	// Common get functions
	constexpr const std::array<std::string_view, maxCurrencies>& getEnumStrings3Len()
	{
		return currencyStrings;
	}
	constexpr const std::array<std::string_view, maxCurrencies>& getEnumStringsOther()
	{
		return currencySymbols;
	}
}

#endif // !defined(CURRENCY)
