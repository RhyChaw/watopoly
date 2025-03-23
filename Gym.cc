#include "Gym.h"
using namespace std;

Gym::Gym(int ID, string name, int price, char owner)
	: Building(ID, name, price, owner) {}

Gym::~Gym() {}

void Gym::setRoll(int roll){
    roll = roll;
}

int Gym::getRoll() const {
    return roll;
}

int Gym::costToimp(std::string squareName, int imprLevel) {
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

int Gym::amountToPay() {
    return this->getRoll() * costToimp(this->getName(), this->getGymLevel());
}

void Gym::currentOn(Player* player) {
    Player* ownerPlayer = getOwner();
    
    if (!ownerPlayer) {
        // No owner, player can purchase
        std::cout << player->getName() << " landed on unowned gym " << getName() << std::endl;
        // Purchase logic
    } else if (ownerPlayer != player) {
        // Another player owns this gym, pay fee
        int diceRoll = roll; // Use the stored roll value
        int fee = calculateFee(diceRoll);
        
        std::cout << player->getName() << " pays " << fee << " to " 
                  << ownerPlayer->getName() << " for landing on " << getName() << std::endl;
        
        player->changeCash(-fee);
        ownerPlayer->changeCash(fee);
    } else {
        // Player owns this gym
        std::cout << player->getName() << " landed on their own gym " << getName() << std::endl;
    }
}

