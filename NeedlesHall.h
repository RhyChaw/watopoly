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
        static int getRandomMovement(int n);
        static void moveeee(std::shared_ptr<Player> p);
        ~NeedlesHall();
};

#endif // NEEDLES_HALL_H
