///////////////////////////////////////////////////////////
//  BankStatement.h
//  Implementation of the Class BankStatement
//  Created on:      04-Mar-2025 14:33:13
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(BANKSTATEMENT)
#define BANKSTATEMENT

#include <string>

#include "MonthlyTotals.h"

#include "ForwardDecls.h"

/**
 * This class inherits from MonthlyTotals and is meant to contain more advanced 
 * analysis funcitons and display functions
 */
class BankStatement : public MonthlyTotals
{

public:
	BankStatement();
	BankStatement(const std::string& fname);
	virtual ~BankStatement();
	BankStatement(const BankStatement& other) = default; // Copy constructor
	// Maybe add copy constructor and assignment operator here?
	void printStatementSummary(int strLen = 0) const; // Held in BankStatement_PrintFunctions due to the need to convince windows to use UTF8, Prints average by category over the whole statement
	void printPerMonthDetails(int dispType = 0, int strLen = 0) const; // Held in BankStatement_PrintFunctions due to the need to convince windows to use UTF8, Prints a month by month breakdown of the statement with various options for display type

private:
	// Stores monthly averages arranged by currency, and then income or expense, and then individual array values are ItemTypes
	// currency.incomeOrExpense.type
	// Type explained below:
	// 0 - (maxItemTypes - 1) = totals according to ItemType enum
	// end = Totals
	CrIEITAvg avgByType = { {{}} };
	
	// Stores values comparing average monthly income to expenses for each currency 
	AvgIEbyCr avgIncVsExp = {};

	void calculateAvg();
	void printPerriodStart(int strLen = 0, std::string printDesc = "CHANGEME") const; // Prints the header at the start of the reporting sections
	void printPerriodEnd(int strLen = 0, std::string printDesc = "CHANGEME") const; // Prints the header at the end of the reporting sections

};
#endif // !defined(BANKSTATEMENT)
