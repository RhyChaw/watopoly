#include "Dice.h"
#include <cstdlib>

// haha

std::pair<int, int> Dice::rollDice() {
    int die1 = rand() % 6 + 1;
    int die2 = rand() % 6 + 1;
    return {die1, die2};
    //hello
}
