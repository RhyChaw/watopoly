#include "Cell.h"

Cell::Cell(int ID, std::string name) : ID{ID}, name{name} {}

std::string Cell::getName() {
    return name;
}

void Cell::setName(std::string name) {
    this->name = name;
}

int Cell::getID() {
    return ID;
}

void Cell::setID(int id) {
    this->ID = id;
}
