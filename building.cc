#include "ownable.h"

building::building(int ID, std::string name, int price, char owner) 
    : cell(ID, name), owner{owner}, price{price}, imprl{0}, payLevel{0}{
}

void building::setOwner(char owner) {
   this-> owner = owner;
}

void building::setMortStatus(bool status) {
    mortgageStatus = status;
}

void building::setImprLevel(int level) {
    imprLevel = level;
}

void building::setPayLevel(int level) {
    payLevel = level;
}

char building::getOwner() const {
    return owner;
}

bool building::getMortStatus() const {
    return mortgageStatus;
}

int building::getImprLevel() const {
    return imprLevel;
}

int building::getPayLevel() const {
    return payLevel;
}

int building::getCostToBuy() const {
    return price;
}

std::string building::getMonoBlock() const {
    return monopolyBlock;
}
