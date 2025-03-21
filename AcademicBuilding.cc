#include "AcademicBuilding.h"
#include "Player.h"
#include <iostream>

AcademicBuilding::AcademicBuilding(std::string name, int cost, int improveCost, std::string block)
    : Building(name, cost), improvements(0), improvementCost(improveCost), monopolyBlock(block) {
    tuitionRates = {
        cost / 10,             // Base rent
        cost / 5,              // 1 improvement
        cost / 2,              // 2 improvements
        cost,                  // 3 improvements
        cost * 2,              // 4 improvements
        cost * 3               // 5 improvements (hotel)
    };
}

AcademicBuilding::~AcademicBuilding() {
    // Nothing to clean up
}

std::string AcademicBuilding::getBlock() const {
    return monopolyBlock;
}

int AcademicBuilding::getImprovement() const {
    return improvements;
}

int AcademicBuilding::getTuition() const {
    return tuitionRates[improvements];
}

int AcademicBuilding::getCurrentLevel() const {
    return improvements;
}

void AcademicBuilding::currentOn(Player* player) {
    // Implementation for when a player lands on this building
    if (getOwner() == nullptr) {
        // No owner, player can purchase
        std::cout << player->getName() << " landed on unowned property " << getName() << std::endl;
        // Purchase logic would go here
    } else if (getOwner() != player) {
        // Another player owns this property, pay rent
        int rent = getTuition();
        if (hasMonopoly() && improvements == 0) {
            rent *= 2; // Double rent for monopoly with no improvements
        }
        
        std::cout << player->getName() << " pays " << rent << " to " 
                  << getOwner()->getName() << " for landing on " << getName() << std::endl;
        
        player->removeMoney(rent);
        getOwner()->addMoney(rent);
    } else {
        // Player owns this property
        std::cout << player->getName() << " landed on their own property " << getName() << std::endl;
    }
}

void AcademicBuilding::addImprovement() {
    if (improvements < 5) {
        improvements++;
        std::cout << "Added improvement to " << getName() 
                  << ". New level: " << improvements << std::endl;
    } else {
        std::cout << getName() << " already has maximum improvements." << std::endl;
    }
}

void AcademicBuilding::removeImprovement() {
    if (improvements > 0) {
        improvements--;
        std::cout << "Removed improvement from " << getName() 
                  << ". New level: " << improvements << std::endl;
    } else {
        std::cout << getName() << " has no improvements to remove." << std::endl;
    }
}
