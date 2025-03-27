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
}

void GameBoard::saveGame(std::string filename) {
    cout << "Saving game to: " << filename << endl;
    // TODO: Implement file writing logic
}
