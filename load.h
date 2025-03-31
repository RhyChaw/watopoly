#ifndef LOAD_H
#define LOAD_H

#include <string>
#include <vector>
#include <fstream>
#include "Player.h"
#include "GameBoard.h"

class Load {
public:
    
private:
    static void loadGame (std::vector<std::shared_ptr<Player>> group, std::shared_ptr<Player> currActingPlayer, bool testMode, std::shared_ptr<GameBoard> b);
    static void saveGame (std::vector<std::shared_ptr<Player>> group, std::shared_ptr<Player> currActingPlayer, bool testMode, std::shared_ptr<GameBoard> b);
};

#endif // LOAD_H
