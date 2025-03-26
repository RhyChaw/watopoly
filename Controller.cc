#include "Controller.h"
#include "load.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "propertyArray.h" // For building type checks

using namespace std;

// Helper functions to determine building types
bool isGym(const string& name) {
    return name == "PAC" || name == "MKV";
}

bool isResidence(const string& name) {
    return name == "MKV" || name == "ECH" || name == "PAS" || name == "HH" || name == "RCH";
}

bool isAcademic(const string& name) {
    return !isGym(name) && !isResidence(name) && name != "DC" && name != "COLLECT OSAP";
}

Controller::Controller() : gameBoard(make_shared<GameBoard>()), currentPlayerIndex(0) {}

bool Controller::loadGame(const string &filename) {
    try {
        loadedState = Load::loadGame(filename);
        initializeFromLoadedState();
        return true;
    } catch (const exception& e) {
        cerr << "Load error: " << e.what() << endl;
        return false;
    }
}

void Controller::initializeFromLoadedState() {
    for (auto playerInfo : loadedState.players) {
        Player* player = make_shared<playerInfo>;
            player->getName();
            player->getSymbol();
            player->getCups();
            player->getCash();
            player->getPosition();
            player->inDC;
            player->turnsInDC;
            0;
            vector<shared_ptr<Building>>{};// Removed incorrect assets reference

        if (playerInfo.inDC) {
            player->moveToDCTims();
            player->setTurnsInTimsLine(playerInfo.turnsInDC);
        }
        
        gameBoard->addNewPlayer(player); // Changed to the correct method name
    }

    for (const auto& buildingInfo : loadedState.buildings) {
        Cell* cell = gameBoard->getCell(buildingInfo.cellPosition); // Fixed incorrect member name
        Building* building = dynamic_cast<Building*>(cell);
        
        if (!building) continue;

        building->setMortStatus(buildingInfo.improvements == -1);

        if (buildingInfo.owner != "BANK") {
            char ownerChar = buildingInfo.owner[0];
            for (auto* player : gameBoard->getAllPlayers()) { // Changed to correct method
                if (player->getSymbol() == ownerChar) {
                    building->setOwner(ownerChar);
                    player->addProperty(shared_ptr<Building>(building)); // Updated to correct function
                    
                    if (isGym(buildingInfo.name)) {
                        player->incrementGymsOwned(); // Corrected function
                    } else if (isResidence(buildingInfo.name)) {
                        player->incrementResidencesOwned(); // Corrected function
                    } else if (isAcademic(buildingInfo.name)) {
                        building->setImprLevel(buildingInfo.improvements);
                        player->incrementAcademicsOwned(); // Corrected function
                    }
                    break;
                }
            }
        }
    }
    
    cout << "=== LOAD SUMMARY ===" << endl;
    cout << "Players loaded: " << loadedState.players.size() << endl;
    cout << "Buildings initialized: " << loadedState.buildings.size() << endl;
}

void Controller::play() {
    if (loadedState.players.empty()) {
        cout << "Starting new game..." << endl;
    }

    while (!gameBoard->isWon()) { // Changed method name
        auto* currentPlayer = gameBoard->getCurrentPlayer(currentPlayerIndex); // Changed method name
        cout << "\n" << currentPlayer->getName() << "'s turn." << endl;

        if (currentPlayer->isInTimsLine()) { // Fixed incorrect method name
            cout << "You are in DC Tims Line. Choose to roll, pay $50, or use a Get Out of Jail Free card." << endl;
            if (currentPlayer->hasTimsCup()) { // Fixed incorrect method name
                cout << "Using a Get Out of Jail Free card." << endl;
                currentPlayer->leaveTimsLine();
            } else {
                cout << "Rolling to get out..." << endl;
                if (currentPlayer->leaveTimsLine()) { // Changed method name
                    cout << "You rolled doubles and are free!" << endl;
                    currentPlayer->leaveTimsLine();
                } else {
                    cout << "Failed to roll doubles. Remaining in jail." << endl;
                }
            }
        } else {
            gameBoard->roll(currentPlayer); 
            Cell* landedCell = gameBoard->getCell(currentPlayer->getPosition());
            cout << "You landed on " << landedCell->getName() << endl;
            
            Building* building = dynamic_cast<Building*>(landedCell);
            if (building) {
                if (building->getOwner() == ' ') {
                    cout << "This property is available for purchase." << endl;
                    // Implement buy logic
                } else if (building->getOwner() != currentPlayer->getSymbol()) {
                    cout << "This property is owned by another player. Paying rent." << endl;
                    currentPlayer->payRent(building->getCostToBuy()); // Changed method name
                }
            }
        }
        
        if (currentPlayer->isBankrupt()) { // Changed method name
            cout << currentPlayer->getName() << " is bankrupt! Removing from game." << endl;
            gameBoard->removeExistingPlayer(currentPlayer); // Changed method name
        }
        
        cout << "End of " << currentPlayer->getName() << "'s turn." << endl;
        currentPlayerIndex = (currentPlayerIndex + 1) % gameBoard->getAllPlayers().size(); // Changed method name
    }
    
    cout << "Game over! The winner is " << gameBoard->getWinner()->getName() << "!" << endl;
}
