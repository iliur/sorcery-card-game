#ifndef MAGIC_MODIFY_EFFECT_H
#define MAGIC_MODIFY_EFFECT_H

#include <iostream>
#include <string>

class MagicModifyEffect {

    int magicModifyValue;

  public:
    MagicModifyEffect(int magicModifyValue);
    MagicModifyEffect(const MagicModifyEffect &other);

    int getMagicModifyValue();
    
};

#endif
