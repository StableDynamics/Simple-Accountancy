///////////////////////////////////////////////////////////
//  AccountingPeriod.cpp
//  Implementation of the Class AccountingPeriod
//  Created on:      07-Mar-2025 15:30:53
//  Original author: matth
///////////////////////////////////////////////////////////

#include "AccountingPeriod.h"


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
 * Populates the description string and string_view based on the member variables
 */
void AccountingPeriod::populateDescription(){
	// Populate the description string using the longform of the month
	descriptionString = std::string(std::to_string(startDay) + "/" + enumToString<Month::Month>(startMonth, "3Len") + "/" + std::to_string(startYear)
	+ " to " +
		std::to_string(endDay) + "/" + enumToString<Month::Month>(endMonth, "3Len") + "/" + std::to_string(endYear));
}


/**
 * Provides a string view of the descriptionString
 */
std::string_view AccountingPeriod::getDescriptionString_ptr(){
	return std::string_view(descriptionString);
}