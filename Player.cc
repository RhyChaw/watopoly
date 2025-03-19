#include "Player.h"
#include <iostream>

// Constructor for new game
Player::Player(string name, char symbol, int index, int position_initial)
    : name(name), symbol(symbol), index(index), position_initial(position_initial), 
      cash(1500), assets(0), ownedResidence(0), ownedGyms(0), ownedAcademic(0),
      isInTimsLine(false), turnsInTimsLine(0), doubles_counter(0), isBankrupt(false), cups(0) {
    for (int i = 0; i < 8; ++i) {
        monopolySet[i] = 0;
    }
    for (int i = 0; i < 28; ++i) {
        buildings[i] = nullptr;
    }
}

// Constructor for loading a saved game
// may be wrong, confirm once individually
Player::Player(std::string name, char symbol, int ownedCups, double cash, int index, 
    bool isTimLine, int turnsInTimsLine, int position_initial, 
    double assets, std::vector<std::shared_ptr<Cell>> ownedProperties,
    int ownedGyms, int ownedResidence, int ownedAcademic, 
    int monopolySet[8], Building* buildings[28])
    : name(name), symbol(symbol), index(index), position_initial(position_initial),
    cash(cash), assets(assets), ownedProperties(ownedProperties),
    ownedGyms(ownedGyms), ownedResidence(ownedResidence), ownedAcademic(ownedAcademic),
    isInTimsLine(isTimLine), turnsInTimsLine(turnsInTimsLine), doubles_counter(0), 
    isBankrupt(false), cups(ownedCups) {

    // Restore monopoly ownership
    for (int i = 0; i < 8; ++i) {
        this->monopolySet[i] = monopolySet[i];
    }

    // Restore buildings ownership
    for (int i = 0; i < 28; ++i) {
        this->buildings[i] = buildings[i];
    }
}

// Destructor
Player::~Player() {}

// Getters
string Player::getName() { return name; }
char Player::getSymbol() { return symbol; }
int Player::getIndex() { return index; }
int Player::getPosition() { return position_initial; }
double Player::getCash() { return cash; }
double Player::getAsset() { return assets; }
int Player::getOwnedResidences() { return ownedResidence; }
int Player::getOwnedGyms() { return ownedGyms; }
int Player::getTurnsInTimsLine() { return turnsInTimsLine; }
int Player::getOwnedCups() { return cups; }
bool Player::isInTimsLine() const { return isInTimsLine; }
bool Player::isBankrupt() const { return isBankrupt; }
std::vector<std::shared_ptr<Cell>> Player::getProperties() const {
    return ownedProperties;
}

// Setters
void Player::setPosition(int p) { position_initial = p; }
void Player::setCash(int amount) { cash = amount; }
void Player::setTurnsInTimsLine(int turns) { turnsInTimsLine = turns; }
void Player::setBankrupt(bool b) { isBankrupt = b; }
void Player::setCups(int n) { cups = n; }
void Player::moveToTimsLine() { isInTimsLine = true;}
void Player::leaveTimsLine() { isInTimsLine = false;}


// Modify assets and properties
void Player::changeAsset(int c) { assets += c; }
void Player::changePropertyCount(int residences, int gyms) {
    ownedResidence += residences;
    ownedGyms += gyms;
}

Building* Player::findBuilding(const std::string &buildingName) {
    for (int i = 0; i < 28; ++i) {
        if (buildings[i] != nullptr && buildings[i]->getName() == buildingName) {
            return buildings[i];
        }
    }
    return nullptr; // Return nullptr if not found
}

bool Player::checkMonopolyImprove(Building *building) {
    AcademicBuilding *ac = dynamic_cast<AcademicBuilding *>(building);
    if (!ac) return false; // If not an academic building, no improvements allowed

    int blockIndex = ac->getBlock();
    
    // Check if the player owns all buildings in the monopoly block
    for (int i = 0; i < 28; ++i) {
        if (buildings[i] != nullptr) {
            AcademicBuilding *ac2 = dynamic_cast<AcademicBuilding *>(buildings[i]);
            if (ac2 && ac2->getBlock() == blockIndex && ac2->getCurrentLevel() > 0) {
                return false; // Found a building in the block with improvements
            }
        }
    }
    return true; // Monopoly is valid for improvement
}
 

