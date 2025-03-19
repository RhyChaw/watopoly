#include "Controller.h"
#include <iostream>
#include <fstream>

Controller::Controller() : gameBoard(std::make_shared<GameBoard>()), currentPlayerIndex(0) {}

// Load game from file (not implemented yet)
bool Controller::loadGame(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    // TODO: Implement file loading logic
    file.close();
    return true;
}

// Main game loop
void Controller::play() {
    std::cout << "Starting the game..." << std::endl;

    while (!gameBoard->isWon()) {
        auto currentPlayer = gameBoard->getPlayer(currentPlayerIndex);
        std::cout << "It's " << currentPlayer->getName() << "'s turn!" << std::endl;

        std::string command;
        std::cin >> command;

        if (command == "roll") {
            gameBoard->roll(currentPlayer);
        } else if (command == "next") {
            currentPlayerIndex = (currentPlayerIndex + 1) % 6;
        } else if (command == "assets") {
            displayAssets();
        } else if (command == "all") {
            displayAll();
        } else if (command == "save") {
            std::string filename;
            std::cin >> filename;
            saveGame(filename);
        } else {
            std::cout << "Unknown command!" << std::endl;
        }

        // Print the board after every turn
        display.printGameBoard(gameBoard->getBoardCells(), gameBoard->getPlayers());

        gameBoard->checkWinCondition();
    }

    std::cout << "Game Over! The winner is " << gameBoard->getWinner()->getName() << "!" << std::endl;
}

// Save game to file (not implemented yet)
void Controller::saveGame(const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error saving game." << std::endl;
        return;
    }
    // TODO: Implement saving logic
    file.close();
}

// Display player assets
void Controller::displayAssets() {
    auto player = gameBoard->getPlayer(currentPlayerIndex);
    std::cout << player->getName() << " has $" << player->getCash() << " and owns: ";
    
    for (auto &property : player->getProperties()) {
        std::cout << property->getName() << " ";
    }
    std::cout << std::endl;
}

// Display all player assets
void Controller::displayAll() {
    std::cout << "Displaying assets for all players..." << std::endl;
    for (int i = 0; i < 6; i++) {
        displayAssets();
    }
}
