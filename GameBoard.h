#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "watopoly-display.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

class GameBoard {
    std::shared_ptr<WatopolyDisplay> display;
    std::map<char, int> playerPositions;  // symbol to board position (0-39)
    std::map<std::string, int> squareImprovements; // square name to improvement count
    std::map<std::string, int> squareToPosition; // maps square names to board positions

    void initializeSquareMap();

public:
    GameBoard();
    ~GameBoard();

    // Display control
    void drawBoard();
    void update();

    // Player management
    void addPlayer(char symbol);
    void removePlayer(char symbol);
    void movePlayer(char symbol, int steps);
    int getPlayerPosition(char symbol) const;

    // Improvement management
    void addImpr(const std::string& square, int count = 1);
    void removeImpr(const std::string& square);
    int getSquareImprovements(const std::string& square) const;

    // Game state
    void loadGame(const std::string& filename);
    void saveGame(const std::string& filename) const;

    std::shared_ptr<WatopolyDisplay> getDisplay() const;
};

#endif // GAMEBOARD_H