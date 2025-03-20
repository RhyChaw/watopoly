#ifndef OSAP_H
#define OSAP_H

#include "NonProperty.h"
#include <string>

class OSAP : public NonProperty {
private:
    static const int COLLECT_AMOUNT = 200;

public:
    OSAP(std::string name);
    ~OSAP();

    void doEvent(Player* player) override;
};

#endif // OSAP_H
