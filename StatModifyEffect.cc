#include "StatModifyEffect.h"

using namespace std;

StatModifyEffect::StatModifyEffect(const Modify attackModifier, const int attackChange, const Modify defenseModifier, const int defenseChange) : 
  attackModifier{attackModifier}, attackChange{attackChange}, defenseModifier{defenseModifier}, defenseChange{defenseChange} {}

StatModifyEffect::StatModifyEffect(const StatModifyEffect &other) : attackModifier{other.attackModifier}, attackChange{other.attackChange}, 
  defenseModifier{other.defenseModifier}, defenseChange{other.defenseChange} {}

int StatModifyEffect::getAttackChange() { return attackChange; }
Modify StatModifyEffect::getAttackModifier() { return attackModifier; }
int StatModifyEffect::getDefenseChange() { return defenseChange; }
Modify StatModifyEffect::getDefenseModifier() { return defenseModifier; }
