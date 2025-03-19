#include "Cell.h"

Cell::Cell(const std::string &name) : name(name) {}

std::string Cell::getName() const {
    return name;
}
