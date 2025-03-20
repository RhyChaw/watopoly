#include "TimsLine.h"
#include "Player.h"
#include <iostream>

TimsLine::TimsLine(std::string name) : NonProperty(name) {
    // Nothing to initialize
}

TimsLine::~TimsLine() {
    // Nothing to clean up
}

void TimsLine::doEvent(Player* player) {
    // When a player lands on Tim's Line, they're just visiting
    std::cout << player->getName() << " is just visiting Tim's Line." << std::endl;
    // No effect on the player
}

bool TimsLine::canLeave(Player* player) const {
    // Player can leave if they have a cup or have waited the required turns
    return player->getOwnedCups() > 0 || player->getNumLineWait() >= 3;
}

void TimsLine::handleRoll(Player* player, int dice1, int dice2) {
    if (player->getIsTimLine()) {
        if (dice1 == dice2) {
            // Rolled doubles, can leave
            std::cout << player->getName() << " rolled doubles and leaves Tim's Line!" << std::endl;
            player->setIsTimLine(false);
            player->setNumLineWait(0);
        } else if (player->getNumLineWait() >= 2) {
            // Third turn, must pay or use cup to leave
            if (player->getOwnedCups() > 0) {
                std::cout << player->getName() << " uses a Tim's Cup to leave Tim's Line!" << std::endl;
                player->removeCup();
            } else {
                std::cout << player->getName() << " pays 50 to leave Tim's Line!" << std::endl;
                player->removeMoney(50);
            }
            player->setIsTimLine(false);
            player->setNumLineWait(0);
        } else {
            // Increment wait counter
            player->setNumLineWait(player->getNumLineWait() + 1);
            std::cout << player->getName() << " is still in Tim's Line. Turns waited: " 
                      << player->getNumLineWait() << std::endl;
        }
    }
}
