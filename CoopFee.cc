#include "CoopFee.h"
#include "Player.h"
#include <iostream>

CoopFee::CoopFee(int ID, std::string name) : nonbuilding(ID, name) {
}

CoopFee::~CoopFee() {}

void CoopFee::pay(std::shared_ptr<Player> p) {
    std::cout << p->getName() << " Has landed on Co-op Fee and must pay $" << "150!" << std::endl;
    p->changeCash(-150);
}
