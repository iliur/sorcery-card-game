#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include "GameManager.h"
#include "Library.h"
#include "window.h"

using namespace std;

int main(int argc, char *argv[]) {
  ifstream ifs;
  string deck1 = "default.deck";
  string deck2 = "default.deck";
  bool graphics = false;
  bool testing = false;

  // set up for taking file arguments
  for (int i = 0; i < argc; ++i) {
    string arg = argv[i];
    if (arg == "-init") {
      ifs = ifstream(argv[i + 1]);
    } 
    else if (arg == "-deck1") {
      deck1 = argv[i + 1];
    } 
    else if (arg == "-deck2") {
      deck2 = argv[i + 1];
    }
    else if (arg == "-testing") {
      testing = true;
    }
    else if (arg == "-graphics") {
      graphics = true;
    }
  }
  
  GameManager g{graphics};
  
  try {
    initLibrary();
    g.init(ifs, deck1, deck2, testing);
    g.startGame(ifs);
  } catch (const std::exception &err) {
    cout << err.what() << endl;
  }
  removeLibrary();
  cout << "Thanks for playing!" << endl;
}
