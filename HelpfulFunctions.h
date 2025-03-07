#if !defined(HELPFULFUNCTIONS)
#define HELPFULFUNCTIONS
#include <string>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <string_view>
#include <memory>

#include "Month.h"
#include "Currency.h"
#include "ReturnTypeName.h"

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Template Functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Convert a string to an enum
*/
template <typename T>
T enumFromString(const std::string& enumString)
{
	static_assert(std::is_enum_v<T>); // Must be an enum
	// Setup blank data variables
	std::unique_ptr<const std::vector<std::string_view>> enum3LenStrings_ptr;
	std::unique_ptr<const std::vector<std::string_view>> enumOtherStrings_ptr;
	size_t length{ 0 };

	// Setup comparison string_views for the current enum type
	std::string_view enumName = getTypeName<T>();
	//TODO: Add more enum types here

	// Based on the type of enum, setup data pointers
	if (enumName == static_cast<std::string_view>("enum Month::Month"))
	{
		enum3LenStrings_ptr = std::make_unique<const std::vector<std::string_view>>(Month::monthStrings3Len);
		enumOtherStrings_ptr = std::make_unique<const std::vector<std::string_view>>(Month::monthStringsOther);
		length = enum3LenStrings_ptr->size();
	}
	else if (enumName == static_cast<std::string_view>("enum Currency::Currency"))
	{
		enum3LenStrings_ptr = std::make_unique<const std::vector<std::string_view>>(Currency::currencyStrings3Len);
		enumOtherStrings_ptr = std::make_unique<const std::vector<std::string_view>>(Currency::currencyStringsOther);
		length = enum3LenStrings_ptr->size();
	}
	else // Throw an exception saying that the enum type is not recognised
	{
		std::stringstream errMsg;
		errMsg << "Enum type not recognised. Type supplied was: " << static_cast<std::string>(enumName) << std::endl;
		std::string err = errMsg.str();
		throw std::runtime_error(err);
	}

	//// Runthrough data variables to find the correct enum
	if (enumString.length() == 3)
	{
		for (size_t i = 0; i < enum3LenStrings_ptr->size(); i++)
		{
			if (enumString == (*enum3LenStrings_ptr)[i])
			{
				return static_cast<T>(i);
			}
		}
	}
	else
	{
		for (size_t i = 0; i < enumOtherStrings_ptr->size(); i++)
		{
			if (enumString == (*enumOtherStrings_ptr)[i])
			{
				return static_cast<T>(i);
			}
		}
	}

	// Error if the month is not found
	std::stringstream errMsg;
	errMsg << "Enum name not recognised. Name supplied was: " << enumString << std::endl
		<< "Enum type being compared was: " << static_cast<std::string>(getTypeName<T>()) << std::endl;
	std::string err = errMsg.str();
	throw std::runtime_error(err);
}

template <typename T>
T enumFromString(const std::string& enumString, size_t index)
{
	try
	{
		T t = enumFromString<T>(enumString);
		return t;
	}
	catch (const std::exception& e)
	{
		std::stringstream errMsg;
		errMsg << e.what() << "Index of value in csv file: " << index << std::endl;
		std::string err = errMsg.str();
		throw std::runtime_error(err);
	}
}

template <typename T>
T enumFromString(const std::string& enumString, size_t index, const std::string& fname)
{
	try
	{
		T t = enumFromString<T>(enumString, index);
		return t;
	}
	catch (const std::exception& e)
	{
		std::stringstream errMsg;
		errMsg << e.what() << "File Name: " << fname << std::endl;
		std::string err = errMsg.str();
		throw std::runtime_error(err);
	}
}

/*
* Error check an enum
*/
template <typename T>
void enumErrorCheck(const std::vector<std::string_view>& strings3Len, const std::vector<std::string_view>& stringsOther, T maxEnum)
{
	std::stringstream errMsg;
	errMsg << "Missing " << static_cast<std::string>(getTypeName<T>());
	
	if (strings3Len.size() != maxEnum)
	{
		errMsg << " 3Len string" << std::endl;
		std::string err = errMsg.str();
		throw std::runtime_error(err);
	}
	if (stringsOther.size() != maxEnum)
	{
		errMsg << " Other string" << std::endl;
		std::string err = errMsg.str();
		throw std::runtime_error(err);
	}
}

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Forward Declared Functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif