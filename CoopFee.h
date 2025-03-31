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
        ~CoopFee();

        static void pay(std::shared_ptr<Player> p);
};

#endif // COOP_FEE_H
