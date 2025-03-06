#include "HelpfulFunctions.h"

/**
 * Bring out the month enum from a short month string
 */
Month::Month monthFromString(const std::string& monthString)
{
	// Iterate through list of months and return the correct one based on search string size
	if (monthString.size() == 3)
	{
		for (size_t i = 0; i < Month::monthStringsShort.size(); i++)
		{
			if (monthString == Month::monthStringsShort[i])
			{
				return static_cast<Month::Month>(i);
			}
		}
	}
	else if (monthString.size() > 3)
	{
		for (size_t i = 0; i < Month::monthStringsLong.size(); i++)
		{
			if (monthString == Month::monthStringsLong[i])
			{
				return static_cast<Month::Month>(i);
			}
		}
	}
	

	// If month is not found - error
	std::stringstream errMsg;
	errMsg << "Month name not recognised. Name supplied was: " << monthString << std::endl;
	std::string err = errMsg.str();
	throw std::runtime_error(err);

}

Month::Month monthFromString(const std::string& monthString, size_t index)
{
	try
	{
		return monthFromString(monthString);
	}
	catch (const std::exception& e)
	{
		std::stringstream errMsg;
		errMsg << e.what() << "Index of month in csv file: " << index << std::endl;
		std::string err = errMsg.str();
		throw std::runtime_error(err);
	}
}

Month::Month monthFromString(const std::string& monthString, size_t index, const std::string& fname)
{
	try
	{
		return monthFromString(monthString, index);
	}
	catch (const std::exception& e)
	{
		std::stringstream errMsg;
		errMsg << e.what() << "File Name: " << fname << std::endl;
		std::string err = errMsg.str();
		throw std::runtime_error(err);
	}
}

Currency::Currency currencyFromString(const std::string& currencyString)
{
	// Iterate through list of months and return the correct one based on search string size
	if (currencyString.size() == 3)
	{
		for (size_t i = 0; i < Currency::currencyStrings.size(); i++)
		{
			if (currencyString == Currency::currencyStrings[i])
			{
				return static_cast<Currency::Currency>(i);
			}
		}
	}
	else if (currencyString.size() == 1)
	{
		for (size_t i = 0; i < Currency::currencySymbols.size(); i++)
		{
			if (currencyString == Currency::currencySymbols[i])
			{
				return static_cast<Currency::Currency>(i);
			}
		}
	}


	// If currency is not found - error
	std::stringstream errMsg;
	errMsg << "Currency name not recognised. Name supplied was: " << currencyString << std::endl;
	std::string err = errMsg.str();
	throw std::runtime_error(err);
}