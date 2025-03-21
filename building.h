#ifndef OWNABLE_H
#define OWNABLE_H
#include <string>
#include "Cell.h"

class cell;

class building : public Square {
    char owner;
    int price;
    bool mortgageStatus = false;
    int imprl;
    int payLevel; //almost the same with imprLevel except for gym and resident, this one show how many gym (or res) all own together 
    std::string monopolyBlock;

  public:
    building(int ID, std::string name, int price, char owner);
    virtual ~building();

    void setOwner(char owner);
    void setMortStatus(bool status);
    void setImprLevel(int level);
    void setPayLevel(int level);

    char getOwner() const;
    bool getMortStatus() const;
    int getImprLevel() const;
    int getPayLevel() const;

    int getCostToBuy() const;
    std::string getMonoBlock() const;
};

#endif
