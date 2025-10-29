#ifndef _SUMMON_DEAD_EFFECT_H_
#define _SUMMON_DEAD_EFFECT_H_

#include <vector>
#include <string>
#include "enums.h"

class SummonDeadEffect {

  int undeadDefense;

  public:
    SummonDeadEffect(const int undeadDefense);
    SummonDeadEffect(const SummonDeadEffect &other);

    int getUndeadDefense() const;
    
};

#endif
