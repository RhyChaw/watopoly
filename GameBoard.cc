#include "GameBoard.h"
#include "AcademicBuilding.h"
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
using namespace std;

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

    // AcademicBuildings
    boardCells.push_back(new AcademicBuilding("AL", 40, 50, "Arts1", {2, 10, 30, 90, 160, 250}));
    boardCells.push_back(new AcademicBuilding("ML", 60, 50, "Arts1", {4, 20, 60, 180, 320, 450}));
    boardCells.push_back(new AcademicBuilding("ECH", 100, 50, "Arts2", {6, 30, 90, 270, 400, 550}));
    boardCells.push_back(new AcademicBuilding("PAS", 100, 50, "Arts2", {6, 30, 90, 270, 400, 550}));
    boardCells.push_back(new AcademicBuilding("HH", 120, 50, "Arts2", {8, 40, 100, 300, 450, 600}));
    boardCells.push_back(new AcademicBuilding("RCH", 140, 100, "Eng", {10, 50, 150, 450, 625, 750}));
    boardCells.push_back(new AcademicBuilding("DWE", 140, 100, "Eng", {10, 50, 150, 450, 625, 750}));
    boardCells.push_back(new AcademicBuilding("CPH", 160, 100, "Eng", {12, 60, 180, 500, 700, 900}));
    boardCells.push_back(new AcademicBuilding("LHI", 180, 100, "Health", {14, 70, 200, 550, 750, 950}));
    boardCells.push_back(new AcademicBuilding("BMH", 180, 100, "Health", {14, 70, 200, 550, 750, 950}));
    boardCells.push_back(new AcademicBuilding("OPT", 200, 100, "Health", {16, 80, 220, 600, 800, 1000}));
    boardCells.push_back(new AcademicBuilding("EV1", 220, 150, "Env", {18, 90, 250, 700, 875, 1050}));
    boardCells.push_back(new AcademicBuilding("EV2", 220, 150, "Env", {18, 90, 250, 700, 875, 1050}));
    boardCells.push_back(new AcademicBuilding("EV3", 240, 150, "Env", {20, 100, 300, 750, 925, 1100}));
    boardCells.push_back(new AcademicBuilding("PHYS", 260, 150, "Sci1", {22, 110, 330, 800, 975, 1150}));
    boardCells.push_back(new AcademicBuilding("B1", 260, 150, "Sci1", {22, 110, 330, 800, 975, 1150}));
    boardCells.push_back(new AcademicBuilding("B2", 280, 150, "Sci1", {24, 120, 360, 850, 1025, 1200}));
    boardCells.push_back(new AcademicBuilding("EIT", 300, 200, "Sci2", {26, 130, 390, 900, 1100, 1275}));
    boardCells.push_back(new AcademicBuilding("ESC", 300, 200, "Sci2", {26, 130, 390, 900, 1100, 1275}));
    boardCells.push_back(new AcademicBuilding("C2", 320, 200, "Sci2", {28, 150, 450, 1000, 1200, 1400}));
    boardCells.push_back(new AcademicBuilding("MC", 350, 200, "Math", {35, 175, 500, 1100, 1300, 1500}));
    boardCells.push_back(new AcademicBuilding("DC", 400, 200, "Math", {50, 200, 600, 1400, 1700, 2000}));

    std::cout << "Game board initialized!" << std::endl;
}

// Rolling dice and moving
void GameBoard::roll(Player* player)
{
    if (player->isBankrupt()) {
        std::cout << player->getName() << " is bankrupt and cannot roll." << std::endl;
        return;
    }

    if (player->getisInTimsLine()) {
        int turnsInTims = player->getTurnsInTimsLine();
        std::cout << player->getName() << " is in DC Tims Line for " << turnsInTims << " turn(s)." << std::endl;

        int roll1 = rand() % 6 + 1;
        int roll2 = rand() % 6 + 1;

        if (roll1 == roll2) {  // Rolled doubles -> Free to leave
            std::cout << player->getName() << " rolled doubles (" << roll1 << " and " << roll2 << ") and is leaving DC Tims Line!" << std::endl;
            player->leaveTimsLine();
        } 
        else if (turnsInTims == 2) {  // Third turn -> Must leave
            if (player->getOwnedCups() > 0) {
                std::cout << player->getName() << " used a Roll Up the Rim cup to leave DC Tims Line." << std::endl;
                player->removeCup();
            } 
            else {
                std::cout << player->getName() << " must pay $50 to leave DC Tims Line." << std::endl;
                player->pay(50);
            }
            player->leaveTimsLine();
        } 
        else {  // Player must wait for another turn
            std::cout << player->getName() << " did not roll doubles and stays in DC Tims Line." << std::endl;
            player->setTurnsInTimsLine(turnsInTims + 1);
            return;
        }

        // Move after leaving Tims Line
        int moveSpaces = roll1 + roll2;
        std::cout << player->getName() << " moves " << moveSpaces << " spaces." << std::endl;
        int newPos = (player->getIndex() + moveSpaces) % boardCells.size();
        player->setIndex(newPos);
        boardCells[newPos]->doEvent(player);
        return;
    }

    // Normal rolling process if not in DC Tims Line
    int roll1 = rand() % 6 + 1;
    int roll2 = rand() % 6 + 1;
    int moveSpaces = roll1 + roll2;

    std::cout << player->getName() << " rolled " << roll1 << " and " << roll2 << ". Moving " << moveSpaces << " spaces." << std::endl;

    int newPos = (player->getIndex() + moveSpaces) % boardCells.size();
    player->setIndex(newPos);

    boardCells[newPos]->doEvent(player);
}

Building* GameBoard::findBuildingByName(const string &name) {
    for (Building* building : buildings) {
        if (building->getName() == name) {
            return building;
        }
    }
    return nullptr; // Not found
}

// End turn
void GameBoard::next()
{
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    
    while (players[currentPlayerIndex]->isBankrupt()) {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }

    std::cout << "It is now " << players[currentPlayerIndex]->getName() << "'s turn." << std::endl;
}

// Trade between players
void GameBoard::trade(Player *currentPlayer, string partnerName, string give, string receive) {
    Player *partner = nullptr;

    // Find the player being traded with
    for (auto *player : players) {
        if (player->getName() == partnerName) {
            partner = player;
            break;
        }
    }

    // Check if partner exists
    if (!partner) {
        cout << "Error: No player named " << partnerName << " found.\n";
        return;
    }

    // Check if the current player is trying to trade with themselves
    if (currentPlayer == partner) {
        cout << "Error: You cannot trade with yourself!\n";
        return;
    }

    // Determine if `give` and `receive` are money or property
    Building *b1 = findBuildingByName(give);
    Building *b2 = findBuildingByName(receive);
    double money1 = 0, money2 = 0;

    // Check if 'give' is money (a number)
    bool isMoney1 = true;
    for (char c : give) {
        if (!(c >= '0' && c <= '9') && c != '.') {
            isMoney1 = false;
            break;
        }
    }
    if (isMoney1) {
        money1 = 0;
        for (char c : give) {
            if (c >= '0' && c <= '9') {
                money1 = money1 * 10 + (c - '0');  // Constructing the money value manually
            } else if (c == '.') {
                break; // Stop at decimal point, assuming no more complex money values for now
            }
        }
        b1 = nullptr; // It's money, not a building
    } else {
        b1 = findBuildingByName(give); // It's a building
    }

    // Check if 'receive' is money (a number)
    bool isMoney2 = true;
    for (char c : receive) {
        if (!(c >= '0' && c <= '9') && c != '.') {
            isMoney2 = false;
            break;
        }
    }
    if (isMoney2) {
        money2 = 0;
        for (char c : receive) {
            if (c >= '0' && c <= '9') {
                money2 = money2 * 10 + (c - '0');  // Constructing the money value manually
            } else if (c == '.') {
                break; // Stop at decimal point
            }
        }
        b2 = nullptr; // It's money, not a building
    } else {
        b2 = findBuildingByName(receive); // It's a building
    }

    // Reject money-for-money trades
    if (money1 > 0 && money2 > 0) {
        cout << "Error: Cannot trade money for money.\n";
        return;
    }

    // Validate property ownership
    if (b1 && b1->getOwner() != currentPlayer) {
        cout << "Error: You do not own " << b1->getName() << "!\n";
        return;
    }
    if (b2 && b2->getOwner() != partner) {
        cout << "Error: " << partner->getName() << " does not own " << b2->getName() << "!\n";
        return;
    }

    // Validate if buildings have improvements
    if (b1 && !currentPlayer->checkMonopolyImprove(b1)) {
        cout << "Error: " << b1->getName() << " has improvements. Cannot trade.\n";
        return;
    }
    if (b2 && !partner->checkMonopolyImprove(b2)) {
        cout << "Error: " << b2->getName() << " has improvements. Cannot trade.\n";
        return;
    }

    // Check if the current player has enough money
    if (money1 > 0 && currentPlayer->getCash() < money1) {
        cout << "Error: You do not have enough money to trade.\n";
        return;
    }

    // Check if the partner has enough money
    if (money2 > 0 && partner->getCash() < money2) {
        cout << "Error: " << partner->getName() << " does not have enough money to trade.\n";
        return;
    }

    // Ask the receiving player if they accept the trade
    string choice;
    cout << partner->getName() << ", do you accept the trade? (yes/no): ";
    cin >> choice;

    if (choice == "yes" || choice == "y" || choice == "accept") {
        // Execute the trade based on what is being exchanged
        if (b1 && b2) currentPlayer->trade(partner, b1, b2);
        else if (b1) currentPlayer->trade(partner, b1, money2);
        else if (b2) currentPlayer->trade(partner, money1, b2);
        else currentPlayer->trade(partner, money1, money2);

        cout << "Trade successful!\n";
    } else {
        cout << "Trade rejected.\n";
    }
}

// Property actions
void GameBoard::improve(Player* player, std::string property, bool buy)
{
    std::cout << player->getName() << (buy ? " buys " : " sells ") << "an improvement on " << property << std::endl;
}

void GameBoard::mortgage(Player* player, std::string property) {
    Building* building = getBuildingByName(property);  // Assuming this function exists and returns the Building by name
    if (!building) {
        std::cout << "Property not found." << std::endl;
        return;
    }

    if (building->getOwner()->getName() != player->getName()) {
        std::cout << player->getName() << " is not the owner of " << property << "." << std::endl;
        return;
    }

    // Call Player's mortgage method
    player->mortgage(building);
}

void GameBoard::unmortgage(Player* player, std::string property) {
    Building* building = getBuildingByName(property);  // Assuming this function exists and returns the Building by name
    if (!building) {
        std::cout << "Property not found." << std::endl;
        return;
    }

    if (building->getOwner()->getName() != player->getName()) {
        std::cout << player->getName() << " is not the owner of " << property << "." << std::endl;
        return;
    }

    // Call Player's unmortgage method
    player->unmortgage(building);
}

bool GameBoard::owesOtherPlayer(Player* player) {
    if (player->getCash() < 0) {
        // The player owes money, now check who they owe it to
        for (auto& otherPlayer : players) {
            if (otherPlayer != player && otherPlayer->getCash() > 0) {
                return true; // Player owes money to another player
            }
        }
    }
    return false; // No debt to other players
}

Player* GameBoard::getCreditor(Player* player) {
    for (auto& otherPlayer : players) {
        if (otherPlayer != player && otherPlayer->getCash() > 0 && player->getCash() < 0) {
            return otherPlayer; // Return the creditor
        }
    }
    return nullptr; // No creditor found
}

void GameBoard::destroyCups(Player* player) {
    std::cout << player->getName() << " loses all Roll Up the Rim cups!" << std::endl;
    player->setCups(0); // Reset the number of cups the player has
}

void GameBoard::receiveAssets(Player* bankruptPlayer, Player* creditor) {
    std::cout << creditor->getName() << " receives all assets from " << bankruptPlayer->getName() << "!" << std::endl;

    // Transfer cash

    creditor->changeCash(bankruptPlayer->getCash());
    bankruptPlayer->setCash(0);

    // Transfer properties
    for (auto& building : bankruptPlayer->getOwnedProperties()) {
        building->setOwner(creditor);
        creditor->addOwnedProperty(building);
    }

    bankruptPlayer->clearOwnedProperties(); // Clear bankrupt player's properties
}


// Bankruptcy
void GameBoard::bankrupt(Player* player)
{
    std::cout << player->getName() << " has declared bankruptcy!" << std::endl;
}

// Auctions
void GameBoard::auction(Cell* property)
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

// Observer pattern implementation
void GameBoard::attach(Observer* observer)
{
    observers.push_back(observer);
}

void GameBoard::detach(Observer* observer)
{
    for (auto it = observers.begin(); it != observers.end();) {
        if (*it == observer) {
            it = observers.erase(it);
        } else {
            ++it;
        }
    }
}

void GameBoard::notifyObservers()
{
    for (auto observer : observers) {
        observer->notify();
    }
}

// Check for a winner
void GameBoard::checkWinCondition()
{
    int activePlayers = 0;
    Player* potentialWinner = nullptr;

    for (auto player : players)
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

// Add a player to the game
void GameBoard::addPlayer(Player* player)
{
    players.push_back(player);
}