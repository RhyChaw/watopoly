#ifndef SLC_H
#define SLC_H

#include "NonProperty.h"
#include <string>
#include <vector>

class SLC : public NonProperty {
private:
    std::vector<int> movements;
    
    int getRandomMovement() const;

public:
    SLC(std::string name);
    ~SLC();

    void doEvent(Player* player) override;
};

#endif // SLC_H
