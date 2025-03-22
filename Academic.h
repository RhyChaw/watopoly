#ifndef ACADEMIC_H
#define ACADEMIC_H
#include <string>
#include "building.h"
#include "Player.h"

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
    int costToPayDou(std::string squareName, int imprLevel);
    int costToPaysin(std::string squareName);
    std::string getBlock() const;
    void setBlock(string block);
    int getOwned() const;
    void setOwned(bool flag);
    virtual int amountToPay() override;
    void currentOn(Player* player);
};

#endif // ACADEMIC_BUILDING_H
