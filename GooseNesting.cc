#include "GooseNesting.h"
#include "Player.h"
#include <iostream>

GooseNesting::GooseNesting(int ID, std::string name) : nonbuilding(ID, name) {}

GooseNesting::~GooseNesting() {
}

void GooseNesting::nesting(std::shared_ptr<Player> p) {
    cout << "You are currently on " << this->getName() << "." << endl;
    std::cout << p->getName() << " landed on Goose Nesting and is taking a break." << std::endl;
}
