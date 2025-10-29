#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <stdexcept>
#include "Observer.h"
#include "Player.h"
#include <algorithm>
#include <random>
#include <chrono>
#include "window.h"

class GraphicsDisplay;
class TextDisplay;

class GameManager {

  int currPlayer = 0;
  bool testing = false;
  bool graphics = false;

  std::vector<Player> players;
  std::vector<std::map<int, std::shared_ptr<CardObserver>>> observers;

  // DISPLAY
  std::shared_ptr<TextDisplay> td = nullptr;
  std::shared_ptr<Xwindow> xw = nullptr;
  std::shared_ptr<GraphicsDisplay> gd = nullptr;

  // Setters
  void setName(std::ifstream &ifs);
  void setDeck(Player *player, std::string deckFile);

  public:
    GameManager(bool graphics);
    ~GameManager();

    // Prepare game
    void init(std::ifstream &ifs, std::string deck1, std::string deck2, bool testing);
    void startGame(std::ifstream &ifs);
    void shuffleDeck();

    // Notifies card for trigger
    void attachObservers(std::shared_ptr<CardObserver>obs, int playerNum);
    void detachObservers(int id);
    void notifyTriggerOnBegin();
    void notifyTriggerOnEnd();
    void notifyTriggerOnLeave();
    void notifyTriggerOnEnter(std::shared_ptr<Card> card);
};

#endif
