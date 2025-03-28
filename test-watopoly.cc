#include "GameBoard.h"
#include <iostream>
#include <unistd.h> // for sleep()

void testPlayers(GameBoard& board) {
    std::cout << "=== Testing Player Functions ===" << std::endl;
    
    // Add players
    board.drawBoard();
    board.addPlayer('G'); // Goose
    board.addPlayer('B'); // GRT Bus
    board.addPlayer('D'); // Doughnut
    sleep(5);
    std::cout << "Added 3 players at GO position" << std::endl;
    
    // Move players
    board.movePlayer('G', 5); // Move Goose to V1
    board.movePlayer('B', 10); // Move Bus to GO TO TIMS
    board.update();
    std::cout << "Moved players to different positions" << std::endl;
    sleep(5);

    
    // Remove player
    board.removePlayer('D');
    board.update();
    std::cout << "Removed Doughnut player" << std::endl;
    sleep(20);
}

void testImprovements(GameBoard& board) {
    std::cout << "=== Testing Improvement Functions ===" << std::endl;
    
    // Add improvements
    board.addImpr("EV1");
    board.addImpr("EV1",4);
    board.drawBoard();
    sleep(20);
    /*std::cout << "Added improvements to EV1 (2) and PHYS (1)" << std::endl;
    sleep(2);
    
    // Add more to test max improvements
    for (int i = 0; i < 4; i++) {
        board.addImprovement("EV1");
    }
    board.drawBoard();
    std::cout << "Added more improvements to EV1 (should max at 5)" << std::endl;
    sleep(2);
    
    // Remove improvements
    board.removeImprovement("EV1");
    board.removeImprovement("PHYS");
    board.drawBoard();
    std::cout << "Removed 1 improvement from EV1 and PHYS" << std::endl;
    sleep(2);*/
}

void testEdgeCases(GameBoard& board) {
    std::cout << "=== Testing Edge Cases ===" << std::endl;
    
    // Test invalid player
    board.movePlayer('X', 5); // Non-existent player
    board.removePlayer('Y');  // Non-existent player
    std::cout << "Attempted moves with invalid players (should do nothing)" << std::endl;
    
    // Test invalid square
    board.addImpr("INVALID");
    board.removeImpr("INVALID");
    std::cout << "Attempted improvements on invalid square (should do nothing)" << std::endl;
    
    // Test board wrapping
    board.movePlayer('G', 35); // Should wrap around (from position 5 to 0)
    board.drawBoard();
    std::cout << "Moved Goose by 35 (should wrap around board)" << std::endl;
    sleep(2);
}

int main() {
    try {
        GameBoard board;
        
        // Run tests
        testPlayers(board);
        //testImprovements(board);
       //testEdgeCases(board);
        
        std::cout << "=== All tests completed ===" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}