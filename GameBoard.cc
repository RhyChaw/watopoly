#include "GameBoard.h"
using namespace std;

GameBoard::GameBoard() {}

GameBoard::~GameBoard() {}

void GameBoard::drawBoard() {
    board->draw();
}

void GameBoard::update() {
    for (auto &p : sqrAndImp) {
        if (p.second > 0) {
            board->addImpr(p.first, p.second);
        }
    }

    for (auto &p : playerAndSqr) {
        string sqr = BOARD[p.second % 40]; // Ensure board wrapping
        board->addPlayer(p.first, sqr);
    }
}

void GameBoard::addPlayer(char symbol) {
    playerAndSqr[symbol] = 0;
}

void GameBoard::removePlayer(char symbol) {
    playerAndSqr.erase(symbol);
}

void GameBoard::addImpr(std::string square) {
    if (sqrAndImp.find(square) != sqrAndImp.end()) {
        sqrAndImp[square]++;
    }
}

void GameBoard::removeImpr(std::string square) {
    if (sqrAndImp.find(square) != sqrAndImp.end() && sqrAndImp[square] > 0) {
        sqrAndImp[square]--;
    }
}

void GameBoard::move(char symbol, int position) {
    if (playerAndSqr.find(symbol) != playerAndSqr.end()) {
        playerAndSqr[symbol] = (playerAndSqr[symbol] + position) % 40; // Wrap board positions
    }
}

int GameBoard::getPlayerPosition(char symbol) const {
    auto it = playerAndSqr.find(symbol);
    return (it != playerAndSqr.end()) ? it->second : -1; // Return -1 if player not found
}

int GameBoard::getSquareImprovements(const std::string& square) const {
    auto it = sqrAndImp.find(square);
    return (it != sqrAndImp.end()) ? it->second : 0; // Return 0 if square not found
}

std::shared_ptr<Display> GameBoard::getBoard() const {
    return board;
}

void GameBoard::loadGame(std::string filename) {
    cout << "Loading game from: " << filename << endl;
    // TODO: Implement file reading logic

    // Load the game state using the Load class
    GameState state = Load::loadGame(filename);
    
    // Clear current game state (if needed)
    playerAndSqr.clear();
    sqrAndImp.clear();
    
    // Load players into the game board
    for (const auto& player : state.players) {
        addPlayer(player.playerChar);
        move(player.playerChar, player.position);
        // Add player-related data (e.g., timsCups, etc.)
        // Store player's information in the appropriate map or class variable if needed
    }

    // Load building information into the game board
    for (const auto& building : state.buildings) {
        // Set building ownership and improvements
        addImpr(building.name);
        // Store building owner and improvements (can be stored in sqrAndImp map)
        sqrAndImp[building.name] = building.improvements;
        // Handle ownership (BANK or player names)
    }
    
    cout << "Game loaded successfully." << endl;

}

void GameBoard::saveGame(std::string filename) {
    cout << "Saving game to: " << filename << endl;
    // TODO: Implement file writing logic

    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file to save game: " + filename);
    }

    // Write number of players
    file << playerAndSqr.size() << std::endl;

    // Write each player's data
    for (const auto& entry : playerAndSqr) {
        char playerChar = entry.first;
        int position = entry.second;
        // You can access additional player data like timsCups, etc., from your map or member variable
        int timsCups = 0;  // Replace with actual value
        int money = 0;     // Replace with actual value

        // Example: Write each player information line (modify as needed based on actual player data)
        file << "player " << playerChar << " " << timsCups << " " << money << " " << position << std::endl;
    }

    // Write building data (ownership and improvements)
    for (const auto& square : sqrAndImp) {
        std::string buildingName = square.first;
        int improvements = square.second;
        
        // Example: Write each building's ownership (modify as needed)
        std::string owner = "BANK";  // Replace with actual owner name
        file << buildingName << " " << owner << " " << improvements << std::endl;
    }
    
    cout << "Game saved successfully." << endl;
}
