#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <map>
#include <vector>
#include <memory>
#include "Cell.h"
#include "Academic.h"
#include "building.h"
#include "TimsLine.h"

class Building;  
class Cell; 
class Academic;

class Player {
private:
    std::string name;  // Name of the player
    char symbol; // Symbol of the player
    int index; // Index on the board [0-39]
    int position_initial; // Dice rolling position
    double cash; // Player's money
    double assets; // Player's total assets
    std::vector<std::shared_ptr<Cell>> ownedProperties; // List of owned properties
    int ownedGyms;
    int ownedResidence;
    int ownedAcademic;
    bool isInTimsLine; // If player is in Tims Line
    int turnsInTimsLine; // Number of turns player must wait in Tims Line
    bool isBankrupt; // Whether the player is bankrupt
    int monopolySet[8]; // Tracks if a player owns a full monopoly set
    int cups; // Number of "Get Out of Jail Free" cards

public:
    Building *buildings[28];

    // Constructors & Destructor
    Player(std::string name, char symbol, int index, int position_initial);
    
    // Constructor for loading a saved game
    Player(std::string name, char symbol, int ownedCups, double cash, int index, 
        bool isTimLine, int turnsInTimsLine, int position_initial, 
        double assets, std::vector<std::shared_ptr<Cell>> ownedProperties,
        int ownedGyms, int ownedResidence, int ownedAcademic);
    
    ~Player();

    // Getters
    std::string getName() const;
    int getIndex() const;
    char getSymbol() const;
    int getPosition() const;
    double getCash() const;  // Changed from int to double
    double getAsset() const; // Changed from int to double
    int getOwnedResidences() const;
    int getOwnedGyms() const;
    int getTurnsInTimsLine() const;
    int getOwnedCups() const;
    bool getisInTimsLine() const;
    bool getisBankrupt() const;
    std::vector<std::shared_ptr<Cell>> getProperties() const;
    bool checkMonopolyImprove(Building *building);
    Building* findBuilding(std::string buildingName); // Made consistent with implementation
    void printAsset();

    // Setters & Modifiers
    void setPosition(int newPosition);
    void setCash(int amount);
    void setTurnsInTimsLine(int turns);
    void setBankrupt(bool b);
    void setCups(int n);
    void moveToTimsLine();
    void leaveTimsLine();
    void changeAsset(double c);
    void changePropertyCount(int residences, int gyms, int academics);
    void changeCash(double c);

    // Gameplay Functions
    void pay(int amount);
    void receive(int amount);
    void addProperty(std::shared_ptr<Cell> property);
    void removeProperty(std::shared_ptr<Cell> property);
    void declareBankruptcy();
    bool checkBankrupt() const;

    // Dice & Tims Line Management
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
    void trade(Player *partner, double money1, double money2);
};

#endif // WATOPOLY_PLAYER_H
