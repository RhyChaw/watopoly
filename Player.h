#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include "Cell.h"

class Player {
private:
    std::string name;  //name of the player
    char Char; //symbol of the player
    int index; //index on the board [40]
    int position_initial; // dice rolling position
    double cash; //money
    double assets; //display assets of a player
    std::vector<std::shared_ptr<Cell>> ownedProperties; // array of properties that a player owns
    int ownedGyms;
    int ownedResidence;
    int ownedAcademic;
    bool isInTimsLine; // if in tims line
    int turnsInTimsLine; // number of rolls player has to miss before he gets his turn
    int doubles_counter; // measures the amount of double a person has rolled
    bool isBankrupt;
    int monopoly[8]; //monopoly if owns a set of cards
    int cups; //get out of jail freecard

public:
    Building *buildings[28];
    Player(const std::string &name, char symbol);

    // Getters
    std::string getName() const;
    char getSymbol() const;
    int getPosition() const;
    int getCash() const;
    int getAsset() const;
    int getOwnedResidences() const;
    int getOwnedGyms() const;
    bool isInTimsLine() const;
    int getTurnsInTimsLine() const;
    int getOwnedCups() const;
    std::vector<std::shared_ptr<Cell>> getProperties() const;

    // Setters & Modifiers
    void setPosition(int newPosition);
    void setCash(int amount);
    void addCup();
    void removeCup();
    void moveToTimsLine();
    void leaveTimsLine();
    bool checkBankrupt() const;
    
    // New Additions
    void pay(int amount);
    void receive(int amount);
    void addProperty(std::shared_ptr<Cell> property);
    void removeProperty(std::shared_ptr<Cell> property);
    void declareBankruptcy();
    bool doubles();
};

#endif // PLAYER_H
