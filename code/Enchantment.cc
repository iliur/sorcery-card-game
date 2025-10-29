#include "Enchantment.h"

using namespace std;

Enchantment::Enchantment(const string name, const CardType type, const int magicCost, Ability ability, string attackDesc, string defenseDesc ):
    Card{name, type, magicCost, ability}, attackDesc{attackDesc}, defenseDesc{defenseDesc} {}

Enchantment::Enchantment(const Enchantment &other):
    Card{other.getName(), other.getType(), other.getMagicCost(), other.getAbility()}, attackDesc{other.attackDesc}, defenseDesc{other.defenseDesc} {}
    
Enchantment::~Enchantment() {}

string Enchantment::getAttackDesc() const { return attackDesc; }
string Enchantment::getDefenseDesc() const { return defenseDesc; }
