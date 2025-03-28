#include "GameBoard.h"
#include <iostream>

GameBoard::GameBoard() : display(std::make_shared<WatopolyDisplay>()) {
    initializeSquareMap();
}

GameBoard::~GameBoard() {}

void GameBoard::initializeSquareMap() {
    // Map square names to their board positions (0-39)
    squareToPosition = {
    {"COLLECT OSAP", 0}, {"AL", 1}, {"SLC", 2}, {"ML", 3}, 
    {"TUITION", 4}, {"MKV", 5}, {"ECH", 6}, {"NEEDLES HALL", 7}, 
    {"PAS", 8}, {"HH", 9}, {"DC Tims Line", 10},
    
    // Right side (top to bottom, positions 11-19)
    {"RCH", 11}, {"PAC", 12}, {"DWE", 13}, {"CPH", 14}, 
    {"UWP", 15}, {"LHI", 16}, {"SLC", 17}, {"BMH", 18}, 
    {"OPT", 19},
    
    // Bottom row (right to left, positions 20-30)
    {"Goose Nesting", 20}, {"EV1", 21}, {"NEEDLES HALL", 22}, {"EV2", 23}, 
    {"EV3", 24}, {"V1", 25}, {"PHYS", 26}, {"B1", 27}, 
    {"CIF", 28}, {"B2", 29}, {"GO TO TIMS", 30},
    
    // Left side (bottom to top, positions 31-39)
    {"EIT", 31}, {"ESC", 32}, {"SLC", 33}, {"C2", 34}, 
    {"REV", 35}, {"NEEDLES HALL", 36}, {"MC", 37}, {"COOP FEES", 38}, 
    {"DC", 39}
    };
}

void GameBoard::drawBoard() {
    display->draw();
}

void GameBoard::update() {
    // Update player positions
    for (const auto& player : playerPositions) {
        display->movePlayer(player.first, player.second);
    }

    // Update improvements
    for (const auto& imp : squareImprovements) {
        auto pos = squareToPosition.find(imp.first);
        if (pos != squareToPosition.end()) {
            display->setImprovements(pos->second, imp.second);
        }
    }
    
    display->draw();
}

void GameBoard::addPlayer(char symbol) {
    playerPositions[symbol] = 0; // Start at GO
    display->addPlayer(symbol, 0);
}

void GameBoard::removePlayer(char symbol) {
    playerPositions.erase(symbol);
    display->removePlayer(symbol);
}

void GameBoard::movePlayer(char symbol, int steps) {
    if (playerPositions.find(symbol) != playerPositions.end()) {
        playerPositions[symbol] = (playerPositions[symbol] + steps) % 40;
        display->movePlayer(symbol, playerPositions[symbol]);
    }
}

int GameBoard::getPlayerPosition(char symbol) const {
    auto it = playerPositions.find(symbol);
    return (it != playerPositions.end()) ? it->second : -1;
}

void GameBoard::addImpr(const std::string& square, int count) {
    // Validate input count
    if (count < 1) count = 1;          // Minimum 1 improvement
    else if (count > 5) count = 5;     // Maximum 5 improvements
    
    auto posIt = squareToPosition.find(square);
    if (posIt == squareToPosition.end()) {
        std::cerr << "Invalid square: " << square << std::endl;
        return;
    }

    int position = posIt->second;
    int current = squareImprovements[square];
    
    // Calculate new count with bounds
    int newCount = current + count;
    if (newCount > 5) newCount = 5;
    
    int actualAdded = newCount - current;
    
    if (actualAdded > 0) {
        squareImprovements[square] = newCount;
        display->setImprovements(position, newCount);
        std::cout << "Added " << actualAdded << " improvement(s) to " << square
                  << " (Total: " << newCount << ")" << std::endl;
    } else {
        std::cout << square << " already has maximum improvements (5)" << std::endl;
    }
}

void GameBoard::removeImpr(const std::string& square) {
    if (squareImprovements.find(square) != squareImprovements.end() && 
        squareImprovements[square] > 0) {
        squareImprovements[square]--;
        update();
    }
}

int GameBoard::getSquareImprovements(const std::string& square) const {
    auto it = squareImprovements.find(square);
    return (it != squareImprovements.end()) ? it->second : 0;
}


std::shared_ptr<WatopolyDisplay> GameBoard::getDisplay() const {
    return display;
}

// addimptr removeimprovemnt drawboard moveplayer addplayer removeplayer 