#ifndef TIMS_LINE_H
#define TIMS_LINE_H
#include <string>
#include <memory>
#include <string>
#include <cstdlib>
#include <ctime>
#include "nonbuilding.h"
#include "Player.h"
#include "Dice.h"
class Player;

class TimsLine: public nonbuilding {
    public:
        TimsLine(int ID, std::string name);
        void sendToJail(std::shared_ptr<Player> p) ;
        static void handleTimsTurn(std::shared_ptr<Player> p, std::shared_ptr<Dice> dice) ;
        int turns(std::shared_ptr<Player> p);
        bool jail(std::shared_ptr<Player> p);
        void add(std::shared_ptr<Player> p);
        ~TimsLine();
};


#endif // TIMS_LINE_H
