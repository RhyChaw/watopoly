#include "Residence.h"
#include "Player.h"
#include <iostream>

// Initialize static rent rates
const int Residence::RENT_RATES[4] = {25, 50, 100, 200};

Residence::Residence(std::string name) : Building(name, 200) {
    // Standard price for all residences is 200
}

Residence::~Residence() {
    // Nothing to clean up
}

int Residence::calculateRent() const {
    if (getOwner() == nullptr) {
        return 0;
    }
    
    int residenceCount = getOwnerResidenceCount();
    // Adjust for 0-based indexing
    return RENT_RATES[residenceCount - 1];
}

void Residence::currentOn(Player* player) {
    // Implementation for when a player lands on this residence
    if (getOwner() == nullptr) {
        // No owner, player can purchase
        std::cout << player->getName() << " landed on unowned residence " << getName() << std::endl;
        // Purchase logic would go here
    } else if (getOwner() != player) {
        // Another player owns this residence, pay rent
        int rent = calculateRent();
        
        std::cout << player->getName() << " pays " << rent << " to " 
                  << getOwner()->getName() << " for landing on " << getName() << std::endl;
        
        player->removeMoney(rent);
        getOwner()->addMoney(rent);
    } else {
        // Player owns this residence
        std::cout << player->getName() << " landed on their own residence " << getName() << std::endl;
    }
}

int Residence::getOwnerResidenceCount() const {
    if (getOwner() == nullptr) {
        return 0;
    }
    
    return getOwner()->getOwnedResidences();
}
