#ifndef BOT_H
#define BOT_H

#include "Player.h"
#include <cstdlib>

class Bot : public Player {
public:
    // ctor
    Bot(std::string name, char symbol, int cash) : Player(name, symbol, cash) {}

    // void functions
    void botController(Bot *b);
    void checkSelfValid(Bot *b);
    void buyBot(Bot *b, std::shared_ptr<Building> property_name);
};

#endif
 
// here prob of auction higher