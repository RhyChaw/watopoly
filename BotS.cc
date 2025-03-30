#include "BotS.h"
#include "Player.h"
#include <iostream>

using namespace std;

void botSController(BotSmart *b, int roll) {
    cout << "I am rolling yay!" << endl;
    b->movePlayer(roll);
    b->getSquareAtCurrPos();

    if (checkSelfValidS(b)) {
        buyBotS(b);
    }
}

bool checkSelfValidS(BotSmart *b) {
    return (b->getAsset() > 0);
}

void buyBotS(BotSmart *b) {
    int idx = b->getPosition();
    vector<shared_ptr<Building>> prop = b->getOwnedPropList();

    if (idx >= 0 && idx < prop.size()) {  // Prevent out-of-bounds errors
        b->addProp(prop[idx]);
    } else {
        cout << "Error: Invalid property index!" << endl;
    }
}
