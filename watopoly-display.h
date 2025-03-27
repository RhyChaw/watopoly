#ifndef WATOPOLY_DISPLAY_H
#define WATOPOLY_DISPLAY_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <map>
#include <vector>

class WatopolyDisplay {
public:
    WatopolyDisplay();
    ~WatopolyDisplay();
    
    void initialize();
    void drawBoard();
    void drawPlayers(const std::map<char, int>& playerPositions);
    void drawImprovements(const std::map<int, int>& positionImprovements);
    void handleEvents();
    bool isWindowOpen() const;

    // Positions that can have improvements (1-based index)
    static const std::vector<int> IMPROVABLE_POSITIONS;

private:
    Display* display;
    Window window;
    GC gc;
    int screen;
    Font font;
    bool windowOpen;

    // Board dimensions and constants
    static const int WIN_WIDTH = 900;
    static const int WIN_HEIGHT = 700;
    static const int TEXT_X = 20;
    static const int TEXT_Y = 20;
    static const int LINE_HEIGHT = 15;
    static const int PLAYER_OFFSET = 6;
    static const int IMPROVEMENT_SIZE = 6;
    static const int IMPROVEMENT_SPACING = 8;

    // Board layout
    static const char *board[];

    // Base coordinates for each board position (0-39)
    static const std::pair<int, int> BOARD_COORDS[40];

    // Helper methods
    void drawBoardBase();
    bool canHaveImprovements(int position) const;
};

#endif // WATOPOLY_DISPLAY_H