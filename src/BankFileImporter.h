///////////////////////////////////////////////////////////
//  BankFileImporter.h
//  Implementation of the Class BankFileImporter
//  Created on:      11-Mar-2025 22:05:24
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(BANKFILEIMPORTER)
#define BANKFILEIMPORTER

#include <functional>
#include <string>
#include <vector>

#include "AccountingPeriod.h"
#include "BankName.h"
#include "LineValue.h"

/*
* This class receives a filename and imports it into a series of LineValues based on which bank the statement is from
*/
class BankFileImporter
{

public:
	BankFileImporter();
	BankFileImporter(const std::string& fname);
	virtual ~BankFileImporter();
	BankFileImporter(const BankFileImporter& other) = default; // Copy constructor
	BankFileImporter(BankFileImporter&& other) noexcept; // Move constructor

	const std::string getBankName() const;
	const std::string_view getAccountName() const;
	const std::vector<std::reference_wrapper<LineValue>> getRawExpRef() const;
	const AccountingPeriod& getAccountingPeriod() const;

	// Overloaded operators
	BankFileImporter& operator=(BankFileImporter other);

	// Friend functions
	friend void swap(BankFileImporter& first, BankFileImporter& second);

private:
	BankName::BankName bankName{ BankName::maxBanks };
	std::string accountName = "Current Account"; // Default is that it is a current account
	std::vector<LineValue> rawExpenses = {};
	std::vector<std::reference_wrapper<LineValue>> rawExpensesRef = {};
	AccountingPeriod accountingPeriod;

	std::vector<std::vector<std::string>> importFile(const std::string& fname);
	void processRawFStream(const std::vector<std::vector<std::string>>& content, const std::string& fname);
	void determineBank(const std::vector<std::vector<std::string>>& content);
	void nationwideUKProcessing(const std::vector<std::vector<std::string>>& content, const std::string& fname);
	void natwestUKProcessing(const std::vector<std::vector<std::string>>& content, const std::string& fname);
	void tideUKProcessing(const std::vector<std::vector<std::string>>& content, const std::string& fname);
	void makeSureDataIsAscending();
	virtual void refreshRefs();

};
#endif // !defined(BANKFILEIMPORTER)
