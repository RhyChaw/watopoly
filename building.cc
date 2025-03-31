#include "building.h"

using namespace std;

std::string Building::monoBlockOfProp(std::string squareName) {
    std::string result = "";

    // this loop is determined on how manit wrote the array in gameboard
    // ownamble is the array name
    for (int i = 0; i < 28; i++) {
        if (OWNABLE[i][0] == squareName) {
            result = OWNABLE[i][1];
        }
    }
    return result;
}

Building::Building(int ID, std::string name, int price, char owner)
    : Cell(ID, name), owner{owner}, price{price}
{
    monopolyBlock = monoBlockOfProp(name);
}

void Building::setOwner(char owner) {
   this->owner = owner;
}

void Building::setMortStatus(bool status) {
    mortgageStatus = status;
}

void Building::setImprLevel(int level) {
    imprLevel = level;
}

void Building::setGymLevel(int level) {
    GymLevel = level;
}

void Building::setResLevel(int level) {
    ResLevel = level;
}

char Building::getOwner() const {
    return owner;
}

bool Building::getMortStatus() const {
    return mortgageStatus;
}

int Building::getImprLevel() const {
    return imprLevel;
}

int Building::getResLevel() const {
    return ResLevel;
}

int Building::getGymLevel() const {
    return GymLevel;
}

int Building::getCostToBuy() const {
    return price;
}

std::string Building::getMonoBlock() const {
    return monopolyBlock;
}

