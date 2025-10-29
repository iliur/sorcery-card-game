#include "GameManager.h"
#include "GraphicsDisplay.h"
#include "TextDisplay.h"

using namespace std;

GameManager::GameManager(bool graphics): graphics{graphics} {
  players.emplace_back(Player{1});
  players.emplace_back(Player{2});
  td = make_shared<TextDisplay>(&players);
}

GameManager::~GameManager() { }

void viewCommands() {
  cout << "Commands: help -- Display this message." << endl;
  cout << "\t  end -- End the current player's turn." << endl;
  cout << "\t  quit -- End the game." << endl;
  cout << "\t  attack minion other-minion -- Orders minion to attack other-minion." << endl;
  cout << "\t  attack minion -- Orders minion to attack the opponent." << endl;
  cout << "\t  play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << endl;
  cout << "\t  use minion [target-player target-card] -- Use minion's special ability, optionally targeting target-card owned by target-player." << endl;
  cout << "\t  inspect minion -- View a minion's card and all enchantments on that minion." << endl;
  cout << "\t  hand -- Describe all cards in you hand." << endl;
  cout << "\t  board -- Describe all cards on the board." << endl;
}

// reads input from file and additional input from command line
string getInput(ifstream &ifs) {

  string line;

  while (line == "") {
    if (ifs.fail()) {
      ifs.clear();
      ifs.close();
    }  
    // takes in input from file
    if (ifs.is_open()) {
      while (getline(ifs, line)) {
        if (!line.empty()) break;
      }
    }
    // takes in additional input from command line
    if (!ifs.is_open())  {
      getline(cin, line);
    }
  }
  return line;
}

void GameManager::setName(ifstream &ifs) {
  string name1 = getInput(ifs);
  string name2 = getInput(ifs);
  players[0].setName(name1);
  players[1].setName(name2);
}

void GameManager::setDeck(Player *player, string deckFile) {
  ifstream ifs{deckFile};
  string cardName;
  while (getline(ifs, cardName)) {
    player->addCard(cardName, player->getDeck());
  }
}

void GameManager::init(ifstream &ifs, string deck1, string deck2, bool testing) {
  setName(ifs);
  setDeck(&players[0], deck1);
  setDeck(&players[1], deck2);
  this->testing = testing;
  observers.emplace_back();
  observers.emplace_back();
  td->initBoard();
  if (graphics) {
    xw = make_shared<Xwindow>();
    gd = make_shared<GraphicsDisplay>(*xw, &players);
    gd->init();
    players[0].setGraphicsDisplay(gd.get());
    players[1].setGraphicsDisplay(gd.get());
    players[0].attachObserver(gd.get());
    players[1].attachObserver(gd.get());
  }
  players[0].setGameManager(this);
  players[0].setOtherPlayer(&players[1]);
  players[1].setGameManager(this);
  players[1].setOtherPlayer(&players[0]);
  players[0].setGraphics(graphics);
  players[1].setGraphics(graphics);
  players[0].setTextDisplay(td.get());
  players[1].setTextDisplay(td.get());
  players[0].attachObserver(td.get());
  players[1].attachObserver(td.get());
} 


void GameManager::startGame(ifstream &ifs) {
  cout << "Game start!" << endl;
  string line, cmd;

  if (!testing) shuffleDeck();
  
  // Outputs player turn
  cout << "Player " << currPlayer + 1 << " turn." << endl;
  players[currPlayer].resetAction();
  players[currPlayer].updateMagic(1);
  players[currPlayer].drawCard();

  while (true) {
    try {

      // ---- BEFORE A COMMAND ------------------
      if (!players[currPlayer].isAlive()) {
        cout << players[!currPlayer].getName() << " has won!" << endl;
        break;
      }
      if (!players[!currPlayer].isAlive()) {
        cout << players[currPlayer].getName() << " has won!" << endl;
        break;
      }
      players[currPlayer].removeDead();
      if (graphics) gd->displayHand(players[currPlayer].getHand(), currPlayer);

      // -----------------------------------------------
      line = getInput(ifs);
      istringstream iss{line};
      int i = -1, j = -1, p = -1, t = -1;

      iss >> cmd;
      if (cmd == "help") {
        cout << "HELP" << endl;
        if (iss.eof()) {          
          viewCommands();
        } else {
          throw std::invalid_argument("Invalid input.");
        }
      }

      else if (cmd == "quit") {
        cout << "QUIT" << endl;
        if (iss.eof()) {
          break;
        } else {
          throw std::invalid_argument("Invalid input.");
        }
      }

      else if (cmd == "end") {
        cout << "END" << endl;
        if (iss.eof()) {
          

          // ==== End Turn ===============================
          notifyTriggerOnEnd();
          // =============================================


          // ==== Start of new turn =====================
          currPlayer = !currPlayer;
          cout << "Player " << currPlayer + 1 << " turn." << endl;
          players[currPlayer].resetAction();
          players[currPlayer].updateMagic(1);
          // if (graphics) gd->displayHand(players[currPlayer].getHand(), currPlayer);
          notifyTriggerOnBegin();
          players[currPlayer].drawCard(); 
          // ============================================

        } else {
          throw std::invalid_argument("Invalid input.");
        }
      }

      else if (cmd == "draw" && testing) {
        cout << "DRAW" << endl;
        if (iss.eof()) {
          players[currPlayer].drawCard();
        } else {
          throw std::invalid_argument("Invalid input.");
        }
      }

      else if (cmd == "discard" && testing) {
        cout << "DISCARD" << endl;
        if (iss >> i && iss.eof()) {
          players[currPlayer].discard(i);
        } else {
          throw std::invalid_argument("Invalid input.");
        }
      }

      else if (cmd == "attack") {
        cout << "ATTACK" << endl;
        if (iss >> i && iss.eof()) {
          players[currPlayer].attack(i);
        } else if (iss >> j && iss.eof()) {
          players[currPlayer].attack(i, j);
        } else {
          throw std::invalid_argument("Invalid input.");
        }
      }

      else if (cmd == "play") {
        cout << "PLAY" << endl;
        string r;
        if (iss >> i && iss.eof()) {
          players[currPlayer].play(i, testing);
        } else if (iss >> p >> r && iss.eof()) {
          if (r == "r") { // target ritual
            players[currPlayer].playOnRitual(i, p, testing);
          } else {
            players[currPlayer].play(i, p, stoi(r), testing);
          }
        } else {
          throw std::invalid_argument("Invalid input.");
        }
      }

      else if (cmd == "use") {
        cout << "USE" << endl;
        if (iss >> i && iss.eof()) {
          players[currPlayer].use(i, testing);
        } else if (iss >> p >> t && iss.eof()) {
          players[currPlayer].use(i, p, t, testing);
        } else {
          throw std::invalid_argument("Invalid input.");
        }
      }

      else if (cmd == "inspect") {
        cout << "INSPECT" << endl;
        if (iss >> i && iss.eof()) {
          players[currPlayer].inspect(i);
        } else {
          throw std::invalid_argument("Invalid input.");
        }
      }

      else if (cmd == "hand") {
        cout << "HAND" << endl;
        if (iss.eof()) {
          td->displayHand(currPlayer);
        } else {
          throw std::invalid_argument("Invalid input.");
        }
      }
    
      else if (cmd == "board") {
        cout << "BOARD" << endl;
        if (iss.eof()) {
          td->displayBoard();
        } else {
          throw std::invalid_argument("Invalid input.");
        }
      }

      else {
        throw std::invalid_argument("Invalid command.");
      }

    } catch (const std::exception &error) {
      cerr << "Error: " << error.what() << endl;
    }

  }
}

void GameManager::attachObservers(std::shared_ptr<CardObserver>obs, int playerNum) {
  observers[playerNum - 1][obs->getId()] = obs;
}

void GameManager::detachObservers(int id) {
  auto it = observers[0].find(id);
  if (it != observers[0].end()) {
    observers[0].erase(it);
  }
  auto it2 = observers[1].find(id);
  if (it2 != observers[1].end()) {
    observers[1].erase(it2);
  }
}

void GameManager::notifyTriggerOnLeave() {
  for (const auto &entry : observers[0]) {
    if (entry.second->getAbility().getCondition() == Condition::ON_MINION_LEAVE) {
      players[0].usePassive(entry.second->getId());
    }
  }
  for (const auto &entry : observers[1]) {
    if (entry.second->getAbility().getCondition() == Condition::ON_MINION_LEAVE) {
      players[1].usePassive(entry.second->getId());
    }
  }
}
void GameManager::notifyTriggerOnEnter(std::shared_ptr<Card> card) {
  for (const auto &entry : observers[currPlayer]) {
    if (entry.second->getAbility().getCondition() == Condition::ON_MINION_ENTER) {
      players[currPlayer].usePassive(entry.second->getId(), card);
    }
  }
}
void GameManager::notifyTriggerOnEnd() {
  for (const auto &entry : observers[currPlayer]) {
    if (entry.second->getAbility().getCondition() == Condition::ON_TURN_END) {
      players[currPlayer].usePassive(entry.second->getId());
    }
  }
}
void GameManager::notifyTriggerOnBegin() {
  for (const auto &entry : observers[currPlayer]) {
    if (entry.second->getAbility().getCondition() == Condition::ON_TURN_BEGIN) {
      players[currPlayer].usePassive(entry.second->getId());
    }
  }
}

void GameManager::shuffleDeck() {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine rng{seed};

  for ( int i = 0; i < 1000; i++ ) {
		std::shuffle( players[0].getDeck().begin(), players[0].getDeck().end(), rng );
		std::shuffle( players[1].getDeck().begin(), players[1].getDeck().end(), rng );
  }
}
