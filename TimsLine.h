#ifndef TIMS_LINE_H
#define TIMS_LINE_H
#include <string>
#include <memory>
#include <string>
#include <cstdlib>
#include <ctime>
#include "nonbuilding.h"
#include "Player.h"
class Player;

class TimsLine: public nonbuilding {
    public:
        TimsLine(int ID, std::string name);   
        int turns(std::shared_ptr<Player> p);
        bool jail(std::shared_ptr<Player> p);
        void add(std::shared_ptr<Player> p);
        ~TimsLine();
};


#endif // TIMS_LINE_H
