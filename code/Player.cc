#include "Player.h"
#include "GameManager.h"
#include "GraphicsDisplay.h"
#include "TextDisplay.h"
#include "Library.h"

using namespace std;

Player::Player(int playerNumber) : playerNumber{playerNumber} {}
Player::~Player() {
  // for (auto &i : deck) delete i;
  // for (auto &i : field) delete i;
  // for (auto &i : graveyard) delete i;
  // for (auto &i : ritual) delete i;
  // for (auto &i : hand) delete i;
}

// ---- SETTERS, GETTERS, CHECKERS --------------
void Player::setName(string name) { this->name = name; }
void Player::setGameManager(GameManager *g) { this->g = g; }
void Player::setOtherPlayer(Player *p) { other = p; }
void Player::setGraphics(bool graphics) { this->graphics = graphics; }
void Player::setGraphicsDisplay(GraphicsDisplay *gd) { this->gd = gd; }
void Player::setTextDisplay(TextDisplay *td) { this->td = td;};
int Player::getPlayerNumber() { return playerNumber; }
string Player::getName() { return name; }
int Player::getHealth() { return health; }
int Player::getMagic() { return magic; }
vector<std::shared_ptr<Card>> &Player::getDeck() { return deck; }
vector<std::shared_ptr<Card>> &Player::getField() { return field; }
vector<std::shared_ptr<Card>> &Player::getGraveyard() { return graveyard; }
vector<std::shared_ptr<Card>> &Player::getRitual() { return ritual; }
vector<std::shared_ptr<Card>> &Player::getHand() { return hand; }
bool Player::isMaxHand() { return hand.size() >= MAX_HAND; }
bool Player::isMaxField() { return field.size() >= MAX_FIELD; }
bool Player::isAlive() { return health > 0; }
// ----------------------------------------


void Player::drawCard() {
  moveCard(0, deck, hand);
}

void Player::discard(int cardNum) {
  // ==== Error Checking ======================================
  size_t cardIndex = cardNum - 1;
  if (cardIndex < 0 || cardIndex >= hand.size()) throw std::out_of_range("Index out of range.");
  // ==== End of Error Checking ===============================
  // delete hand[cardIndex];
  hand.erase(hand.begin() + cardIndex);
}


void Player::attack(int atkNum) {
  // ==== Error Checking ======================================
  size_t atkIndex = atkNum - 1;
  if (atkIndex < 0 || atkIndex >= field.size()) throw std::out_of_range("Index out of range.");

  std::shared_ptr<Card> atkCard = field[atkIndex];

  if (atkCard->getAction() <= 0) throw std::logic_error("Minion has no action.");
  
  // ==== End of Error Checking ===============================

  other->updateHealth(-atkCard->getAttack());
  atkCard->updateAction(-1);
}


void Player::attack(int atkNum, int defNum) {
  // ==== Error Checking ======================================
  size_t atkIndex = atkNum - 1;
  size_t defIndex = defNum - 1;
  if (atkIndex < 0 || atkIndex >= field.size()) throw std::out_of_range("Index out of range.");
  if (defIndex < 0 || defIndex >= other->getField().size()) throw std::out_of_range("Index out of range.");

  std::shared_ptr<Card> atkCard = field[atkIndex];
  std::shared_ptr<Card> defCard = other->getField()[defIndex];

  if (atkCard->getAction() <= 0) throw std::logic_error("Minion has no action.");

  // ==== End of Error Checking ===============================

  atkCard->modifyDefense(Modify::SUBTRACT, defCard->getAttack());
  defCard->modifyDefense(Modify::SUBTRACT, atkCard->getAttack()); 
  atkCard->updateAction(-1);
}

void Player::playOnRitual(int handNum, int playerNum, bool testing) {
    // ==== Error Checking ======================================
  size_t handIndex = handNum - 1;

  if (handIndex < 0 || handIndex >= hand.size()) throw std::out_of_range("Index out of range.");
  if (playerNum != 1 && playerNum != 2) throw std::out_of_range("Index out of range.");
  
  std::shared_ptr<Card> card = hand[handIndex];
  if (!testing && magic < card->getMagicCost()) throw std::logic_error("Insufficient magic.");

  if (other->getRitual().size() == 0) throw std::logic_error("No ritual found.");
  // ==== End of Error Checking ===============================

  vector<std::shared_ptr<Card> > *targetRitual;
  if (playerNum == playerNumber) {
    targetRitual = &ritual;
  } else if (playerNum == other->getPlayerNumber()) {
    targetRitual = &other->getRitual();
  }

  Ability ability = card->getAbility();
  if (card->getType() == CardType::SPELL) {
    useAbility(&ability, *targetRitual, 0);
  } else {
    throw std::logic_error("Invalid card type.");
  }

  // remove magic from player
  if (!testing) updateMagic(-card->getMagicCost());
  moveCard(handIndex, hand, graveyard);
}

void Player::play(int handNum, bool testing) {
  // ==== Error Checking ======================================
  size_t handIndex = handNum - 1;
  if (handIndex < 0 || handIndex >= hand.size()) throw std::out_of_range("Index out of range.");

  std::shared_ptr<Card> card = hand[handIndex];
  if (!testing && magic < card->getMagicCost()) throw std::logic_error("Insufficient magic.");
  if (ritual.size() == 0 && card->getAbility().getTarget() == Target::RITUAL) throw std::logic_error("No target ritual");
  // ==== End of Error Checking ===============================

  if (card->getType() == CardType::MINION) {
    moveCard(handIndex, hand, field);
    if (card->getAbility().getType() == AbilityType::PASSIVE && card->getAbility().getTarget() == Target::ALLY_FIELD) {
      g->attachObservers(card, playerNumber); // CHANGED FROM MINION TO CARD HEHEH
    } else if (card->getAbility().getType() == AbilityType::PASSIVE && card->getAbility().getTarget() == Target::ENEMY_FIELD) {
      g->attachObservers(card, other->getPlayerNumber());
    } else if (card->getAbility().getType() == AbilityType::PASSIVE) {
      g->attachObservers(card, playerNumber);
    }
  }

  else if (card->getType() == CardType::RITUAL) {
    // check if there is an existing ritual
    if (ritual.size() == 1) moveCard(0, ritual, graveyard);
    moveCard(handIndex, hand, ritual);
    g->attachObservers(card, playerNumber);
  }

  else if (card->getType() == CardType::SPELL) {
    Ability ability = card->getAbility();
    if (ability.getTarget() == Target::SINGLE) throw std::invalid_argument("No target selected.");
    
    if (ability.getTarget() == Target::ALLY_FIELD) {
      useAbility(&ability, field);
    } 
    else if (ability.getTarget() == Target::ENEMY_FIELD) {
      useAbility(&ability, other->getField());
    } 
    else if (ability.getTarget() == Target::BOTH_FIELDS) {
      vector<std::shared_ptr<Card> > cardList;
      cardList.insert(cardList.end(), field.begin(), field.end());
      cardList.insert(cardList.end(), other->getField().begin(), other->getField().end());
      useAbility(&ability, cardList);
    } 
    else if (ability.getTarget() == Target::PLAYER) {
      // useAbility();
    } 
    else if (ability.getTarget() == Target::ENEMY) {
      // useAbility();
    } 
    else if (ability.getTarget() == Target::RITUAL) {
      // useAbility();
      useAbility(&ability, ritual, 0);
    } 
    else if (ability.getTarget() == Target::ENEMY_RITUAL) {
      // useAbility();
      useAbility(&ability, other->getRitual(), 0);
    } 
    else if (ability.getTarget() == Target::SUMMON) {
      useAbility(&ability, card);
    }
    else {
      throw std::logic_error("Invalid target.");
    }

    moveCard(handIndex, hand, graveyard);

  } else {
    throw std::logic_error("Invalid card type.");
  }

  // remove magic from player
  if (!testing) updateMagic(-card->getMagicCost());
}


void Player::play(int handNum, int playerNum, int targetNum, bool testing) {
  // ==== Error Checking ======================================
  size_t handIndex = handNum - 1;
  if (handIndex < 0 || handIndex >= hand.size()) throw std::out_of_range("Index out of range.");
  if (playerNum != 1 && playerNum != 2) throw std::out_of_range("Index out of range.");
  
  size_t targetIndex = targetNum - 1;
  vector<std::shared_ptr<Card> > *targetField;
  if (playerNumber == playerNum) {
    if (targetIndex < 0 || targetIndex >= field.size()) throw std::out_of_range("Index out of range.");
    targetField = &field;
  } else {
    if (targetIndex < 0 || targetIndex >= other->getField().size()) throw std::out_of_range("Index out of range.");
    targetField = &other->getField();
  }
  
  std::shared_ptr<Card> card = hand[handIndex];
  if (!testing && magic < card->getMagicCost()) throw std::logic_error("Insufficient magic.");
  // ==== End of Error Checking ===============================

  Ability ability = card->getAbility();
  if (card->getType() == CardType::SPELL) {
    useAbility(&ability, *targetField, targetIndex);
    moveCard(handIndex, hand, graveyard);
  }
  else if (card->getType() == CardType::ENCHANTMENT) {
    useAbility(&ability, *targetField, targetIndex);
    (*targetField)[targetIndex]->addEnchantment(card);
    moveCard(handIndex, hand, graveyard);
  }
  else {
    throw std::logic_error("Invalid card type.");
  }

  // remove magic from player
  if (!testing) updateMagic(-card->getMagicCost());
}


void Player::use(int minionNum, bool testing) {
  // ==== Error Checking ======================================
  size_t minionIndex = minionNum - 1;
  if (minionIndex < 0 || minionIndex >= field.size()) throw std::out_of_range("Index out of range.");
  
  std::shared_ptr<Card> minion = field[minionIndex];
  if (minion->getAction() <= 0) throw std::logic_error("Minion has no action.");
  if (minion->getStatus() == MinionStatus::SILENCED) throw std::logic_error("Minion is silenced.");

  Ability ability = minion->getAbility();
  if (ability.getType() != AbilityType::ACTIVE) throw std::invalid_argument("Minion has no active ability.");
  if (ability.getTarget() == Target::SINGLE) throw std::invalid_argument("No target selected.");

  if (!testing && magic < ability.getMagicCost()) throw std::logic_error("Insufficient magic.");
  // ==== End of Error Checking ===============================


  if (ability.getTarget() == Target::ALLY_FIELD) {
    useAbility(&ability, field);
  } 
  else if (ability.getTarget() == Target::ENEMY_FIELD) {
    useAbility(&ability, other->getField());
  } 
  else if (ability.getTarget() == Target::BOTH_FIELDS) {
    vector<std::shared_ptr<Card> > cardList;
    cardList.insert(cardList.end(), field.begin(), field.end());
    cardList.insert(cardList.end(), other->getField().begin(), other->getField().end());
    useAbility(&ability, cardList);
  } 
  else if (ability.getTarget() == Target::PLAYER) {
    useAbility(&ability, this);
  } 
  else if (ability.getTarget() == Target::ENEMY) {
    useAbility(&ability, other);
  } 
  else if (ability.getTarget() == Target::RITUAL) {
    // ability->useAbility();
  } 
  else if (ability.getTarget() == Target::ENEMY_RITUAL) {
    // ability->useAbility();
  }
  else if (ability.getTarget() == Target::SUMMON) {
    useAbility(&ability, minion);
  }
  else {
    throw std::logic_error("Invalid target.");
  }


  // remove magic from player
  if (!testing) updateMagic(-ability.getMagicCost());
  minion->updateAction(-1);
}


void Player::use(int minionNum, int playerNum, int targetNum, bool testing) {
  // ==== Error Checking ======================================
  size_t minionIndex = minionNum - 1;
  if (minionIndex < 0 || minionIndex >= field.size()) throw std::out_of_range("Index out of range.");
  if (playerNum != 1 && playerNum != 2) throw std::out_of_range("Index out of range.");

  std::shared_ptr<Card> minion = field[minionIndex];
  if (minion->getAction() <= 0) throw std::logic_error("Minion has no action.");
  if (minion->getStatus() == MinionStatus::SILENCED) throw std::logic_error("Minion is silenced.");
  
  Ability ability = minion->getAbility();
  if (ability.getType() != AbilityType::ACTIVE) throw std::invalid_argument("Minion has no active ability.");

  size_t targetIndex = targetNum - 1;
  vector<std::shared_ptr<Card> > *targetField;
  if (playerNumber == playerNum) {
    if (targetIndex < 0 || targetIndex >= field.size()) throw std::out_of_range("Index out of range.");
    targetField = &field;
  } else {
    if (targetIndex < 0 || targetIndex >= other->getField().size()) throw std::out_of_range("Index out of range.");
    targetField = &other->getField();
  }

  if (!testing && magic < ability.getMagicCost()) throw std::logic_error("Insufficient magic.");
  // ==== End of Error Checking ===============================


  useAbility(&ability, *targetField, targetIndex);

  // remove magic from player
  if (!testing) updateMagic(-ability.getMagicCost());
  minion->updateAction(-1);
}


void Player::inspect(int cardNum) {
  // ==== Error Checking ======================================
  size_t cardIndex = cardNum - 1;
  if (cardIndex < 0 || cardIndex >= field.size()) throw std::out_of_range("Index out of range.");
  // ==== End of Error Checking ===============================
  if (graphics) gd->displayInspect(field[cardIndex]);
  td->inspectMinion(field[cardIndex]);
}

void Player::moveCard(size_t index, vector<std::shared_ptr<Card> > &source, vector<std::shared_ptr<Card> > &destination) {
  // ==== Error Checking ======================================
  if (index < 0 || index >= source.size()) throw std::out_of_range("Index out of range.");
  if (&field == &destination && isMaxField()) throw std::length_error("Field is max.");
  if (&other->getField() == &destination && other->isMaxField()) throw std::length_error("Field is max.");
  if (&hand == &destination && isMaxHand()) throw std::length_error("Hand is max.");
  if (&other->getHand() == &destination && other->isMaxHand()) throw std::length_error("Hand is max.");
  // ==== End of Error Checking ===============================
  
  std::shared_ptr<Card> card = source[index]; // holds the address of the card that is going to be moved
  cout << card->getName() << " has been moved." << endl;
  
  // Checking for board notify location

  auto it = std::find(source.begin(), source.end(), card); // find the position of the card in source
  if (it != source.end()) source.erase(it); // remove card from source
 
  destination.emplace_back(card); // add card to destination

  // attaching and detaching observers
  if (&source == &hand) card->detachObserver();
  if (&source == &field) {
    card->detachObserver();
    shiftField(field);
  }
  if (&source == &other->getField()) {
    card->detachObserver();
    shiftField(other->getField());
  }

  if (&source == &ritual) {
    card->detachObserver();
  }

  if (&source == &other->getRitual()) {
    card->detachObserver();
  }

  if (&source == &graveyard) {
    source[index - 1]->notifyDisplay();
  }

  if (playerNumber == 1 && &destination == &graveyard) {
    card->setBoard(4, 0, playerNumber - 1);
  }
  if (playerNumber == 2 && &destination == &graveyard) {
    card->setBoard(4, 3, playerNumber - 1);
  }
  if (playerNumber == 1 && &destination == &other->getGraveyard()) {
    card->setBoard(4, 3, other->getPlayerNumber() - 1);
  }
  if (playerNumber == 2 && &destination == &other->getGraveyard()) {
    card->setBoard(4, 0, other->getPlayerNumber() - 1);
  }

  if (playerNumber == 1 && &destination == &ritual) {
    card->setBoard(0, 0, playerNumber - 1);
  }
  if (playerNumber == 2 && &destination == &ritual) {
    card->setBoard(0, 3, playerNumber - 1);
  }
  if (playerNumber == 1 && &destination == &field) {
    card->setBoard(field.size() - 1, 1, playerNumber - 1);
  }
  if (playerNumber == 2 && &destination == &field) {
    card->setBoard(field.size() - 1, 2, playerNumber - 1);
  }
  if (card->getBoardX() != -1 && card->getBoardY() != -1) {
    if (graphics) card->attachObserver(gd);
    card->attachObserver(td);
    card->notifyDisplay();

  }

  
  if (&source == &field && card->getAbility().getType() == AbilityType::PASSIVE) g->detachObservers(card->getId());
  if (&source == &other->getField() && card->getAbility().getType() == AbilityType::PASSIVE) g->detachObservers(card->getId());
  if (&source == &ritual) g->detachObservers(card->getId());
  if ((&source == &field || &source == &other->getField()) && card->getType() == CardType::MINION) {
    vector<std::shared_ptr<Card> > enchantList = card->getEnchantments();
    for (size_t i = 0; i < enchantList.size(); i++) {
      std::shared_ptr<Card> removeEnchant = spellLibrary["Disenchant"];
      Ability ability = removeEnchant->getAbility();
      useAbility(&ability, source, index);
    }
  } 

  if (&source == &field || &source == &other->getField()) g->notifyTriggerOnLeave();
  if (&destination == &field) g->notifyTriggerOnEnter(card);
  
}


void Player::addCard(string cardName, vector<std::shared_ptr<Card> > &destination) {
  // ==== Error Checking ======================================
  if (&field == &destination && isMaxField()) throw std::length_error("Field is max.");
  // if (&other->getField() == &destination && other->isMaxField()) throw std::length_error("Field is max.");
  if (&hand == &destination && isMaxHand()) throw std::length_error("Hand is max.");
  // if (&other->getHand() == &destination && other->isMaxHand()) throw std::length_error("Hand is max.");
  // ==== End of Error Checking ===============================
  
  shared_ptr<Card> card;
  // Searching minionLibrary
  auto itMinion = minionLibrary.find(cardName);
  if (itMinion != minionLibrary.end()) {
    card = make_shared<Minion>((*minionLibrary[cardName]));
    destination.emplace_back(card);
    return;
  }

  auto itSpell = spellLibrary.find(cardName);
  if (itSpell != spellLibrary.end()) {
    card = make_shared<Spell>(*spellLibrary[cardName]);
    destination.emplace_back(card);
    return;
  }
  
  auto itEnchantment = enchantmentLibrary.find(cardName);
  if (itEnchantment != enchantmentLibrary.end()) {
    card = make_shared<Enchantment>(*enchantmentLibrary[cardName]);
    destination.emplace_back(card);
    return;
  }

  auto itRitual = ritualLibrary.find(cardName);
  if (itRitual != ritualLibrary.end()) {
    card = make_shared<Ritual>(*ritualLibrary[cardName]);
    destination.emplace_back(card);
    return;
  }

  if (cardName != "") cerr << cardName + " is not found in any library.";
}

void Player::updateHealth(int value) { health += value; notifyDisplay(); }
void Player::updateMagic(int value) { magic += value; notifyDisplay(); }

void Player::useAbility(Ability *ability, std::shared_ptr<Card> card) {
  if (SummonEffect *effect = std::get_if<SummonEffect>(&ability->effectHolder)) {
    useSummonEffect(effect);
  } else if (SummonDeadEffect *effect = std::get_if<SummonDeadEffect>(&ability->effectHolder)) {
    useSummonDeadEffect(effect);
  } else if (StatModifyEffect *effect = std::get_if<StatModifyEffect>(&ability->effectHolder)) {
    useStatModifyEffect(card, effect);
  } 
}

void Player::useAbility(Ability *ability, Player *p) {
  if (MagicModifyEffect *effect = std::get_if<MagicModifyEffect>(&ability->effectHolder)) {
    useMagicModifyEffect(p, effect);
  } 
}

void Player::useAbility(Ability *ability, vector<std::shared_ptr<Card> > &cardList) {
  for (size_t i = 0; i < cardList.size(); ++i) {
    useAbility(ability, cardList, i);
  }
}
void Player::useAbility(Ability *ability, vector<std::shared_ptr<Card> > &cardList, size_t cardIndex) {
  if (MoveEffect *effect = std::get_if<MoveEffect>(&ability->effectHolder)) {
    useMoveEffect(cardIndex, cardList, effect);
  } else if (StatModifyEffect *effect = std::get_if<StatModifyEffect>(&ability->effectHolder)) {
    useStatModifyEffect(cardList[cardIndex], effect);
  } else if (AbilityCostModifyEffect *effect = std::get_if<AbilityCostModifyEffect>(&ability->effectHolder)) {
    useAbilityCostModifyEffect(cardList[cardIndex], effect);
  } else if (ActionModifyEffect *effect = std::get_if<ActionModifyEffect>(&ability->effectHolder)) {
    useActionModifyEffect(cardList[cardIndex], effect);
  } else if (ChargeModifyEffect *effect = std::get_if<ChargeModifyEffect>(&ability->effectHolder)) {
    useChargeModifyEffect(cardList[cardIndex], effect);
  } else if (StatusChangeEffect *effect = std::get_if<StatusChangeEffect>(&ability->effectHolder)) {
    useStatusChangeEffect(cardList[cardIndex], effect);
  } else if (RemoveEnchantEffect *effect = std::get_if<RemoveEnchantEffect>(&ability->effectHolder)) {
    useRemoveEnchantEffect(cardList[cardIndex], effect);
  }
}

// Function to search for a card by ID
std::shared_ptr<Card> findCardById(const std::vector<std::shared_ptr<Card> > &cardList, int targetId) {
  for (auto& card : cardList) {
    if (card->getId() == targetId) {
      return card;
    }
  }
  return nullptr; // Card with the specified ID not found
}

void Player::usePassive(int cardId) {
  // ==== Error Checking ======================================
  std::shared_ptr<Card> card = findCardById(field, cardId);
  if (!card) card = findCardById(other->getField(), cardId);
  if (!card) card = findCardById(ritual, cardId);
  if (!card) card = findCardById(other->getRitual(), cardId);
  if (!card) throw std::logic_error("Passive card not found.");
  if (card->getType() == CardType::RITUAL && card->getCharges() <= 0) return;
  Ability ability = card->getAbility();
  if (ability.getType() != AbilityType::PASSIVE) throw std::logic_error("Ability is not passive.");
  // ==========================================================

  if (ability.getTarget() == Target::ALLY_FIELD) {
    useAbility(&ability, field);
  } 
  else if (ability.getTarget() == Target::ENEMY_FIELD) {
    useAbility(&ability, other->getField());
  } 
  else if (ability.getTarget() == Target::BOTH_FIELDS) {
    vector<std::shared_ptr<Card> > cardList;
    cardList.insert(cardList.end(), field.begin(), field.end());
    cardList.insert(cardList.end(), other->getField().begin(), other->getField().end());
    useAbility(&ability, cardList);
  } 
  else if (ability.getTarget() == Target::PLAYER) {
    useAbility(&ability, this);
  } 
  else if (ability.getTarget() == Target::ENEMY) {
    useAbility(&ability, other);
  } 
  else if (ability.getTarget() == Target::RITUAL) {
    // ability->useAbility();
  } 
  else if (ability.getTarget() == Target::ENEMY_RITUAL) {
    // ability->useAbility();
  }
  else if (ability.getTarget() == Target::SUMMON) {
    useAbility(&ability, card);
  } 
  else if (ability.getTarget() == Target::SELF) {
    useAbility(&ability, card);
  }
  else {
    throw std::logic_error("Invalid target.");
  }

  if (card->getType() == CardType::RITUAL) {
    card->updateCharges(-card->getActivationCost());
  }

}

void Player::usePassive(int cardId, std::shared_ptr<Card> card) {
  // ==== Error Checking ======================================
  std::shared_ptr<Card> passiveCard = findCardById(field, cardId);
  if (!passiveCard) passiveCard = findCardById(other->getField(), cardId);
  if (!passiveCard) passiveCard = findCardById(ritual, cardId);
  if (!passiveCard) passiveCard = findCardById(other->getRitual(), cardId);
  if (!passiveCard) throw std::logic_error("Passive card not found.");
  if (passiveCard->getType() == CardType::RITUAL && passiveCard->getCharges() <= 0) return;
  Ability passiveAbility = passiveCard->getAbility();
  if (passiveAbility.getType() != AbilityType::PASSIVE) throw std::logic_error("Ability is not passive.");
  int targetCardIndex = -1;
  vector<std::shared_ptr<Card> > *targetField;

  if (!field.empty() && card == field.back()) {
    targetCardIndex = field.size() - 1;
    targetField = &field;
  }

  if (!other->getField().empty() && card == other->getField().back()) {
    targetCardIndex = other->getField().size() - 1;
    targetField = &other->getField();
  }
  if (targetCardIndex == -1) throw std::logic_error("Target card not found.");
  // ==========================================================

  useAbility(&passiveAbility, *targetField, targetCardIndex);
  if (passiveCard->getType() == CardType::RITUAL) {
    passiveCard->updateCharges(-passiveCard->getActivationCost());
  }
  
}


void Player::useSummonEffect(SummonEffect *effect) {
  Player *p;

  if (effect->getSide() == PlayerSide::MINE) {
    p = this;
  } else if (effect->getSide() == PlayerSide::THEIRS) {
    p = other;
  } else {
    throw std::logic_error ("PlayerSide not found.");
  }

  for (int i = 0; i < effect->getNumSummon(); ++i) {
    if (!isMaxField()) {
      addCard(effect->getCardName(), p->getDeck());
      moveCard(p->getDeck().size()-1, p->getDeck(), p->getField());
    } else {
      cout << "Field is full." << endl;
    }
  }
}

void Player::useSummonDeadEffect(SummonDeadEffect *effect) {
  std::shared_ptr<Card> card = nullptr;
  int currIndex;
  int len = graveyard.size();
  if (len <= 0) throw std::logic_error("No card in graveyard.");
  for (int i = len - 1; i >= 0; i--) {
    if (graveyard[i]->getType() == CardType::MINION) {
      card = graveyard[i];
      currIndex = i;
      break;
    }
  }
  
  if (!card) throw logic_error("No minion in graveyard.");
  card->setDefense(effect->getUndeadDefense());
  card->setAlive();
  moveCard(currIndex, graveyard, field);
}

void Player::useStatModifyEffect(std::shared_ptr<Card> card, StatModifyEffect *effect) {
  card->modifyAttack(effect->getAttackModifier(), effect->getAttackChange());
  card->modifyDefense(effect->getDefenseModifier(), effect->getDefenseChange());
}

// Helper function to get cardList for useMoveEffect()
vector<std::shared_ptr<Card> > *getCardList(Player *p, Location loc) {
  switch (loc) {
    case Location::DECK: return &p->getDeck();
    case Location::FIELD: return &p->getField();
    case Location::GRAVEYARD: return &p->getGraveyard();
    case Location::HAND: return &p->getHand();
    case Location::RITUAL: return &p->getRitual();
    default: return nullptr;  // Handle invalid location
  }
}

void Player::useMoveEffect(const size_t currIndex, vector<std::shared_ptr<Card> > &currLocation, MoveEffect *effect) {

  Player *p;
  if (effect->getSide() == PlayerSide::MINE) {
    p = this;
  } else if (effect->getSide() == PlayerSide::THEIRS) {
    p = other;
  } else if (effect->getSide() == PlayerSide::BOTH) {
    if (&currLocation == &field) {
      p = this;
    } else if (&currLocation == &other->getField()) {
      p = other;
    }
  } else {
    throw std::logic_error("PlayerSide not found.");
  }

  vector<std::shared_ptr<Card> > *destLocation = getCardList(p, effect->getLocation());
  moveCard(currIndex, currLocation, *destLocation);
}


void Player::useAbilityCostModifyEffect(std::shared_ptr<Card> card, AbilityCostModifyEffect *effect) {
  if (card->getAbility().getType() == AbilityType::ACTIVE) {
    if (effect->getAbilityCostValue() < 0 && 
        (card->getAbility().getMagicCost() < -effect->getAbilityCostValue())) {
      card->updateAbilityCost(-card->getAbility().getMagicCost());
    } else {
      card->updateAbilityCost(effect->getAbilityCostValue());
    } 
  }
}

void Player::useActionModifyEffect(std::shared_ptr<Card> card, ActionModifyEffect *effect) {
  card->updateMaxAction(effect->getActionValue());
  card->updateAction(effect->getActionValue());
}

void Player::useChargeModifyEffect(std::shared_ptr<Card> card, ChargeModifyEffect *effect) {
  card->updateCharges(effect->getChargeValue());
}

void Player::useMagicModifyEffect(Player *p, MagicModifyEffect *effect) {
  p->updateMagic(effect->getMagicModifyValue());
}

void Player::useStatusChangeEffect(std::shared_ptr<Card> card, StatusChangeEffect *effect) {
  card->changeStatus(effect->getNewStatus());
}

void Player::useRemoveEnchantEffect(std::shared_ptr<Card> card, RemoveEnchantEffect *effect) {
  vector<std::shared_ptr<Card> > *enchants = &card->getEnchantments();
  std::shared_ptr<Card> enchantCard = nullptr;
  if ((*enchants).size() > 0) {
    enchantCard = (*enchants).back();
    (*enchants).pop_back();
  }
  if (!enchantCard) throw std::logic_error("No enchant found.");
  Ability ability = enchantCard->getAbility();

  if (StatModifyEffect *effect = std::get_if<StatModifyEffect>(&ability.effectHolder)) {
    removeStatModifyEffect(card, effect);
  } else if (AbilityCostModifyEffect *effect = std::get_if<AbilityCostModifyEffect>(&ability.effectHolder)) {
    removeAbilityCostModifyEffect(card, effect);
  } else if (ActionModifyEffect *effect = std::get_if<ActionModifyEffect>(&ability.effectHolder)) {
    removeActionModifyEffect(card, effect);
  } else if (StatusChangeEffect *effect = std::get_if<StatusChangeEffect>(&ability.effectHolder)) {
    removeStatusChangeEffect(card, effect);
  }

}

void Player::removeStatModifyEffect(std::shared_ptr<Card> card, StatModifyEffect *effect) {
  if (effect->getAttackModifier() == Modify::ADD) {
    card->modifyAttack(Modify::SUBTRACT, effect->getAttackChange());
  } else if (effect->getAttackModifier() == Modify::SUBTRACT) {
    card->modifyAttack(Modify::ADD, effect->getAttackChange());
  } else if (effect->getAttackModifier() == Modify::MULTIPLY) {
    card->modifyAttack(Modify::DIVIDE, effect->getAttackChange());
  } else if (effect->getAttackModifier() == Modify::DIVIDE) {
    card->modifyAttack(Modify::MULTIPLY, effect->getAttackChange());
  }

  if (effect->getDefenseModifier() == Modify::ADD) {
    card->modifyDefense(Modify::SUBTRACT, effect->getDefenseChange());
  } else if (effect->getDefenseModifier() == Modify::SUBTRACT) {
    card->modifyDefense(Modify::ADD, effect->getDefenseChange());
  } else if (effect->getDefenseModifier() == Modify::MULTIPLY) {
    card->modifyDefense(Modify::DIVIDE, effect->getDefenseChange());
  } else if (effect->getDefenseModifier() == Modify::DIVIDE) {
    card->modifyDefense(Modify::MULTIPLY, effect->getDefenseChange());
  }
}

void Player::removeAbilityCostModifyEffect(std::shared_ptr<Card> card, AbilityCostModifyEffect *effect) {
  if (card->getAbility().getType() == AbilityType::ACTIVE) {
    card->updateAbilityCost(-effect->getAbilityCostValue());
  }
}

void Player::removeActionModifyEffect(std::shared_ptr<Card> card, ActionModifyEffect *effect) {
  card->updateMaxAction(-effect->getActionValue());
  card->updateAction(-effect->getActionValue());
}

void Player::removeStatusChangeEffect(std::shared_ptr<Card> card, StatusChangeEffect *effect) {
  card->changeStatus(MinionStatus::NONE);
}

void Player::shiftField(vector<std::shared_ptr<Card> > &displayField) {
  if (displayField.size() > 0) {
    displayField[displayField.size() - 1]->notifyDisplay();
    for (int i = displayField.size() - 1; i >= 0 ; i--) {
      displayField[i]->setX(i);
      displayField[i]->notifyDisplay(); 
    }
  }

}


void Player::removeDead() {

  const int field1Size = field.size();
  const int field2Size = other->getField().size();
  if (field1Size > 0) {
    for (int i = field1Size - 1; i >= 0 ; --i) {
      if (field[i]->getIsDead()) {
        cout << field[i]->getName() << " has been sent to the graveyard." << endl;
        moveCard(i, field, graveyard);
      }
    }
  }

  if (field2Size > 0) {
    for (int i = field2Size - 1; i >= 0; --i) {
      if (other->getField()[i]->getIsDead()) {
        cout << other->getField()[i]->getName() << " has been sent to the graveyard." << endl;
        moveCard(i, other->getField(), other->getGraveyard());
      }
    }
  }
}

void Player::resetAction() {
  for (size_t i = 0; i < field.size(); ++i) {
    field[i]->resetAction();
  }
}

void Player::attachObserver(Observer *obs) {
  observers.emplace_back(obs);
}

void Player::detachObserver() {
  observers.clear();
}

void Player::notifyDisplay() {
  td->updatePlayer(playerNumber - 1);
  if (graphics) gd->updatePlayer(playerNumber - 1);
}
