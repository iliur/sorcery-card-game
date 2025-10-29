#include "Ritual.h"
#include "iostream"

using namespace std;

Ritual::Ritual(const string name, const CardType type, const int magicCost, Ability ability, int charges, int activationCost):
    Card{name, type, magicCost, ability}, charges{charges}, activationCost{activationCost} {}

Ritual::Ritual(const Ritual &other): 
    Card{other.getName(), other.getType(), other.getMagicCost(), other.getAbility()}, charges{other.charges}, activationCost{other.activationCost} {}

Ritual::~Ritual() {}

void Ritual::updateCharges(int value) { charges += value; notifyDisplay(); }
int Ritual::getCharges() const { return charges; }
int Ritual::getActivationCost() const { return activationCost; }
