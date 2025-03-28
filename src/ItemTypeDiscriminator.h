#pragma once

#include <string_view>

#include "ItemType.h"

/*
* The ItemTypeDiscriminator will work out the type of the bank statement line item be nice if it 
* was worked out by an AI... I can dream...
*
* Currently it is just a stub
*/
ItemType::ItemType determineItemType(const std::string_view description);

