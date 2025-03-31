#include "load.h"
#include <sstream>
#include <stdexcept>
#include <iostream>

void Load::loadGame (std::vector<std::shared_ptr<Player>> group, std::shared_ptr<Player> currActingPlayer, bool testMode, std::shared_ptr<GameBoard> b) {
    std::cout << "loading a saved game " << endl;
    std::ifstream f;
    int num;
    f >> num;
    for (int i = 0; i < num; i++) {
        string name;
        char piece;
        int cup;
        int cash;
        int pos;
        f >> name;
        f >> piece;
        f >> cup;
        f >> cash;
        f >> pos;
        auto p = std::make_shared<Player>(name, piece, cash);
        p->setCups(cup);
        b->addPlayer(piece);
        if (pos == 10) {
            bool in;
            f >> in;
            if (in) {
                int turn;
                f >> turn;
                p->setTurnsInTims(turn);
                b->movePlayer(piece, 10);
                p->moveToDCTims();
            } else {
                p->movePlayer(pos); 
                b->movePlayer(piece, pos);
            }
        } else {
            p->movePlayer(pos); 
            b->movePlayer(piece, pos);
        }
        group.push_back(p);
    }

    for (int i = 0; i < 28; i++) {  // Outer loop for properties
        string property_name;
        string owner;
        int imp;
        f >> property_name;
        f >> owner;
        f >> imp;
        if (owner != "BANK") {
            int playerIndex = -1;
            // Use a different loop variable (playerIndex) to find the player with the matching name
            for (int j = 0; j < num; j++) {
                if (group[j]->getName() == owner) {
                    playerIndex = j;
                    break;  // Found the player, no need to continue the loop
                }
            }

            int propertyIndex = -1;
            // Use a different loop variable (propertyIndex) to find the property
            for (int k = 0; k < 40; k++) {
                if (property_name == OWNABLE[k][0]) {
                    propertyIndex = k;
                    break;  // Found the property, no need to continue the loop
                }
            }

            int buycost = 0;
            // Look for the property in OWNABLE array to get the buy cost
            for (int l = 0; l < 28; l++) {
                if (OWNABLE[l][0] == property_name) {
                    std::stringstream ss(OWNABLE[l][2]);
                    ss >> buycost;
                    break;  // Found the buy cost, no need to continue the loop
                }
            }

            char owner_symbol = group[playerIndex]->getSymbol();
            std::shared_ptr<Building> build;
            // Create the building object based on the property type
            if (isGym(property_name)) {
                auto production = std::make_shared<Gym>(propertyIndex, property_name, buycost, owner_symbol);	
                build = std::dynamic_pointer_cast<Building>(production);
                group[playerIndex]->setGymsOwned();
            } else if (isResidence(property_name)) {
                auto production = std::make_shared<Residence>(propertyIndex, property_name, buycost, owner_symbol);
                build = std::dynamic_pointer_cast<Building>(production);
                group[playerIndex]->setResOwned();
            } else if (isAcademic(property_name)) {
                auto production = std::make_shared<Academic>(propertyIndex, property_name, buycost, owner_symbol);
                build = std::dynamic_pointer_cast<Building>(production);
            }

            // Add the property to the player's assets and update the building status
            group[playerIndex]->addProp(build);
            Transactions::setowned(build);
            if (imp == -1) {
                build->setMortStatus(true);
            } else {
                build->setImprLevel(imp); 
            }
            b->addImpr(property_name, imp);
        }

        for (auto& player : group) {
            int gymCount = 0;
            // First count gyms
            for (const auto& prop : player->getOwnedPropList()) {
                if (isGym(prop->getName())) gymCount++;
            }
            // Then set the count for each gym
            for (auto& prop : player->getOwnedPropList()) {
                if (isGym(prop->getName())) {
                    prop->setGymLevel(gymCount);
                }
            }
        }

        // Update every player's monopoly block and the amount they need to pay
        for (int m = 0; m < num; m++) {
            group[m]->updateMonopolyBlock();
            group[m]->loadUpdateAmountToPay();
        }

        // Display assets of every player
        std::cout << "Displaying assets of every player, so everyone is on track" << std::endl;
        for (int m = 0; m < num; m++) {
            group[m]->getAsset();
        }

        // Draw the game board
        b->drawBoard();
    }
}

void Load::saveGame (std::vector<std::shared_ptr<Player>> group, std::shared_ptr<Player> currActingPlayer, bool testMode, std::shared_ptr<GameBoard> b) {
    std::cout << "saving the game. are you sure?(y/n)" << endl;
    char c;
    std::cin >> c;
    std::ofstream f;
    if(c == 'y') {
        std::cout << "enter the name of the file you want to save in" << endl;
        string file;
        std::cin >> file;
        file+=".txt";
        f.open(file);
        int size = group.size();
        f << size << endl;
        for (int i = 0; i < size; i++) {
            f << group[i]->getName() << " ";
            f << group[i]->getSymbol() << " ";
            f << group[i]->getCups() << " ";
            f << group[i]->getCash() << " ";
            f << group[i]->getPosition() << " ";
            if (group[i]->getPosition() == 10) {
                f << group[i]->getisInTimsLine()<< " ";
                if (group[i]->getisInTimsLine()) {
                    f << group[i]->getTurnsInTimsLine()<< " ";
                }
            }
            if (group[i]->getPosition() == 4) {
                f << " " << 0 << endl;
            }
            else {
                f << endl;
            }
        }
        for (int i = 0; i < 28; i++) {
            f << OWNABLE[i][0] << " ";
            int size = group.size();
            bool owned = false;
            for (int j = 0; j < size; j++)
            {
                if (group[j]->ownThisProp(OWNABLE[i][0]))
                {
                    f << group[j]->getName() << " ";
                    owned = true;
                    break;
                }
            }

            if (!owned)
            {
                f << "BANK" << " ";
            }
            f << b->getSquareImprovements(OWNABLE[i][0]) << endl;
        }
        return;
    } else {
        std::cout << "file not saved......" << endl;
    }
}

