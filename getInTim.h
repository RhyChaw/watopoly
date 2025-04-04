#ifndef GET_IN_TIM_H
#define GET_IN_TIM_H
#include <string>
#include <memory>
#include <string>
#include <cstdlib>
#include <ctime>
#include "nonbuilding.h"
#include "Player.h"
class Player;

class GetInTim: public nonbuilding {
    public:
        GetInTim(int ID, std::string name);   
        static void goToJail(std::shared_ptr<Player> currActingPlayer);
        ~GetInTim();
};


#endif // GET_IN_TIM_H

