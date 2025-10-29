#include <iostream>
#include "TextDisplay.h"
#include "Player.h"
#include "Card.h"
using namespace std;

TextDisplay::TextDisplay(vector<Player> *p): p{p} {}


card_template_t setCardGeneral(std::shared_ptr<Card> card) {
  if (!card) return CARD_TEMPLATE_BORDER;
  else if (card->getType() == CardType::MINION) {
      return minionTemplate(card);
  } else if (card->getType() == CardType::ENCHANTMENT) {
      return enchantTemplate(card);
  } else if(card->getType() == CardType::SPELL) {
      return spellTemplate(card);
  } else if (card->getType() == CardType::RITUAL) {
      return ritualTemplate(card);
  } else {
    return CARD_TEMPLATE_EMPTY;
  }
}

void TextDisplay::notify(int boardX, int boardY, bool remove, int currPlayer) {
  std::shared_ptr<Card> card = nullptr;

  if (boardY == 0 && boardX == 0) {
    card = (*p)[0].getRitual()[0];
  } 
  
  else if (boardY == 1) {
    card = (*p)[0].getField()[boardX];
    int len = (*p)[0].getField().size();
    if (len <= boardX) {
      card = nullptr;
    }
  } 

  else if (boardY == 2) {
    card = (*p)[1].getField()[boardX];
    int len = (*p)[1].getField().size();
    if (len <= boardX) {
      card = nullptr;
    }
  } 

  else if (boardY == 0 && boardX == 4) {
    card = (*p)[0].getGraveyard()[(*p)[0].getGraveyard().size() - 1];
  } 
  else if (boardY == 3 && boardX == 4) {
    card = (*p)[1].getGraveyard()[(*p)[1].getGraveyard().size() - 1];
  }
  
  else if (boardY == 3 && boardX == 0) {
    card = (*p)[1].getRitual()[0];
  } 
  
  if (remove) card = nullptr;

  updateBoard(boardX, boardY, card);
}

void TextDisplay::updateBoard(int boardX, int boardY, std::shared_ptr<Card>  card) {
  int lenY = listDisplay.size();
  if (boardY < 0 || boardY >= lenY) throw ("BoardY is out of index.");
  int lenX = listDisplay[0].size();
  if (boardX < 0 || boardX >= lenX) throw ("BoardX is out of index.");
  listDisplay[boardY][boardX] = setCardGeneral(card); 
}
 
void TextDisplay::displayHand(int playerIndex) {
  vector<card_template_t> tempList;
  for (size_t i = 0; i < (*p)[playerIndex].getHand().size(); i++) {
    tempList.emplace_back(setCardGeneral((*p)[playerIndex].getHand()[i]));
  }
  displayRowGraphics(tempList, false);
}

void TextDisplay::initBoard() {

  for (size_t i = 0; i < 4; i++) {
    vector<card_template_t> temp;
    for (size_t j = 0; j < 5; j++) {
      temp.emplace_back(CARD_TEMPLATE_BORDER);
    }
    listDisplay.emplace_back(temp);
  }
  // empty boxes between ritual, player, and graveyard
  listDisplay[0][1] = CARD_TEMPLATE_EMPTY;
  listDisplay[0][3] = CARD_TEMPLATE_EMPTY;

  listDisplay[3][1] = CARD_TEMPLATE_EMPTY;
  listDisplay[3][3] = CARD_TEMPLATE_EMPTY;

  // player cards
  listDisplay[0][2] = display_player_card((*p)[0].getPlayerNumber(), (*p)[0].getName(), (*p)[0].getHealth(), (*p)[0].getMagic());
  listDisplay[3][2] = display_player_card((*p)[1].getPlayerNumber(), (*p)[1].getName(), (*p)[1].getHealth(), (*p)[1].getMagic());

}

void rowBorder(const string leftCorner, const string rightCorner) {
  int cardWidth = CARD_TEMPLATE_EMPTY[0].size();
  int boardWidth = 5 * cardWidth + 1;
  for (int i = 0; i < boardWidth; ++i) {
    if (i == 0) {
      cout << leftCorner;
    }
    if (i == boardWidth - 1) {
      cout << rightCorner;
    }
    else {
      cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
  }
  cout << endl;
}

void TextDisplay::displayBoard() {

  rowBorder(EXTERNAL_BORDER_CHAR_TOP_LEFT, EXTERNAL_BORDER_CHAR_TOP_RIGHT);

  for (size_t i = 0; i < listDisplay.size(); i++) {
    displayRowGraphics(listDisplay[i], true);
    if (i == 1) {
      displayGraphics(CENTRE_GRAPHIC);
    }
  }

  rowBorder(EXTERNAL_BORDER_CHAR_BOTTOM_LEFT, EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT);

}


void displayCard(card_template_t temp) {
  for (size_t i = 0; i < temp.size(); i++) {
    cout << temp[i] << endl;
  }
}

void TextDisplay::inspectMinion(std::shared_ptr<Card> card) {
  card_template_t minion = setCardGeneral(card);
  vector<vector<card_template_t>> enchantList;
  vector<std::shared_ptr<Card> > enchants = card->getEnchantments();
  int row = 0;
  int col = 0;

  vector<card_template_t> temp;

  // enchantList.emplace_back(temp);
  for (size_t i = 0; i < enchants.size(); i++) {
    temp.emplace_back(setCardGeneral(enchants[i]));
    col++;
    if (col == 5) {
      enchantList.emplace_back(temp);
      col = 0;
      row++;
      temp.clear();
    }
  }

  enchantList.emplace_back(temp);

  displayCard(minion);
  for (size_t i = 0; i < enchantList.size(); i++) {
    displayRowGraphics(enchantList[i], false);
  }
}

void TextDisplay::updatePlayer(int currPlayer) {
  if (currPlayer == 0) {
    listDisplay[0][2] = display_player_card((*p)[0].getPlayerNumber(), (*p)[0].getName(), (*p)[0].getHealth(), (*p)[0].getMagic());
  } else {
    listDisplay[3][2] = display_player_card((*p)[1].getPlayerNumber(), (*p)[1].getName(), (*p)[1].getHealth(), (*p)[1].getMagic());
  }
}
