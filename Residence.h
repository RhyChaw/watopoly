#ifndef RESIDENCE_H
#define RESIDENCE_H
#include <iostream>
#include <string>
#include "building.h"
#include "propertyArray.h"

class Player;
class building;

class Residence : public Building {
private:
    // Rent rates based on number of residences owned
    static const int RENT_RATES[4];

public:
    Residence(int ID, std::string name, int price, char owner);
    ~Residence();

    // Methods
    int calculateRent() const;
    virtual int amountToPay() override;
    virtual void currentOn(Player* player) override;
    int costToimp(std::string squareName, int imprLevel);
};

#endif // RESIDENCE_H
