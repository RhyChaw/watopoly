#ifndef ACADEMIC_BUILDING_H
#define ACADEMIC_BUILDING_H

#include "Building.h"
#include <string>
#include <vector>

class AcademicBuilding : public Building {
private:
    int improvements;
    int improvementCost;
    std::vector<int> tuitionRates;
    std::string monopolyBlock;

public:
    AcademicBuilding(std::string name, int cost, int improveCost, std::string block = "");
    ~AcademicBuilding();

    // Getters
    std::string getBlock() const;
    int getImprovement() const;
    int getTuition() const;
    int getCurrentLevel() const;
    
    // Building methods
    void currentOn(Player* player) override;
    
    // Academic building specific methods
    void addImprovement();
    void removeImprovement();
};

#endif // ACADEMIC_BUILDING_H
