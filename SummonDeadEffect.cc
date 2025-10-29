#include "SummonDeadEffect.h"

using namespace std;

SummonDeadEffect::SummonDeadEffect(const int undeadDefense) : undeadDefense{undeadDefense} {}

SummonDeadEffect::SummonDeadEffect(const SummonDeadEffect &other) : undeadDefense{other.undeadDefense} {}

int SummonDeadEffect::getUndeadDefense() const { return undeadDefense; }
