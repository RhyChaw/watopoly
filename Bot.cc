#include "Bot.h"
#include "Player.h"
#include <iostream>

using namespace std;

void botController(Bot *b, int roll) {
    cout << "I am rolling yay!" << endl;
    b->movePlayer(roll);
    b->getSquareAtCurrPos();

    if (checkSelfValid(b)) {
        buyBot(b);
    }
}

bool checkSelfValid(Bot *b) {
    return (b->getAsset() > 0);
}

void buyBot(Bot *b) {
    int idx = b->getPosition();
    vector<shared_ptr<Building>> prop = b->getOwnedPropList();
    
    if (idx >= 0 && idx < prop.size()) {  // Prevent out-of-bounds errors
        b->addProp(prop[idx]);
    }
}
