///////////////////////////////////////////////////////////
//  Month.h
//  Implementation of the Enumeration Month
//  Created on:      03-Mar-2025 15:20:29
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(MONTH)
#define MONTH

#include <array>
#include <string_view>

/**
 * What month is it?
 */
namespace Month
{
	enum Month
	{
		Unused,
		January,
		February,
		March,
		April,
		May,
		June,
		July,
		August,
		September,
		October,
		November,
		December,
		maxMonths
	};

	// Using sc suffix so std::array will infer that it is a string_view
	using namespace std::string_view_literals;
	constexpr std::array monthStrings3Len =
	{
		"Unused"sv,
		"Jan"sv,
		"Feb"sv,
		"Mar"sv,
		"Apr"sv,
		"May"sv,
		"Jun"sv,
		"Jul"sv,
		"Aug"sv,
		"Sep"sv,
		"Oct"sv,
		"Nov"sv,
		"Dec"sv
	};
	
	constexpr std::array monthStringsOther =
	{
		"Unused"sv,
		"January"sv,
		"February"sv,
		"March"sv,
		"April"sv,
		"May"sv,
		"June"sv,
		"July"sv,
		"August"sv,
		"September"sv,
		"October"sv,
		"November"sv,
		"December"sv
	};

	//Make sure we've defined all enums
	static_assert(monthStrings3Len.size() == maxMonths, "Missing 3 Length Month string");
	static_assert(monthStringsOther.size() == maxMonths, "Missing Other Month string");

	// Common get functions
	constexpr const std::array<std::string_view, maxMonths> getEnumStrings3Len()
	{
		return monthStrings3Len;
	}
	constexpr const std::array<std::string_view, maxMonths> getEnumStringsOther()
	{
		return monthStringsOther;
	}
}


#endif // !defined(MONTH)
