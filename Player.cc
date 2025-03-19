#include "Player.h"
#include <iostream>

Player::Player(const std::string &name, char symbol)
    : name(name), symbol(symbol), position(0), cash(1500), numCups(0), inTimsLine(false), turnsInLine(0) {}

// Getters
std::string Player::getName() const {
    return name;
}

char Player::getSymbol() const {
    return symbol;
}

int Player::getIndex() const {
    return position;
}

int Player::getCash() const {
    return cash;
}

bool Player::getIsTimLine() const {
    return inTimsLine;
}

int Player::getNumLineWait() const {
    return turnsInLine;
}

int Player::getOwnedCups() const {
    return numCups;
}

std::vector<std::shared_ptr<Cell>> Player::getProperties() const {
    return ownedProperties;
}

// Setters
void Player::setIndex(int newPosition) {
    position = newPosition;
}

void Player::setCash(int amount) {
    cash = amount;
}

// Cup management
void Player::addCup() {
    if (numCups < 4) {
        numCups++;
    }
}

void Player::removeCup() {
    if (numCups > 0) {
        numCups--;
    }
}

// Tims Line management
void Player::moveToTimsLine() {
    inTimsLine = true;
    turnsInLine = 0;
}

void Player::leaveTimsLine() {
    inTimsLine = false;
    turnsInLine = 0;
}

// Check if player is bankrupt
bool Player::checkBankrupt() const {
    return cash < 0;
}
