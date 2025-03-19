#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include "GameBoard.h"
#include "Display.h"

class Controller {
private:
    std::shared_ptr<GameBoard> gameBoard;
    Display display;
    int currentPlayerIndex;

public:
    Controller();

    // Game control
    bool loadGame(const std::string &filename);
    void play();
    void saveGame(const std::string &filename);
    void displayAssets();
    void displayAll();
};

#endif // CONTROLLER_H
