#include "GooseNesting.h"
#include "Player.h"
#include <iostream>

GooseNesting::GooseNesting(int ID, std::string name) : nonbuilding(ID, name) {}

GooseNesting::~GooseNesting() {
}

void GooseNesting::nesting(std::shared_ptr<Player> p) {
    cout << "You are currently on " << p->getPosition() << "." << endl;
    cout << p->getName() << " has landed on Goose Nesting and is taking a break.." << endl;

    cout << R"(
                 __
               <(o )___
                (  ._> /
                 `---'
          HONK! You have encountered a very territorial goose!
    It hisses at you aggressively while blocking your path...
    )" << endl;
}

