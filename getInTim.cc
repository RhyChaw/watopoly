#include "getInTim.h"
#include "Player.h"
#include <iostream>
using namespace std;

GetInTim::GetInTim(int ID, std::string name) : nonbuilding(ID, name) {}

GetInTim::~GetInTim() {}

void GetInTim::goToJail(std::shared_ptr<Player> p) {
    p->moveToDCTims();
}
