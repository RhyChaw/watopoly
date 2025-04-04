#include "auction.h"
#include <algorithm>
using namespace std;

Auction::Auction(std::vector<std::shared_ptr<Player>> people, std::shared_ptr<Player> maxBidder, std::string build) : people{people}, maxBidder{maxBidder}, build{build} {
    bidders = people.size();
}

void Auction::place(std::shared_ptr<Player> p, int amount) {
	if (amount <= maxBid) {
		cout << "The bid you put is lower than the highest bid, please try again." << endl;
		return;
	}

	if (p->getCash() < amount) {
		cout << "You don't have enough cash to bid the current amount, please withdraw." << endl;
		return;
	}
	maxBid = amount;
	maxBidder = p;
	cout << "New highest bid has been set!" << endl;
}

//assuming maxbidder cant withdraw
void Auction::withdraw(std::shared_ptr<Player> p) {
    std::cout << "The player " << p->getName() << " withdraws from the bid" << std::endl << std::endl;
    
    bidders -= 1;
    
    // Remove the player from the bidders
    // added change here
    auto it = std::find_if(people.begin(), people.end(),
    [&p](const std::shared_ptr<Player>& player) {
        return player == p;
    });


    if (it != people.end()) {
        people.erase(it);
    }
    
    if (bidders == 1) {
        maxBidder = people[0];
        std::cout << "Congratulations!";
        std::cout << maxBidder->getName() << " wins the property! " << std::endl << std::endl;
        
        
        Transactions::addPropByAuction(build, maxBidder, maxBid);
        return;
    }
}

// getter 

int Auction::getMaxBid() const {
    return maxBid;
}
