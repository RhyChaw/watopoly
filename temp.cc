#include "Gym.h"
using namespace std;
#include <sstream>

Gym::Gym(int ID, string name, int price, char owner)
    : Building(ID, name, price, owner) {}

Gym::~Gym() {}

void Gym::setRoll(int roll){
    this->roll = roll;
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