#include "ItemTypeDiscriminator.h"

#include <fstream>

#include "HelpfulFunctions.h"
#include "json.hpp"

// Stub is a stub
ItemType::ItemType determineItemType(const std::string_view description)
{
	// Debug stub to trigger enumFromString with ItemType
	ItemType::ItemType debugVal = enumFromString<ItemType::ItemType>("Other");
	return ItemType::Other;
}



/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* JSON functions
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
* Checks to see if a file is present, if not creates a basic example in the working directory
*/
void jsonFilePresent() {
	// See if the file can be opened
	const std::string fname{ ".\\itemtypelist.json" };
	std::ifstream file(fname, std::ifstream::in);
	if (!file.is_open())
	{

	}
	else
	{
		// Load data


		file.close();
	}
}