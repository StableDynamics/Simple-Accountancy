#include "ItemTypeDiscriminator.h"

#include "GlobalDiscriminatorConfiguration.h"
#include "HelpfulFunctions.h"
#include "json.hpp"

// Stub is a stub
ItemType::ItemType determineItemType(const std::string_view description)
{
	using json = nlohmann::json;

	// Data values
	std::string subType;
	int itemEnum{ 0 };

	for (auto itemType : globalDiscriminatorConfiguration.getConfigData())
	{
		if (itemType.find(description) != itemType.end())	// Exact match
		{
			break;
		}
		else												// Partial match
		{
			for (auto comparisonDesc : itemType.items())
			{
				if (description.find(comparisonDesc.key()) != std::string::npos)
				{
					break;
				}
			}
		}
		itemEnum += 1;
	}

	// Debug stub to trigger enumFromString with ItemType
	ItemType::ItemType debugVal = enumFromString<ItemType::ItemType>("Other");
	return ItemType::Other;
}