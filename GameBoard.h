#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "building.h"
#include "nonbuilding.h"
#include "Dice.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <vector>
#include "watopoly-display.h"
#include "propertyArray.h"

using namespace std;

class GameBoard {
private:
    std::unique_ptr<Display> board = nullptr;
    map<char, int> playerAndSqr;
    map<string, int> sqrAndImp = IMPR; 

public:
    GameBoard();
    ~GameBoard();
    void update();
    void drawBoard();
    void addPlayer(char symbol);
    void removePlayer(char symbol);
    void addImpr(std::string square);
    void removeImpr(std::string square);
    void move(char symbol, int position);
    int getPlayerPosition(char symbol) const;
    int getSquareImprovements(const std::string& square) const;
    std::shared_ptr<Display> getBoard() const;
    void loadGame(std::string filename);
    void saveGame(std::string filename);
};

#endif // GAMEBOARD_H
