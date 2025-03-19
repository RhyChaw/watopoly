#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include <memory>
#include "Player.h"
#include "Cell.h"

class GameBoard {
private:
    std::vector<std::shared_ptr<Player>> players;
    std::vector<std::shared_ptr<Cell>> boardCells;
    int totalCups;
    bool gameWon;
    std::shared_ptr<Player> winner;

public:
    GameBoard();

    // Player management
    std::shared_ptr<Player> getPlayer(int index) const;
    std::shared_ptr<Cell> getCell(int index) const;
    int getTotalCups() const;
    std::shared_ptr<Player> getWinner() const;
    bool isWon() const;

    // Game actions
    void trade(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, std::string give, std::string receive);
    void roll(std::shared_ptr<Player> player);
    void next();
    void improve(std::shared_ptr<Player> player, std::string property, bool buy);
    void mortgage(std::shared_ptr<Player> player, std::string property);
    void unmortgage(std::shared_ptr<Player> player, std::string property);
    void bankrupt(std::shared_ptr<Player> player);
    void auction(std::shared_ptr<Cell> property);

    // Tim Hortons Cups management
    void addCup();
    void removeCup();

    // Game setup and reset
    void initializeBoard();
    void checkWinCondition();
};

#endif // GAMEBOARD_H
