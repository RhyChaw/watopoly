#ifndef WATOPOLY_PLAYER_H
#define WATOPOLY_PLAYER_H
#include <string>
#include <vector>
#include "GameBoard.h"
#include <string>

class Player {
private:
    std::string name;  //name of the player
    char symbol; //symbol of the player
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
    int monopolySet[8]; //monopoly if owns a set of cards
    int cups; //get out of jail freecard

public:
    Building *buildings[28];
    Player(std::string name, char symbol, int index, int position_initial);
    Player(std::string name, char symbol, int ownedCups, double cash, int index, bool isTimLine, int turnsInTimsLine, int position_initial);
    ~Player();

    // Getters
    std::string getName() const;
    char getSymbol() const;
    int getPosition() const;
    int getCash() const;
    int getAsset() const;
    int getOwnedResidences() const;
    int getOwnedGyms() const;
    int getTurnsInTimsLine() const;
    int getOwnedCups() const;
    bool isInTimsLine() const;
    bool isBankrupt() const;
    std::vector<std::shared_ptr<Cell>> getProperties() const;
    bool checkMonopolyImprove(Building *building);
    Building *findBuilding(const std::string &buildingName);
    void printAsset();

    // Setters & Modifiers
    void setPosition(int newPosition);
    void setCash(int amount);
    void setTurnsInTimsLine(int turns);
    void setBankrupt(bool b);
    void setCups(int n);
    void moveToTimsLine();
    void leaveTimsLine();
    void changeAsset(int c);
    void changePropertyCount(int residences, int gyms);

    // Gameplay Functions
    void pay(int amount);
    void receive(int amount);
    void addProperty(std::shared_ptr<Cell> property);
    void removeProperty(std::shared_ptr<Cell> property);
    void declareBankruptcy();
    bool checkBankrupt() const;

    // Dice & Tims Line Management
    bool doubles();
    void addCup();
    void removeCup();

    // Property Management   
    bool checkMonopoly(int block);
    void buyBuilding(Building *building);
    void sellBuilding(Building *building);
    void mortgage(Building *building);
    void unmortgage(Building *building);
    void buyImprovement(Building *building);
    void sellImprovement(Building *building);

    // Trading
    void trade(Player *partner, double money, Building *building);
    void trade(Player *partner, Building *building1, Building *building2);
    void trade(Player *partner, Building *building, double money);
};

#endif //WATOPOLY_PLAYER_H

    