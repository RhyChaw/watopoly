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
void Player::changeCash(double c) {
    //check for bankcruptcy;
    cash += c;
    changeAsset(c);
}

void Player::changeAsset(double c) {
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
    ++cups;
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

void Player::buyBuilding(Building *building) {
    if (building->getName() == "PAC" || building->getName() == "CIF") {
        changePropertyCount(0, 1, 0);
    } else if (building->getName() == "MKV" || building->getName() == "UWP" || building->getName() == "V1" || building->getName() == "REV") {
        changePropertyCount(1, 0, 0);
    } else {
        AcademicBuilding *ac = dynamic_cast<AcademicBuilding *>(building);
        if (ac) {
            ++monopolySet[ac->getBlock()]; 
            changePropertyCount(0, 0, 1);
        }
    }
    int cost = building->getCostToBuy();
    changeCash(-cost);
    changeAsset(cost);
    for (int i = 0; i < 28; ++i) {
        if (buildings[i] == nullptr) {
            buildings[i] = building;
            break;
        }
    }
    building->setOwner(this->symbol); // Changed to match Building class
    //print statement
}

void Player::sellBuilding(Building *building) {
    if (building->getName() == "PAC" || building->getName() == "CIF") {
        changePropertyCount(0, -1, 0);
   } else if (building->getName() == "MKV" || building->getName() == "UWP" || building->getName() == "V1" || building->getName() == "REV") {
        changePropertyCount(-1, 0, 0);
   } else {
       AcademicBuilding *ac = dynamic_cast<AcademicBuilding *>(building);
       if (ac) {
           --monopolySet[ac->getBlock()];
           changePropertyCount(0, 0, -1);
       }
   }
   changeAsset(-(building->getCostToBuy()));
    int cost = building->getCostToBuy();
    changeCash(cost); 
   for (int i = 0; i < 28; ++i) {
       if (buildings[i] && buildings[i]->getName() == building->getName()) {
           buildings[i] = nullptr;
           break;
       }
   }
   building->setOwner(' '); // Set to empty ownership
   //print statement
}

void Player::mortgage(Building *building) {
    if (building->getOwner() != this->symbol) {
        // print statement not the owner
        return;
    } 
    if (building->getMortStatus() == true) {
        //print statement already mortgaged
        return;
    } 
    
    // Check if it's not an academic building or has improvements
    if (building->getName() != "PAC" && building->getName() != "CIF" && 
        building->getName() != "MKV" && building->getName() != "UWP" && 
        building->getName() != "V1" && building->getName() != "REV") {
        
        AcademicBuilding *acad = dynamic_cast<AcademicBuilding *>(building);
        if (acad && acad->getImprLevel() != 0) {
            // print there are still improvements you can sell.
            return;
        }
    }
    
    double mortgagedCash = building->getCostToBuy() * 0.5;
    changeAsset(-(building->getCostToBuy()));
    changeCash(mortgagedCash);
    building->setMortStatus(true);
    //print statement that it worked
}

void Player::unmortgage(Building *building) {
    if (building->getOwner() != this->symbol) {
        //print statement you are not the owner
        return;
    } 
    if (building->getMortStatus() == false) {
        // is not a mortgaged building
        return;
    } 
    
    double unmortgageCost = building->getCostToBuy() * 0.6;
    if (cash < unmortgageCost) {
        // does not have enough money to unmortgage
        return;
    } 
    
    changeCash(-unmortgageCost);
    changeAsset(building->getCostToBuy());
    building->setMortStatus(false);
    // print statement that it is successful
}

void Player::buyImprovement(Building *building) {
    // Check if it's an academic building
    if (building->getName() == "PAC" || building->getName() == "CIF" || 
        building->getName() == "MKV" || building->getName() == "UWP" || 
        building->getName() == "V1" || building->getName() == "REV") {
        //print statement cant improve non-academic buildings
        return;
    } 
    
    AcademicBuilding *acad = dynamic_cast<AcademicBuilding *>(building);
    if (!acad) {
        // Not an academic building
        return;
    }
    
    if (checkMonopoly(acad->getBlock()) == false) {
        // only monopoly can be improved.
        return;
    } 
    
    int improveCost = acad->getImprovementCost();
    if (cash < improveCost) {
        //dont have enough money
        return;
    } 
    
    if(acad->getImprLevel() >= 5){
        //already max level
        return;
    }
    
    changeCash(-improveCost);
    changeAsset(improveCost);
    acad->setImprLevel(acad->getImprLevel() + 1);
    // successfully printed
}

void Player::sellImprovement(Building *building) {
    // Check if it's an academic building
    if (building->getName() == "PAC" || building->getName() == "CIF" || 
        building->getName() == "MKV" || building->getName() == "UWP" || 
        building->getName() == "V1" || building->getName() == "REV") {
        // not academic building
        return;
    } 
    
    AcademicBuilding *acad = dynamic_cast<AcademicBuilding *>(building);
    if (!acad) {
        // Not an academic building
        return;
    }
    
    if (acad->getImprLevel() == 0) {
        //no improvements to remove
        return;
    } 
    
    int sellImproveFee = acad->getImprovementCost() / 2;
    changeCash(sellImproveFee);
    changeAsset(-(acad->getImprovementCost()));
    acad->setImprLevel(acad->getImprLevel() - 1);
    // successfully sold parameter.
}

void Player::trade(Player *partner, double money, Building *building) {
    if (building->getOwner() != partner->symbol) {
        // partner doesn't own this property
        return;
    } 
    if (getCash() < money) {
        // not enough money
        return;
    } 
    
    // Check for improvements on academic buildings
    AcademicBuilding *acad = dynamic_cast<AcademicBuilding *>(building);
    if (acad && acad->getImprLevel() != 0) {
        // property has improvements
        return;
    } 
    
    // print to ask if partner wants this offer
    string choice;
    cout << partner->getName() << ", do you accept this trade offer? (yes/no): ";
    cin >> choice;
    if (choice == "accept" || choice == "y" || choice == "yes") {
        //trade accepted initiating trade
        changeCash(-money);
        partner->changeCash(money);
        
        // Update the property ownership
        for (int i = 0; i < 28; ++i) {
            if (partner->buildings[i] && partner->buildings[i] == building) {
                partner->buildings[i] = nullptr;
                break;
            }
        }
        
        for (int i = 0; i < 28; ++i) {
            if (buildings[i] == nullptr) {
                buildings[i] = building;
                break;
            }
        }
        
        // Update property counts and assets
        if (building->getName() == "PAC" || building->getName() == "CIF") {
            changePropertyCount(0, 1, 0);
            partner->changePropertyCount(0, -1, 0);
        } else if (building->getName() == "MKV" || building->getName() == "UWP" || 
                   building->getName() == "V1" || building->getName() == "REV") {
            changePropertyCount(1, 0, 0);
            partner->changePropertyCount(-1, 0, 0);
        } else {
            AcademicBuilding *acad = dynamic_cast<AcademicBuilding *>(building);
            if (acad) {
                ++monopolySet[acad->getBlock()];
                --partner->monopolySet[acad->getBlock()];
                changePropertyCount(0, 0, 1);
                partner->changePropertyCount(0, 0, -1);
            }
        }
        
        changeAsset(building->getCostToBuy());
        partner->changeAsset(-(building->getCostToBuy()));
        building->setOwner(this->symbol);
        
        cout << "Trade successful!" << endl;
    } else {
        cout << "Trade rejected." << endl;
    }
}

void Player::trade(Player *partner, Building *building1, Building *building2) {
    if (building1->getOwner() != this->symbol) {
        // I don't own the first building
        return;
    } 
    if (building2->getOwner() != partner->symbol) {
        // Partner doesn't own the second building
        return;
    } 
    
    // Check for improvements on academic buildings
    AcademicBuilding *acad1 = dynamic_cast<AcademicBuilding *>(building1);
    AcademicBuilding *acad2 = dynamic_cast<AcademicBuilding *>(building2);
    
    if (acad1 && acad1->getImprLevel() != 0) {
        // I have improvements on my building
        return;
    } 
    if (acad2 && acad2->getImprLevel() != 0) {
        // Partner has improvements on their building
        return;
    } 
    
    // print to ask if partner wants this offer
    string choice;
    cout << partner->getName() << ", do you accept this trade offer? (yes/no): ";
    cin >> choice;
    if (choice == "accept" || choice == "y" || choice == "yes") {
        // Update property ownerships in the buildings array
        Building *temp = nullptr;
        
        for (int i = 0; i < 28; ++i) {
            if (buildings[i] && buildings[i] == building1) {
                buildings[i] = nullptr;
                break;
            }
        }
        
        for (int i = 0; i < 28; ++i) {
            if (partner->buildings[i] && partner->buildings[i] == building2) {
                partner->buildings[i] = nullptr;
                break;
            }
        }
        
        for (int i = 0; i < 28; ++i) {
            if (buildings[i] == nullptr) {
                buildings[i] = building2;
                break;
            }
        }
        
        for (int i = 0; i < 28; ++i) {
            if (partner->buildings[i] == nullptr) {
                partner->buildings[i] = building1;
                break;
            }
        }
        
        // Update property counts
        if (building1->getName() == "PAC" || building1->getName() == "CIF") {
            changePropertyCount(0, -1, 0);
            partner->changePropertyCount(0, 1, 0);
        } else if (building1->getName() == "MKV" || building1->getName() == "UWP" || 
                   building1->getName() == "V1" || building1->getName() == "REV") {
            changePropertyCount(-1, 0, 0);
            partner->changePropertyCount(1, 0, 0);
        } else if (acad1) {
            --monopolySet[acad1->getBlock()];
            ++partner->monopolySet[acad1->getBlock()];
            changePropertyCount(0, 0, -1);
            partner->changePropertyCount(0, 0, 1);
        }
        
        if (building2->getName() == "PAC" || building2->getName() == "CIF") {
            changePropertyCount(0, 1, 0);
            partner->changePropertyCount(0, -1, 0);
        } else if (building2->getName() == "MKV" || building2->getName() == "UWP" || 
                   building2->getName() == "V1" || building2->getName() == "REV") {
            changePropertyCount(1, 0, 0);
            partner->changePropertyCount(-1, 0, 0);
        } else if (acad2) {
            ++monopolySet[acad2->getBlock()];
            --partner->monopolySet[acad2->getBlock()];
            changePropertyCount(0, 0, 1);
            partner->changePropertyCount(0, 0, -1);
        }
        
        // Update assets and ownership
        building1->setOwner(partner->symbol);
        building2->setOwner(this->symbol);
        
        changeAsset(building2->getCostToBuy() - building1->getCostToBuy());
        partner->changeAsset(building1->getCostToBuy() - building2->getCostToBuy());
        
        cout << "Trade successful!" << endl;
    } else {
        cout << "Trade rejected." << endl;
    }
}

void Player::trade(Player *partner, Building *building, double money) {
    if (building->getOwner() != this->symbol) {
        // I don't own the building
        return;
    } 
    if (partner->getCash() < money) {
        // Partner doesn't have enough money
        return;
    } 
    
    // Check for improvements on academic buildings
    AcademicBuilding *acad = dynamic_cast<AcademicBuilding *>(building);
    if (acad && acad->getImprLevel() != 0) {
        // I have improvements on the building
        return;
    } 
    
    // print to ask if partner wants this offer
    string choice;
    cout << partner->getName() << ", do you accept this trade offer? (yes/no): ";
    cin >> choice;
    if (choice == "accept" || choice == "y" || choice == "yes") {
        //trade accepted initiating trade
        changeCash(money);
        partner->changeCash(-money);
        
        // Update the property ownership
        for (int i = 0; i < 28; ++i) {
            if (buildings[i] && buildings[i] == building) {
                buildings[i] = nullptr;
                break;
            }
        }
        
        for (int i = 0; i < 28; ++i) {
            if (partner->buildings[i] == nullptr) {
                partner->buildings[i] = building;
                break;
            }
        }
        
        // Update property counts
        if (building->getName() == "PAC" || building->getName() == "CIF") {
            changePropertyCount(0, -1, 0);
            partner->changePropertyCount(0, 1, 0);
        } else if (building->getName() == "MKV" || building->getName() == "UWP" || 
                   building->getName() == "V1" || building->getName() == "REV") {
            changePropertyCount(-1, 0, 0);
            partner->changePropertyCount(1, 0, 0);
        } else if (acad) {
            --monopolySet[acad->getBlock()];
            ++partner->monopolySet[acad->getBlock()];
            changePropertyCount(0, 0, -1);
            partner->changePropertyCount(0, 0, 1);
        }
        
        changeAsset(-(building->getCostToBuy()));
        partner->changeAsset(building->getCostToBuy());
        building->setOwner(partner->symbol);
        
        cout << "Trade successful!" << endl;
    } else {
        cout << "Trade rejected." << endl;
    }
}

void Player::trade(Player *partner, double money1, double money2) {
    cout << "This trade doesn't involve any property exchange. Are you sure?" << endl;
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
