///////////////////////////////////////////////////////////
//  Month.h
//  Implementation of the Enumeration Month
//  Created on:      03-Mar-2025 15:20:29
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(MONTH)
#define MONTH

#include <vector>
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

	const std::vector<std::string_view> monthStrings3Len =
	{
		"Unused",
		"Jan",
		"Feb",
		"Mar",
		"Apr",
		"May",
		"Jun",
		"Jul",
		"Aug",
		"Sep",
		"Oct",
		"Nov",
		"Dec"
	};
	/*constexpr std::array monthStrings3Len =
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
	};*/
	
	const std::vector<std::string_view> monthStringsOther =
	{
		"Unused",
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
	};

	//Make sure we've defined all enums
	//static_assert(monthStrings3Len.size() == maxMonths, "Missing 3 Length Month string");
	//static_assert(monthStringsOther.size() == maxMonths, "Missing Other Month string");

	// Common get functions
	/*const std::vector<std::string_view>& getEnumStrings3Len()
	{
		return monthStrings3Len;
	}
	const std::vector<std::string_view>& getEnumStringsOther()
	{
		return monthStringsOther;
	}*/
}


#endif // !defined(MONTH)
