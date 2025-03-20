#include "HelpfulFunctions.h"

/*
* Allow conversion between u8string and string so that cout can print it to console
*/
#if defined(__cpp_lib_char8_t)
std::string fromu8String(const std::u8string& s) {
    return std::string(s.begin(), s.end());
}
#endif