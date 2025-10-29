#ifndef SPELL_H
#define SPELL_H

#include <string>
#include "Card.h"

using namespace std;

class Spell : public Card {
  public:
    Spell(const string name, const CardType type, const int magicCost, Ability ability);
    Spell(const Spell &other);
    ~Spell() override;
};

#endif
