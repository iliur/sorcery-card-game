#ifndef _ACTION_MODIFY_EFFECT_H_
#define _ACTION_MODIFY_EFFECT_H_

class ActionModifyEffect {
  int actionValue;

  public:
    ActionModifyEffect(const int actionValue);
    ActionModifyEffect(const ActionModifyEffect &other);

    int getActionValue();
};

#endif
