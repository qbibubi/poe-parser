#include "utils/parser.h"
#include "utils/eventHandler.h"

const std::string rawItemData = 
  R"(Item Class: Wands
  Rarity: Magic
  Discharging Imbued Wand of Shocking
  --------
  Wand
  Physical Damage: 29-53
  Critical Strike Chance: 7.00%
  Attacks per Second: 1.50
  --------
  Requirements:
  Level: 59
  Int: 188
  --------
  Sockets: B-R-B 
  --------
  Item Level: 69
  --------
  { Implicit Modifier — Damage, Caster }
  37(33-37)% increased Spell Damage (implicit)
  --------
  { Prefix Modifier "Discharging" (Tier: 2) — Damage, Elemental, Lightning, Caster }
  Adds 5(4-11) to 142(136-144) Lightning Damage to Spells
  { Suffix Modifier "of Shocking" (Tier: 3) — Elemental, Lightning, Ailment }
  10% chance to Shock
  (Shock increases Damage taken by up to 50%, depending on the amount of Lightning Damage in the hit, for 2 seconds))";


int main()
{
  std::string parsedItemData = PoEParser::parseItem(rawItemData);
  std::vector<PoEParser::ItemModData> parsedModData = PoEParser::parseMods(parsedItemData);
  PoEParser::printMods(parsedModData);
}
