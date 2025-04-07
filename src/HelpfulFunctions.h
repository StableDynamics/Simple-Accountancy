#if !defined(HELPFULFUNCTIONS)
#define HELPFULFUNCTIONS


#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

#include "BankName.h"
#include "Currencies.h"
#include "IncomeOrExpense.h"
#include "ItemType.h"
#include "Month.h"
#include "ReturnTypeName.h"
#include "TextConversion.h"

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Template Functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Helper function that takes in a variable enumData and spits out the resulting enum value
*/
template <typename T, typename EnumData>
T searchEnumDataForEnum(const EnumData& enumData, std::string_view enumString)
{
	if (enumString.length() == 3)
	{
		auto it = std::find_if(enumData.begin(), enumData.end(),
			[enumString](const auto& tuple) { return std::get<1>(tuple).substr(0, 3) == enumString; });
		if (it != enumData.end())
			return std::get<0>(*it);
	}
	else
	{
		auto it = std::find_if(enumData.begin(), enumData.end(),
			[enumString](const auto& tuple) { return std::get<1>(tuple) == enumString; });
		if (it != enumData.end())
			return std::get<0>(*it);

		// Currency is a special one
		if constexpr (std::is_same_v<T, Currency::Currency>)
		{
			auto it = std::find_if(enumData.begin(), enumData.end(),
				[enumString](const auto& tuple) { return std::get<2>(tuple) == enumString; });
			if (it != enumData.end())
				return std::get<0>(*it);
		}
	}

	// If it gets here it's an error
	std::ostringstream errMsg;
	errMsg << "Enum string not found in enumDataToEnum for " << getTypeName<T>() << ". String supplied was: " << enumString << std::endl;
	throw std::runtime_error(errMsg.str());
}


/*
* Helper function that takes in a variable enumData and spits out the resulting string value
*/
template <typename T, typename EnumData>
std::string searchEnumDataForString(const EnumData& enumData, T enumValue, std::string_view wantedStringType)
{
	auto it = std::find_if(enumData.begin(), enumData.end(),
		[enumValue](const auto& tuple) { return std::get<0>(tuple) == enumValue; });

	if (it != enumData.end())
	{
		if (wantedStringType == "3Len")
			return std::string(std::get<1>(*it).substr(0, 3));
		else if (wantedStringType == "Other")
		{
			if constexpr (std::is_same_v<T, Currency::Currency>)
			{
#ifdef _WIN32
				return u8StrToStr(std::u8string(std::get<3>(*it)));
#else
				return std::string(std::get<2>(*it));
#endif
			}
			else
				return std::string(std::get<1>(*it));
		}
	}
	else
	{
		std::ostringstream errMsg;
		errMsg << "Enum type not recognised in enumDataToEnum for " << getTypeName<T>() << std::endl;
		throw std::runtime_error("Enum value not found in enumToString for BankName");
	}

	// If it gets here it's an error
	std::ostringstream errMsg;
	errMsg << "Enum type not recognised in enumDataToEnum for " << getTypeName<T>() << std::endl;
	throw std::runtime_error("Enum value not found in enumToString for BankName");
}

/*
* Convert a string to an enum
*/
template <typename T>
T enumFromString(const std::string_view enumString)
{
	static_assert(std::is_enum_v<T>); // Must be an enum
	
	// Based on the type of enum: search the tuple for the requested values
	if constexpr (std::is_same_v<T, BankName::BankName>)
		return searchEnumDataForEnum<BankName::BankName>(BankName::enumData, enumString);
	else if constexpr (std::is_same_v<T, Currency::Currency>)
		return searchEnumDataForEnum<Currency::Currency>(Currency::enumData, enumString);
	else if constexpr (std::is_same_v<T, Month::Month>)
		return searchEnumDataForEnum<Month::Month>(Month::enumData, enumString);
	else if constexpr (std::is_same_v<T, IncomeOrExpense::IncomeOrExpense>)
		return searchEnumDataForEnum<IncomeOrExpense::IncomeOrExpense>(IncomeOrExpense::enumData, enumString);
	else if constexpr (std::is_same_v<T, ItemType::ItemType>)
		return searchEnumDataForEnum<ItemType::ItemType>(ItemType::enumData, enumString);
	else // Throw an exception saying that the enum type is not recognised
	{
		std::stringstream errMsg;
		errMsg << "Enum type not recognised in enumFromString(const std::string& enumString). Type supplied was: " << getTypeName<T>() << std::endl;
		throw std::runtime_error(errMsg.str());
	}
}

template <typename T>
T enumFromString(const std::string_view enumString, size_t index)
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
T enumFromString(const std::string_view enumString, size_t index, const std::string& fname)
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
* Convert an enum to a string
*/
template <typename T>
std::string enumToString(T enumValue, std::string_view wantedStringType = "Other")
{
	static_assert(std::is_enum_v<T>); // Must be an enum

	// Work out what type of string the caller wants and from what enum
	std::vector<std::string> acceptedStringTypes{ "3Len", "Other" }; // Accepted string types based on enum arrays
	const auto found = std::find(acceptedStringTypes.begin(), acceptedStringTypes.end(), wantedStringType);
	const auto index = std::distance(acceptedStringTypes.begin(), found);

	std::string_view dummyStr{ "ERROR" };

	if (found == acceptedStringTypes.end())
	{
		// This is an error state as the requested string type has not been found
		std::stringstream errMsg;
		errMsg << "Requested string type " << wantedStringType << " not recognised in "
			<< "enumToString(T enumValue, std::string_view wantedStringType)";
		std::string err = errMsg.str();
		throw std::runtime_error(err);
	}
	else
	{
		if constexpr (std::is_same_v<T, BankName::BankName>)
			return searchEnumDataForString<BankName::BankName>(BankName::enumData, enumValue, wantedStringType);
		else if constexpr (std::is_same_v<T, Currency::Currency>)
			return searchEnumDataForString<Currency::Currency>(Currency::enumData, enumValue, wantedStringType);
		else if constexpr (std::is_same_v<T, Month::Month>)
			return searchEnumDataForString<Month::Month>(Month::enumData, enumValue, wantedStringType);
		else if constexpr (std::is_same_v<T, IncomeOrExpense::IncomeOrExpense>)
			return searchEnumDataForString<IncomeOrExpense::IncomeOrExpense>(IncomeOrExpense::enumData, enumValue, wantedStringType);
		else if constexpr (std::is_same_v<T, ItemType::ItemType>)
			return searchEnumDataForString<ItemType::ItemType>(ItemType::enumData, enumValue, wantedStringType);
		else
		{
			std::ostringstream errMsg;
			errMsg << "Enum type not recognised in enumToString(T enumValue, std::string_view wantedStringType). Type supplied was: " << getTypeName<T>() << std::endl;
			throw std::runtime_error(errMsg.str());
		}
	}
}

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Forward Declared Functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Most occurred string
std::string mostOccurredString(const std::vector<std::string>& stringVec);

#endif