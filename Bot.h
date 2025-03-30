#ifndef BOT_H
#define BOT_H

#include "Player.h"
#include <cstdlib>
#include <memory>
#include <vector>

class Bot : public Player {
public:
    // Constructor
    Bot(std::string name, char symbol, int cash) : Player(name, symbol, cash) {}
};

// Declare helper functions outside the class
bool checkSelfValid(Bot *b);
void buyBot(Bot *b);

#endif  // BOTS_H
