///////////////////////////////////////////////////////////
//  Month.h
//  Implementation of the Enumeration Month
//  Created on:      03-Mar-2025 15:20:29
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(MONTH)
#define MONTH

#include <string_view>
#include <vector>

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
}


#endif // !defined(MONTH)
