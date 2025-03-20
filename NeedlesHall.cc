#include "NeedlesHall.h"
#include "Player.h"
#include <iostream>
#include <cstdlib> // for rand()
#include <ctime>   // for time()

NeedlesHall::NeedlesHall(std::string name) : NonProperty(name) {
    // Initialize possible monetary outcomes
    outcomes = {-200, -100, -50, 25, 50, 100, 200};
    
    // Seed random number generator
    srand(time(NULL));
}

NeedlesHall::~NeedlesHall() {
    // Nothing to clean up
}

int NeedlesHall::getRandomOutcome() const {
    // Generate a random index into the outcomes vector
    int index = rand() % outcomes.size();
    return outcomes[index];
}

void NeedlesHall::doEvent(Player* player) {
    int moneyChange = getRandomOutcome();
    
    std::cout << player->getName() << " landed on Needles Hall and drew a card." << std::endl;
    
    if (moneyChange > 0) {
        std::cout << player->getName() << " receives " << moneyChange << " dollars." << std::endl;
        player->addMoney(moneyChange);
    } else if (moneyChange < 0) {
        std::cout << player->getName() << " pays " << -moneyChange << " dollars." << std::endl;
        player->removeMoney(-moneyChange); // Convert negative to positive for removeMoney
    } else {
        std::cout << "No change in funds." << std::endl;
    }
}
