#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include "load.h"
#include "Player.h"
#include "GameBoard.h"
#include "Dice.h"
#include "transaction.h"
#include "watopoly_display.h"
#include "building.h"
#include "nonbuilding.h"
#include "propertyArray.h"
#include "SLC.h"
#include "NeedlesHall.h"

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
    void letTheGameBegin(int argc, char **argv);
    void commandTrade(std::vector<std::shared_ptr<Player>> group, std::shared_ptr<Player> currActingPlayer);
    void commandImprove(std::vector<std::shared_ptr<Player>> group, std::shared_ptr<Player> currActingPlayer, std::shared_ptr<GameBoard> b);
    void commandMortgage(std::shared_ptr<Player> currActingPlayer);
    void commandUnmortgage(std::shared_ptr<Player> currActingPlayer);
void commandBankrupt(std::shared_ptr<Player> currActingPlayer, std::shared_ptr<Player> owner);
void commandAuction(std::vector<std::shared_ptr<Player>> group, std::shared_ptr<Player> currActingPlayer, std::string prop);

void CommandRoll(std::vector<std::shared_ptr<Player>> group, std::shared_ptr<Player> currActingPlayer, bool testMode, std::shared_ptr<GameBoard> b);




};

#endif // CONTROLLER_H
