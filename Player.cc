#include "Player.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

Player::Player(std::string name, char symbol, int Cash) : name{name}, symbol{symbol}, cash{Cash} {};


// Player::Player(std::string name, char symbol, int ownedCups, double cash, int index, 
//     bool isTimLine, int turnsInTimsLine, int position_initial, 
//     double assets, std::vector<std::shared_ptr<Building>> ownedProperties,
//     int ownedGyms, int ownedResidence, int ownedAcademic)
//     : name(name), symbol(symbol), index(index), position(position),
//     cash(cash), assets(assets), ownedProperties(ownedProperties),
//     ownedGyms(ownedGyms), ownedResidence(ownedResidence), ownedAcademic(ownedAcademic),
//     isInTimsLine(isTimLine), turnsInTimsLine(turnsInTimsLine), 
//     isBankrupt(false), cups(ownedCups) {

//     // Initialize monopoly ownership
//     for (int i = 0; i < 8; ++i) {
//         monopolyBlocks[i] = 0;
//     }
// }

Player::~Player() {}

// Getters
char Player::getSymbol() const { 
    return symbol; 
}

string Player::getName() const{ 
    return name; 
}

double Player::getCash() const { 
    return cash; 
}

int Player::getPosition() const { 
    return position; 
}

int Player::getCups() const { 
    return cups; 
}

bool Player::getisBankrupt() const { 
    return isBankrupt; 
}

int Player::getOwnedResidences() const { 
    return ownedResidence; 
}

int Player::getOwnedGyms() const { 
    return ownedGyms; 
}

int Player::getOwnedAcademic() const { 
    return ownedAcademic; 
}

string Player::getSquareAtCurrPos() {
    return BOARD[position];
}

std::vector<std::shared_ptr<Building>> Player::getOwnedPropList() {
    return ownedProperties;
}

int Player::getIndex() const { 
    return index; 
}

double Player::getAsset() const { 
    int result = cash;
    int size = ownedProperties.size();
    int cost = 0;
    for (int i = 0; i < size; i++){
	    std::string propName = ownedProperties[i]->getName();
        int cost = 0;
        for (int i = 0; i < 28; ++i) {
            if (propName == OWNABLE[i][0]) {
                std::stringstream ss(OWNABLE[i][2]);
                ss >> cost;
                result += cost;
            }
        }
	    int imprLevel = ownedProperties[i]->getImprLevel();
        

	    if (imprLevel > 0){
            for (int i = 0; i < 28; ++i) {
                if (propName == OWNABLE[i][0]) {
                    std::stringstream ss(OWNABLE[i][3]);
                    ss >> cost;
                    cost = imprLevel*cost;
                    result += cost;
                    break;
                }
            }
	    }
    }
    return result; 
}

bool Player::getisInTimsLine() const { 
    return isInTimsLine; 
}

int Player::getTurnsInTimsLine() const { 
    return turnsInTimsLine; 
}

int Player::getadd_roll_for_jail() const {
    return roll_for_jail;
}

// Setters
void Player::setCups(int n) { 
    cups = n; 
}

void Player::setPos(int pos) { 
    if (pos < 0) {
        pos = (pos + 40) % 40;  // Ensure it wraps around correctly
    } else {
        pos = pos % 40;  // Ensure valid board position
    }
    position = pos; 
}

void Player::setBankrupt(bool b) { 
    isBankrupt = b; 
}

void Player::setownedGyms(int n) {
    ownedGyms = n;
}

void Player::setownedResidence(int n) {
    ownedResidence = n;
}

void Player::setownedAcademic(int n) {
    ownedAcademic = n;
}

void Player::setIndex(int n) { 
    index = n; 
}

void Player::setTurnsInTimsLine(int turns) { 
    turnsInTimsLine = turns; 
}

void Player::changeTurnsInTimsLine() {
    turnsInTimsLine--;
}

void Player::setRollForJail(int n) {
    roll_for_jail = n;
}

void Player::useCups() {
    cups--;
}

void Player::resetTurnsInTims() { turnsInTimsLine = 3; }

bool Player::checkIfInMonopolyBlock(std::string name) {
    std::string monoBlockOfSquare = monoBlockOfProp(name);
    int size = monopolyBlocks.size();

    for (int i = 0; i < size; i++) {
        if (monopolyBlocks[i] == monoBlockOfSquare) {
            return true;
        }
    }

    return false;
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

void Player::changeCash(double c) {
    //check for bankcruptcy;
    cash += c;
    changeAsset(c);
}


void Player::updateMonopolyBlock() {
    int size = ownedProperties.size();
    std::map<std::string, int> tracking; 
    std::string eachBlock;

    ownedGyms = 0;
    ownedResidence = 0;
    for (int i = 0; i < size; i++) {
        std::string propName = ownedProperties[i]->getName();
        if (isGym(propName)){
            ownedGyms++;
        } else if (isResidence(propName)){
            ownedResidence++;
        }
        eachBlock = ownedProperties[i]->getMonoBlock();
	    tracking[eachBlock] += 1;
    }

    for (auto &block: tracking) {
        if (block.second == 2 && (block.first == "Math" || block.first == "Arts1")) {
            monopolyBlocks.push_back(block.first);
        } else if (block.second == 3) {
            monopolyBlocks.push_back(block.first);
        }
    }
}

void Player::addTimsCup() {
    ++cups;
}

bool Player::mortgageProp(std::shared_ptr<Building> prop) {
    int cost = 0;
    for (int i = 0; i < 28; ++i) {
        if (prop->getName() == OWNABLE[i][0]) {
            int cost;
            std::stringstream ss(OWNABLE[i][2]);
            ss >> cost;
        }
    }
    cost = cost * 0.5;
    cash += cost;

    int size = ownedProperties.size();
    for (int i = 0; i < size; i++) {
        if (prop == ownedProperties[i]) {
            ownedProperties[i]->setMortStatus(true);
            break;
        }
    }
    return true;
}

bool Player::unmortgageProp(std::shared_ptr<Building> prop) {
    int cost = 0;
    for (int i = 0; i < 28; ++i) {
        if (prop->getName() == OWNABLE[i][0]) {
            int cost;
            std::stringstream ss(OWNABLE[i][2]);
            ss >> cost;
        }
    }
    cost = cost * 0.6;
    
    if (cost > cash) {
        std::cout << "you don't have enough money to unmortgage" << std::endl;
        return false;
    }

    cash -= cost;

    int size = ownedProperties.size();
    for (int i = 0; i < size; i++) {
        if (prop == ownedProperties[i]) {
            ownedProperties[i]->setMortStatus(false);
            break;
        }
    }
    return true;
}

void Player::movePlayer(int roll) {
    position += roll;
    if (position >= 40) {
        std::cout << "***You receive OSAP SALARY for landing or passing it!***" << std::endl;
        position %= 40;
        this->changeCash(200);
    }
}

void Player::moveToDCTims() {
    position = 10;
    isInTimsLine = true;
    return;
}

void Player::printAsset() {
    cout << "Player : " << name << endl;
    cout << "Money Owned : $" << cash << endl;
    printOwnedProp();
    cout << "The Number of Tims Cups Owned : " << cups << endl;
    cout << "Total worth: " << getAsset() << endl;
}


bool Player::isGym(std::string squareName){
    for (int i = 22; i < 24; i++){
        if (OWNABLE[i][0] == squareName) {
            return true;
        }
    }
    return false;
}

bool Player::isAcademic(std::string squareName){
    for (int i = 0; i < 22; i++){
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

void Player::printOwnedProp() {
    int size = ownedProperties.size();
    
    for (int i = 0; i < size; i++) {
        if (!ownedProperties[i]) {  // Check for nullptr before accessing
            std::cerr << "Error: Null property found at index " << i << std::endl;
            continue;
        }

        cout << ownedProperties[i]->getName() << "\t";

        int cost = 0;
        for (int j = 0; j < 28; ++j) {  // Loop through OWNABLE, not ownedProperties
            if (OWNABLE[j][0] == ownedProperties[i]->getName()) {
                std::stringstream ss(OWNABLE[j][2]);
                ss >> cost;
                break;  // Stop once we find the matching property
            }
        }

        cout << "Cost: $" << cost << "   ";
        cout << "Mortgaged: ";
        
        if (ownedProperties[i]->getMortStatus()) {
            cout << "Yes   " << endl;
        } else {
            cout << "No   ";
            if (isGym(ownedProperties[i]->getName())) {
                cout << "Gym   ";
            }
            if (isResidence(ownedProperties[i]->getName())) {
                cout << "Residence   ";
            }
            if (isAcademic(ownedProperties[i]->getName())) {
                cout << "Improvements: " << ownedProperties[i]->getImprLevel() << "\t";
            }
            cout << endl;
        }
    }
}

void Player::loadUpdateAmountToPay() {
    int size = ownedProperties.size();
    for (int i = 0; i < size; i++){ 
        if (isGym(ownedProperties[i]->getName())) {
            ownedProperties[i]->setGymLevel(ownedGyms-1);
        }
        if (isResidence(ownedProperties[i]->getName())) {
            ownedProperties[i]->setResLevel(ownedResidence-1);
        }
        if (isAcademic(ownedProperties[i]->getName())) {
            bool blockOwned = checkIfInMonopolyBlock(ownedProperties[i]->getName());
            if (blockOwned){
                auto acad = std::dynamic_pointer_cast<Academic>(ownedProperties[i]);
                acad->setOwned(true);
            }
        }
    }
}

void Player::removeProp(std::shared_ptr<Building> property_name) {
    if (!ownThisProp(property_name->getName())) {
        std::cout << "this props is nnowned" << std::endl;
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
    if (ownThisProp(property_name->getName())) {
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
    ownedProperties.emplace_back(property_name);
}

void Player::leaveTimsLine() { 
    isInTimsLine = false;
}

void Player::setIsInTimsLine(bool status) { isInTimsLine = status; }

void Player::changeAsset(double c) {
    assets += c; 
}

void Player::changePropertyCount(int residences, int gyms, int academics) {
    int r = residences;
    int g = gyms;
    int a = academics;
}

void Player::receive(int amount) {
    cash += amount;
}

void Player::removeCup() {
    --cups;
}

void Player::add_roll_for_jail() {
    --roll_for_jail;
}

std::string Player::monoBlockOfProp(std::string name) {
    std::string result = "";

    for (int i = 0; i < 28; i++) {
        if (OWNABLE[i][0] == name) {
            result = OWNABLE[i][1];
        }
    }

    return result;
}


// bool Player::checkMonopoly(int block) {
//     int getMonopoly[8] = {2, 3, 3, 3, 3, 3, 3, 2};
//     if (monopolyBlocks[block] == getMonopoly[block]) {
//         return true;
//     } else {
//         return false;
//     }
// }


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
        monopolyBlocks.clear();
    }


    cout << getName() << " has declared bankruptcy!" << endl;
}

bool Player::checkBankrupt() const {
    return cash < 0;
}
