#include "ActionModifyEffect.h"

using namespace std;

ActionModifyEffect::ActionModifyEffect(const int actionValue) : actionValue{actionValue} {}

ActionModifyEffect::ActionModifyEffect(const ActionModifyEffect &other) :
  actionValue{other.actionValue} {}

int ActionModifyEffect::getActionValue() { return actionValue; }
