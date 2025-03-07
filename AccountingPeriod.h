///////////////////////////////////////////////////////////
//  AccountingPeriod.h
//  Implementation of the Class AccountingPeriod
//  Created on:      07-Mar-2025 15:30:53
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(ACCOUNTINGPERIOD)
#define ACCOUNTINGPERIOD

#include <string>
#include <string_view>
#include <stdexcept>
#include <iterator>

#include "Month.h"
#include "LineValue.h"
#include "HelpfulFunctions.h"

/**
 * Contains the accounting period of the statement contained in the BankStatement
 */
class AccountingPeriod
{

public:
	AccountingPeriod();
	AccountingPeriod(const std::vector<LineValue>* expenses_ptr);
	virtual ~AccountingPeriod();

	std::string_view getDescriptionString_ptr();

private:
	int startDay{ 0 };
	Month::Month startMonth{ Month::maxMonths };
	int startYear{ 0 };
	int endDay{ 0 };
	Month::Month endMonth{ Month::maxMonths };
	int endYear{ 0 };
	std::string descriptionString{ "" };

	void populateDescription();

};
#endif // !defined(ACCOUNTINGPERIOD)
