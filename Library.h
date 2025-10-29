#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include "Minion.h"
#include "Spell.h"
#include "Enchantment.h"
#include "Ritual.h"
#include "Ability.h"
#include "enums.h"
#include "AbilityCostModifyEffect.h"
#include "ActionModifyEffect.h"
#include "ChargeModifyEffect.h"
#include "MagicModifyEffect.h"
#include "MoveEffect.h"
#include "NoEffect.h"
#include "StatModifyEffect.h"
#include "StatusChangeEffect.h"
#include "SummonEffect.h"

extern std::map<std::string, std::shared_ptr<Minion>> minionLibrary;
extern std::map<std::string, std::shared_ptr<Spell>> spellLibrary;
extern std::map<std::string, std::shared_ptr<Enchantment>> enchantmentLibrary;
extern std::map<std::string, std::shared_ptr<Ritual>> ritualLibrary;

extern void initLibrary();
extern void removeLibrary();


#endif
