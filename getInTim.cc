#include "getInTim.h"
#include "Player.h"
#include <iostream>
using namespace std;

GetInTim::GetInTim(int ID, std::string name) : nonbuilding(ID, name) {}

GetInTim::~GetInTim() {}

void GetInTim::goToJail(std::shared_ptr<Player> currActingPlayer) {
    std::cout << "Go to TIMS" << endl;
    cout << R"(
        ┌─┬─┬─┬─┬─┬─┐
        │ │ │ │ │ │ │
        │(╥_╥)│ │ │ │
        │ │ │ │ │ │ │
        └─┴─┴─┴─┴─┴─┘
           "Let me out!"
          )" << endl;
    currActingPlayer->setIsInTimsLine(true);
    currActingPlayer->resetTurnsInTims();
    currActingPlayer->setPos(10);
    currActingPlayer->setRollForJail(0);
}
