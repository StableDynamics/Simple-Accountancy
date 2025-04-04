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
#include <tuple>

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

	inline constexpr std::array enumData = { std::tuple<Month, std::string_view>{Unused		, "Unused"},
											std::tuple<Month, std::string_view>{January		, "January"},
											std::tuple<Month, std::string_view>{February	, "February"},
											std::tuple<Month, std::string_view>{March		, "March"},
											std::tuple<Month, std::string_view>{April		, "April"},
											std::tuple<Month, std::string_view>{May			, "May"},
											std::tuple<Month, std::string_view>{June		, "June"},
											std::tuple<Month, std::string_view>{July		, "July"},
											std::tuple<Month, std::string_view>{August		, "August"},
											std::tuple<Month, std::string_view>{September	, "September"},
											std::tuple<Month, std::string_view>{October		, "October"},
											std::tuple<Month, std::string_view>{November	, "November"},
											std::tuple<Month, std::string_view>{December	, "December"} };

	static_assert(enumData.size() == static_cast<int>(maxMonths), "Month enumData array size mismatch");
}


#endif // !defined(MONTH)
