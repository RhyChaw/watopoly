#ifndef BOT_H
#define BOT_H

#include "Player.h"
#include <cstdlib>

// this is the smart bot

class BotS : public Player {
public:
    // ctor
    BotS(std::string name, char symbol, int cash) : Player(name, symbol, cash) {}

    // void functions
    void botSController(BotS *b);
    void checkSelfValid(BotS *b);
    void buyBotS(BotS *b, std::shared_ptr<Building> property_name);
};

#endif
 
// here prob of buy higher
