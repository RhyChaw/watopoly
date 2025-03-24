#ifndef DISPLAY_H
#define DISPLAY_H

#include "GameBoard.h"
#include "Player.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <vector>

class Display {
public:
    Display();
    
    // Displays the current game board
    void showBoard(const GameBoard& gameBoard) const;
    
    // Displays assets of a specific player
    void showPlayerAssets(const Player* player) const;
    
    // Displays assets of all players
    void showAllPlayers(const std::vector<Player*>& players) const;
    
    // Displays a message to the console (general purpose output)
    void showMessage(const std::string& message) const;
};

#endif // DISPLAY_H
