#ifndef _ABILITY_COST_MODIFY_EFFECT_H_
#define _ABILITY_COST_MODIFY_EFFECT_H_

class AbilityCostModifyEffect {
  int abilityCostValue;

  public:
    AbilityCostModifyEffect(const int abilityCostValue);
    AbilityCostModifyEffect(const AbilityCostModifyEffect &other);

    int getAbilityCostValue();
};

#endif
