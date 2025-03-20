#ifndef GYM_H
#define GYM_H

#include "Building.h"
#include <string>

class Gym : public Building {
public:
    Gym(std::string name);
    ~Gym();

    // Methods
    int calculateFee(int diceRoll) const;
    void currentOn(Player* player) override;
    int getOwnerGymCount() const;
};

#endif // GYM_H
