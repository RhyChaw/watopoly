#include "OSAP.h"
#include "Player.h"
#include <iostream>

OSAP::OSAP(std::string name) : NonProperty(name) {
    // Nothing to initialize
}

OSAP::~OSAP() {
    // Nothing to clean up
}

void OSAP::doEvent(Player* player) {
    // Give player money when they land on or pass OSAP
    player->addMoney(COLLECT_AMOUNT);
    std::cout << player->getName() << " collects " << COLLECT_AMOUNT 
              << " from OSAP." << std::endl;
}
