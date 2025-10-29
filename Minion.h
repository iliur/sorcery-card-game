#ifndef _MINION_H_
#define _MINION_H_

#include <string>
#include "enums.h"
#include "Card.h"
#include "Enchantment.h"

class Minion : public Card {
  int attack;
  int defense;
  
  MinionStatus status = MinionStatus::NONE;
  std::vector<std::shared_ptr<Card>> enchantments;
  int maxAction = 1;
  int action = 0;
  bool isDead = false;

  public:
    Minion(const std::string name, const CardType type, const int magicCost, 
      Ability ability, const int attack, const int defense);
    // Minion(const Minion &other);
    ~Minion() override;

    // Getters and setters
    int getAttack() const override;
    int getDefense() const override;
    MinionStatus getStatus() const override;
    std::vector<std::shared_ptr<Card>> &getEnchantments() override;
    int getMaxAction() const override;
    int getAction() const override;
    bool getIsDead() const override;
    void setAlive() override;
    void setDead() override;
    void setDefense(int value) override;

    // modifies minions' attack and defense value
    void modifyAttack(Modify modifier, int value) override;
    void modifyDefense(Modify modifier, int value) override;

    // modifies minions' max and current number of actions
    void updateMaxAction(int value) override;
    void updateAction(int value) override;
    void resetAction() override;

    // changes a minion's current status
    void changeStatus(MinionStatus newStatus) override;

    // adds enchantment to a minion's list of enchantments
    void addEnchantment(std::shared_ptr<Card>enchant) override;
};

#endif
