#include "Tuition.h"
#include "Player.h"
#include <iostream>


Tuition::Tuition(int ID, std::string name) : nonbuilding(ID, name) {

}

Tuition::~Tuition() {
    // Nothing to clean up
}

void Tuition::pay(std::shared_ptr<Player> p) {
    char option;
    int money;
    while (true) {
        std::cout << p->getName() << " landed on Tuition." << std::endl;
        std::cout << "Options: \n\tA) Pay $300 or \n\tB) Pay 10% of your total net worth!" << std::endl;
        cin >> option;
        std::cout << "Please select an option!"
        if (option == 'A' || option == 'B') {
            break;
        }
    }
    if (option == 'A') {
        p->changeCash(-300);
        money = 300;
    } else if (option == 'B') {
        money = p->getAsset() * 0.1;
        p->changeAsset(p->getAsset() * 0.1);
    }

    std::cout << p->getName() << " pays $" << money << " for tuition." << std::endl;
}


