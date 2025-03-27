#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <iostream>
#include <vector>
#include "Player.h"
#include "Cell.h"
#include "building.h"
#include "auction.h"
#include "Academic.h"
#include "Gym.h"
#include "Residence.h"
#include "propertyArray.h"

class Cell;
class Player;
class Building;
class Auction;
class Academic;
class Gym;
class Residence;

static std::vector<std::shared_ptr<Building>> ownedProperties; 

class Transactions{
    public:
    static bool isGym(std::string squareName);
    static int  getPropertyCost(const std::string &property_name);
    static bool isResidence(std::string squareName);
    static bool isAcademic(std::string squareName);
    static bool isOwned(std::string nameSquare);
    static void transferProperty(std::shared_ptr<Building> building, std::shared_ptr<Player> from, std::shared_ptr<Player> to);
    static bool checkFund(std::shared_ptr<Player> p1, int amt);
    static void trade(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, double money, std::shared_ptr<Building> building);
    static void trade(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, std::shared_ptr<Building> building1, std::shared_ptr<Building> building2);
    static void trade(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, std::shared_ptr<Building> building, double money);
    static void trade(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, double money1, double money2);
    static void payRent(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, int rent); 
    static void payBank(std::shared_ptr<Player> p1, int rent);
    static void buyBuilding(std::string property_name, std::shared_ptr<Player> owner);
    static void sellBuilding(std::string property_name, std::shared_ptr<Player> owner);
    static void buyImprovement(std::shared_ptr<Building> property_name, std::shared_ptr<Player> owner);
    static void sellImprovement(std::shared_ptr<Building> property_name, std::shared_ptr<Player> owner);
    static void mortgage(std::shared_ptr<Building> property_name, std::shared_ptr<Player> owner);
    static void unmortgage(std::shared_ptr<Building> property_name, std::shared_ptr<Player> owner);
    static std::shared_ptr<Building> listProp(std::string property_name);
    static void addPropByAuction(std::string build, std::shared_ptr<Player> p, int amount);

};

#endif
