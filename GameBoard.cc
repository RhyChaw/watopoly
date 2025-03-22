#include "GameBoard.h"
#include "Academic.h"
#include "Residence.h"
#include "Gym.h"
#include "NeedlesHall.h"
#include "SLC.h"
#include "Tuition.h"
#include "CoopFee.h"
#include "OSAP.h"
#include "GooseNesting.h"
#include "TimsLine.h"
#include <iostream>

GameBoard::GameBoard() : totalCups(0), gameWon(false), winner(nullptr)
{
    initializeBoard();
}

GameBoard::~GameBoard()
{
    // Clean up allocated memory
    for (Cell *cell : boardCells)
    {
        delete cell;
    }
    boardCells.clear();

    // Players should be deleted by whoever created them
    // (usually the Controller)
}

// Getters
Player *GameBoard::getPlayer(int index) const
{
    return players[index];
}

Cell *GameBoard::getCell(int index) const
{
    return boardCells[index];
}

int GameBoard::getTotalCups() const
{
    return totalCups;
}

Player *GameBoard::getWinner() const
{
    return winner;
}

bool GameBoard::isWon() const
{
    return gameWon;
}

// Initialize the board
void GameBoard::initializeBoard()
{
    boardCells.clear();

    boardCells.push_back(new OSAP("Collect OSAP"));
    boardCells.push_back(new Academic("AL", 40, 50));
    boardCells.push_back(new SLC("SLC"));
    boardCells.push_back(new Academic("ML", 60, 50));
    boardCells.push_back(new Tuition("Tuition"));
    boardCells.push_back(new Residence("MKV"));
    boardCells.push_back(new Academic("ECH", 100, 50));
    boardCells.push_back(new NeedlesHall("Needles Hall"));
    boardCells.push_back(new Academic("PAS", 100, 50));
    boardCells.push_back(new Academic("HH", 120, 50));
    boardCells.push_back(new TimsLine("DC Tims Line"));
    boardCells.push_back(new Academic("RCH", 140, 100));
    boardCells.push_back(new Gym("PAC"));
    boardCells.push_back(new Academic("DWE", 140, 100));
    boardCells.push_back(new Academic("CPH", 160, 100));
    boardCells.push_back(new Residence("UWP"));
    boardCells.push_back(new Academic("LHI", 180, 100));
    boardCells.push_back(new SLC("SLC"));
    boardCells.push_back(new Academic("BMH", 180, 100));
    boardCells.push_back(new Academic("OPT", 200, 100));
    boardCells.push_back(new GooseNesting("Goose Nesting"));
    boardCells.push_back(new AcademicBuilding("EV1", 220, 150));
    boardCells.push_back(new NeedlesHall("Needles Hall"));
    boardCells.push_back(new AcademicBuilding("EV2", 220, 150));
    boardCells.push_back(new AcademicBuilding("EV3", 240, 150));
    boardCells.push_back(new Residence("V1"));
    boardCells.push_back(new AcademicBuilding("PHYS", 260, 150));
    boardCells.push_back(new AcademicBuilding("B1", 260, 150));
    boardCells.push_back(new Gym("CIF"));
    boardCells.push_back(new AcademicBuilding("B2", 280, 150));
    boardCells.push_back(new TimsLine("GO TO TIMS"));
    boardCells.push_back(new AcademicBuilding("EIT", 300, 200));
    boardCells.push_back(new AcademicBuilding("ESC", 300, 200));
    boardCells.push_back(new SLC("SLC"));
    boardCells.push_back(new AcademicBuilding("C2", 320, 200));
    boardCells.push_back(new Residence("REV"));
    boardCells.push_back(new NeedlesHall("Needles Hall"));
    boardCells.push_back(new AcademicBuilding("MC", 350, 200));
    boardCells.push_back(new CoopFee("COOP FEE"));
    boardCells.push_back(new AcademicBuilding("DC", 400, 200));

    std::cout << "Game board initialized!" << std::endl;
}

// Rolling dice and moving
void GameBoard::roll(std::shared_ptr<Player> player)
{
    int roll1 = rand() % 6 + 1;
    int roll2 = rand() % 6 + 1;
    int moveSpaces = roll1 + roll2;

    std::cout << player->getName() << " rolled " << roll1 << " and " << roll2 << ". Moving " << moveSpaces << " spaces." << std::endl;

    int newPos = (player->getIndex() + moveSpaces) % boardCells.size();
    player->setIndex(newPos);

    boardCells[newPos]->doEvent(player);
}

// End turn
void GameBoard::next()
{
    // Logic to advance turn to the next player
}

// Trade between players
void GameBoard::trade(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, std::string give, std::string receive)
{
    std::cout << p1->getName() << " offers to trade " << give << " for " << receive << " with " << p2->getName() << std::endl;
}

// Property actions
void GameBoard::improve(std::shared_ptr<Player> player, std::string property, bool buy)
{
    std::cout << player->getName() << (buy ? " buys " : " sells ") << "an improvement on " << property << std::endl;
}

void GameBoard::mortgage(std::shared_ptr<Player> player, std::string property)
{
    std::cout << player->getName() << " mortgages " << property << std::endl;
}

void GameBoard::unmortgage(std::shared_ptr<Player> player, std::string property)
{
    std::cout << player->getName() << " unmortgages " << property << std::endl;
}

// Bankruptcy
void GameBoard::bankrupt(std::shared_ptr<Player> player)
{
    std::cout << player->getName() << " has declared bankruptcy!" << std::endl;
}

// Auctions
void GameBoard::auction(std::shared_ptr<Cell> property)
{
    std::cout << "Auctioning property: " << property->getName() << std::endl;
}

// Tim Hortons Cups management
void GameBoard::addCup()
{
    if (totalCups < 4)
    {
        totalCups++;
        std::cout << "A Roll Up the Rim Cup has been added. Total: " << totalCups << std::endl;
    }
}

void GameBoard::removeCup()
{
    if (totalCups > 0)
    {
        totalCups--;
        std::cout << "A Roll Up the Rim Cup has been removed. Total: " << totalCups << std::endl;
    }
}

// Check for a winner
void GameBoard::checkWinCondition()
{
    int activePlayers = 0;
    std::shared_ptr<Player> potentialWinner = nullptr;

    for (auto &player : players)
    {
        if (!player->checkBankrupt())
        {
            activePlayers++;
            potentialWinner = player;
        }
    }

    if (activePlayers == 1)
    {
        gameWon = true;
        winner = potentialWinner;
        std::cout << winner->getName() << " has won the game!" << std::endl;
    }
}
