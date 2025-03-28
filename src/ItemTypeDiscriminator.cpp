#include "ItemTypeDiscriminator.h"

#include <vector>

#include "GlobalDiscriminatorConfiguration.h"
#include "HelpfulFunctions.h"
#include "json.hpp"

// Stub is a stub
ItemType::ItemType determineItemType(const std::string_view description)
{
	using json = nlohmann::json;

	// Data values
	std::array<int, static_cast<int>(ItemType::maxItemTypes)> exactTypeTally{}; // Holds the tally of the itemTypes that are exact matches
	std::array<int, static_cast<int>(ItemType::maxItemTypes)> partialTypeTally{}; // Holds the tally of the itemTypes that are partial matches
	auto configData = globalDiscriminatorConfiguration.getConfigData();
	auto configDataKeys = configData.items();
	std::string subType;
	int jsonItemIdx{ 0 };
	ItemType::ItemType itemEnum{ ItemType::Other };

	for (auto itemType : globalDiscriminatorConfiguration.getConfigData())
	{
		for (auto comparisonDesc : itemType.items())
		{
			break;
		}

		//if (itemType.find(description) != itemType.end())	// Exact match
		//{
		//	exactTypeTally[itemEnum] += 1;
		//}
		//else												// Partial match
		//{
		//	for (auto comparisonDesc : itemType.items())
		//	{
		//		if (description.find(comparisonDesc.key()) != std::string::npos)
		//		{
		//			partialTypeTally[itemEnum] += 1;
		//		}
		//	}
		//}
	}

	// Debug stub to trigger enumFromString with ItemType
	ItemType::ItemType debugVal = enumFromString<ItemType::ItemType>("Other");
	return ItemType::Other;
}