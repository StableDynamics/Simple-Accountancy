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


class BankFileImporter
{

public:
	BankFileImporter();
	BankFileImporter(const std::string& fname);
	virtual ~BankFileImporter();

	const std::string getBankName() const;
	const std::vector<std::reference_wrapper<LineValue>> getRawExpRef() const;
	const AccountingPeriod& getAccountingPeriod() const;

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

};
#endif // !defined(BANKFILEIMPORTER)
