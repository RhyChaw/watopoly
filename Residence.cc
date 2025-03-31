#include "Residence.h"
#include "Player.h"
#include <sstream>

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

