///////////////////////////////////////////////////////////
//  BankName.h
//  Implementation of the Enumeration BankName
//  Created on:      05-Mar-2025 11:00:07
//  Original author: matth
///////////////////////////////////////////////////////////

#if !defined(BANKNAME)
#define BANKNAME

#include <vector>
#include <string_view>

/*
 * What bank is the statement from?
 */
namespace BankName
{
	enum BankName
	{
		Nationwide_UK_2024,
		Natwest_UK,
		Halifax_UK,
		Tide_UK,
		maxBanks
	};

	const std::vector<std::string_view> bankNameStrings3Len =
	{
		"Nat",
		"Nat",
		"Hal",
		"Tid"
	};

	const std::vector<std::string_view> bankNameStringsOther =
	{
		"Nationwide UK",
		"Natwest UK",
		"Halifax UK",
		"Tide UK"
	};
}

#endif // !defined(BANKNAME)
