#include "Bot.h"
// #include "game.h"  // Include your game state class

#include <cstdlib> // For random number generation
#include <ctime>   // For seeding the random number generator

Bot::Bot() {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    randomnessLevel = 10; // Set some randomness level, e.g., for randomized decision-making
}

int Bot::makeMove(Game &game) {
    // Example: make a random move
    std::vector<int> moves = availableMoves(game);
    if (moves.empty()) {
        return -1; // No available move (or game over)
    }
    
    int moveIndex = std::rand() % moves.size(); // Randomly choose a move
    return moves[moveIndex];
}

std::vector<int> Bot::availableMoves(Game &game) {
    // Here you'd implement logic to get all available moves based on the game state
    std::vector<int> moves;
    
    // Assuming the game has a method to get available moves
    // moves = game.getAvailableMoves(); 
    
    return moves;
}

// Optional: Add a more strategic move function
int Bot::strategicMove(Game &game) {
    // This could be an algorithm like minimax or others, depending on your game type
    return evaluateBestMove(game);
}

// Placeholder function for evaluating the best move (you can expand it based on your game logic)
int Bot::evaluateBestMove(Game &game) {
    // Implement a simple evaluation function for the best move
    std::vector<int> moves = availableMoves(game);
    if (moves.empty()) {
        return -1; // No available move
    }

    // For now, just return the first available move as a placeholder for a strategy
    return moves[0];
}
