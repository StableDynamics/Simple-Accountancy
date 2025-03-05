#include "HelpfulFunctions.h"


Month monthFromString(std::string monthString)
{
	if (monthString == "Jan")
	{
		return Month::January;
	}
	else if (monthString == "Feb")
	{
		return Month::February;
	}
	else if (monthString == "Mar")
	{
		return Month::March;
	}
	else if (monthString == "Apr")
	{
		return Month::April;
	}
	else if (monthString == "May")
	{
		return Month::May;
	}
	else if (monthString == "Jun")
	{
		return Month::June;
	}
	else if (monthString == "Jul")
	{
		return Month::July;
	}
	else if (monthString == "Aug")
	{
		return Month::August;
	}
	else if (monthString == "Sep")
	{
		return Month::September;
	}
	else if (monthString == "Oct")
	{
		return Month::October;
	}
	else if (monthString == "Nov")
	{
		return Month::November;
	}
	else if (monthString == "Dec")
	{
		return Month::December;
	}
	else
	{
		throw std::runtime_error("Month not recognised");
	}
}

Currency currencyFromString(std::string currencyString)
{
	if (currencyString == "GBP" || currencyString == "£")
	{
		return Currency::GBP;
	}
	else if (currencyString == "EUR" || currencyString == "€")
	{
		return Currency::EUR;
	}
	else if (currencyString == "USD" || currencyString == "$")
	{
		return Currency::USD;
	}
	else
	{
		throw std::runtime_error("Currency not recognised");
	}
}