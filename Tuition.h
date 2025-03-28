#ifndef TUITION_H
#define TUITION_H

#include <string>
#include <memory>
#include <string>
#include <cstdlib>
#include <ctime>
#include "nonbuilding.h"
#include "Player.h"

class Tuition: public nonbuilding {
    public:
        Tuition(int ID, std::string name);
        static void pay(std::shared_ptr<Player> p);
        ~Tuition();
};

#endif // TUITION_H
