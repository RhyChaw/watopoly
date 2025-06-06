#ifndef RESIDENCE_H
#define RESIDENCE_H
#include <iostream>
#include <string>
#include "building.h"
#include "propertyArray.h"

class Residence : public Building {
private:
    static const int RENT_RATES[4];

public:
    Residence(int ID, std::string name, int price, char owner);
    ~Residence();

    // Methods
    int calculateRent() const;
    virtual int amountToPay() override;
    int costToimp(std::string squareName, int imprLevel);
};

#endif // RESIDENCE_H
