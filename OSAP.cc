#include "OSAP.h"
#include "Player.h"
#include <iostream>

using namespace std;

OSAP::OSAP(int ID, std::string name) : nonbuilding(ID, name){
}

OSAP::~OSAP() {}

void OSAP::collectOSAP(std::shared_ptr<Player> p) {
    p->changeCash(COLLECT_AMOUNT);
    std::cout << p->getName() << " collects " << COLLECT_AMOUNT << " from OSAP." << std::endl;
}
