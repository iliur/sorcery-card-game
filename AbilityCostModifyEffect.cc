#include "AbilityCostModifyEffect.h"

AbilityCostModifyEffect::AbilityCostModifyEffect(const int abilityCostValue) :
  abilityCostValue{abilityCostValue} {}

AbilityCostModifyEffect::AbilityCostModifyEffect(const AbilityCostModifyEffect &other) :
  abilityCostValue{other.abilityCostValue} {}

int AbilityCostModifyEffect::getAbilityCostValue() { return abilityCostValue; }
