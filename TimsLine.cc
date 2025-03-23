#include "TimsLine.h"
#include "Player.h"
#include <iostream>
using namespace std;

TimsLine::TimsLine(int ID, std::string name) : nonbuilding(ID, name) {}

TimsLine::~TimsLine() {}

int TimsLine::turns(std::shared_ptr<Player> p) {
    return p->getadd_roll_for_jail();
}

bool TimsLine::jail(std::shared_ptr<Player> p) {
    return p->getisInTimsLine();
}

void TimsLine::add(std::shared_ptr<Player> p){
    p->add_roll_for_jail();
}

// void TimsLine::handleRoll(Player* player, int dice1, int dice2) {
//     if (player->getIsTimLine()) {
//         if (dice1 == dice2) {
//             // Rolled doubles, can leave
//             std::cout << player->getName() << " rolled doubles and leaves Tim's Line!" << std::endl;
//             player->setIsTimLine(false);
//             player->setNumLineWait(0);
//         } else if (player->getNumLineWait() >= 2) {
//             // Third turn, must pay or use cup to leave
//             if (player->getOwnedCups() > 0) {
//                 std::cout << player->getName() << " uses a Tim's Cup to leave Tim's Line!" << std::endl;
//                 player->removeCup();
//             } else {
//                 std::cout << player->getName() << " pays 50 to leave Tim's Line!" << std::endl;
//                 player->removeMoney(50);
//             }
//             player->setIsTimLine(false);
//             player->setNumLineWait(0);
//         } else {
//             // Increment wait counter
//             player->setNumLineWait(player->getNumLineWait() + 1);
//             std::cout << player->getName() << " is still in Tim's Line. Turns waited: " 
//                       << player->getNumLineWait() << std::endl;
//         }
//     }
// }
