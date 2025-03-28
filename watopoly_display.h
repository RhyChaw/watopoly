#ifndef WATOPOLY_DISPLAY_H
#define WATOPOLY_DISPLAY_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <vector>
#include <map>
#include <memory>
#include <string>

class WatopolyDisplay {
    Display *display;
    Window window;
    GC gc;
    Font font;
    
    // Board dimensions
    static const int WIN_WIDTH = 700;
    static const int WIN_HEIGHT = 1500;
    static const int TEXT_X = 20;
    static const int TEXT_Y = 20;
    static const int LINE_HEIGHT = 15;
    static const int PLAYER_OFFSET = 6;
    static const int IMPROVEMENT_SIZE = 6;
    static const int IMPROVEMENT_SPACING = 8;
    static const int COLOR_BLOCK_HEIGHT = 15;
    static const int COLOR_BLOCK_WIDTH = 40;
    
    // Game state
    std::map<char, int> players; // symbol to position
    std::map<int, int> improvements; // position to count
    std::map<std::string, std::vector<int>> colorGroups;
    std::map<std::string, std::string> colorNames;
    
    // Board layout
    static const char *board[];
    static const std::pair<int, int> BOARD_COORDS[40];
    
    // Drawing methods
    void drawPlayers();
    void drawImprovements();
    void drawColorBlocks();
    void drawBoard();

public:
    WatopolyDisplay();
    ~WatopolyDisplay();
    
    // Interface methods
    void draw();
    void reset();
    void addPlayer(char symbol, int position = 0);
    void removePlayer(char symbol);
    void movePlayer(char symbol, int absolutePosition); // Update declaration
    void addImprovement(int position);
    void removeImprovement(int position);
    void setImprovements(int position, int count);
};

#endif // WATOPOLY_DISPLAY_H