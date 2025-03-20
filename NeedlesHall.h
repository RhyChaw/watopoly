#ifndef NEEDLES_HALL_H
#define NEEDLES_HALL_H

#include "NonProperty.h"
#include <string>
#include <vector>

class NeedlesHall : public NonProperty {
private:
    std::vector<int> outcomes;
    
    int getRandomOutcome() const;

public:
    NeedlesHall(std::string name);
    ~NeedlesHall();

    void doEvent(Player* player) override;
};

#endif // NEEDLES_HALL_H
