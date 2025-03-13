#pragma once
#include <string_view>

// If C++ version is higher than or equal to 202002L, include source_location
#if __cplusplus >= 202002L
# include <source_location>
#endif

/*
* Return the name of the typesupplied as a string
*/
template <typename T> constexpr std::string_view getTypeName();

template <>
constexpr std::string_view getTypeName<void>() { return "void"; }

namespace Detail
{
	using typeNameProber = void;

	template <typename T>
	// Returns the full typed name based on compiler-specific functions
	constexpr std::string_view getWrappedTypeName()
	{
	#if __cplusplus >= 202002L
			return std::source_location::current().function_name();
	#else
	# if defined(__clang__) || defined(__GNUC__)
			return __PRETTY_FUNCTION__;
	# elif defined(_MSC_VER)
			return __FUNCSIG__;
	# else
			error "Unknown compiler";
	# endif
	#endif
	}

	// Returns the length of the prefix of the type name
	constexpr std::size_t getWrappedTypeNamePrefixLength()
	{
		return getWrappedTypeName<typeNameProber>().find(getTypeName<typeNameProber>());
	}

	// Returns the length of the suffix of the type name
	constexpr std::size_t getWrappedTypeNameSuffixLength()
	{
		return getWrappedTypeName<typeNameProber>().length() - 
			getWrappedTypeNamePrefixLength() - getTypeName<typeNameProber>().length();
	}
}

template <typename T>
// To use it you have to do getTypeName<Type>() where Type is the type being used in the template
// eg getTypeName<const int>() will return "const int"
constexpr std::string_view getTypeName()
{
	// Get the full type name including prefixes and siffixes
	constexpr auto wrappedName = Detail::getWrappedTypeName<T>();
	constexpr auto prefixLength = Detail::getWrappedTypeNamePrefixLength();
	constexpr auto suffixLength = Detail::getWrappedTypeNameSuffixLength();

	constexpr auto typeNameLength = wrappedName.length() - prefixLength - suffixLength;

	return wrappedName.substr(prefixLength, typeNameLength);
}
