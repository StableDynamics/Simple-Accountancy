#include "TextConversion.h"

#include <cstdlib>
#include <wchar.h>

/*
* Allow conversion between u8string and string so that cout can print it to console
* Did have the Vec converters as a lambda within BankStatement_WindowsStuff but thought they would be more useful here
*/
#if defined(__cpp_lib_char8_t)
const std::string u8StrToStr(const std::u8string& s) {
    return std::string(s.begin(), s.end());
}

const std::vector<std::string> u8StrVecToStrVec(const std::vector<std::u8string>& s) {
    std::vector<std::string> strConv;
    for (auto u8Str : s)
        strConv.emplace_back(u8StrToStr(u8Str));
    return strConv;
}

const std::vector<std::string> u8StrvVecToStrVec(const std::vector<std::u8string_view>& s) {
    std::vector<std::string> strvConv;
    for (auto u8Strv : s)
        strvConv.emplace_back(u8StrToStr(std::u8string(u8Strv)));
    return strvConv;
}
#endif

// String conversion functions
std::string wc_tToString(const wchar_t* wstr) {
    size_t wstrSz = wcslen(wstr) + 1; // Work out length of string with a +1 for null character
    size_t convertedChars = 0;

    // Allocate two bytes for each character for multi-byte string
    const size_t chSz = wstrSz * 2;

    char* newChar{ new char[chSz] }; // eugh

    // Copy across the wstr to newChar
    wcstombs_s(&convertedChars, newChar, chSz, wstr, _TRUNCATE);

    // Convert to string
    std::string convString{ newChar };

    // Delete pointer
    delete[]newChar;

    return convString;
}


std::string wstringToString(const std::wstring wstr) {
    size_t convertedChars = 0;

    // Allocate two bytes for each character for multi-byte string
    const size_t chSz = (wstr.size() + 1) * 2;

    char* newChar{ new char[chSz]}; // eugh

    // Copy across the wstr to newChar
    wcstombs_s(&convertedChars, newChar, chSz, wstr.c_str(), _TRUNCATE);

    // Convert to string
    std::string convString{ newChar };

    // Delete pointer
    delete[]newChar;

    return convString;
}