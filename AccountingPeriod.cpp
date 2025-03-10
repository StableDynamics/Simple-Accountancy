///////////////////////////////////////////////////////////
//  AccountingPeriod.cpp
//  Implementation of the Class AccountingPeriod
//  Created on:      07-Mar-2025 15:30:53
//  Original author: matth
///////////////////////////////////////////////////////////

#include "AccountingPeriod.h"

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Public functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AccountingPeriod::AccountingPeriod() {
}

AccountingPeriod::AccountingPeriod(const std::vector<LineValue>& expenses){
	// Assign member variables
	startDay	= expenses.begin()->day;
	startMonth	= expenses.begin()->month;
	startYear	= expenses.begin()->year;
	endDay		= std::prev(expenses.end())->day;
	endMonth	= std::prev(expenses.end())->month;
	endYear		= std::prev(expenses.end())->year;
	populateDescription();
}


AccountingPeriod::~AccountingPeriod(){

}


/**
 * Provides a string view of the descriptionString
 */
std::string_view AccountingPeriod::getDescriptionString_sv(int idx){
	// Return a string_view of the requested description based on the index
	// 0 = 3Len string
	// 1 = Long string
	// 2 = Num string
	switch (idx)
	{
	case 0:
		return std::string_view(descriptionString3Len);
	case 1:
		return std::string_view(descriptionStringLong);
	case 2:
		return std::string_view(descriptionStringNum);
	default:
		// If caller uses wrong value
		std::stringstream errMsg;
		errMsg << "AccountingPeriod::getDescriptionString_sv(int idx) does not recognise idx of " << idx << "."
			<< " Recognised idx values are 0 for 3Len, 1 for Long, and 2 for Num." << std::endl;
		std::string err = errMsg.str();
		throw std::runtime_error(err);
	}
}

/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* Private functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Populates the description string and string_view based on the member variables
 */
void AccountingPeriod::populateDescription() {
	// Populate the description strings
	descriptionString3Len = std::string(std::to_string(startDay) + "/" + enumToString<Month::Month>(startMonth, "3Len") + "/" + std::to_string(startYear)
		+ " to " +
		std::to_string(endDay) + "/" + enumToString<Month::Month>(endMonth, "3Len") + "/" + std::to_string(endYear));
	descriptionStringLong = std::string(std::to_string(startDay) + "/" + enumToString<Month::Month>(startMonth, "Other") + "/" + std::to_string(startYear)
		+ " to " +
		std::to_string(endDay) + "/" + enumToString<Month::Month>(endMonth, "Other") + "/" + std::to_string(endYear));
	descriptionStringNum = std::string(std::to_string(startDay) + "/" + std::to_string(static_cast<int>(startMonth)) + "/" + std::to_string(startYear)
		+ " to " +
		std::to_string(endDay) + "/" + std::to_string(static_cast<int>(endMonth)) + "/" + std::to_string(endYear));
}