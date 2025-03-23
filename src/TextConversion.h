#pragma once
// Functions specific to Windows deployments to (hopefully) make things work reliably

#include <string>
#include <vector>
#include <version>

/*
* Allow conversion between u8string and string so that cout can print it to console
*/
#if defined(__cpp_lib_char8_t)
const std::string u8StrToStr(const std::u8string& s);
const std::vector<std::string> u8StrVecToStrVec(const std::vector<std::u8string>& s);
const std::vector<std::string> u8StrvVecToStrVec(const std::vector<std::u8string_view>& s);
#endif

/*
* Convert between Wide characters to std::String and vice versa
*/
std::string wc_tToString(const wchar_t* wstr);
std::string wstringToString(const std::wstring wstr);