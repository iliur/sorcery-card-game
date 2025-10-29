#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include <string>
#include "Card.h"

class Enchantment : public Card {
  std::string attackDesc;
  std::string defenseDesc;

  public:
    Enchantment(const std::string name, const CardType type, const int magicCost, Ability ability, std::string attackDesc = "", std::string defenseDesc = "");
    Enchantment(const Enchantment &other);
    ~Enchantment() override;

    // Getters and setters
    std::string getAttackDesc() const override;
    std::string getDefenseDesc() const override;
};

#endif
