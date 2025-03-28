#ifndef DICE_H
#define DICE_H

#include <cstdlib>

class Dice {
private:
    static int lastRoll1;
    static int lastRoll2;
    int doubles_count = 3;

public:
    // Rolls both dice and stores the results internally
    static void roll();
    
    // Returns the value of the first die from the last roll
    static int getFirstDie();
    
    // Returns the value of the second die from the last roll
    static int getSecondDie();
    
    // Returns the sum of both dice from the last roll
    static int getSum();
    
    // Checks if the last roll was doubles
    static bool isDoubles();
    void changeDouble();
    int getDoubles();
};

#endif // DICE_H