#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <string>
#include "GameBoard.h"
#include "load.h"
#include "Player.h"
#include <memory>


class Controller {
private:
    std::shared_ptr<GameBoard> gameBoard;
    // Display display;
    int currentPlayerIndex;
    GameState loadedState;

    void initializeFromLoadedState();

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
