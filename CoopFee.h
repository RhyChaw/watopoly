#ifndef COOP_FEE_H
#define COOP_FEE_H

#include <string>
#include <memory>
#include <string>
#include <cstdlib>
#include <ctime>
#include "nonbuilding.h"
#include "Player.h"

class CoopFee: public nonbuilding {
    public:
        CoopFee(int ID, std::string name);
        void pay(std::shared_ptr<Player> p);
        ~CoopFee();
};

#endif // COOP_FEE_H
