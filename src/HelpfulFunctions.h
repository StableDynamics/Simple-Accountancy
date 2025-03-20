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
	std::unique_ptr<const std::vector<std::string_view>> enum3LenStrings_sv;
	std::unique_ptr<const std::vector<std::string_view>> enumOtherStrings_sv;

	// Determine enum name as a string_view
	std::string_view enumName = getTypeName<T>();

	// Based on the type of enum, setup data pointers, could this be done better?
	if constexpr (std::is_same_v<T, Month::Month>)
	{
		enum3LenStrings_sv = std::make_unique<const std::vector<std::string_view>>(Month::monthStrings3Len);
		enumOtherStrings_sv = std::make_unique<const std::vector<std::string_view>>(Month::monthStringsOther);
	}
	else if constexpr (std::is_same_v<T, Currency::Currency>)
	{
		enum3LenStrings_sv = std::make_unique<const std::vector<std::string_view>>(Currency::currencyStrings3Len);
		enumOtherStrings_sv = std::make_unique<const std::vector<std::string_view>>(Currency::currencyStringsOther);
	}
	else if constexpr (std::is_same_v<T, ItemType::ItemType>)
	{
		enum3LenStrings_sv = std::make_unique<const std::vector<std::string_view>>(ItemType::itemTypeStrings3Len);
		enumOtherStrings_sv = std::make_unique<const std::vector<std::string_view>>(ItemType::itemTypeStringsOther);
	}
	else if constexpr (std::is_same_v<T, IncomeOrExpense::IncomeOrExpense>)
	{
		enum3LenStrings_sv = std::make_unique<const std::vector<std::string_view>>(IncomeOrExpense::incomeOrExpenseStrings3Len);
		enumOtherStrings_sv = std::make_unique<const std::vector<std::string_view>>(IncomeOrExpense::incomeOrExpenseStringsOther);
	}
	else if constexpr (std::is_same_v<T, BankName::BankName>)
	{
		enum3LenStrings_sv = std::make_unique<const std::vector<std::string_view>>(BankName::bankNameStrings3Len);
		enumOtherStrings_sv = std::make_unique<const std::vector<std::string_view>>(BankName::bankNameStringsOther);
	}
	else // Throw an exception saying that the enum type is not recognised
	{
		std::stringstream errMsg;
		errMsg << "Enum type not recognised in enumFromString(const std::string& enumString). Type supplied was: " << enumName << std::endl;
		std::string err = errMsg.str();
		throw std::runtime_error(err);
	}
	// Both arrays *should* be same length

	// Define error message
	std::stringstream errMsg;
	errMsg << "Enum name not recognised in enumFromString(const std::string& enumString). Name supplied was: " << enumString << std::endl
		<< "Enum type being compared was: " << enumName << std::endl;
	std::string err = errMsg.str();

	// Runthrough data variables to find the correct enum
	if (enumString.length() == 3)
	{
		const auto found = std::find(enum3LenStrings_sv->begin(), enum3LenStrings_sv->end(), enumString);
		const auto index = std::distance(enum3LenStrings_sv->begin(), found);
		if (found == enum3LenStrings_sv->end()) throw std::runtime_error(err);
		else return static_cast<T>(index);
	}
	else
	{
		const auto found = std::find(enumOtherStrings_sv->begin(), enumOtherStrings_sv->end(), enumString);
		const auto index = std::distance(enumOtherStrings_sv->begin(), found);
		if (found == enumOtherStrings_sv->end()) throw std::runtime_error(err);
		else return static_cast<T>(index);
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
std::string enumToString(T enumValue, std::string_view wantedStringType)
{
	static_assert(std::is_enum_v<T>); // Must be an enum

	// Work out what type of string the caller wants and from what enum
	std::vector<std::string> acceptedStringTypes{ "3Len", "Other" }; // Accepted string types based on enum arrays
	const auto found = std::find(acceptedStringTypes.begin(), acceptedStringTypes.end(), wantedStringType);
	const auto index = std::distance(acceptedStringTypes.begin(), found);

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
		if constexpr (std::is_same_v<T, Month::Month>)
		{
			return static_cast<std::string>(Month::monthStrings3Len[enumValue]);
		}
		else if constexpr (std::is_same_v < T, Currency::Currency>)
		{
			return static_cast<std::string>(Currency::currencyStrings3Len[enumValue]);
		}
		else if constexpr (std::is_same_v < T, ItemType::ItemType>)
		{
			return static_cast<std::string>(ItemType::itemTypeStrings3Len[enumValue]);
		}
		else if constexpr (std::is_same_v < T, IncomeOrExpense::IncomeOrExpense>)
		{
			return static_cast<std::string>(IncomeOrExpense::incomeOrExpenseStrings3Len[enumValue]);
		}
		else if constexpr (std::is_same_v < T, BankName::BankName>)
		{
			return static_cast<std::string>(BankName::bankNameStrings3Len[enumValue]);
		}
	}
	else if (acceptedStringTypes[index] == "Other")
	{
		if constexpr (std::is_same_v<T, Month::Month>)
		{
			return static_cast<std::string>(Month::monthStringsOther[enumValue]);
		}
		else if constexpr (std::is_same_v < T, Currency::Currency>)
		{
			return static_cast<std::string>(Currency::currencyStringsOther[enumValue]);
		}
		else if constexpr (std::is_same_v < T, ItemType::ItemType>)
		{
			return static_cast<std::string>(ItemType::itemTypeStringsOther[enumValue]);
		}
		else if constexpr (std::is_same_v < T, IncomeOrExpense::IncomeOrExpense>)
		{
			return static_cast<std::string>(IncomeOrExpense::incomeOrExpenseStringsOther[enumValue]);
		}
		else if constexpr (std::is_same_v < T, BankName::BankName>)
		{
			return static_cast<std::string>(BankName::bankNameStringsOther[enumValue]);
		}
	}
	
	// Catch missing enum types
	std::string_view enumName = getTypeName<T>();
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

/*
* Allow conversion between u8string and string so that cout can print it to console
*/
#if defined(__cpp_lib_char8_t)
std::string fromu8String(const std::u8string& s);
#endif
#endif