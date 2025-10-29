#include "Minion.h"

using namespace std;

Minion::Minion(const string name, const CardType type, const int magicCost, 
  Ability ability, const int attack, const int defense) :
      Card{name, type, magicCost, ability}, attack{attack}, defense{defense} {}

// Minion::Minion(const Minion &other) : 
//   Card{other.getName(), other.getType(), other.getMagicCost(), other.getAbility()},
//   attack{other.attack}, defense{other.defense} {}

Minion::~Minion() {}

int Minion::getAttack() const { return attack; }
int Minion::getDefense() const { return defense; }
MinionStatus Minion::getStatus() const { return status; }
vector<std::shared_ptr<Card>> &Minion::getEnchantments() { return enchantments; }
int Minion::getMaxAction() const { return maxAction; }
int Minion::getAction() const { return action; }
bool Minion::getIsDead() const { return isDead; }

void Minion::setDefense(int value) { defense = value; }
void Minion::setAlive() { isDead = false; }
void Minion::setDead() { isDead = true; }
void Minion::modifyAttack(Modify modifier, int value) {
  if (modifier == Modify::ADD) { attack += value; }
  else if (modifier == Modify::SUBTRACT) { attack -= value; }
  else if (modifier == Modify::MULTIPLY) { attack *= value; }
  else if (modifier == Modify::DIVIDE && value != 0) { attack /= value; }
  else { throw std::logic_error("Invalid modify attack value / modifier"); }
  if (value != 0) notifyDisplay();
}

void Minion::modifyDefense(Modify modifier, int value) {
  if (modifier == Modify::ADD) { defense += value; }
  else if (modifier == Modify::SUBTRACT) { defense -= value; }
  else if (modifier == Modify::MULTIPLY) { defense *= value; }
  else if (modifier == Modify::DIVIDE && value != 0) { defense /= value; }
  else { throw std::logic_error("Invalid modify defense value / modifier"); }

  if (defense <= 0) {
    setDead();
  }
  if (value != 0) notifyDisplay();
}

void Minion::updateMaxAction(int value) { 
  maxAction += value; 
  notifyDisplay();
}
void Minion::updateAction(int value) { action += value; }
void Minion::resetAction() { action = maxAction; }

void Minion::changeStatus(MinionStatus newStatus) { status = newStatus; }

void Minion::addEnchantment(std::shared_ptr<Card>enchant) { enchantments.emplace_back(enchant); }
