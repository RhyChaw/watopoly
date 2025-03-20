#ifndef TUITION_H
#define TUITION_H

#include "NonProperty.h"
#include <string>

class Tuition : public NonProperty {
public:
    Tuition(std::string name);
    ~Tuition();

    void doEvent(Player* player) override;
};

#endif // TUITION_H
