#include "Spell.h"

Spell::Spell(const string name, const CardType type, const int magicCost, Ability ability) :
      Card{name, type, magicCost, ability} {}


Spell::Spell(const Spell &other) : Card{other.getName(), other.getType(), other.getMagicCost(), other.getAbility()} 
  {}

Spell::~Spell() {}
