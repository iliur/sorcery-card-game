#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_
#include <iostream>
#include <vector>
#include "ascii_graphics.h"
#include "Observer.h"
class Player;
class Card;

class TextDisplay: public Observer {

  std::vector<Player> *p;
  std::vector<std::vector<card_template_t>> listDisplay;

  void updateBoard(int boardX, int boardY, std::shared_ptr<Card> card);
  

 public:
  TextDisplay(std::vector<Player> *players);

  void initBoard();
  void inspectMinion(std::shared_ptr<Card> card);
  void updatePlayer(int currPlayer);
  void notify(int boardX, int boardY, bool remove, int currPlayer);
  void displayHand(int playerIndex);
  void displayBoard();
  
  ~TextDisplay() = default;

};

#endif
