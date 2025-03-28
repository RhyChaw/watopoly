#ifndef GYM_H
#define GYM_H
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include "building.h"
#include "propertyArray.h"

using namespace std;

class Gym : public Building {
private:
    int roll;
public:
    //big 5
    Gym(int ID, std::string name, int price, char owner);
    ~Gym();

    void setRoll(int roll);
    int getRoll() const;

    // Methods
    int costToimp(std::string squareName, int imprLevel);
    int amountToPay() override;
};

#endif // GYM_H
