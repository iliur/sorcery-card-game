#ifndef _SUMMON_EFFECT_H_
#define _SUMMON_EFFECT_H_

#include <vector>
#include <string>
#include "enums.h"

class SummonEffect {

  std::string cardName;
  int numSummon;
  PlayerSide side;

  public:
    SummonEffect(const std::string cardName, const int numSummon, const PlayerSide side);
    SummonEffect(const SummonEffect &other);

    std::string getCardName();
    int getNumSummon();
    PlayerSide getSide();
    
};

#endif
