#ifndef GOOSE_NESTING_H
#define GOOSE_NESTING_H

#include "NonProperty.h"
#include <string>

class GooseNesting : public NonProperty {
public:
    GooseNesting(std::string name);
    ~GooseNesting();

    void doEvent(Player* player) override;
};

#endif // GOOSE_NESTING_H
