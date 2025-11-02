
#include <iostream>
#include <string>
#include <tuple>

#include "UserInputFunctions.h"

void selectedBSOperation(const BankStatement& bankStatement, int operationIndex)
{
	switch (operationIndex)
	{
	case 0: // Print statement summary
		std::cout << "Summary for " << bankStatement.getBankName() << " for period: "
			<< bankStatement.getAccountingPeriod().getDescriptionString_sv() << std::endl;
		bankStatement.printStatementSummary();
		break;
	case 1: // Print statement details per month - Categories Only
		std::cout << "Details per month (Categories Only) for " << bankStatement.getBankName() << " for period: "
			<< bankStatement.getAccountingPeriod().getDescriptionString_sv() << std::endl;
		bankStatement.printPerMonthDetails(0); // 0 for top level categories only
		break;
	case 2: // Print statement details per month - Categories and Sub-Categories
		std::cout << "Details per month (Categories and Sub-Categories) for " << bankStatement.getBankName() << " for period: "
			<< bankStatement.getAccountingPeriod().getDescriptionString_sv() << std::endl;
		bankStatement.printPerMonthDetails(1); // 1 for categories and sub-categories
		break;
	case 3: // Print statement details per month - All Details
		std::cout << "Details per month (All Details) for " << bankStatement.getBankName() << " for period: "
			<< bankStatement.getAccountingPeriod().getDescriptionString_sv() << std::endl;
		bankStatement.printPerMonthDetails(2); // 2 for all details
		break;
	default:
		std::cout << "Invalid operation selected." << std::endl;
		break;
	}
}

void userActionBankStatements(std::vector<BankStatement>& bankStatementsVec)
{
	std::string input;
	int bsIdx{ 0 };
	int chosenBSIdx{ 0 };
	int chosenOperIdx{ 0 };

	// Acceptable User Operations in a tuple
	std::tuple<int, std::string> userOperations[] = {
		{0, "Print statement summary"},
		{1, "Print statement details per month - Categories Only"},
		{2, "Print statement details per month - Categories and Sub-Categories"},
		{3, "Print statement details per month - All Details"}
	};

	while (input != "exit" && input != "x")
	{
		bsIdx = 0; chosenOperIdx = 0;// Reset indexes for each loop

		std::cout << "Please select the statement you would like to take further action on " << std::endl <<
			"using the number in [], or type e(x)it to exit:" << std::endl << std::endl;

		for (auto& bs : bankStatementsVec)
		{
			std::cout << "[" << bsIdx << "] " << "Statement: " << bs.getBankName() << ", Period : " << bs.getAccountingPeriod().getDescriptionString_sv() << std::endl;
			bsIdx += 1;
		}
		std::cout << "[" << bsIdx << "] " << "All" << std::endl << std::endl;

		std::cout << "Enter your choice (or e(x)it): ";
		std::getline(std::cin, input);
		std::string bsChoice = input;

		try
		{
		ProcessChoice:
			if (input == "exit" || input == "x")
			{
				std::cout << "Exiting...." << std::endl << std::endl;
				continue; // Exit the loop
			}
			else if (std::stoi(bsChoice) <= bsIdx && std::stoi(bsChoice) >= 0)
			{
				chosenBSIdx = std::stoi(bsChoice);
				// Select the operation to perform on the selected bank statement
				std::cout << std::endl << "Please select the operation you would like to perform:" << std::endl << std::endl;

				for (const auto& oper : userOperations)
				{
					std::cout << "[" << std::get<0>(oper) << "] " << std::get<1>(oper) << std::endl;
				}
				std::cout << std::endl;
				std::cout << "Enter your choice: ";

				std::getline(std::cin, input);
				if (input == "exit" || input == "x")
				{
					std::cout << "Exiting...." << std::endl << std::endl;
					continue; // Exit the loop
				}
				else if (std::stoi(input) < static_cast<int>(std::size(userOperations)) && std::stoi(input) >= 0) // Make sure the operation index is valid
				{
					chosenOperIdx = std::stoi(input);

					if (chosenBSIdx < bsIdx && chosenBSIdx >= 0) // Select one of the statements
					{
						selectedBSOperation(bankStatementsVec[chosenBSIdx], chosenOperIdx);
					}
					else if (chosenBSIdx == bsIdx) // Select all statements
					{
						for (auto& bs : bankStatementsVec)
						{
							selectedBSOperation(bs, chosenOperIdx);
						}
					}
				}
				else
				{
					std::cout << "Invalid operation choice. Please try again." << std::endl << std::endl;
					goto ProcessChoice; // Restart the loop for valid input as part of the user operation selection
				}
			}
			else
			{
				std::cout << "Invalid input. Please try again." << std::endl << std::endl;
			}
		}
		catch (const std::exception&)
		{
			std::cout << "Invalid input. Please try again." << std::endl << std::endl;
		}

	}
}
