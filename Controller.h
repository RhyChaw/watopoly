#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "load.h"
#include "Player.h"
#include "GameBoard.h"
#include "Dice.h"
#include "transaction.h"
#include "watopoly-display.h"
#include "building.h"
#include "nonbuilding.h"

using namespace std;

class Board;
class Player;
class Dice;
class Transactions;
class nonbuilding;

class Controller {
private:

public:
    Controller();
    ~Controller();
    void letTheGameBegin(int argc, char *argv);
    void loadGame(std::ifstream f);
};

#endif // CONTROLLER_H
