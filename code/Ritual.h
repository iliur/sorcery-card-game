#ifndef RITUAL_H
#define RITUAL_H

#include "Card.h"

class Ritual : public Card {
  
    int charges;
    int activationCost;

  public:
    Ritual(const std::string name, const CardType type, const int magicCost, Ability ability, int charges, int activationCost);
    Ritual(const Ritual &other);
    ~Ritual() override;

    void updateCharges(int value) override;
    int getCharges() const override;
    int getActivationCost() const override;
};

#endif
