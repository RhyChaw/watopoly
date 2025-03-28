#ifndef AUCTION_H
#define AUCTION_H
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>
#include "Player.h"
#include "building.h"
#include "transaction.h"

class Player;
class Building;
class Transactions;

class Auction {
    int maxBid = 0;
    int bidders;
    std::vector<std::shared_ptr<Player>> people;
    std::shared_ptr<Player> maxBidder;
    std::string build;

  public:
    Auction(std::vector<std::shared_ptr<Player>> people, std::shared_ptr<Player> maxBidder, std::string build);
    void place(std::shared_ptr<Player> p, int amount);
    void withdraw(std::shared_ptr<Player> p);

    // getter
    int getMaxBid() const;
};

#endif

