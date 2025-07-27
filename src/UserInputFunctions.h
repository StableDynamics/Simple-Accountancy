#pragma once
#include <vector>

#include "BankStatement.h"

void selectedBSOperation(const BankStatement& bankStatement, int operationIndex);

void userActionBankStatements(std::vector<BankStatement>& bankStatementsVec);