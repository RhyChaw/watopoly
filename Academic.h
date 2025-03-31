#ifndef ACADEMIC_H
#define ACADEMIC_H
#include <string>
#include "building.h"
#include "Player.h"
#include "propertyArray.h"

using namespace std;

class building;

class Academic : public Building {
private:
    int rentatata;
    bool owned = false;
    string block;

public:
    Academic(int ID, std::string name, int price, char owner);
    ~Academic();

    // Getters
    int costToimp(std::string squareName, int imprLevel);
    int costTogen(std::string squareName);
    std::string getBlock() const;
    void setBlock(string block);
    bool getOwned() const;
    void setOwned(bool flag);
    virtual int amountToPay() override;
};

#endif // ACADEMIC_BUILDING_H
