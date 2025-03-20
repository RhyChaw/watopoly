#include "Gym.h"
#include "Player.h"
#include <iostream>

Gym::Gym(std::string name) : Building(name, 150) {
    // Standard price for all gyms is 150
}

Gym::~Gym() {
    // Nothing to clean up
}

int Gym::calculateFee(int diceRoll) const {
    if (getOwner() == nullptr) {
        return 0;
    }
    
    int gymCount = getOwnerGymCount();
    
    if (gymCount == 1) {
        return diceRoll * 4; // 4 times the dice roll
    } else if (gymCount == 2) {
        return diceRoll * 10; // 10 times the dice roll
    }
    
    return 0; // Should not reach here
}

void Gym::currentOn(Player* player) {
    // Implementation for when a player lands on this gym
    if (getOwner() == nullptr) {
        // No owner, player can purchase
        std::cout << player->getName() << " landed on unowned gym " << getName() << std::endl;
        // Purchase logic would go here
    } else if (getOwner() != player) {
        // Another player owns this gym, pay fee
        // For simplicity, we'll use a fixed dice roll of 7
        // In a real implementation, you'd get the actual dice roll from the game
        int diceRoll = 7; // Placeholder
        int fee = calculateFee(diceRoll);
        
        std::cout << player->getName() << " pays " << fee << " to " 
                  << getOwner()->getName() << " for landing on " << getName() << std::endl;
        
        player->removeMoney(fee);
        getOwner()->addMoney(fee);
    } else {
        // Player owns this gym
        std::cout << player->getName() << " landed on their own gym " << getName() << std::endl;
    }
}

int Gym::getOwnerGymCount() const {
    if (getOwner() == nullptr) {
        return 0;
    }
    
    return getOwner()->getOwnedgyms();
}
