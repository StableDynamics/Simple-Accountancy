///////////////////////////////////////////////////////////
//  AccountingPeriod.cpp
//  Implementation of the Class AccountingPeriod
//  Created on:      07-Mar-2025 15:30:53
//  Original author: matth
///////////////////////////////////////////////////////////

#include "AccountingPeriod.h"

#include <sstream>
#include <stdexcept>
#include <utility>

#include "HelpfulFunctions.h"

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


/*
* Move constructor
*/
AccountingPeriod::AccountingPeriod(AccountingPeriod&& other) noexcept
: AccountingPeriod() {
	swap(*this, other);
}


/**
 * Provides a string view of the descriptionString
 */
const std::string_view AccountingPeriod::getDescriptionString_sv(int idx) const{
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


// Overloaded operators
AccountingPeriod& AccountingPeriod::operator=(AccountingPeriod other) {
	swap(*this, other);

	return *this;
}

// Friend Functions
void swap(AccountingPeriod& first, AccountingPeriod& second) {
	using std::swap; // Allows association to the std::swap function

	swap(first.startDay, second.startDay);
	swap(first.startMonth, second.startMonth);
	swap(first.startYear, second.startYear);
	swap(first.endDay, second.endDay);
	swap(first.endMonth, second.endMonth);
	swap(first.endYear, second.endYear);
	swap(first.descriptionString3Len, second.descriptionString3Len);
	swap(first.descriptionStringLong, second.descriptionStringLong);
	swap(first.descriptionStringNum, second.descriptionStringNum);
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