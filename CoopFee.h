#ifndef COOP_FEE_H
#define COOP_FEE_H

#include "NonProperty.h"
#include <string>

class CoopFee : public NonProperty {
private:
    static const int FEE_AMOUNT = 150;

public:
    CoopFee(std::string name);
    ~CoopFee();

    void doEvent(Player* player) override;
};

#endif // COOP_FEE_H
