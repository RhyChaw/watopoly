#include "SLC.h"
#include "Player.h"
#include <iostream>
#include <cstdlib> // for rand()
#include <ctime>   // for time()

SLC::SLC(std::string name) : NonProperty(name) {
    // Initialize possible movements
    // Positive values move forward, negative values move backward
    movements = {-3, -2, -1, 1, 2, 3, 10}; // 10 is "Advance to OSAP"
    
    // Seed random number generator
    srand(time(NULL));
}

SLC::~SLC() {
    // Nothing to clean up
}

int SLC::getRandomMovement() const {
    // Generate a random index into the movements vector
    int index = rand() % movements.size();
    return movements[index];
}

void SLC::doEvent(Player* player) {
    int movement = getRandomMovement();
    std::cout << player->getName() << " landed on SLC and drew a card." << std::endl;
    
    if (movement == 10) {
        // Special case: Advance to OSAP
        std::cout << player->getName() << " advances to OSAP." << std::endl;
        player->setIndex(0); // OSAP is at position 0
        // The GameBoard should handle calling doEvent on the new cell
    } else {
        // Regular movement
        int newPos = (player->getIndex() + movement) % 40;
        if (newPos < 0) newPos += 40; // Handle negative positions
        
        std::cout << player->getName() << " moves " 
                  << (movement > 0 ? "forward " : "backward ")
                  << abs(movement) << " spaces." << std::endl;
        
        player->setIndex(newPos);
        // The GameBoard should handle calling doEvent on the new cell
    }
}

