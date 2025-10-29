#ifndef STATUS_CHANGE_EFFECT_H
#define STATUS_CHANGE_EFFECT_H

#include <iostream>
#include <string>
#include "enums.h"

class StatusChangeEffect {

    MinionStatus newStatus;

  public:
    StatusChangeEffect(MinionStatus newStatus);
    StatusChangeEffect(const StatusChangeEffect &other);

    MinionStatus getNewStatus();
    
};

#endif
