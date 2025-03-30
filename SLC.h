#ifndef SLC_H
#define SLC_H

#include <string>
#include <memory>
#include <string>
#include <cstdlib>
#include <ctime>
#include "nonbuilding.h"
#include "Player.h"
class Player;

class SLC: public nonbuilding {
    public:
        SLC(int ID, std::string name);
        static int getRandomMovement(int n);
        static void moveeee(std::shared_ptr<Player> p, std::vector<std::shared_ptr<Player>> group);
        ~SLC();
};
#endif // SLC_H
