#ifndef BOTS_H
#define BOTS_H

#include "Player.h"
#include <cstdlib>
#include <memory>
#include <vector>

// Smart Bot class
class BotSmart : public Player {
public:
    BotSmart(std::string name, char symbol, int cash) : Player(name, symbol, cash) {}
};

// Declare free functions
bool checkSelfValidS(BotSmart *b);
void buyBotS(BotSmart *b);
void botSController(BotSmart *b, int roll);

#endif  // BOTS_H
