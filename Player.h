#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
#include "Card.h"

const size_t MAX_HAND = 5;
const size_t MAX_FIELD = 5;

class GameManager;
class GraphicsDisplay;
class TextDisplay;

class Player {
  int playerNumber;
  std::string name;
  int health = 20;
  int magic = 3;

  std::vector<std::shared_ptr<Card>> deck;
  std::vector<std::shared_ptr<Card>> field;
  std::vector<std::shared_ptr<Card>> graveyard;
  std::vector<std::shared_ptr<Card>> ritual;
  std::vector<std::shared_ptr<Card>> hand;

  GameManager *g;
  GraphicsDisplay *gd;
  TextDisplay *td;
  bool graphics;
  Player *other;

  std::vector<Observer *> observers;

  // ---- HELPER FUNCTIONS ------------------
  void moveCard(size_t index, std::vector<std::shared_ptr<Card> > &source, std::vector<std::shared_ptr<Card> > &destination);
  void updateHealth(int value);
  void useAbility(Ability *ability, std::shared_ptr<Card> card);
  void useAbility(Ability *ability, Player *p);
  void useAbility(Ability *ability, std::vector<std::shared_ptr<Card> > &cardList);
  void useAbility(Ability *ability, std::vector<std::shared_ptr<Card> > &cardList, size_t cardIndex);
  void shiftField(std::vector<std::shared_ptr<Card> > &displayField);
  // ----------------------------------------


  // ---- EFFECT FUNCTIONS ------------------
  void useSummonEffect(SummonEffect *effect);
  void useSummonDeadEffect(SummonDeadEffect *effect);
  void useStatModifyEffect(std::shared_ptr<Card> card, StatModifyEffect *effect);
  void useMoveEffect(const size_t currIndex, std::vector<std::shared_ptr<Card> > &currLocation, MoveEffect *effect);
  void useAbilityCostModifyEffect(std::shared_ptr<Card> card, AbilityCostModifyEffect *effect);
  void useActionModifyEffect(std::shared_ptr<Card> card, ActionModifyEffect *effect);
  void useChargeModifyEffect(std::shared_ptr<Card> card, ChargeModifyEffect *effect);
  void useMagicModifyEffect(Player *p, MagicModifyEffect *effect);
  void useStatusChangeEffect(std::shared_ptr<Card> card, StatusChangeEffect *effect);
  void useRemoveEnchantEffect(std::shared_ptr<Card> card, RemoveEnchantEffect *effect);
  // ----------------------------------------

  // ---- REMOVE EFFECT FUNCTIONS -----------
  void removeStatModifyEffect(std::shared_ptr<Card> card, StatModifyEffect *effect);
  void removeAbilityCostModifyEffect(std::shared_ptr<Card> card, AbilityCostModifyEffect *effect);
  void removeActionModifyEffect(std::shared_ptr<Card> card, ActionModifyEffect *effect);
  void removeStatusChangeEffect(std::shared_ptr<Card> card, StatusChangeEffect *effect);
  // ----------------------------------------

  public:
    Player(int playerNumber);
    ~Player();
    
    // ---- SETTERS, GETTERS, CHECKERS --------------
    void setName(std::string name);
    void setGameManager(GameManager *g);
    void setOtherPlayer(Player *p);
    void setGraphics(bool graphics);
    void setGraphicsDisplay(GraphicsDisplay *gd);
    void setTextDisplay(TextDisplay *td);
    int getPlayerNumber();
    std::string getName();
    int getHealth();
    int getMagic();

    std::vector<std::shared_ptr<Card>> &getDeck();
    std::vector<std::shared_ptr<Card>> &getField();
    std::vector<std::shared_ptr<Card>> &getGraveyard();
    std::vector<std::shared_ptr<Card>> &getRitual();
    std::vector<std::shared_ptr<Card>> &getHand();
    bool isMaxHand();
    bool isMaxField();
    bool isAlive();
    void updateMagic(int value);
    void resetAction();
    // ----------------------------------------


    // ---- USER COMMANDS ---------------------
    void drawCard();
    void discard(int cardNum);
    void attack(int attackerNum);
    void attack(int attackerNum, int defenderNum);
    void playOnRitual(int handNum, int playerNum, bool testing);
    void play(int handNum, bool testing);
    void play(int handNum, int playerNum, int targetNum, bool testing);
    void use(int minionNum, bool testing);
    void use(int minionNum, int playerNum, int targetNum, bool testing);
    void inspect(int cardNum);
    // ----------------------------------------

    // ---- PUBLIC HELPER FUNCTION ------------
    void addCard(std::string cardName, std::vector<std::shared_ptr<Card> > &destination);
    void usePassive(int cardId); // possibly have to redesign 
    void usePassive(int cardId, std::shared_ptr<Card> card);
    void removeDead();
    void attachObserver(Observer *obs);
    void detachObserver();
    void notifyDisplay();  
    // ----------------------------------------

};

#endif
