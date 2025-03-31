#ifndef DICE_H
#define DICE_H

#include <cstdlib>
#include <ctime> 

class Dice {
private:
    static int lastRoll1;
    static int lastRoll2;
    int doubles_count = 3;

public:
    Dice();
    static void roll();
    static int getFirstDie();
    static int getSecondDie();
    static int getSum();
    static bool isDoubles();
    void changeDouble();
    int getDoubles();
};

#endif // DICE_H