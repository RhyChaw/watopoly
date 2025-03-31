#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "watopoly_display.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

class GameBoard {
    std::shared_ptr<WatopolyDisplay> display;
    std::map<char, int> playerPositions;
    std::map<std::string, int> squareImprovements;
    std::map<std::string, int> squareToPosition;
    std::map<char, int> totalSteps;

    void initializeSquareMap();

public:
    GameBoard();
    ~GameBoard();

    void printBoardToTerminal();
    void printBoard() { printBoardToTerminal(); }
    void drawBoard();
    void update();
    void setBoardColor(const std::string &mode); // "dark" or "light"
    
    void addPlayer(char symbol);
    void removePlayer(char symbol);
    void movePlayer(char symbol, int absolutePosition);
    int getPlayerPosition(char symbol) const;
    
    void addImpr(const std::string& square, int count = 1);
    void removeImpr(const std::string& square);
    int getSquareImprovements(const std::string& square) const;
    int getTotalSteps(char symbol) const;

    std::shared_ptr<WatopolyDisplay> getDisplay() const;
};

#endif
