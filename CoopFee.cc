#include "CoopFee.h"
#include "Player.h"
#include <iostream>

CoopFee::CoopFee(std::string name) : NonProperty(name) {
    // Nothing to initialize
}

CoopFee::~CoopFee() {
    // Nothing to clean up
}

void CoopFee::doEvent(Player* player) {
    // Player must pay the co-op fee
    std::cout << player->getName() << " landed on Co-op Fee and must pay $" 
              << FEE_AMOUNT << "." << std::endl;
    
    player->removeMoney(FEE_AMOUNT);
}
