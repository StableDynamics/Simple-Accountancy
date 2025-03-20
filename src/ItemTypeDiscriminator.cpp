#include "ItemTypeDiscriminator.h"

#include <string>
#include "HelpfulFunctions.h"

// Stub is a stub
ItemType::ItemType determineItemType(const std::string_view description)
{
	// Debug stub to trigger enumFromString with ItemType
	ItemType::ItemType debugVal = enumFromString<ItemType::ItemType>("Other");
	return ItemType::Other;
}