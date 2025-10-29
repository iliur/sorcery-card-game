#include <iostream>
#include "GraphicsDisplay.h"
using namespace std;

const std::vector<std::string> CENTRE_GRAPHIC = 
      {                                                                
       " ______                                   ",
       "/  ____|                                  ",
       "| (___   ___  _ __ ___ ___ _ __ _   _     ",
       "\\___  \\ / _ \\| '__/ __/ _ \\ '__| | | |",
       "____)  | (_) | | | (_|  __/ |  | |_| |     ",
       "|_____/ \\___/|_|  \\___\\___|_|   \\__, |",
       "                                 __/ |    ",
       "                                |___/     ",};


const int xGap = 8; // CHANGE THIS
const int cardWidth = 28 * xGap, cardHeight = 16 * xGap, yGap = 2 * xGap;
const int edge = 15;

GraphicsDisplay::GraphicsDisplay(Xwindow &w, vector<Player> *p): w{w}, p{p} {}

void GraphicsDisplay::display_minion_no_ability(int x, int y, std::string name,int cost,int attack,int defence) {
  w.fillRectangle(x, y, cardWidth, cardHeight, Xwindow::White);
  w.drawString(x + xGap, y + yGap, name);
  w.drawRectangle(x, y, cardWidth, cardHeight);
  w.drawLine(x, y + 1.5 * yGap, x + cardWidth, y + 1.5 * yGap);

  // magic cost
  w.drawLine(x + cardWidth - 5 * xGap, y, x + cardWidth - 5 * xGap, y + 1.5 * yGap);
  w.drawString(x + cardWidth - 2.5 * xGap, y + yGap, to_string(cost));

  // CardType
  w.drawLine(x, y + yGap * 3, x + cardWidth, y + yGap * 3);
  w.drawString(cardWidth + x - 5 * xGap, y + yGap * 2.5, "Minion");

  // Attack Box
  w.drawRectangle(x, y + cardHeight - yGap * 1.5, xGap * 5, yGap * 1.5);
  w.drawString(x + xGap * 2, y + cardHeight - yGap * 0.5, to_string(attack));

  // Defense Box
  w.drawRectangle(x + cardWidth - 5 * xGap, y + cardHeight - yGap * 1.5, xGap * 5, yGap * 1.5);
  w.drawString(x + cardWidth - 2.5 * xGap, y + cardHeight - yGap * 0.5, to_string(defence));

}

void GraphicsDisplay::display_minion_triggered_ability(int x, int y, std::string name,int cost,int attack,int defence,
                                                std::string trigger_desc) {
  w.fillRectangle(x, y, cardWidth, cardHeight, Xwindow::White);
  w.drawString(x + xGap, y + yGap, name);
  w.drawRectangle(x, y, cardWidth, cardHeight);
  w.drawLine(x, y + 1.5 * yGap, x + cardWidth, y + 1.5 * yGap);

  // magic cost
  w.drawLine(x + cardWidth - 5 * xGap, y, x + cardWidth - 5 * xGap, y + 1.5 * yGap);
  w.drawString(x + cardWidth - 2.5 * xGap, y + yGap, to_string(cost));


  // CardType
  w.drawLine(x, y + yGap * 3, x + cardWidth, y + yGap * 3);
  w.drawString(cardWidth + x - 5 * xGap, y + yGap * 2.5, "Minion");

  // Attack Box
  w.drawRectangle(x, y + cardHeight - yGap * 1.5, xGap * 5, yGap * 1.5);
  w.drawString(x + xGap * 2, y + cardHeight - yGap * 0.5, to_string(attack));

  // Defense Box
  w.drawRectangle(x + cardWidth - 5 * xGap, y + cardHeight - yGap * 1.5, xGap * 5, yGap * 1.5);
  w.drawString(x + cardWidth - 2.5 * xGap, y + cardHeight - yGap * 0.5, to_string(defence));

  // Description
  w.drawWrappedString(x + xGap, y + yGap * 4, cardWidth, trigger_desc);

}
void GraphicsDisplay::display_minion_activated_ability(int x, int y, std::string name,int cost,int attack,int defence,
                                                int ability_cost, std::string ability_desc) {
  w.fillRectangle(x, y, cardWidth, cardHeight, Xwindow::White);
  w.drawString(x + xGap, y + yGap, name);
  w.drawRectangle(x, y, cardWidth, cardHeight);
  w.drawLine(x, y + 1.5 * yGap, x + cardWidth, y + 1.5 * yGap);

  // magic cost
  w.drawLine(x + cardWidth - 5 * xGap, y, x + cardWidth - 5 * xGap, y + 1.5 * yGap);
  w.drawString(x + cardWidth - 2.5 * xGap, y + yGap, to_string(cost));

  // CardType
  w.drawLine(x, y + yGap * 3, x + cardWidth, y + yGap * 3);
  w.drawString(cardWidth + x - 5 * xGap, y + yGap * 2.5, "Minion");
  
  // Ability Cost
  w.drawRectangle(x, y + yGap * 3, xGap * 5, yGap * 1.5);
  w.drawString(x + xGap * 2, y + yGap * 4, to_string(ability_cost));

  // Attack Box
  w.drawRectangle(x, y + cardHeight - yGap * 1.5, xGap * 5, yGap * 1.5);
  w.drawString(x + xGap * 2, y + cardHeight - yGap * 0.5, to_string(attack));

  // Defense Box
  w.drawRectangle(x + cardWidth - 5 * xGap, y + cardHeight - yGap * 1.5, xGap * 5, yGap * 1.5);
  w.drawString(x + cardWidth - 2.5 * xGap, y + cardHeight - yGap * 0.5, to_string(defence));

  // Description
  w.drawWrappedString(x + xGap * 6, y + yGap * 4, cardWidth - xGap * 6, ability_desc);

}
void GraphicsDisplay::display_ritual(int x, int y, std::string name,int cost,int ritual_cost,std::string ritual_desc,
                            int ritual_charges) {
  w.fillRectangle(x, y, cardWidth, cardHeight, Xwindow::White);
  w.drawString(x + xGap, y + yGap, name);
  w.drawRectangle(x, y, cardWidth, cardHeight);
  w.drawLine(x, y + 1.5 * yGap, x + cardWidth, y + 1.5 * yGap);

  // magic cost
  w.drawLine(x + cardWidth - 5 * xGap, y, x + cardWidth - 5 * xGap, y + 1.5 * yGap);
  w.drawString(x + cardWidth - 2.5 * xGap, y + yGap, to_string(cost));

  // CardType
  w.drawLine(x, y + yGap * 3, x + cardWidth, y + yGap * 3);
  w.drawString(cardWidth + x - 5 * xGap, y + yGap * 2.5, "Ritual");
  
  // Ability Cost
  w.drawRectangle(x, y + yGap * 3, xGap * 5, yGap * 1.5);
  w.drawString(x + xGap * 2, y + yGap * 4, to_string(ritual_cost));

  // Defense Box
  w.drawRectangle(x + cardWidth - 5 * xGap, y + cardHeight - yGap * 1.5, xGap * 5, yGap * 1.5);
  w.drawString(x + cardWidth - 2.5 * xGap, y + cardHeight - yGap * 0.5, to_string(ritual_charges));

  // Description
  w.drawWrappedString(x + xGap * 6, y + yGap * 4, cardWidth - xGap * 6, ritual_desc);

}
void GraphicsDisplay::display_spell(int x, int y, std::string name,int cost,std::string desc) {
  w.fillRectangle(x, y, cardWidth, cardHeight, Xwindow::White);
  w.drawString(x + xGap, y + yGap, name);
  w.drawRectangle(x, y, cardWidth, cardHeight);
  w.drawLine(x, y + 1.5 * yGap, x + cardWidth, y + 1.5 * yGap);

  // magic cost
  int magicCostLine = x + cardWidth - xGap * 4;
  w.drawLine(magicCostLine - xGap, y, magicCostLine - xGap, y + 1.5 * yGap);
  w.drawString(magicCostLine + xGap * 2, y + yGap, to_string(cost));

  // CardType
  w.drawLine(x, y + yGap * 3, x + cardWidth, y + yGap * 3);
  w.drawString(cardWidth + x - 4.5 * xGap, y + yGap * 2.5, "Spell");
  
  // Description
  w.drawWrappedString(x + xGap, y + yGap * 4, cardWidth, desc);

}
void GraphicsDisplay::display_enchantment_attack_defence(int x, int y, std::string name,int cost,std::string desc,
                                                std::string attack,std::string defence) {
  w.fillRectangle(x, y, cardWidth, cardHeight, Xwindow::White);
  w.drawString(x + xGap, y + yGap, name);
  w.drawRectangle(x, y, cardWidth, cardHeight);
  w.drawLine(x, y + 1.5 * yGap, x + cardWidth, y + 1.5 * yGap);

  // magic cost
  w.drawLine(x + cardWidth - 5 * xGap, y, x + cardWidth - 5 * xGap, y + 1.5 * yGap);
  w.drawString(x + cardWidth - 2.5 * xGap, y + yGap, to_string(cost));

  // CardType
  w.drawLine(x, y + yGap * 3, x + cardWidth, y + yGap * 3);
  w.drawString(cardWidth + x - 8 * xGap, y + yGap * 2.5, "Enchantment");
  
  // Attack Box
  w.drawRectangle(x, y + cardHeight - yGap * 1.5, xGap * 5, yGap * 1.5);
  w.drawString(x + xGap * 2, y + cardHeight - yGap * 0.5, attack);

  // Defense Box
  w.drawRectangle(x + cardWidth - 5 * xGap, y + cardHeight - yGap * 1.5, xGap * 5, yGap * 1.5);
  w.drawString(x + cardWidth - 2.5 * xGap, y + cardHeight - yGap * 0.5, defence);

  // Description
  w.drawWrappedString(x + xGap, y + yGap * 4, cardWidth, desc);
}
void GraphicsDisplay::display_enchantment(int x, int y, std::string name,int cost,std::string desc) {
  w.fillRectangle(x, y, cardWidth, cardHeight, Xwindow::White);
  w.drawString(x + xGap, y + yGap, name);
  w.drawLine(x, y + 1.5 * yGap, x + cardWidth, y + 1.5 * yGap);

  // magic cost
  w.drawLine(x + cardWidth - 5 * xGap, y, x + cardWidth - 5 * xGap, y + 1.5 * yGap);
  w.drawString(x + cardWidth - 2.5 * xGap, y + yGap, to_string(cost));

  // CardType
  w.drawLine(x, y + yGap * 3, x + cardWidth, y + yGap * 3);
  w.drawString(cardWidth + x - 8 * xGap, y + yGap * 2.5, "Enchantment");
  
  // Description
  w.drawWrappedString(x + xGap, y + yGap * 4, cardWidth, desc);


  w.drawRectangle(x, y, cardWidth, cardHeight);


}
void GraphicsDisplay::display_player_card(int x, int y, int currPlayer,std::string name,int life,int mana) {
    int len = name.length();
    // name
    w.fillRectangle(x, y, cardWidth, cardHeight, Xwindow::White);
    w.drawString(x + cardWidth/2 - 3 * len, y + cardHeight/2 - 1.5 * yGap, name);
    w.drawRectangle(x, y, cardWidth, cardHeight);

    // HP
    w.drawRectangle(x, y + cardHeight - yGap * 1.5, xGap * 5, yGap * 1.5);
    w.drawString(x + xGap * 2, y + cardHeight - yGap * 0.5, to_string(life));

    // Mana
    w.drawRectangle(x + cardWidth - 5 * xGap, y + cardHeight - yGap * 1.5, xGap * 5, yGap * 1.5);
    w.drawString(x + cardWidth - 2.5 * xGap, y + cardHeight - yGap * 0.5, to_string(mana));
}

void GraphicsDisplay::displayEmptyBorder(int x, int y) {
  w.fillRectangle(x, y, cardWidth, cardHeight, Xwindow::White);
  w.drawRectangle(x, y, cardWidth, cardHeight);
}

void GraphicsDisplay::displayPlayerBanner(int playerNum, int x, int y) {
  if (playerNum == 1) {
    displayEmptyBorder(x, y);
    display_player_card(x + (cardWidth + xGap) * 2, y, playerNum, (*p)[0].getName(), (*p)[0].getHealth(), (*p)[0].getMagic());
    displayEmptyBorder(x + (cardWidth + xGap) * 4, y);
  } else {
    displayEmptyBorder(x, y);
    display_player_card(x + (cardWidth + xGap) * 2, y, playerNum, (*p)[1].getName(), (*p)[1].getHealth(), (*p)[1].getMagic());
    displayEmptyBorder(x + (cardWidth + xGap) * 4, y);
  }
}

void GraphicsDisplay::drawName(int x, int y) {
  for (size_t i = 0; i < CENTRE_GRAPHIC.size(); i++) {
    w.drawString(x, y + i * 10, CENTRE_GRAPHIC[i]);
  }
}

void GraphicsDisplay::displayCenter(int x, int y) {
  w.drawRectangle(x, y, cardWidth * 5 + xGap * 6, cardHeight * 0.6);
  drawName(x + cardWidth * 2.2, y + yGap * 0.5);
}


void GraphicsDisplay::displayMinionWithEnchants(int x, int y, std::shared_ptr<Card> minion, vector<std::shared_ptr<Card> > enchants) {

  // containter
  w.fillRectangle(x, y, cardWidth + 2 * xGap, cardHeight * 5.6 + 3 * yGap + yGap, Xwindow::White);
  w.drawRectangle(x, y, cardWidth + 2 * xGap, cardHeight * 5.6 + 3 * yGap + yGap);


  // minion
  w.drawString(x + xGap, y + yGap, "INSPECTING MINION");
  display_minion_activated_ability(x + xGap, y + 2 * yGap, minion->getName(), minion->getMagicCost(), minion->getAttack(), minion->getDefense(), minion->getAbility().getMagicCost(), minion->getAbility().getDescription());

  // enchants
  w.drawString(x + xGap, y + cardHeight + yGap * 4, "ENCHANTMENTS");
  size_t len = enchants.size();

  for (size_t i = 0; i < len; i++) {
    int difference = (2 * cardHeight + 4 * yGap) / len;
    int distance =  y + cardHeight + yGap * 5 + difference * i;
    display_enchantment(x + xGap, distance, enchants[i]->getName(), enchants[i]->getMagicCost(), enchants[i]->getAbility().getDescription());
  }
}


void GraphicsDisplay::displayMinionGeneral(int x, int y, std::shared_ptr<Card> minion) {
  if (minion->getAbility().getType() == AbilityType::NONE) {
    display_minion_no_ability(x, 
                              y, 
                        minion->getName(), 
                        minion->getMagicCost(), 
                      minion->getAttack(), 
                     minion->getDefense());

  } else if (minion->getAbility().getType() == AbilityType::PASSIVE) {
    display_minion_triggered_ability(x, y,
                                minion->getName(), 
                                      minion->getMagicCost(), 
                                      minion->getAttack(),
                                      minion->getDefense(),
                                      minion->getAbility().getDescription());
  } else if (minion->getAbility().getType() == AbilityType::ACTIVE) {
    display_minion_activated_ability(x, y,
                                                minion->getName(),
                                              minion->getMagicCost(),
                                              minion->getAttack(),
                                              minion->getDefense(),
                                              minion->getAbility().getMagicCost(),
                                              minion->getAbility().getDescription()); // the 5th parameter is ability_cost
  } // else not a valid minionType
}

void GraphicsDisplay::displayEnchantGeneral(int x, int y, std::shared_ptr<Card> enchant) {
  if (enchant->getAttackDesc() == "") {
    display_enchantment(x, y, enchant->getName(),
                                         enchant->getMagicCost(),
                                         enchant->getAbility().getDescription());
  } else {
    display_enchantment_attack_defence(x, y, enchant->getName(), 
                                                          enchant->getMagicCost(),
                                                          enchant->getAbility().getDescription(), 
                                                          enchant->getAttackDesc(), 
                                                          enchant->getDefenseDesc());
  }
}

void GraphicsDisplay::displaySpellGeneral(int x, int y, std::shared_ptr<Card> spell) {
  display_spell(x, y, spell->getName(), 
                                       spell->getMagicCost(), 
                                       spell->getAbility().getDescription());

}

void GraphicsDisplay::displayRitualGeneral(int x, int y, std::shared_ptr<Card> ritual) {
  display_ritual(x, y, ritual->getName(), 
                                   ritual->getMagicCost(), 
                                   ritual->getActivationCost(), 
                                   ritual->getAbility().getDescription(), 
                                   ritual->getCharges());
}

void GraphicsDisplay::displayCardGeneral(int x, int y, std::shared_ptr<Card> card) {

  if (!card) {
    displayEmptyBorder(x, y);
  }
  else if (card->getType() == CardType::MINION) {
    displayMinionGeneral(x, y, card);
  }
  else if (card->getType() == CardType::SPELL) {
    displaySpellGeneral(x, y, card);
  }
  else if (card->getType() == CardType::ENCHANTMENT) {
    displayEnchantGeneral(x, y, card);
  }
  else if (card->getType() == CardType::RITUAL) {
    displayRitualGeneral(x, y, card);
  } 
}


void GraphicsDisplay::displayRowGraphics(int x, int y, vector<std::shared_ptr<Card> > cardList) {
  for (size_t i = 0; i < cardList.size(); i++) {
    displayCardGeneral(x + (cardWidth + xGap) * i, y, cardList[i]);
  }
  for (size_t i = cardList.size(); i < 5; i++) {
    displayEmptyBorder(x + (cardWidth + xGap) * i, y);
  }
}

void GraphicsDisplay::displayRowEmpty(int x, int y) {
  for (int i = 0; i < 5; i++) {
    displayEmptyBorder(x + (cardWidth + xGap) * i, y);
  }
}


void GraphicsDisplay::displayBoard(int x, int y) {

  // WHOLE BORDER
  w.drawRectangle(x, y, cardWidth * 5 + xGap * 6, cardHeight * 4.6 + yGap * 3);

  // PLAYER 1
  displayPlayerBanner((*p)[0].getPlayerNumber(), x + xGap, y + yGap / 2);

  // FIELD 1
  displayRowEmpty(x + xGap, y + (yGap + cardHeight) * 1);

  // RIVER
  displayCenter(x, y + yGap * 1.5 + cardHeight * 2);

  // FIELD 2
  displayRowEmpty(x + xGap, y + (yGap + cardHeight) * 2.6 - yGap / 2);

  // PLAYER 2
  displayPlayerBanner((*p)[1].getPlayerNumber(), x + xGap, y + yGap * 2.5 + cardHeight * 3.6);

  // HAND
  displayRowEmpty(x + xGap, y + (yGap + cardHeight) * 4.6 - yGap);
}

void GraphicsDisplay::updateBoard(int x, int y, int boardX, int boardY, std::shared_ptr<Card> card) {

  // Player 1's Side
  if (boardY <= 1) {
    displayCardGeneral(x + boardX * (cardWidth + xGap) + xGap, y + boardY * (cardHeight + yGap / 2) + yGap / 2, card);
  } 
  // Player 2's Side
  else if (boardY == 2) {
    displayCardGeneral(x + boardX * (cardWidth + xGap) + xGap, y + (yGap + cardHeight) * 2.6 - yGap / 2, card);
  } else if (boardY == 3) {
    displayCardGeneral(x + boardX * (cardWidth + xGap) + xGap, y + yGap * 2.5 + cardHeight * 3.6, card);
  } 
}


void GraphicsDisplay::displayHand(vector<std::shared_ptr<Card> > cardList, int currPlayer) {
  w.fillRectangle(edge + xGap, edge + (cardHeight + yGap) * 5.6 - yGap * 1.5, cardWidth * 3, yGap * 2, Xwindow::White);
  w.drawString(edge + xGap, edge + (cardHeight + yGap) * 5.6 - yGap, (*p)[currPlayer].getName() + "'s Hand");
  displayRowGraphics(edge + xGap, edge + (cardHeight + yGap) * 4.6 - yGap, cardList);
}

void GraphicsDisplay::init() {
  displayBoard(edge, edge);
}

void GraphicsDisplay::notify(int boardX, int boardY, bool remove, int currPlayer) {
  std::shared_ptr<Card> card = nullptr;

  // player 1 field
  if (boardY == 1) {
    card = (*p)[0].getField()[boardX];
    int len = (*p)[0].getField().size();
    if (len <= boardX) {
      card = nullptr;
    }
  } 
  
  // player 2 field
  else if (boardY == 2) {
    card = (*p)[1].getField()[boardX];
    int len = (*p)[1].getField().size();
    if (len <= boardX) {
      card = nullptr;
    }
  }

  // player 1 ritual
  else if (boardY == 0 && boardX == 0) {
    card = (*p)[0].getRitual()[0];
  } 
  // player 2 ritual
  else if (boardY == 3 && boardX == 0) {
    card = (*p)[1].getRitual()[0];
  } 
  // player 1 graveyard
  else if (boardY == 0 && boardX == 4) {
    card = (*p)[0].getGraveyard()[(*p)[0].getGraveyard().size() - 1];
  } 
  // player 2 graveyard
  else if (boardY == 3 && boardX == 4) {
    card = (*p)[1].getGraveyard()[(*p)[1].getGraveyard().size() - 1];
  }

  // removes card  
  if (remove) card = nullptr;
  
  updateBoard(edge, edge, boardX, boardY, card);
}

void GraphicsDisplay::displayInspect(std::shared_ptr<Card>  minion) {
  displayMinionWithEnchants(edge + (cardWidth + xGap) * 5 + 3 * xGap, edge, minion, minion->getEnchantments());
}



void GraphicsDisplay::updatePlayerCard(int x, int y, int currPlayer) {
  if (currPlayer == 0) {
    display_player_card(x + cardWidth * 2 + xGap * 3, y + yGap / 2, 0, (*p)[0].getName(), (*p)[0].getHealth(), (*p)[0].getMagic());
  } else {
    display_player_card(x + cardWidth * 2 + xGap * 3, y + yGap * 2.5 + cardHeight * 3.6, 1, (*p)[1].getName(), (*p)[1].getHealth(), (*p)[1].getMagic());
  }
}

void GraphicsDisplay::updatePlayer(int currPlayer) {
  updatePlayerCard(edge, edge, currPlayer);
}
