// GameBoard.h
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include <string>
#include "Cell.h"
#include "Player.h"
#include "propertyArray.h"

class GameBoard {
private:
    std::vector<std::vector<std::string>> boardCells;
    std::vector<Player*> players;
    int totalCups;
    bool gameWon;
    Player* winner;
    
    void initializeBoard();

public:
    GameBoard();
    ~GameBoard();

    // Getters
    Player* getPlayer(int index) const;//done
    Cell* getCell(int index) const;//done
    int getTotalCups() const;//done
    Player* getWinner() const;//done
    bool isWon() const;//done

    // Game actions
    void roll(Player* player);//done
    void improve(Player* player, const std::string& property, bool buy);
    void mortgage(Player* player, const std::string& property);//done
    void unmortgage(Player* player, const std::string& property);//done
    void bankrupt(Player* player);
    void auction(Cell* property);

    // drawBoard
    // addPlayer
    // removePlayer
    // addImprovements
    // removeImprovements
    // movePlayer
    // update
};

#endif // GAMEBOARD_H
