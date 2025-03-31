#ifndef WATOPOLY_DISPLAY_H
#define WATOPOLY_DISPLAY_H

#include <X11/Xlib.h>
#include <map>
#include <string>
#include <vector>

class WatopolyDisplay {
    Display *display;
    Window window;
    GC gc;
    Font font;
    std::string colorMode; // "dark" or "light"
    
    // Board layout
    static const char *board[];
    static const std::pair<int, int> BOARD_COORDS[40];
    
    // Drawing constants
    static const int WIN_WIDTH = 600;
    static const int WIN_HEIGHT = 850;
    static const int TEXT_X = 20;
    static const int TEXT_Y = 20;
    static const int LINE_HEIGHT = 15;
    static const int PLAYER_OFFSET = 6;
    static const int IMPROVEMENT_SIZE = 6;
    static const int IMPROVEMENT_SPACING = 8;
    static const int COLOR_BLOCK_WIDTH = 40;
    static const int COLOR_BLOCK_HEIGHT = 15;
    
    // Game state
    std::map<char, int> players;
    std::map<int, int> improvements;
    std::map<std::string, std::vector<int>> colorGroups;
    std::map<std::string, std::string> colorNames;

    void drawBoard();
    void drawPlayers();
    void drawImprovements();
    void drawColorBlocks();

public:
    WatopolyDisplay();
    ~WatopolyDisplay();
    
    void draw();
    void reset();
    void addPlayer(char symbol, int position = 0);
    void removePlayer(char symbol);
    void movePlayer(char symbol, int absolutePosition);
    void addImprovement(int position);
    void removeImprovement(int position);
    void setImprovements(int position, int count);
    void setColorMode(const std::string &mode);
};

#endif
