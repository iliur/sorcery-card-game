#include "SummonEffect.h"

using namespace std;

SummonEffect::SummonEffect(const string cardName, const int numSummon, const PlayerSide side) : 
  cardName{cardName}, numSummon{numSummon}, side{side} {}

SummonEffect::SummonEffect(const SummonEffect &other) : cardName{other.cardName}, 
  numSummon{other.numSummon}, side{other.side} {}

string SummonEffect::getCardName() { return cardName; }
int SummonEffect::getNumSummon() { return numSummon; }
PlayerSide SummonEffect::getSide() { return side; }
