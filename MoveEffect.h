#ifndef MOVE_EFFECT_H
#define MOVE_EFFECT_H

#include <vector>
#include "enums.h"

class MoveEffect {

  Location location;
  PlayerSide side;

  public:
    MoveEffect(const Location location, const PlayerSide side);
    MoveEffect(const MoveEffect &other);

    Location getLocation();
    PlayerSide getSide();

};

#endif
