#ifndef BUILDING_H
#define BUILDING_H
#include <string>
#include "Cell.h"
#include "propertyArray.h"

class Building : public Cell {
    char owner;
    int price;
    bool mortgageStatus = false;
    int imprLevel;
    int GymLevel = 0; // number of gyms owned by a player
    int ResLevel = 0; // number of res owned by a player
    std::string monopolyBlock;

  public:
    std::string monoBlockOfProp(std::string squareName);
    //big 5
    Building(int ID, std::string name, int price, char owner);
    virtual ~Building() = default;
    
    //setter
    void setOwner(char owner);
    void setMortStatus(bool status);
    void setImprLevel(int level);
    void setGymLevel(int level);
    void setResLevel(int level);

    //getter
    char getOwner() const;
    bool getMortStatus() const;
    int getImprLevel() const;
    int getGymLevel() const;
    int getResLevel() const;
    int getCostToBuy() const;
    std::string getMonoBlock() const;

    //other functions needed for the bottom classes
    virtual int amountToPay() = 0; 

};

#endif // BUILDING_H
