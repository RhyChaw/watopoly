#include "square.h"

cell::cell(int ID, std::string name) : ID{ID}, name{name} {}


std::string cell::getName () {
    return name;
}

void cell::setName (string name) {
    this->name = name;
}

int cell::getID() {
    return ID;
}

void cell::getID(int id) {
    this->id = id;
}
