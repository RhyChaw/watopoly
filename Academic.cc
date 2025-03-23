#include "Academic.h"
#include "Player.h"
#include <iostream>
#include <sstream>


Academic::Academic(int ID, std::string name, int price, char owner) : Building(ID, name, price, owner) {
    rentatata = costTogen(name);  
    block = monoBlockOfProp(this->getName());  
}

int Academic::costTogen(std::string squareName) {
    int result = 0;

    for (int i = 0; i < 28; i++) {
        if (OWNABLE[i][0] == squareName) {
            std::stringstream ss(OWNABLE[i][4]);
            int cost = 0;
            ss >> cost;
            result += cost;
        }
    }

    return result;
}

int Academic::costToimp(std::string squareName, int imprLevel) {
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



Academic::~Academic() {}

std::string Academic::getBlock() const {
    return block;
}

void Academic::setBlock(string Block) {
    block = Block;
}

void Academic::setOwned(bool own) {
    owned = own;
}

bool Academic::getOwned() const {
    return owned;
}

void Academic::currentOn(Player* player) {
    // Implementation for when a player lands on this building
    if (getOwner() == nullptr) {
        // No owner, player can purchase
        std::cout << player->getName() << " landed on unowned property " << getName() << std::endl;
        // Purchase logic would go here
    } else if (getOwner() != player) {
        // Another player owns this property, pay rent
        int rent = getTuition();
        if (hasMonopoly() && improvements == 0) {
            rent *= 2; // Double rent for monopoly with no improvements
        }
        
        std::cout << player->getName() << " pays " << rent << " to " 
                  << getOwner()->getName() << " for landing on " << getName() << std::endl;
        
        player->removeMoney(rent);
        getOwner()->addMoney(rent);
    } else {
        // Player owns this property
        std::cout << player->getName() << " landed on their own property " << getName() << std::endl;
    }
}

//change this yes sirrrrrrrr
int Academic::amountToPay() {
    if (owned) {
        return 2 * costTogen(this->getName());
    }
    return costToimp(this->getName(), this->getImprLevel());
}
