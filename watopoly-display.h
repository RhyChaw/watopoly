#ifndef WATOPOLY_DISPLAY_H
#define WATOPOLY_DISPLAY_H

#include <X11/Xlib.h>
#include <string>
#include <vector>

class WatopolyDisplay {
public:
    WatopolyDisplay();
    ~WatopolyDisplay();
    
    void initializeWindow();
    void drawBoard();
    void addPlayer(const std::string& playerName, char symbol, int position);
    void addImprovement(const std::string& propertyName, int level);
    void updateDisplay();
    
private:
    Display* display;
    Window window;
    GC gc;
    int screen;
    
    const int WIN_WIDTH = 900;
    const int WIN_HEIGHT = 400;
    const int TEXT_X = 20;
    const int TEXT_Y = 20;
    const int LINE_HEIGHT = 15;
    
    std::vector<std::string> board;
    std::vector<std::pair<int, char>> playerPositions; // position, symbol
    std::vector<std::pair<std::string, int>> improvements; // property name, level
    
    void initializeBoard();
    void drawPlayers();
    void drawImprovements();
};

#endif
