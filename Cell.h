#ifndef CELL_H
#define CELL_H

#include <string>
#include <memory>
#include "Player.h"

class Cell {
protected:
    std::string name;

public:
    Cell(const std::string &name);
    virtual ~Cell() = default;

    std::string getName() const;
    
    // This function will be overridden in derived classes (properties, OSAP, etc.)
    virtual void doEvent(std::shared_ptr<Player> player) = 0;
};

#endif // CELL_H
