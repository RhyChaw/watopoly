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
        int getRandomMovement(int n);
        void moveeee(std::shared_ptr<Player> p);
        ~SLC();
};
#endif // SLC_H
