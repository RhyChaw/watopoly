#include "Player.h"
#include "building.h"
#include "AcademicBuilding.h"
#include <string>
#include <iostream>

using namespace std;

// Constructor for new game
Player::Player(string name, char symbol, int index, int position_initial)
    : name(name), symbol(symbol), index(index), position_initial(position_initial), 
      cash(1500), assets(0), ownedResidence(0), ownedGyms(0), ownedAcademic(0),
      isInTimsLine(false), turnsInTimsLine(0), isBankrupt(false), cups(0) {
    for (int i = 0; i < 8; ++i) {
        monopolySet[i] = 0;
    }
    for (int i = 0; i < 28; ++i) {
        buildings[i] = nullptr;
    }
}

// Constructor for loading a saved game
Player::Player(std::string name, char symbol, int ownedCups, double cash, int index, 
    bool isTimLine, int turnsInTimsLine, int position_initial, 
    double assets, std::vector<std::shared_ptr<Cell>> ownedProperties,
    int ownedGyms, int ownedResidence, int ownedAcademic)
    : name(name), symbol(symbol), index(index), position_initial(position_initial),
    cash(cash), assets(assets), ownedProperties(ownedProperties),
    ownedGyms(ownedGyms), ownedResidence(ownedResidence), ownedAcademic(ownedAcademic),
    isInTimsLine(isTimLine), turnsInTimsLine(turnsInTimsLine), 
    isBankrupt(false), cups(ownedCups) {

    // Initialize monopoly ownership
    for (int i = 0; i < 8; ++i) {
        monopolySet[i] = 0;
    }

    // Initialize buildings array
    for (int i = 0; i < 28; ++i) {
        buildings[i] = nullptr;
    }
    
    // Setup would need to be done to populate buildings array based on ownedProperties
}

// Destructor
Player::~Player() {}

// Getters
string Player::getName() const{ 
    return name; 
}

char Player::getSymbol() const { 
    return symbol; 
}

int Player::getIndex() const { 
    return index; 
}

int Player::getPosition() const { 
    return position_initial; 
}

double Player::getCash() const { 
    return cash; 
}

double Player::getAsset() const { 
    return assets; 
}

int Player::getOwnedResidences() const { 
    return ownedResidence; 
}

int Player::getOwnedGyms() const { 
    return ownedGyms; 
}

int Player::getTurnsInTimsLine() const { 
    return turnsInTimsLine; 
}

int Player::getOwnedCups() const { 
    return cups; 
}

bool Player::getisInTimsLine() const { 
    return isInTimsLine; 
}

bool Player::getisBankrupt() const { 
    return isBankrupt; 
}

std::vector<std::shared_ptr<Cell>> Player::getProperties() const {
    return ownedProperties;
}

int Player::getadd_roll_for_jail() const {
    return roll_for_jail;
}

// Setters
//i this you might need to set postiotn like actually with numbers
void Player::setPosition(int p) { 
    position_initial = p; 
}

void Player::setCash(int amount) { 
    cash = amount; 
}

void Player::setTurnsInTimsLine(int turns) { 
    turnsInTimsLine = turns; 
}


void Player::setBankrupt(bool b) { 
    isBankrupt = b; 
}

void Player::setCups(int n) { 
    cups = n; 
}

void Player::moveToTimsLine() { 
    isInTimsLine = true;
}

void Player::leaveTimsLine() { 
    isInTimsLine = false;
}

// Modify assets and properties
void Player::changeCash(double c) {
    //check for bankcruptcy;
    cash += c;
    changeAsset(c);
}

void Player::changeAsset(double c) {
     assets += c; 
}

void Player::changePropertyCount(int residences, int gyms, int academics) {
    //not doing anything rn....
}
    int ownedResidence += residences;
    int ownedGyms += gyms;
    int ownedAcademic += academics;
}

// Handle cash transactions
//pay fund
void Player::pay(int amount) {
    if (isBankrupt) {
        std::cout << "this player is bankrupted" << std::endl;
        return;
    }

    if (cash < amount) {
        std::cout << " insufficient fund to pay" << std::endl;
        return;
    }

    changeCash(-amount);
}

void Player::receive(int amount) {
    cash += amount;
}

// Add and remove properties
void Player::addProperty(std::shared_ptr<Cell> property) {
    ownedProperties.emplace_back(property);
}

void Player::removeProperty(std::shared_ptr<Cell> property) {
    for (auto it = ownedProperties.begin(); it != ownedProperties.end(); ++it) {
        if (*it == property) {
            ownedProperties.erase(it);
            break;
        }
    }
}

void Player::addCup() {
    ++cups;
}

void Player::add_roll_for_jail() {
    ++roll_for_jail;
}

void Player::removeCup() {
    --cups;
}

Building *Player::findBuilding(string buildingName) {
    Building *bd = nullptr;
    for (int i = 0; i < 28; ++i) {
        if (buildings[i] && buildings[i]->getName() == buildingName) {
            bd = buildings[i];
            break;
        }
    }
    return bd;
}

bool Player::checkMonopolyImprove(Building *building) {
    AcademicBuilding *acad = dynamic_cast<AcademicBuilding *>(building);
    if (!acad) return false;
    
    int blocki = acad->getBlock();
    bool result = true;
    for (int i = 0; i < 28; ++i) {
        if (buildings[i] != nullptr) {
            AcademicBuilding *acad2 = dynamic_cast<AcademicBuilding *>(buildings[i]);
            if (acad2) {
                if (acad2->getBlock() == blocki) {
                    if (acad2->getCurrentLevel() != 0) {
                        result = false;
                        break;
                    }
                }
            }
        }
    }
    return result;
}

bool Player::checkMonopoly(int block) {
    int getMonopoly[8] = {2, 3, 3, 3, 3, 3, 3, 2};
    if (monopolySet[block] == getMonopoly[block]) {
        return true;
    } else {
        return false;
    }
}

bool Player::ownThisProp(std::string name) {
    int size = ownedProperties.size();

    for (int i = 0; i < size; i++) {
        if (ownedProperties[i]->getName() == name) {
            return true;
        }
    }

    return false;
}

void Player::printAsset() {
    cout << "Player : " << name << endl;
    cout << "Money Owned : $" << cash << endl;
    cout << "Net Worth: $" << assets << endl;  // Fixed to use assets instead of asset
    cout << "The Number of Tims Cups Owned : " << cups << endl;
    cout << "Properties Owned : ";
    for (int i = 0; i < 28; ++i) {
        if (buildings[i] != nullptr) {
            cout << buildings[i]->getName() << " ";
        }
    }
    cout << endl;
}

void Player::declareBankruptcy() {
    isBankrupt = true;
    cash = 0;
    assets = 0;
    ownedProperties.clear();
    ownedResidence = 0;
    ownedGyms = 0;
    ownedAcademic = 0;
    cups = 0;

    for (int i = 0; i < 8; ++i) {
        monopolySet[i] = 0;
    }

    // Reset ownership of all buildings
    for (int i = 0; i < 28; ++i) {
        if (buildings[i]) {
            buildings[i]->setOwner(' ');
            buildings[i] = nullptr;
        }
    }

    cout << getName() << " has declared bankruptcy!" << endl;
}

bool Player::checkBankrupt() const {
    return cash < 0;
}


bool Player::isGym(std::string squareName){
    for (int i = 22; i < 24; i++){
        if (OWNABLE[i][0] == squareName) {
            return true;
        }
    }
    return false;
}


bool Player::isResidence(std::string squareName){
    for (int i = 24; i < 28; i++){
        if (OWNABLE[i][0] == squareName){
	    return true;
	}
    }
    return false;
}

void Player::removeProp(std::shared_ptr<Building> property_name) {
    // check if property is owned
    if (!this->ownThisProp(property_name->getName())) {
        std::cout << "this props is not owned" << std::endl;
        return;
    }

    for (unsigned int i = 0; i < ownedProperties.size(); i++) {
        if (property_name == ownedProperties[i]) {
            ownedProperties.erase(ownedProperties.begin() + i);
            break;
        }
    }
}


void Player::addProp(std::shared_ptr<Building> property_name) {
    if (this->ownThisProp(property_name->getName())) {
        std::cout << "this props is owned" << std::endl;
        return;
    }

    for (int i = 22; i < 24; i++){
        if (OWNABLE[i][0] == property_name->getName()) {
            ownedGyms++;
        }
    }
    for (int i = 24; i < 28; i++){
        if (OWNABLE[i][0] == property_name->getName()) {
            ownedResidence++;
        }
    }
    ownedProperties.emplace_back(propperty_name);
}

void Player::updateMonopolyBlock() {
    std::map<std::string, int> tracking; 
    std::string eachBlock;

    ownedGyms = 0;
    ownedResidence = 0;
    for (int i = 0; i < 28; i++) {
        std::string propName = ownedProperties[i]->getName();
        if (isGym(propName)){
            ownedGyms++;
        } else if (isResidence(propName)){
            ownedResidence++;
        }
	    eachBlock = ownedProperties[i]->getMonoBlock();
	    arr[eachBlock] += 1;
    }

    for (auto &block: trackingBuilding) {
        if (block.second == 2 && (block.first == "Math" || block.first == "Arts1")) {
            monopolyBlocks.push_back(block.first);
        } else if (block.second == 3) {
            monopolyBlocks.push_back(block.first);
        }
    }
}

std::string Player::monoBlockOfProp(std::string name) {
    std::string result = "";

    for (int i = 0; i < 28; i++) {
        if (OWNABLE[i][0] == squareName) {
            result = OWNABLE[i][1];
        }
    }

    return result;
}

bool Player::checkIfInMonopolyBlock(std::string name) {
    std::string monoBlockOfSquare = monoBlockOfProp(squareName);
    int size = monopolyBlocks.size();

    for (int i = 0; i < size; i++) {
        if (monopolyBlocks[i] == monoBlockOfSquare) {
            return true;
        }
    }

    return false;
}
