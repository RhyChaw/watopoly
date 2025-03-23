#include "Residence.h"
#include "Player.h"

// Define the static rent array
const int Residence::RENT_RATES[4] = {25, 50, 100, 200};

Residence::Residence(int ID, std::string name, int price, char owner)
    : Building(ID, name, price, owner) {}

Residence::~Residence() {}

int Residence::calculateRent() const {
    char ownerPlayer = getOwner();
    if (ownerPlayer == ' ') {
        return 0;
    }

    int residenceCount = getResLevel();
    return RENT_RATES[residenceCount - 1];
}

void Residence::currentOn(Player* player) {
    char ownerPlayer = getOwner();
    
    if (ownerPlayer == ' ') {
        // No owner, player can purchase
        std::cout << player->getName() << " landed on unowned residence " << getName() << std::endl;
        // Purchase logic would go here
    } else if (ownerPlayer != player->getSymbol()) {
        // Another player owns this residence, pay rent
        int rent = calculateRent();
        
        std::cout << player->getName() << " pays " << rent << " to " 
                  << ownerPlayer << " for landing on " << getName() << std::endl;
    } else {
        // Player owns this residence
        std::cout << player->getName() << " landed on their own residence " << getName() << std::endl;
    }
}

int Residence::costToimp(std::string squareName, int imprLevel) {
    int result = 0;
    int levelIndex = 4 + imprLevel; 

    for (int i = 0; i < 28; i++) {
        if (OWNABLE[i][0] == squareName) {
            std::stringstream ss(OWNABLE[i][levelIndex]);
            int cost = 0;
            ss >> cost;
            result += cost;
        }
    }

    return result;
}

int Residence::amountToPay() {
    return costToimp(this->getName(), this->getResLevel());
}

