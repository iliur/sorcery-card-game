#include "Card.h"

using namespace std;

int Card::cardId = 0;

Card::Card(const string name, const CardType type, const int magicCost, Ability ability) :
  name{name}, type{type}, magicCost{magicCost}, ability{ability} {
  id = cardId++;
}

Card::Card(const Card &other) :name{other.name}, type{other.type}, 
  magicCost{other.magicCost}, ability{other.ability} {}

Card::~Card() {}

// Getters and setters
int Card::getId() const { return id; }
string Card::getName() const { return name; }
CardType Card::getType() const { return type; }
int Card::getMagicCost() const { return magicCost; }
Ability Card::getAbility() const { return ability; }
void Card::updateAbilityCost(int value) { 
  ability.modifyMagicCost(value);
  // cout << "VALUE: " << value << endl;
  // cout << "Magic Cost: " << getAbility().getMagicCost() << endl;
  notifyDisplay();
}
int Card::getBoardX() const { return boardX; } 
int Card::getBoardY() const { return boardY; }
void Card::setBoard(int x, int y, int playerIndex) {
  boardX = x;
  boardY = y;
  this->playerIndex = playerIndex;
}
void Card::setX(int x) {
  boardX = x;
}

// Virtual getters and setters
int Card::getAttack() const { return 0; }
int Card::getDefense() const { return 0; }
MinionStatus Card::getStatus() const { return MinionStatus::NONE; }
vector<std::shared_ptr<Card> > &Card::getEnchantments() {}
int Card::getMaxAction() const { return 0; }
int Card::getAction() const { return 0; }
bool Card::getIsDead() const { return false; }
string Card::getAttackDesc() const { return ""; }
string Card::getDefenseDesc() const { return ""; }
int Card::getCharges() const { return 0; }
int Card::getActivationCost() const { return 0; }
void Card::setAlive() {}
void Card::setDead() {}
void Card::setDefense(int value) {}

// Overridden by Minion
void Card::modifyAttack(Modify modifier, int value) {}
void Card::modifyDefense(Modify modifier, int value) {}
void Card::changeStatus(MinionStatus newStatus) {}
void Card::addEnchantment(std::shared_ptr<Card> enchant) {}
void Card::updateMaxAction(int value) {}
void Card::updateAction(int value) {}
void Card::resetAction() {}

// Overridden by Ritual
void Card::updateCharges(int value) {}

// Observer pattern
void Card::attachObserver(Observer *obs) {
  observers.emplace_back(obs);
}
void Card::detachObserver() {
  for (auto &obs : observers) {
    obs->notify(boardX, boardY, true, playerIndex);
  }
  observers.clear();
  
}
void Card::notifyDisplay() {
  for (auto &obs : observers) {
    obs->notify(boardX, boardY, false, playerIndex);
  }
}
