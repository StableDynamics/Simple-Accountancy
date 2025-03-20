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

#include "Month.h"
#include "LineValue.h"

/**
 * Contains the accounting period of the statement contained in the BankStatement
 */
class AccountingPeriod
{

public:
	AccountingPeriod();
	AccountingPeriod(const std::vector<LineValue>& expenses);
	virtual ~AccountingPeriod();
	AccountingPeriod(const AccountingPeriod& other) = default; // Copy constructor
	AccountingPeriod(AccountingPeriod&& other) noexcept; // Move constructor

	const std::string_view getDescriptionString_sv(int idx) const;

	// Overloaded operators
	AccountingPeriod& operator=(AccountingPeriod other);

	// Friend functions
	friend void swap(AccountingPeriod& first, AccountingPeriod& second);

private:
	int startDay{ 0 };
	Month::Month startMonth{ Month::maxMonths };
	int startYear{ 0 };
	int endDay{ 0 };
	Month::Month endMonth{ Month::maxMonths };
	int endYear{ 0 };
	std::string descriptionString3Len{ "" };
	std::string descriptionStringLong{ "" };
	std::string descriptionStringNum{ "" };

	void populateDescription();

};
#endif // !defined(ACCOUNTINGPERIOD)
