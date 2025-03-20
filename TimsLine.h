#ifndef TIMS_LINE_H
#define TIMS_LINE_H

#include "NonProperty.h"
#include <string>

class TimsLine : public NonProperty {
public:
    TimsLine(std::string name);
    ~TimsLine();

    void doEvent(Player* player) override;
    bool canLeave(Player* player) const;
    void handleRoll(Player* player, int dice1, int dice2);
};

#endif // TIMS_LINE_H
