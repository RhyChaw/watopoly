#include "GooseNesting.h"
#include "Player.h"
#include <iostream>

GooseNesting::GooseNesting(std::string name) : NonProperty(name) {
    // Nothing to initialize
}

GooseNesting::~GooseNesting() {
    // Nothing to clean up
}

void GooseNesting::doEvent(Player* player) {
    // Goose Nesting is just a free resting spot
    std::cout << player->getName() << " landed on Goose Nesting and is taking a break." << std::endl;
    // No effect on the player
}
