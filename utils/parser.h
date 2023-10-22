#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include <vector>

namespace PoEParser 
{
	struct ItemModData
	{
		std::string modifierType;
		std::string modifierOfName;
		int modifierTier;
		std::vector<std::string> modifierRolled;
		std::vector<std::string> modifierInfluence;
	};

	std::string parseItem(std::string& rawItemData);
	std::vector<ItemModData> parseMods(std::string& parsedItemData);
	int parseTier(std::string line);
	void printMods(std::vector<PoEParser::ItemModData>& mods);
};
