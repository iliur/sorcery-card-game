#ifndef _ABILITY_H_
#define _ABILITY_H_

#include <variant>
#include <string>
#include <vector>
#include "enums.h"
#include "AbilityCostModifyEffect.h"
#include "ActionModifyEffect.h"
#include "ChargeModifyEffect.h"
#include "MagicModifyEffect.h"
#include "MoveEffect.h"
#include "NoEffect.h"
#include "RemoveEnchantEffect.h"
#include "StatModifyEffect.h"
#include "StatusChangeEffect.h"
#include "SummonDeadEffect.h"
#include "SummonEffect.h"

class Ability {
  AbilityType type;
  Condition useCondition;
  Target target;

  public:
    std::variant<AbilityCostModifyEffect, ActionModifyEffect, ChargeModifyEffect, MagicModifyEffect, 
    MoveEffect, NoEffect, RemoveEnchantEffect, StatModifyEffect, StatusChangeEffect, 
    SummonDeadEffect, SummonEffect > effectHolder;

    Ability(const AbilityType type, const Condition useCondition, 
    const Target target, const std::variant<AbilityCostModifyEffect, ActionModifyEffect, ChargeModifyEffect, MagicModifyEffect, 
    MoveEffect, NoEffect, RemoveEnchantEffect, StatModifyEffect, StatusChangeEffect, SummonDeadEffect, SummonEffect> effectHolder, 
    const std::string description = "", const int magicCost = 0);

    Ability(const Ability &other);

    // Getters and setters
    AbilityType getType();
    Condition getCondition();
    Target getTarget();
    std::string getDescription();
    int getMagicCost();

    void modifyMagicCost(int value);
  
    private:
      std::string description;
      int magicCost;
};

#endif

