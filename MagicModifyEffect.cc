#include "MagicModifyEffect.h"

using namespace std;

MagicModifyEffect::MagicModifyEffect(int magicModifyValue): magicModifyValue{magicModifyValue} {}

MagicModifyEffect::MagicModifyEffect(const MagicModifyEffect &other): magicModifyValue{other.magicModifyValue} {}

int MagicModifyEffect::getMagicModifyValue() { return magicModifyValue; }
