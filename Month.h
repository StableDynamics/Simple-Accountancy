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
	constexpr std::array monthStringsLong =
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

	constexpr std::array monthStringsShort =
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

	//Make sure we've defined all enums
	static_assert(monthStringsLong.size() == maxMonths, "Missing long Month string");
	static_assert(monthStringsShort.size() == maxMonths, "Missing short Month string");
}


#endif // !defined(MONTH)
