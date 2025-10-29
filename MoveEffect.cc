#include "MoveEffect.h"

using namespace std;

MoveEffect::MoveEffect(const Location location, const PlayerSide side) : 
  location{location}, side{side} {}

MoveEffect::MoveEffect(const MoveEffect &other) : location{other.location},
  side{other.side} {}

Location MoveEffect::getLocation() { return location; }
PlayerSide MoveEffect::getSide() { return side; }
