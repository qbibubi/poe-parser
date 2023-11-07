#include "parser.h"


using namespace PoEParser;


std::string 
parseItem( std::string& rawItemData ) 
{
  const std::string delimiter = "--------";
  auto startingPosition = rawItemData.find( delimiter );
  std::vector<size_t> vec;

  // Append a delimiter to a typical rare item
  // (Non-fractured, non-influenced, non-synthesized, etc.)
  if ( rawItemData.at( rawItemData.length() - 1 ) != '-' ) 
  {
    rawItemData += delimiter;
  }

  while ( startingPosition != std::string::npos )
  {
    vec.push_back( startingPosition );
    startingPosition = rawItemData.find( delimiter, startingPosition + 1 );
  }

  const auto start = vec.at( vec.size() - 2 );
  const auto end = vec.at( vec.size() - 1 );
  const auto parsedItemData = rawItemData.substr( start + delimiter.size(), end - start - delimiter.size() );

  std::istringstream stream( parsedItemData );
  std::string line;
  std::string filteredItemData;

  // Get rid of Searing Exarch and Eater of Worlds mods
  while ( std::getline( stream, line ) ) 
  {
    if ( line.find("Item") != line.length() - 4 ) 
    {
      filteredItemData += line + '\n';
    }
  }

  return filteredItemData;
}


std::vector<ItemModData> 
parseMods( const std::string& parsedItemData ) 
{
  std::istringstream stream( parsedItemData );
  std::string line{};
  std::vector<ItemModData> mods{};
  ItemModData mod{ 0 };
  int i = 0;

  while( std::getline( stream, line ) )
  {
    // find mods
    if ( line.find('{') == 0 )
    {
      if ( i++ != 0 ) 
      {
        mods.push_back( mod );
      } 

      // clear memory for struct
      // memset(&mod, '\0', sizeof(mod));
      
      // set modifier type to prefix or suffix
      mod.modifierType = line.find( "Prefix" ) != std::string::npos ? std::string( "Prefix" ) : std::string( "Suffix" );

      char modifierDelimiter = '\"';
      auto modifierPos = line.find( modifierDelimiter );
      std::vector<size_t> modifierVec;

      while ( modifierPos != std::string::npos )
      {
        modifierVec.push_back( modifierPos );
        modifierPos = line.find( modifierDelimiter, modifierPos + 1 );
      }

      const auto firstQuote = modifierVec.at( 0 );
      const auto secondQuote = modifierVec.at( 1 );
      if (firstQuote != std::string::npos && secondQuote != std::string::npos)
        mod.modifierOfName = line.substr( firstQuote + 1, secondQuote - firstQuote - 1 );
      

      mod.modifierTier = parseTier( line );
      continue;
    }

    mod.modifierRolled.push_back( line );
  }

  mods.push_back( mod );

  return mods;
}


int 
parseTier( const std::string line ) 
{
  const auto tierIndex = line.find( "Tier" );

  if ( tierIndex != std::string::npos )
  {
    const auto firstTierElement = line.at( tierIndex + 6 );
    const auto secondTierElement = line.at( tierIndex + 7 );
    std::string tier;

    tier += firstTierElement;

    if ( secondTierElement != ')' )
      tier += secondTierElement;
    

    int modifierTier = atoi( tier.c_str() );
    return modifierTier;
  }

  return 0;
}


void 
printMods( const std::vector<ItemModData>& mods )
{
  if ( mods.begin() == mods.end() )
  {
    return;
  }


  for ( const auto& mod : mods )
  {
    std::cout 
      << mod.modifierType << '\n' 
      << mod.modifierTier << '\n' 
      << mod.modifierOfName << 
    std::endl;

    for (auto submod : mod.modifierRolled)
        std::cout << "> " + submod << std::endl;

    std::cout << "-----" << std::endl;
  }
}
