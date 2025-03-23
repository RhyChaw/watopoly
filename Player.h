#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include "Cell.h"
#include "building.h"
#include "auction.h"
#include "Academic.h"
#include "Gym.h"
#include "Residence.h"
#include "nonbuilding.h"
#include "TimsLine.h"

class Cell;
class Building;
class nonbuilding;
class Auction;
class Academic;
class Gym;
class Residence;
class TimsLine;

class Player {
private:
    std::string name;  // Name of the player
    char symbol; // Symbol of the player
    int index; // Index on the board [0-39]
    int position_initial; // Dice rolling position
    double cash; // Player's money
    double assets; // Player's total assets
    std::vector<std::shared_ptr<Building>> ownedProperties; // List of owned properties
    int ownedGyms;
    int ownedResidence;
    int ownedAcademic;
    bool isInTimsLine; // If player is in Tims Line
    int turnsInTimsLine; // Number of turns player must wait in Tims Line
    bool isBankrupt; // Whether the player is bankrupt
    int monopolySet[8]; // Tracks if a player owns a full monopoly set
    int cups; // Number of "Get Out of Jail Free" cards
    int roll_for_jail = 0; //you jut added this, its used in timeline

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
    int getadd_roll_for_jail() const;

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
    void add_roll_for_jail();

    // Property Management
    bool checkMonopoly(int block);
    void sellBuilding(Building *building);
    void mortgage(Building *building);

    //transactions
    bool isOwned(std::string nameSquare);
    void trade(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, double money, std::shared_ptr<Ownable> *building);
    void trade(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, std::shared_ptr<Ownable> *building1, std::shared_ptr<Ownable> *building2);
    void trade(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, std::shared_ptr<Ownable> building, double money);
    void trade(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, double money1, double money2);
    void payRent(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, int rent); 
    void payBank(std::shared_ptr<Player> p1, int rent);
    void buyBuilding(std::string property_name, std::shared_ptr<Player> owner);
    void buyImprovement(std::shared_ptr<Ownable> property_name, std::shared_ptr<Player> owner);
    void sellImprovement(std::shared_ptr<Ownable> property_name, std::shared_ptr<Player> owner);
    void mortgage(std::shared_ptr<Ownable> property_name, std::shared_ptr<Player> owner);
    void unmortgage(std::shared_ptr<Ownable> property_name, std::shared_ptr<Player> owner);

    static std::shared_ptr<Ownable> pointerOfProp(std::string ownableName);
    static void addPropByAuction(std::string ownableName, std::shared_ptr<Player> buyer, int price);

};

#endif // WATOPOLY_PLAYER_H
