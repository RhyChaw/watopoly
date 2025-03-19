#include "Dice.h"
#include <cstdlib>

std::pair<int, int> Dice::rollDice() {
    int die1 = rand() % 6 + 1;
    int die2 = rand() % 6 + 1;
    return {die1, die2};
}
