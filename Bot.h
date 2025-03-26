#ifndef BOT_H
#define BOT_H

#include <vector>

// Forward declare the Game class or any other class representing the game state
class Game;

class Bot {
public:
    Bot();
    
    // Function to decide the next move
    int makeMove(Game &game);

    // Optionally add a strategy method to decide moves (for future extensions)
    int strategicMove(Game &game);

private:
    // Function to evaluate the best move (for example, using minimax or another algorithm)
    int evaluateBestMove(Game &game);
    
    // Any other helper functions needed for decision-making (e.g., checking available moves)
    std::vector<int> availableMoves(Game &game);
    
    // Optionally, add any bot attributes (e.g., strategy level, randomness factor)
    int randomnessLevel;
};

#endif // BOT_H
