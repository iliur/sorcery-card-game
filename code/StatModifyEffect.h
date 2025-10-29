#ifndef _STAT_MODIFY_EFFECT_H_
#define _STAT_MODIFY_EFFECT_H_

#include <vector>
#include "enums.h"

class StatModifyEffect {

  Modify attackModifier;
  int attackChange;
  Modify defenseModifier;
  int defenseChange;

  public:
    StatModifyEffect(const Modify attackModifier, const int attackChange, const Modify defenseModifier, const int defenseChange);
    StatModifyEffect(const StatModifyEffect &other);

    int getAttackChange();
    Modify getAttackModifier();
    int getDefenseChange();
    Modify getDefenseModifier();
    
    
};

#endif
