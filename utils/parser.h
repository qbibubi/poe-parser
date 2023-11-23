#pragma once


#include <iostream>
#include <string>
#include <vector>
#include <sstream>


namespace PoEParser 
{

	struct ItemModData
	{
		int modifierTier;
		std::string modifierType;
		std::string modifierOfName;
		std::vector<std::string> modifierRolled;
		std::vector<std::string> modifierInfluence;
	};

	std::string parseItem( const std::string& rawItemData );
	std::vector<ItemModData> parseMods( const std::string& parsedItemData );
	int parseTier( std::string line );
	void printMods( const std::vector<ItemModData>& mods );

};
