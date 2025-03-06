#if !defined(HELPFULFUNCTIONS)
#define HELPFULFUNCTIONS
#include <string>
#include <stdexcept>
#include <sstream>

#include "Month.h"
#include "Currency.h"

// String to Enum convertions
Month::Month monthFromString(const std::string& monthString);

Month::Month monthFromString(const std::string& monthString, size_t index);

Month::Month monthFromString(const std::string& monthString, size_t index, const std::string& fname);

Currency::Currency currencyFromString(const std::string& currencyString);


#endif