#ifndef NEEDLES_HALL_H
#define NEEDLES_HALL_H

#include <string>
#include <memory>
#include <string>
#include <cstdlib>
#include <ctime>
#include "nonbuilding.h"
#include "Player.h"
class Player;

class NeedlesHall: public nonbuilding {
    public:
        NeedlesHall(int ID, std::string name);
        int getRandomMovement(int n);
        void moveeee(std::shared_ptr<Player> p);
        ~NeedlesHall();
};

#endif // NEEDLES_HALL_H
