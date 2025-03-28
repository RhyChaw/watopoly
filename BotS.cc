#include "BotS.h"
#include "Player.h"
using namespace std;

BotS::BotS(std::string name, char symbol, int cash) : Player(name, symbol, cash) {}

void botSController(BotS *b, int roll) {
    std::cout << "I am rolling yay!" << endl;
    b->movePlayer(roll);

    b->getSquareAtCurrPos();

    if (checkSelfValid(b)) {
        buyBotS(b);
    }
}

bool checkSelfValid(BotS *b) {
    return (b->getAsset() > 0);
}

void buyBotS(BotS *b) {
    int idx = b->getPosition();
    vector<shared_ptr<Building>> prop = b->getOwnedPropList();
    b->addProp(prop[idx]);
}

