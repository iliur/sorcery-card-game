#ifndef CHARGE_MODIFY_EFFECT_H
#define CHARGE_MODIFY_EFFECT_H

class ChargeModifyEffect {

    int chargeValue;

  public:
    ChargeModifyEffect(int chargeValue);
    ChargeModifyEffect(const ChargeModifyEffect &other);

    int getChargeValue();
    
};

#endif
