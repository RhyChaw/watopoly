#include "auction.h";
using namespace std;

Auction::Auction(std::vector<std::shared_ptr<Player>> people, std::shared_ptr<Player> maxBidder, std::string build) : people{people}, maxBidder{maxBidder}, build{build} {
    bidders = people.size();
}

void Auction::place(std::shared_ptr<Player> p, int amount) {
	if (amount <= maxBid) {
		cout << "bid is lower than the highest bid" << endl;
		return;
	}

	if (p->getCash() < amount) {
		cout << "You don't have enough fund to bid the current amount" << endl;
		return;
	}
	maxBid = amount;
	maxBidder = p;
	cout << "new highest bid set" << endl;
}

//assuming maxbidder cant withdraw
void Auction::withdraw(std::shared_ptr<Player> p) {
    std::cout << "--> The player " << p->getName() << " withdraw from the bid" << endl << endl;
	bidders -= 1;

    people.erase(p);

	if (bidders == 1) {
        maxBidder = people[0];
		std::cout << "$$$$$ Congratulation $$$$$ -->";
		std::cout << maxBidder->getName() << " wins the property " << endl << endl;
        Transactions::addPropByAuction(build, maxBidder, maxBid);
        return;
	}
}




