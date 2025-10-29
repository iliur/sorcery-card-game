#ifndef _GRAPHICS_DISPLAY_H_
#define _GRAPHICS_DISPLAY_H_
#include <iostream>
#include <vector>
#include "window.h"
#include "Player.h"
#include "Observer.h"

class GraphicsDisplay : public Observer {

  Xwindow &w;
  std::vector<Player> *p;

  void display_minion_no_ability(int x, int y, std::string name,int cost,int attack,int defence);
  void display_minion_triggered_ability(int x, int y, std::string name,int cost,int attack,int defence,
                                                  std::string trigger_desc);
  void display_minion_activated_ability(int x, int y, std::string name,int cost,int attack,int defence,
                                                  int ability_cost, std::string ability_desc);
  void display_ritual(int x, int y, std::string name,int cost,int ritual_cost,std::string ritual_desc,
                              int ritual_charges);
  void display_spell(int x, int y, std::string name,int cost,std::string desc);
  void display_enchantment_attack_defence(int x, int y, std::string name,int cost,std::string desc,
                                                  std::string attack,std::string defence);
  void display_enchantment(int x, int y, std::string name,int cost,std::string desc);
  void display_player_card(int x, int y, int player_num,std::string name,int life,int mana);

  void displayRowGraphics(int x, int y, std::vector<std::shared_ptr<Card> > cardList);
  void displayEmptyBorder(int x, int y);
  void displayPlayerBanner(int playerNum, int x, int y);
  void displayCenter(int x, int y);
  void drawName(int x, int y);
  void displayBoard(int x, int y);
  void displayMinionWithEnchants(int x, int y, std::shared_ptr<Card> minion, std::vector<std::shared_ptr<Card> > enchants);
  void displayMinionGeneral(int x, int y, std::shared_ptr<Card> minion);
  void displayEnchantGeneral(int x, int y, std::shared_ptr<Card> enchant);
  void displaySpellGeneral(int x, int y, std::shared_ptr<Card> spell);
  void displayRitualGeneral(int x, int y, std::shared_ptr<Card> ritual);
  void displayCardGeneral(int x, int y, std::shared_ptr<Card> card);

  void displayRowEmpty(int x, int y);
  void updateBoard(int x, int y, int boardX, int boardY, std::shared_ptr<Card> card);
  void updatePlayerCard(int x, int y, int currPlayer);
  
 public:
  GraphicsDisplay(Xwindow &w, std::vector<Player> *p);
  ~GraphicsDisplay() = default;

  void init();
  void displayInspect(std::shared_ptr<Card> minion);
  void updatePlayer(int currPlayer);
  void displayHand(std::vector<std::shared_ptr<Card> > cardList, int currPlayer);
  void notify(int boardX, int boardY, bool remove, int currPlayer) override;

};

#endif
