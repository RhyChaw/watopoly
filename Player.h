#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include "Cell.h"

class Player {
private:
    std::string name;
    char symbol;
    int position;
    int cash;
    int numCups;
    std::vector<std::shared_ptr<Cell>> ownedProperties;
    bool inTimsLine;
    int turnsInLine;

public:
    Player(const std::string &name, char symbol);

    // Getters
    std::string getName() const;
    char getSymbol() const;
    int getIndex() const;
    int getCash() const;
    bool getIsTimLine() const;
    int getNumLineWait() const;
    int getOwnedCups() const;
    std::vector<std::shared_ptr<Cell>> getProperties() const;

    // Setters
    void setIndex(int newPosition);
    void setCash(int amount);
    void addCup();
    void removeCup();
    void moveToTimsLine();
    void leaveTimsLine();
    bool checkBankrupt() const;
};

#endif // PLAYER_H
