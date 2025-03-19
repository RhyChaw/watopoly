#include "Display.h"
#include <iostream>

void Display::printGameBoard(const std::vector<std::shared_ptr<Cell>> &board, const std::vector<std::shared_ptr<Player>> &players) {
    std::cout << "====================== Watopoly Board ======================" << std::endl;
    
    for (size_t i = 0; i < board.size(); i++) {
        std::cout << "[" << board[i]->getName() << "] ";
        for (auto &player : players) {
            if (player->getIndex() == static_cast<int>(i)) {
                std::cout << "(" << player->getSymbol() << ") ";
            }
        }
        std::cout << std::endl;
    }

    std::cout << "===========================================================" << std::endl;
}
