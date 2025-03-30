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

void Academic::setOwned(bool flag) {
    owned = flag;
}

bool Academic::getOwned() const {
    return owned;
}

int Academic::amountToPay() {
    if (this->getImprLevel() == 0 && owned) {
        std::cout <<"This is a Monopoly without improvements, hence you will be required to pay double the rent on this building." <<endl;
        return 2 * costTogen(this->getName());
    }
    return costToimp(this->getName(), this->getImprLevel());
}
