#include "Player.h"
#include "building.h"
#include "AcademicBuilding.h"
#include <string>
#include <iostream>
module Player;

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
// may be wrong, confirm once individually
Player::Player(std::string name, char symbol, int ownedCups, double cash, int index, 
    bool isTimLine, int turnsInTimsLine, int position_initial, 
    double assets, std::vector<std::shared_ptr<Cell>> ownedProperties,
    int ownedGyms, int ownedResidence, int ownedAcademic, 
    int monopolySet[8], Building* buildings[28])
    : name(name), symbol(symbol), index(index), position_initial(position_initial),
    cash(cash), assets(assets), ownedProperties(ownedProperties),
    ownedGyms(ownedGyms), ownedResidence(ownedResidence), ownedAcademic(ownedAcademic),
    isInTimsLine(isTimLine), turnsInTimsLine(turnsInTimsLine), 
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

// Setters
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
void Player::changeCash(int c) {
    cash += c;
}

void Player::changeAsset(int c) {
     assets += c; 
}

void Player::changePropertyCount(int residences, int gyms, int academics) {
    ownedResidence += residences;
    ownedGyms += gyms;
    ownedAcademic += academics;
}

// Handle cash transactions
void Player::pay(int amount) {
    changeCash(-amount); 
    if (checkBankrupt()) {
        declareBankruptcy(); 
    }
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
    ++ownedCups;
}

void Player::removeCup() {
    --ownedCups;
}

Building *Player::findBuilding(string buildingName) {
    Building *bd;
    for (int i = 0; i < 28; ++i) {
        if (buildings[i]->getName() == buildingName) {
            bd = buildings[i];
            break;
        }
    }
    return bd;
}

bool Player::checkMonopolyImprove(Building *building) {
    AcademicBuilding *acad = dynamic_cast<AcademicBuilding *> (building);
    int blocki = acad->getBlock();
    bool result = true;
    for (int i = 0; i < 28; ++i) {
        if (buildings[i] != nullptr) {
            AcademicBuilding *acad2 = dynamic_cast<AcademicBuilding *> (buildings[i]);
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
    if (monopoly[block] == getMonopoly[block]) {
        return true;
    } else {
        return false;
    }
}

void Player::buyBuilding(Building *building) {
    if (building->getName() == "PAC" || building->getName() == "CIF") {
        changePropertyCount(0, 1, 0);
    } else if (building->getName() == "MKV" || building->getName() == "UWP" || building->getName() == "V1" || building->getName() == "REV") {
        changePropertyCount(1, 0, 0);
    } else {
        AcademicBuilding *ac = dynamic_cast<AcademicBuilding *>(building);
        ++monopolySet[ac->getBlock()]; 
        changePropertyCount(0 , 0 ,1);

    }
    int cost = building->getCost();
    changeCash(-cost);
    changeAsset(building->getCost());
    for (int i = 0; i < 28; ++i) {
        if (buildings[i] == nullptr) {
            buildings[i] = building;
            break;
        }
    }
    building->setOwner(this);
    //print statement
}

void Player::sellBuilding(Building *building) {
    if (building->getName() == "PAC" || building->getName() == "CIF") {
        changePropertyCount(0, -1, 0);
   } else if (building->getName() == "MKV" || building->getName() == "UWP" || building->getName() == "V1" || building->getName() == "REV") {
        changePropertyCount(-1, 0, 0);
   } else {
       AcademicBuilding *ac = dynamic_cast<AcademicBuilding *>(building);
       --monopoly[ac->getBlock()];
       changePropertyCount(0 , 0 ,-1);
   }
   changeAsset(-(building->getCost()));
    int cost = building->getCost();
    changeCash(cost); 
   for (int i = 0; i < 28; ++i) {
       if (buildings[i]->getName() == building->getName()) {
           buildings[i] = nullptr;
           break;
       }
   }
   //print statement
}

void Player::mortgage(Building *building) {
    if (building->getOwner()->getName() != name) {
        // print statement not the owner
    } else if (building->getMortgage() == true) {
        //print statement already mortgaged
    } else if (building->getName() != "PAC" && building->getName() != "CIF" && building->getName() != "MKV" && building->getName() != "UWP" && building->getName() != "V1" && building->getName() != "REV") {
        //print NOT A ACADEMIC BUILDING 
    } else if (building->getCurrentLevel() != 0) {
        // print there are still improvments you can sell.
    } else {
        double mortgagedCash = building->getCost()*0.5;
        changeAsset(-(building->getCost()));
        changeCash(mortgagedCash);
        building->setMortgage(true);
        //priont statement that it worked
    }
}

void Player::unmortgage(Building *building) {
    if (building->getOwner()->getName() != name) {
        //print sttement you are the owner
    } else if (building->getMortgage() == false) {
        // is not a mortgaged building
    } else {
        double unmortgageCost = building->getCost()*0.6;
        if (cash < unmortgageCost) {
            // does not have enough money to unmortgage
        } else {
            changeCash(-unmortgageCost);
            changeAsset(building->getCost());
            building->setMortgage(false);
            // print statement that it is successful
        }
    }
}

void Player::buyImprovement(Building *building) {
    AcademicBuilding *acad = dynamic_cast<AcademicBuilding *> (building);
    if (building->getName() == "PAC" || building->getName() == "CIF" || building->getName() == "MKV" || building->getName() == "UWP" || building->getName() == "V1" || building->getName() == "REV") {
        //print statement cant imprive non acad.....
    } else if (checkMonopoly(acad->getBlock()) == false) {
        // only monopoly can be improved.
    } else {
        int improveCost = acad->getImprovementCost();
        if (cash < improveCost) {
            //dont have enough money
        } else {
            if(acad->getCurrentLevel() >= 5){
                //already max level
                return;
            }
            changeCash(-improveCost);
            changeAsset(improveCost);
            acad->changeLevel(1);
            // successfully printed
        }
    }
}

void Player::sellImprovement(Building *building) {
    AcademicBuilding *acad = dynamic_cast<AcademicBuilding *> (building);
    if (building->getName() == "PAC" || building->getName() == "CIF" || building->getName() == "MKV" || building->getName() == "UWP" || building->getName() == "V1" || building->getName() == "REV") {
        // not acad
    } else if (acad->getCurrentLevel() == 0) {
        //no improvemnets to remove
    } else {
        int sellImproveFee = acad->getImprovementCost() / 2;
        changeCash(sellImproveFee);
        changeAsset(-(ac->getImprovementCost()));
        acad->changeLevel(-1);
        // succesfully sold parameter.
    }
}

void Player::trade(Player *partner, double money, Building *building) {
    if (building->getOwner()->getName() != partner->getName()) {
        // manit dont own this property.
    } else if (getCash() < money) {
        // i got no money
    } else if (checkMonopolyImprove(building) == false) {
        // property has improvments
    } else {
        // print to ask if he want this offer
        string choice;
        cin >> choice;
        if (choice == "accept" || choice == "y" || choice == "yes") {
            //trade accecpted intititing trade
            buyBuilding(building);
            changeCash(-money);
            changeAsset(building->getCost());
            partner->sellBuilding(building);
            partner->changeCash(money);
            partner->changeAsset(-(building->getCost()));
            // trade successful
        } else {
            //trade rejected 
        }
    }
}

void Player::trade(Player *partner, Building *building1, Building *building2) {
    AcademicBuilding *acad1 = dynamic_cast<AcademicBuilding *>(building1);
    AcademicBuilding *acad2 = dynamic_cast<AcademicBuilding *>(building2);
    if (building1->getOwner()->getName() != name) {
        // i dont own this building
    } else if (building2->getOwner()->getName() != partner->getName()) {
        // rhythm dont own this building
    } else if (acad1 &&  checkMonopolyImprove(acad1) == false) {
        // i have improvemnt on...
    } else if (acad2 &&  checkMonopolyImprove(acad2) == false){
        // manit have improvement on.....
    } else {
        // print to ask if he want this offer
        string choice;
        cin >> choice;
        if (choice == "accept" || choice == "y" || choice == "yes") {
            buyBuilding(building2);
            sellBuilding(building1);
            changeAsset(building2->getCost());
            changeAsset(-(building1->getCost()));

            partner->sellBuilding(building2);
            partner->buyBuilding(building1);
            partner->changeAsset(building1->getCost());
            partner->changeAsset(-(building2->getCost()));
            // done deal
        } else {
            // nah bruhhhhh
        }
    }
}

void Player::trade(Player *partner, Building *building, double money) {
    if (building->getOwner()->getName() != name) {
        // i dont own the building
    } else if (partner->getCash() < money) {
        // rhthm doesnt have money
    } else if (checkMonopolyImprove(building) == false) {
        // i have improvemnts on the building
    } else {
        // print to ask if he want this offer
        string choice;
        cin >> choice;
        if (choice == "accept" || choice == "y" || choice == "yes") {
            //trade accecpted intititing trade
            sellBuilding(building);
            changeCash(money);
            changeAsset(-(building->getCost()));
            partner->buyBuilding(building);
            partner->changeAsset(building->getCost());
            partner->changeCash(-money);
            // trade successful
        } else {
            //trade rejected 
        }
    }
}

void Player::trade(Player *partner, double money1, double money2) {
    // print statement for why u gotta do this.........
}

void Player::printAsset() {
    cout << "Player : " << name << endl;
    cout << "Money Owned : $" << cash << endl;
    cout << "Net Worth: $" << asset << endl;
    cout << "The Number of Tims Cups Owned : " << ownedCups << endl;
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

    for (int i = 0; i < 28; ++i) {
        buildings[i] = nullptr;
    }

    cout << getName() << " has declared bankruptcy!" << endl;
}

bool Player::checkBankrupt() const {
    return cash < 0;
}

