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
#include "ItemType.h"
#include "IncomeOrExpense.h"
#include "BankName.h"
#include "ReturnTypeName.h"

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Template Functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Convert a string to an enum
*/
template <typename T>
T enumFromString(const std::string_view enumString)
{
	static_assert(std::is_enum_v<T>); // Must be an enum
	// Setup blank data variables
	std::unique_ptr<const std::vector<std::string_view>> enum3LenStrings_ptr;
	std::unique_ptr<const std::vector<std::string_view>> enumOtherStrings_ptr;
	size_t length{ 0 };

	// Setup comparison string_views for the current enum type
	std::string_view enumName = getTypeName<T>();

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
	else if (enumName == static_cast<std::string_view>("enum ItemType::ItemType"))
	{
		enum3LenStrings_ptr = std::make_unique<const std::vector<std::string_view>>(ItemType::itemTypeStrings3Len);
		enumOtherStrings_ptr = std::make_unique<const std::vector<std::string_view>>(ItemType::itemTypeStringsOther);
		length = enum3LenStrings_ptr->size();
	}
	else if (enumName == static_cast<std::string_view>("enum IncomeOrExpense::IncomeOrExpense"))
	{
		enum3LenStrings_ptr = std::make_unique<const std::vector<std::string_view>>(IncomeOrExpense::incomeOrExpenseStrings3Len);
		enumOtherStrings_ptr = std::make_unique<const std::vector<std::string_view>>(IncomeOrExpense::incomeOrExpenseStringsOther);
		length = enum3LenStrings_ptr->size();
	}
	else if (enumName == static_cast<std::string_view>("enum BankName::BankName"))
	{
		enum3LenStrings_ptr = std::make_unique<const std::vector<std::string_view>>(BankName::bankNameStrings3Len);
		enumOtherStrings_ptr = std::make_unique<const std::vector<std::string_view>>(BankName::bankNameStringsOther);
		length = enum3LenStrings_ptr->size();
	}
	else // Throw an exception saying that the enum type is not recognised
	{
		std::stringstream errMsg;
		errMsg << "Enum type not recognised in enumFromString(const std::string& enumString). Type supplied was: " << enumName << std::endl;
		std::string err = errMsg.str();
		throw std::runtime_error(err);
	}

	// Define error message
	std::stringstream errMsg;
	errMsg << "Enum name not recognised in enumFromString(const std::string& enumString). Name supplied was: " << enumString << std::endl
		<< "Enum type being compared was: " << enumName << std::endl;
	std::string err = errMsg.str();

	// Runthrough data variables to find the correct enum
	if (enumString.length() == 3)
	{
		const auto found = std::find(enum3LenStrings_ptr->begin(), enum3LenStrings_ptr->end(), enumString);
		const auto index = std::distance(enum3LenStrings_ptr->begin(), found);
		if (found == enum3LenStrings_ptr->end()) throw std::runtime_error(err);
		else return static_cast<T>(index);
	}
	else
	{
		const auto found = std::find(enumOtherStrings_ptr->begin(), enumOtherStrings_ptr->end(), enumString);
		const auto index = std::distance(enumOtherStrings_ptr->begin(), found);
		if (found == enumOtherStrings_ptr->end()) throw std::runtime_error(err);
		else return static_cast<T>(index);
	}

	// Should only get here if the enum is not found so error
	throw std::runtime_error(err);
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
std::string enumToString(T enumValue, std::string_view wantedStringType)
{
	static_assert(std::is_enum_v<T>); // Must be an enum

	// Work out what type of string the caller wants and from what enum
	std::vector<std::string> acceptedStringTypes{ "3Len", "Other" }; // Accepted string types based on enum arrays
	const auto found = std::find(acceptedStringTypes.begin(), acceptedStringTypes.end(), wantedStringType);
	const auto index = std::distance(acceptedStringTypes.begin(), found);
	std::string_view enumName = getTypeName<T>();

	if (found == acceptedStringTypes.end())
	{
		// This is an error state as the requested string type has not been found
		std::stringstream errMsg;
		errMsg << "Requested string type " << wantedStringType << " not recognised in "
			<< "enumToString(T enumValue, std::string_view wantedStringType)";
		std::string err = errMsg.str();
		throw std::runtime_error(err);
	}
	else if (acceptedStringTypes[index] == "3Len")
	{
		if (enumName == "enum Month::Month")
		{
			return static_cast<std::string>(Month::monthStrings3Len[enumValue]);
		}
		else if (enumName == "enum Currency::Currency")
		{
			return static_cast<std::string>(Currency::currencyStrings3Len[enumValue]);
		}
		else if (enumName == "enum ItemType::ItemType")
		{
			return static_cast<std::string>(ItemType::itemTypeStrings3Len[enumValue]);
		}
		else if (enumName == "enum IncomeOrExpense::IncomeOrExpense")
		{
			return static_cast<std::string>(IncomeOrExpense::incomeOrExpenseStrings3Len[enumValue]);
		}
		else if (enumName == "enum BankName::BankName")
		{
			return static_cast<std::string>(BankName::bankNameStrings3Len[enumValue]);
		}
	}
	else if (acceptedStringTypes[index] == "Other")
	{
		if (enumName == "enum Month::Month")
		{
			return static_cast<std::string>(Month::monthStringsOther[enumValue]);
		}
		else if (enumName == "enum Currency::Currency")
		{
			return static_cast<std::string>(Currency::currencyStringsOther[enumValue]);
		}
		else if (enumName == "enum ItemType::ItemType")
		{
			return static_cast<std::string>(ItemType::itemTypeStringsOther[enumValue]);
		}
		else if (enumName == "enum IncomeOrExpense::IncomeOrExpense")
		{
			return static_cast<std::string>(IncomeOrExpense::incomeOrExpenseStringsOther[enumValue]);
		}
		else if (enumName == "enum BankName::BankName")
		{
			return static_cast<std::string>(BankName::bankNameStringsOther[enumValue]);
		}
	}
	
	// Catch missing enum types
	std::stringstream errMsg;
	errMsg << "Enum type not recognised in enumFromString(const std::string & enumString).Type supplied was : " << enumName;
	std::string err = errMsg.str();
	throw std::runtime_error(err);
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