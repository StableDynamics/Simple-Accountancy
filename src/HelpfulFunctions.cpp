#include "HelpfulFunctions.h"

#include <map>

std::string mostOccurredString(const std::vector<std::string>& stringVec) {
	std::string mostOccurredString;
	int mostOccurredCount{ 0 };
	std::map<std::string, int> stringCountMap;
	for (const auto& str : stringVec)
	{
		stringCountMap[str]++;
		if (stringCountMap[str] > mostOccurredCount)
		{
			mostOccurredCount = stringCountMap[str];
			mostOccurredString = str;
		}
	}
	return mostOccurredString;
}