#if !defined(HELPFULFUNCTIONS)
#define HELPFULFUNCTIONS
#include <string>
#include <stdexcept>

#include "Month.h"
#include "Currency.h"

// string to Enum convertions
Month monthFromString(std::string monthString);

Currency currencyFromString(std::string currencyString);


#endif