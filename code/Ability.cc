#include "Ability.h"

using namespace std;

Ability::Ability(const AbilityType type, const Condition useCondition, const Target target, 
  const variant<AbilityCostModifyEffect, ActionModifyEffect, ChargeModifyEffect, MagicModifyEffect, 
  MoveEffect, NoEffect, RemoveEnchantEffect, StatModifyEffect, StatusChangeEffect, SummonDeadEffect, SummonEffect> effectHolder, 
  const string description, const int magicCost) 
  : type{type}, 
    useCondition{useCondition}, 
    target{target}, 
    effectHolder{effectHolder},
    description{description}, 
    magicCost{magicCost} {}

Ability::Ability(const Ability &other) 
  : type{other.type}, 
    useCondition{other.useCondition},
    target{other.target}, 
    effectHolder{other.effectHolder},
    description{other.description}, 
    magicCost{other.magicCost} {
  }

AbilityType Ability::getType() { return type; }
Condition Ability::getCondition() { return useCondition; }
Target Ability::getTarget() { return target; }
string Ability::getDescription() { return description; }
int Ability::getMagicCost() { return magicCost; }

void Ability::modifyMagicCost(int value) { magicCost += value; }


