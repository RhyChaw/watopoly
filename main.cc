#include "Controller.h"
#include <iostream>

int main(int argc, char *argv[]) {
    Controller gameController;

    // Check if loading a saved game
    if (argc > 1) {
        std::string arg1 = argv[1];
        if (arg1 == "-load" && argc > 2) {
            std::string filename = argv[2];
            if (!gameController.loadGame(filename)) {
                std::cerr << "Error: Could not load game from " << filename << std::endl;
                return 1;
            }
        }
    }

    // Start the game
    gameController.play();
    
    return 0;
}
