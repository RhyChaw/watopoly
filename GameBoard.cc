#include "GameBoard.h"
#include <set>
#include <iostream>

GameBoard::GameBoard() : display(std::make_shared<WatopolyDisplay>()) {
    initializeSquareMap();
}

void GameBoard::setBoardColor(const std::string &mode) {
    if (mode == "dark" || mode == "light") {
        display->setColorMode(mode);
        drawBoard();
    }
}

GameBoard::~GameBoard() {}

void GameBoard::printBoardToTerminal() {
    const std::set<int> improvementPositions = {
        1,3,6,8,9,11,13,14,16,18,19,21,23,24,26,27,29,31,32,34,37,39
    };
    std::vector<std::string> terminalBoard = {
    "_________________________________________________________________________________________",
    "|Goose  |       |NEEDLES|       |       |V1     |       |       |CIF    |       |GO TO  |",
    "|Nesting|-------|HALL   |-------|-------|       |-------|-------|       |-------|TIMS   |",
    "|       |EV1    |       |EV2    |EV3    |       |PHYS   |B1     |       |B2     |       |",
    "|       |       |       |       |       |       |       |       |       |       |       |",
    "|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|",
    "|       |                                                                       |       |",
    "|-------|                                                                       |-------|",
    "|OPT    |                                                                       |EIT    |",
    "|       |                                                                       |       |",
    "|_______|                                                                       |_______|",
    "|       |                                                                       |       |",
    "|-------|                                                                       |-------|",
    "|BMH    |                                                                       |ESC    |",
    "|       |                                                                       |       |",
    "|_______|                                                                       |_______|",
    "|SLC    |                                                                       |SLC    |",
    "|       |                                                                       |       |",
    "|       |                                                                       |       |",
    "|       |                                                                       |       |",
    "|_______|                                                                       |_______|",
    "|       |                                                                       |       |",
    "|-------|                                                                       |-------|",
    "|LHI    |                                                                       |C2     |",
    "|       |             _____________________________________________             |       |",
    "|_______|            |                                             |            |_______|",
    "|UWP    |            | #   #  ##  #####  ###  ###   ###  #   #   # |            |REV    |",
    "|       |            | #   # #  #   #   #   # #  # #   # #   #   # |            |       |",
    "|       |            | # # # ####   #   #   # ###  #   # #    # #  |            |       |",
    "|       |            | # # # #  #   #   #   # #    #   # #     #   |            |       |",
    "|_______|            | ##### #  #   #    ###  #     ###  ## #  #   |            |_______|",
    "|       |            |_____________________________________________|            |NEEDLES|",
    "|-------|                                                                       |HALL   |",
    "|CPH    |                                                                       |       |",
    "|       |                                                                       |       |",
    "|_______|                                                                       |_______|",
    "|       |                                                                       |       |",
    "|-------|                                                                       |-------|",
    "|DWE    |                                                                       |MC     |",
    "|       |                                                                       |       |",
    "|_______|                                                                       |_______|",
    "|PAC    |                                                                       |COOP   |",
    "|       |                                                                       |FEE    |",
    "|       |                                                                       |       |",
    "|_______|                                                                       |_______|",
    "|       |                                                                       |       |",
    "|-------|                                                                       |-------|",
    "|RCH    |                                                                       |DC     |",
    "|       |                                                                       |       |",
    "|_______|_______________________________________________________________________|_______|",
    "|DC Tims|       |       |NEEDLES|       |MKV    |TUITION|       |SLC    |       |COLLECT|",
    "|Line   |-------|-------|HALL   |-------|       |       |-------|       |-------|OSAP   |",
    "|       |HH     |PAS    |       |ECH    |       |       |ML     |       |AL     |       |",
    "|       |       |       |       |       |       |       |       |       |       |       |",
    "|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|"
    };

    std::map<int, std::pair<int, int>> posToTerminal = {
    // Top row (left to right, positions 0-10)
    {0, {53, 81}},  // COLLECT OSAP (bottom right)
    {1, {53, 73}},  // AL
    {2, {53, 65}},  // SLC
    {3, {53, 57}},  // ML
    {4, {53, 49}},  // TUITION
    {5, {53, 41}},  // MKV
    {6, {53, 33}},  // ECH
    {7, {53, 25}},  // NEEDLES HALL
    {8, {53, 17}},  // PAS
    {9, {53, 9}},   // HH
    {10, {53, 1}},  // DC Tims Line (bottom left)
    
    // Right side (bottom to top, positions 11-19)
    {11, {48, 1}},  // RCH
    {12, {43, 1}},  // PAC
    {13, {39, 1}},  // DWE
    {14, {34, 1}},  // CPH
    {15, {29, 1}},  // UWP
    {16, {24, 1}},  // LHI
    {17, {19, 1}},  // SLC
    {18, {14, 1}},  // BMH
    {19, {9, 1}},   // OPT
    
    // Bottom row (right to left, positions 20-30)
    {20, {3, 1}},  // Goose Nesting (top left)
    {21, {3, 9}}, // EV1
    {22, {3, 17}}, // NEEDLES HALL
    {23, {3, 25}}, // EV2
    {24, {3, 33}}, // EV3
    {25, {3, 41}}, // V1
    {26, {3, 49}}, // PHYS
    {27, {3, 57}}, // B1
    {28, {3, 65}}, // CIF
    {29, {3, 73}}, // B2
    {30, {3, 81}}, // GO TO TIMS (top right)
    
    // Left side (top to bottom, positions 31-39)
    {31, {9, 81}}, // EIT
    {32, {14, 81}}, // ESC
    {33, {19, 81}}, // SLC
    {34, {24, 81}}, // C2
    {35, {29, 81}}, // REV
    {36, {34, 81}}, // NEEDLES HALL
    {37, {39, 81}}, // MC
    {38, {43, 81}}, // COOP FEES
    {39, {49, 81}}  // DC
};

    std::map<int, int> positionCounts;

    for (const auto& player : playerPositions) {
        int pos = player.second;
        if (posToTerminal.find(pos) == posToTerminal.end()) continue;

        auto [line, col] = posToTerminal[pos];
        int offset = positionCounts[pos]++ * 1;
        
        if (col + offset < terminalBoard[line].length()) {
            terminalBoard[line][col + offset] = player.first;
        }
    }
    for (const auto& imp : squareImprovements) {
        auto posIt = squareToPosition.find(imp.first);
        if (posIt == squareToPosition.end()) continue;
        
        int pos = posIt->second;
        if (improvementPositions.find(pos) == improvementPositions.end()) continue;
        if (imp.second == 0) continue;

        auto [line, col] = posToTerminal[pos];
        line -= 3;

        // Draw improvements (max 5)
        int improvementsToShow = std::min(imp.second, 5);
        for (int i = 0; i < improvementsToShow; i++) {
            int impCol = col + i;
            if (line >= 0 && line < terminalBoard.size() && 
                impCol >= 0 && impCol < terminalBoard[line].length()) {
                char impChar = (i == 4) ? 'C' : 'B';
                terminalBoard[line][impCol] = impChar;
            }
        }
    }

    for (const auto& line : terminalBoard) {
        std::cout << line << "\n";
    }
}


void GameBoard::initializeSquareMap() {
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

void printBoard() { 
    printBoardToTerminal(); 
}

void GameBoard::drawBoard() {
    display->draw();
}

void GameBoard::update() {
    for (const auto& player : playerPositions) {
        display->movePlayer(player.first, player.second);
    }

    for (const auto& imp : squareImprovements) {
        auto pos = squareToPosition.find(imp.first);
        if (pos != squareToPosition.end()) {
            display->setImprovements(pos->second, imp.second);
        }
    }
    
    display->draw();
}


void GameBoard::addPlayer(char symbol) {
    playerPositions[symbol] = 0;
    totalSteps[symbol] = 0;
    display->addPlayer(symbol, 0);
}
void GameBoard::removePlayer(char symbol) {
    playerPositions.erase(symbol);
    display->removePlayer(symbol);
}

int GameBoard::getTotalSteps(char symbol) const {
    auto it = totalSteps.find(symbol);
    return (it != totalSteps.end()) ? it->second : -1;
}

void GameBoard::movePlayer(char symbol, int absolutePosition) {
    if (playerPositions.find(symbol) != playerPositions.end()) {
        playerPositions[symbol] = absolutePosition % 40;
        display->movePlayer(symbol, absolutePosition % 40);
    }
}

int GameBoard::getPlayerPosition(char symbol) const {
    auto it = playerPositions.find(symbol);
    return (it != playerPositions.end()) ? it->second : -1;
}

void GameBoard::addImpr(const std::string& square, int count) {
    if (count==0){
        return;
    }
    if (count < 1) count = 1;          // Min 1 imprv
    else if (count > 5) count = 5;     // Max 5 imprv
    
    auto posIt = squareToPosition.find(square);
    if (posIt == squareToPosition.end()) {
        std::cerr << "Invalid square: " << square << std::endl;
        return;
    }

    int position = posIt->second;
    int current = squareImprovements[square];
    
    int newCount = current + count;
    if (newCount > 5) newCount = 5;
    
    int actualAdded = newCount - current;
    
    if (actualAdded > 0) {
        squareImprovements[square] = newCount;
        display->setImprovements(position, newCount);
        std::cout << "Added " << actualAdded << " improvement(s) to " << square
                  << " (Total: " << newCount << ")." << std::endl;
    } else {
        std::cout << square << " already has maximum improvements(5)." << std::endl;
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
