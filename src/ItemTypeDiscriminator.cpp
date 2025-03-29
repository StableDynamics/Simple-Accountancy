#include "ItemTypeDiscriminator.h"

#include <array>
#include <sstream>
#include <string>
#include <vector>

#include "GlobalDiscriminatorConfiguration.h"
#include "HelpfulFunctions.h"
#include "ItemType.h"
#include "json.hpp"

// Determines the item type based on string searches
void determineItemType(LineValue& lineVal)
{
	using json = nlohmann::json;

	// Data values
	std::vector<std::string> itemTypeStrJSON;
	for (auto& item : globalDiscriminatorConfiguration.getConfigData().items())
		itemTypeStrJSON.emplace_back(item.key()); // Pulls ItemType values in order from JSON

	std::array<int, static_cast<int>(ItemType::maxItemTypes)> exactTypeTally{}; // Holds the tally of the itemTypes that are exact matches
	std::array<int, static_cast<int>(ItemType::maxItemTypes)> partialTypeTally{}; // Holds the tally of the itemTypes that are partial matches
	std::vector<std::string> subtypeStrings;
	int jsonItemIdx{ 0 };

	for (auto& item : globalDiscriminatorConfiguration.getConfigData())
	{
		for (auto& searchTerm : item)
		{
			// Match if the description string applies to income, expense, or both. 
			// Array index for searchTerm is as follows:
			// 0 = User defined search term for description
			// 1 = Income is Income, Expense is Expense, Income or Expense is either
			// 2 = User defined sub-type
			if (searchTerm.at(1) == enumToString(lineVal.incomeOrExpense) || searchTerm.at(1) == globalDiscriminatorConfiguration.getIorEVal().back())
			{
				// Exact match
				if (lineVal.description == searchTerm.at(0).get<std::string>())
				{
					exactTypeTally[jsonItemIdx] += 1;
					subtypeStrings.emplace_back(searchTerm.at(2));
					// ASSUMPTION: once an exact match is found no searching required anymore
					goto endsearch;
				}
				// Partial match
				else if (lineVal.description.find(searchTerm.at(0).get<std::string>()) != std::string::npos)
				{
					partialTypeTally[jsonItemIdx] += 1;
					subtypeStrings.emplace_back(searchTerm.at(2));
				}
			}
		}
		jsonItemIdx += 1;
	}
	endsearch:
	
	if (*std::max_element(exactTypeTally.begin(), exactTypeTally.end()) != 0) // Exact Match
	{
		lineVal.itemType = enumFromString<ItemType::ItemType>(itemTypeStrJSON[jsonItemIdx]);
	}
	else if (*std::max_element(partialTypeTally.begin(), partialTypeTally.end()) != 0) // If partial matches are found
	{
		// ASSUMPTION: Whichever one scores the most use that
		auto [minIter, maxIter] = std::minmax_element(partialTypeTally.begin(), partialTypeTally.end());
		auto maxIdx = std::distance(partialTypeTally.begin(), maxIter);
		lineVal.itemType = enumFromString<ItemType::ItemType>(itemTypeStrJSON[maxIdx]);
	}
	else // Everything else
		lineVal.itemType = ItemType::Other;

	if (lineVal.itemType == ItemType::maxItemTypes)
	{
		std::stringstream errMsg;
		errMsg << "LineItem " << lineVal.description << " has errored and been left as maxItemTypes enum." << std::endl;
		throw std::runtime_error(errMsg.str());
	}
}