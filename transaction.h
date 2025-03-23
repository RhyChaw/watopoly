#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#include <iostream>
#include <vector>
#include "Player.h"
#include "Cell.h"
#include "building.h"
#include "auction.h"
#include "Academic.h"
#include "Gym.h"
#include "Residence.h"

class Cell;
class Player;
class building;
class Auction;
class Academic;
class Gym;
class Residence;

static std::vector<std::shared_ptr<Building>> ownedProperties; 

class Transactions{
    public:
    bool isGym(std::string squareName);
    int  getPropertyCost(const std::string &property_name);
    bool isResidence(std::string squareName);
    bool isAcademic(std::string squareName);
    bool isOwned(std::string nameSquare);
    void transferProperty(std::shared_ptr<Building> building, std::shared_ptr<Player> from, std::shared_ptr<Player> to);
    bool checkFund(std::shared_ptr<Player> p1, int amt);
    void trade(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, double money, std::shared_ptr<Building> building);
    void trade(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, std::shared_ptr<Building> building1, std::shared_ptr<Building> building2);
    void trade(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, std::shared_ptr<Building> building, double money);
    void trade(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, double money1, double money2);
    void payRent(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, int rent); 
    void payBank(std::shared_ptr<Player> p1, int rent);
    void buyBuilding(std::string property_name, std::shared_ptr<Player> owner);
    void sellBuilding(std::string property_name, std::shared_ptr<Player> owner);
    void buyImprovement(std::shared_ptr<Building> property_name, std::shared_ptr<Player> owner);
    void sellImprovement(std::shared_ptr<Building> property_name, std::shared_ptr<Player> owner);
    void mortgage(std::shared_ptr<Building> property_name, std::shared_ptr<Player> owner);
    void unmortgage(std::shared_ptr<Building> property_name, std::shared_ptr<Player> owner);
    std::shared_ptr<Building> listProp(std::string property_name);
};

#endif
