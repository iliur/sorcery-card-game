#ifndef _CARD_H_
#define _CARD_H_

#include <string>
#include <vector>
#include <memory>
#include "Ability.h"
#include "CardObserver.h"
#include "enums.h"
#include "Observer.h"

class Card : public CardObserver {
  static int cardId; 
  int id = 0;
  std::string name;
  CardType type;
  int magicCost;
  Ability ability;
  int boardX = -1;
  int boardY = -1;
  int playerIndex;

  std::vector<Observer *> observers;

  public:
    Card(const std::string name, const CardType type, const int magicCost, Ability ability);
    Card(const Card &other);
    virtual ~Card() override;

    // Getters and setters
    int getId() const override; // For CardObserver
    std::string getName() const;
    CardType getType() const;
    int getMagicCost() const;
    Ability getAbility() const override;
    void updateAbilityCost(int value);
    int getBoardX() const; // For Observer
    int getBoardY() const; // For Observer
    void setBoard(int x, int y, int playerIndex);
    void setX(int x);

    // Virtual getters and setters
    virtual int getAttack() const;
    virtual int getDefense() const;
    virtual MinionStatus getStatus() const;
    virtual std::vector<std::shared_ptr<Card>> &getEnchantments();
    virtual int getMaxAction() const;
    virtual int getAction() const;
    virtual bool getIsDead() const;
    virtual std::string getAttackDesc() const;
    virtual std::string getDefenseDesc() const;
    virtual int getCharges() const;
    virtual int getActivationCost() const;
    virtual void setAlive();
    virtual void setDead();
    virtual void setDefense(int value);

    // Overridden by Minion
    virtual void modifyAttack(Modify modifier, int value);
    virtual void modifyDefense(Modify modifier, int value);
    virtual void changeStatus(MinionStatus newStatus);
    virtual void addEnchantment(std::shared_ptr<Card> enchant);
    virtual void updateMaxAction(int value);
    virtual void updateAction(int value);
    virtual void resetAction();
    
    // Overridden by Ritual
    virtual void updateCharges(int value);

    // Observer pattern
    void attachObserver(Observer *obs);
    void detachObserver();
    void notifyDisplay();
};

#endif
