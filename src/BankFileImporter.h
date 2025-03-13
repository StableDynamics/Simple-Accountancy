///////////////////////////////////////////////////////////
//  BankFileImporter.h
//  Implementation of the Class BankFileImporter
//  Created on:      11-Mar-2025 22:05:24
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(BANKFILEIMPORTER)
#define BANKFILEIMPORTER

#include <string_view>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <functional>

#include "AccountingPeriod.h"
#include "LineValue.h"
#include "HelpfulFunctions.h"
#include "ItemTypeDiscriminator.h"

/*
* This class receives a filename and imports it into a series of LineValues based on which bank the statement is from
*/
class BankFileImporter
{

public:
	BankFileImporter();
	BankFileImporter(const std::string& fname);
	virtual ~BankFileImporter();
	BankFileImporter(const BankFileImporter& other); // Copy constructor
	BankFileImporter(BankFileImporter&& other) noexcept; // Move constructor

	const std::string getBankName() const;
	const std::vector<std::reference_wrapper<LineValue>> getRawExpRef() const;
	const AccountingPeriod& getAccountingPeriod() const;

	// Overloaded operators
	BankFileImporter& operator=(BankFileImporter other);

	// Friend functions
	friend void swap(BankFileImporter& first, BankFileImporter& second);

private:
	BankName::BankName bankName{ BankName::maxBanks };
	std::vector<LineValue> rawExpenses = {};
	std::vector<std::reference_wrapper<LineValue>> rawExpensesRef = {};
	AccountingPeriod accountingPeriod;

	std::vector<std::vector<std::string>> importFile(const std::string& fname);
	void processRawFStream(const std::vector<std::vector<std::string>>& content, const std::string& fname);
	void determineBank(const std::vector<std::vector<std::string>>& content);
	void nationwideUKProcessing(const std::vector<std::vector<std::string>>& content, const std::string& fname);
	void makeSureDataIsAscending();
	virtual void refreshRefs();

};
#endif // !defined(BANKFILEIMPORTER)
