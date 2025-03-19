#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>
#include <memory>
#include "Player.h"
#include "Cell.h"

class Display {
public:
    void printGameBoard(const std::vector<std::shared_ptr<Cell>> &board, const std::vector<std::shared_ptr<Player>> &players);
};

#endif // DISPLAY_H
