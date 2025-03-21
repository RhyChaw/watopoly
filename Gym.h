#ifndef GYM_H
#define GYM_H

#include "Building.h"
#include <string>
using namespace std;
class Gym : public Building {
private:
    int roll;
public:
    Gym(int ID, std::string name, int price, char owner);
    ~Gym();

    // Methods
    int calculateFee(int diceRoll) const;
    void currentOn(Player* player) override;
    int getOwnerGymCount() const;
};

#endif // GYM_H
