#if !defined(HELPFULFUNCTIONS)
#define HELPFULFUNCTIONS
#include <string>
#include <stdexcept>
#include <sstream>

#include "Month.h"
#include "Currency.h"
#include "ReturnTypeName.h"

/**
* Convert a string to an enum
*/
template <typename T>
T enumFromString(const std::string& enumString)
{
	static_assert(std::is_enum_v<T>); // Must be an enum
	// Based on enumString size loop through relevant enumStrings and return the correct one
	const auto& enum3Strings = T::getEnumStrings3Len();
	const auto& enumOtherStrings = T::getEnumStringsOther();
	if (enumString.length() == 3)
	{
		for (size_t i = 0; i < enum3Strings.size(); i++)
		{
			if (enumString == enum3Strings[i])
			{
				return static_cast<T>(i);
			}
		}
	}
	else
	{
		for (size_t i = 0; i < enumOtherStrings.size(); i++)
		{
			if (enumString == enumOtherStrings[i])
			{
				return static_cast<T>(i);
			}
		}
	}

	std::stringstream errMsg;
	errMsg << "Enum name not recognised. Name supplied was: " << enumString << std::endl
		<< "Enum type being compared was: " << static_cast<std::string>(getTypeName<T>());
	std::string err = errMsg.str();
	throw std::runtime_error(err);
}

Month::Month monthFromString(const std::string& monthString);

Month::Month monthFromString(const std::string& monthString, size_t index);

Month::Month monthFromString(const std::string& monthString, size_t index, const std::string& fname);

Currency::Currency currencyFromString(const std::string& currencyString);


#endif