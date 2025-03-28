#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <memory>
#include <map>
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
#include "getInTim.h"
#include "propertyArray.h"

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
    double cash; // Player's money
    int position = 0; // Dice rolling position
    int cups = 0; // Number of "Get Out of Jail Free" cards
    bool isBankrupt = false; // Whether the player is bankrupt
    int ownedGyms = 0;
    int ownedResidence = 0;
    int ownedAcademic = 0;
    std::vector<std::shared_ptr<Building>> ownedProperties;
    std::vector<std::string> monopolyBlocks; // ie: {"Sci1", "Math", "Eng"}
    
    int index = 0; // Index on the board [0-39]
    double assets = 0; // Player's total assets
    bool isInTimsLine = false; // If player is in Tims Line
    int turnsInTimsLine = 0; // Number of turns player must wait in Tims Line
    int roll_for_jail = 0; //you jut added this, its used in timeline

public:
    //big five
    Player(std::string name, char symbol, int Cash);
    
    Player(std::string name, char symbol, int ownedCups, double cash, int index, 
        bool isTimLine, int turnsInTimsLine, int position_initial, 
        double assets, std::vector<std::shared_ptr<Building>> ownedProperties,
        int ownedGyms, int ownedResidence, int ownedAcademic);
    ~Player();

    //basic functions
    bool isResidence(std::string squareName);
    bool isGym(std::string squareName);
    bool isAcademic(std::string squareName);
    bool checkIfInMonopolyBlock(std::string name) ;
    bool ownThisProp(std::string name);
    void pay(int amount);
    void changeCash(double c);
    void removeProp(std::shared_ptr<Building> prop);
    void addProp(std::shared_ptr<Building> property_name);
    bool mortgageProp(std::shared_ptr<Building> prop); 
    bool unmortgageProp(std::shared_ptr<Building> prop);
    void updateMonopolyBlock();
    void movePlayer(int roll);
    void moveToDCTims();
    void addTimsCup();
    void loadUpdateAmountToPay();
    void printAsset();
    void printOwnedProp();

    //getters
    char getSymbol() const;
    std::string getName() const;
    double getCash() const;  
    int getPosition() const;
    std::string getSquareAtCurrPos();
    int getCups() const;
    bool getisBankrupt() const;
    int getOwnedResidences() const;
    int getOwnedGyms() const;
    int getOwnedAcademic() const;
    std::vector<std::shared_ptr<Building>> getOwnedPropList();

    int getIndex() const;
    double getAsset() const; 
    bool getisInTimsLine() const;
    int getTurnsInTimsLine() const;
    int getadd_roll_for_jail() const;

    //setters
    void setCups(int n); 
    void useCups();
    void setPos(int pos);
    void setBankrupt(bool b);
    void setIsInTimsLine(bool status);
    void setownedGyms(int n);
    void setownedResidence(int n);
    void setownedAcademic(int n);
    void setIndex(int n);
    void setTurnsInTimsLine(int turns);
    void setRollForJail(int n);
    void resetTurnsInTims()

    //additional functions
    void leaveTimsLine();
    void changeTurnsInTimsLine();
    void changeAsset(double c);
    void changePropertyCount(int residences, int gyms, int academics);
    void receive(int amount);
    void addProperty(std::shared_ptr<Cell> property);
    void removeProperty(std::shared_ptr<Cell> property);
    void removeCup();
    void add_roll_for_jail();
    std::string monoBlockOfProp(std::string name);
    bool checkMonopoly(int block);
    void declareBankruptcy();
    bool checkBankrupt() const;
};

#endif 
