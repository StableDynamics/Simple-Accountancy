///////////////////////////////////////////////////////////
//  LineValue.cpp
//  Implementation of the Class LineValue
//  Created on:      03-Mar-2025 15:20:29
//  Original author: matth
///////////////////////////////////////////////////////////

#include "LineValue.h"

/*
* Prints a string summary of the LineValue allowing selection of month sizes and currency display
*/
std::string LineValue::lineValueSummary(int threeOrOtherMonth, int threeOrOtherCurrency) const{
	// 0 = 3Len
	// 1 = Other
	if ((threeOrOtherCurrency == 0 || threeOrOtherCurrency == 1) && (threeOrOtherMonth == 0 || threeOrOtherMonth == 1)) {}
	else
	{
		std::stringstream errMsg;
		errMsg << "LineValue::lineValueSummary is being requested with incorrect values. Acceptable values are 0 or 1, requested values are: threeOrOtherMonth = " <<
			threeOrOtherMonth << ", threeOrOtherCurrency = " << threeOrOtherCurrency << "." << std::endl;
		std::string err = errMsg.str();
		throw std::runtime_error(err);
	}

	std::stringstream msg;
	// Month Switch
	switch (threeOrOtherMonth)
	{
	case 0: // 3Len
		msg << day << "/" << enumToString(month, "3Len");
		break;
	case 1: // Other
		msg << day << "/" << enumToString(month, "Other");
		break;
	default:
		break;
	}
	
	msg << "/" << year << ", " << description << ", ";

	// Currency switch
	switch (threeOrOtherCurrency)
	{
	case 0: // 3Len
		msg << enumToString(currency, "3Len");
		break;
	case 1: // Other
		msg << enumToString(currency, "Other");
		break;
	default:
		break;
	}

	msg << ", " << paidIn << ", " << paidOut << ", " << balance <<
		", " << enumToString(incomeOrExpense, "Other") << ", " << itemType << "." << std::endl;
	return std::string(msg.str());
}