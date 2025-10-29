#include "ChargeModifyEffect.h"

using namespace std;

ChargeModifyEffect::ChargeModifyEffect(int chargeValue): chargeValue{chargeValue} {}

ChargeModifyEffect::ChargeModifyEffect(const ChargeModifyEffect &other): chargeValue{other.chargeValue} {}

int ChargeModifyEffect::getChargeValue() { return chargeValue; }
