#include "Dice.h"
#include <cstdlib> // For rand()

void Dice::roll() {
    lastRoll1 = rand() % 6 + 1;
    lastRoll2 = rand() % 6 + 1;
}

int Dice::getFirstDie() {
    return lastRoll1;
}

int Dice::getSecondDie() {
    return lastRoll2;
}

int Dice::getSum() {
    return lastRoll1 + lastRoll2;
}

bool Dice::isDoubles() {
    return lastRoll1 == lastRoll2;
}

int Dice::changeDouble() {
    doubles_count++;
}
