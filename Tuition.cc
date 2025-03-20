#include "Tuition.h"
#include "Player.h"
#include <iostream>
#include <algorithm> // for std::min

Tuition::Tuition(std::string name) : NonProperty(name) {
    // Nothing to initialize
}

Tuition::~Tuition() {
    // Nothing to clean up
}

void Tuition::doEvent(Player* player) {
    std::cout << player->getName() << " landed on Tuition." << std::endl;
    std::cout << "Options: 1) Pay $300 or 2) Pay 10% of total worth" << std::endl;
    
    // Calculate 10% of total worth
    int totalWorth = player->getCash() + player->getAsset();
    int tenPercent = totalWorth / 10;
    
    // For simplicity, we'll automatically choose the lower amount
    // In a real implementation, you'd let the player choose
    int payment = std::min(300, tenPercent);
    
    std::cout << player->getName() << " pays $" << payment << " for tuition." << std::endl;
    player->removeMoney(payment);
}
