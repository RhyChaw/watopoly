#include "Controller.h"
#include <iostream>
#include <fstream>

Controller::Controller() : gameBoard(std::make_shared<GameBoard>()), currentPlayerIndex(0) {}

// Load game from file
bool Controller::loadGame(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
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
            gameBoard->next();
            currentPlayerIndex = (currentPlayerIndex + 1) % gameBoard->getPlayers().size();
        } else if (command == "trade") {
            std::string p2Name, give, receive;
            std::cin >> p2Name >> give >> receive;
            Player* p2 = nullptr;
            for (auto* player : gameBoard->getPlayers()) {
                if (player->getName() == p2Name) {
                    p2 = player;
                    break;
                }
            }
            if (p2) {
                gameBoard->trade(currentPlayer, p2, give, receive);
            } else {
                std::cout << "Invalid trade partner!" << std::endl;
            }
        } else if (command == "improve") {
            std::string property;
            std::string action;
            std::cin >> property >> action;
            gameBoard->improve(currentPlayer, property, action == "buy");
        } else if (command == "mortgage") {
            std::string property;
            std::cin >> property;
            gameBoard->mortgage(currentPlayer, property);
        } else if (command == "unmortgage") {
            std::string property;
            std::cin >> property;
            gameBoard->unmortgage(currentPlayer, property);
        } else if (command == "bankrupt") {
            gameBoard->bankrupt(currentPlayer);
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
        display.showBoard(*gameBoard);

        gameBoard->checkWinCondition();
    }

    std::cout << "Game Over! The winner is " << gameBoard->getWinner()->getName() << "!" << std::endl;
}

// Save game to file
void Controller::saveGame(const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to save game." << std::endl;
        return;
    }
    // TODO: Implement saving logic
    file.close();
}

// Display player assets
void Controller::displayAssets() {
    auto player = gameBoard->getPlayer(currentPlayerIndex);
    display.showPlayerAssets(player);
}

// Display all player assets
void Controller::displayAll() {
    display.showAllPlayers(gameBoard->getPlayers());
}
