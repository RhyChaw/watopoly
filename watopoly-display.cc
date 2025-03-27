#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <vector>
#include <map>
#include <unistd.h>
#include <cstring>

// Board dimensions
const int WIN_WIDTH = 900;
const int WIN_HEIGHT = 700;
const int TEXT_X = 20;
const int TEXT_Y = 20;
const int LINE_HEIGHT = 15;
const int PLAYER_OFFSET = 6; // Space between players on same position
const int IMPROVEMENT_SIZE = 6; // Size of improvement squares
const int IMPROVEMENT_SPACING = 8; // Space between improvements

// Player pieces
const std::map<std::string, char> PLAYER_PIECES = {
    {"Goose", 'G'},
    {"GRT Bus", 'B'},
    {"Tim Hortons Doughnut", 'D'},
    {"Professor", 'P'},
    {"Student", 'S'},
    {"Money", '$'},
    {"Laptop", 'L'},
    {"Pink tie", 'T'}
};

// Board layout (same as before)
const char *board[] = {
    "_________________________________________________________________________________________",
    "|Goose  |       |NEEDLES|       |       |V1     |       |       |CIF    |       |GO TO  |",
    "|Nesting|-------|HALL   |-------|-------|       |-------|-------|       |-------|TIMS   |",
    "|       |EV1    |       |EV2    |EV3    |       |PHYS   |B1     |       |B2     |       |",
    "|       |       |       |       |       |       |       |       |       |       |       |",
    "|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|",
    "|       |                                                                       |       |",
    "|-------|                                                                       |-------|",
    "|OPT    |                                                                       |EIT    |",
    "|       |                                                                       |       |",
    "|_______|                                                                       |_______|",
    "|       |                                                                       |       |",
    "|-------|                                                                       |-------|",
    "|BMH    |                                                                       |ESC    |",
    "|       |                                                                       |       |",
    "|_______|                                                                       |_______|",
    "|SLC    |                                                                       |SLC    |",
    "|       |                                                                       |       |",
    "|       |                                                                       |       |",
    "|       |                                                                       |       |",
    "|_______|                                                                       |_______|",
    "|       |                                                                       |       |",
    "|-------|                                                                       |-------|",
    "|LHI    |                                                                       |C2     |",
    "|       |             _____________________________________________             |       |",
    "|_______|            |                                             |            |_______|",
    "|UWP    |            | #   #  ##  #####  ###  ###   ###  #   #   # |            |REV    |",
    "|       |            | #   # #  #   #   #   # #  # #   # #   #   # |            |       |",
    "|       |            | # # # ####   #   #   # ###  #   # #    # #  |            |       |",
    "|       |            | # # # #  #   #   #   # #    #   # #     #   |            |       |",
    "|_______|            | ##### #  #   #    ###  #     ###  ## #  #   |            |_______|",
    "|       |            |_____________________________________________|            |NEEDLES|",
    "|-------|                                                                       |HALL   |",
    "|CPH    |                                                                       |       |",
    "|       |                                                                       |       |",
    "|_______|                                                                       |_______|",
    "|       |                                                                       |       |",
    "|-------|                                                                       |-------|",
    "|DWE    |                                                                       |MC     |",
    "|       |                                                                       |       |",
    "|_______|                                                                       |_______|",
    "|PAC    |                                                                       |COOP   |",
    "|       |                                                                       |FEE    |",
    "|       |                                                                       |       |",
    "|_______|                                                                       |_______|",
    "|       |                                                                       |       |",
    "|-------|                                                                       |-------|",
    "|RCH    |                                                                       |DC     |",
    "|       |                                                                       |       |",
    "|_______|_______________________________________________________________________|_______|",
    "|DC Tims|       |       |NEEDLES|       |MKV    |TUITION|       |SLC    |       |COLLECT|",
    "|Line   |-------|-------|HALL   |-------|       |       |-------|       |-------|OSAP   |",
    "|       |HH     |PAS    |       |ECH    |       |       |ML     |       |AL     |       |",
    "|       |       |       |       |       |       |       |       |       |       |       |",
    "|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|"
};

struct Player {
    char symbol;
    int position; // 0-39
};

// Improvement data structure
struct Improvement {
    int count; // Number of improvements (0-5)
};

// Map of positions that can have improvements (1-based index)
std::map<int, Improvement> improvements = {
    {1, {0}}, {3, {0}}, {6, {0}}, {8, {0}}, {9, {0}}, {11, {0}}, {13, {0}}, {14, {0}},
    {16, {0}}, {18, {0}}, {19, {0}}, {21, {0}}, {23, {0}}, {24, {0}}, {26, {0}},
    {27, {0}}, {29, {0}}, {31, {0}}, {32, {0}}, {34, {0}}, {37, {0}}, {39, {0}}
};

std::vector<Player> players;

// Base coordinates for each board position (0-39)
const std::pair<int, int> BOARD_COORDS[40] = {
    // Top row (left to right, positions 0-10)
    {506, 829}, {458,829}, {410, 829}, {362, 829}, {314, 829},
    {266, 829}, {218, 829}, {170, 829}, {122, 829}, {74, 829}, {26, 829},
    
    // Right side (top to bottom, positions 11-19)
    {26, 754}, {26, 679}, {26, 618}, {26, 543}, {26, 468},
    {26, 393}, {26, 318}, {26, 243}, {26, 168},
    
    // Bottom row (right to left, positions 20-30)
    {26, 93}, {74, 93}, {122, 93}, {170, 93}, {218, 93}, 
    {266, 93}, {314, 93}, {362, 93}, {410, 93}, {458, 93},
    
    // Left side (bottom to top, positions 31-39)
    {506, 93}, {506, 168}, {506, 243}, {506, 318}, {506, 393},
    {506, 468}, {506, 543}, {506, 618}, {506, 679}, {506, 754}
};

void drawPlayers(Display *display, Window window, GC gc) {
    std::map<int, int> position_counts; // Tracks how many players are at each position
    
    XSetForeground(display, gc, BlackPixel(display, DefaultScreen(display)));
    
    for (const auto &player : players) {
        if (player.position < 0 || player.position >= 40) continue;
        
        // Count players at this position
        int count = position_counts[player.position]++;
        if (count >= 6) continue; // Max 6 players per position
        
        // Calculate offset for this player
        int x_offset = count * PLAYER_OFFSET;
        
        // Get base coordinates
        int x = BOARD_COORDS[player.position].first + x_offset;
        int y = BOARD_COORDS[player.position].second;
        
        // Draw player symbol
        char symbolStr[2] = {player.symbol, '\0'};
        XDrawString(display, window, gc, x, y, symbolStr, 1);
    }
}

void drawImprovements(Display *display, Window window, GC gc) {
    XSetForeground(display, gc, BlackPixel(display, DefaultScreen(display)));
    
    for (const auto &imp : improvements) {
        int position = imp.first; // 1-based index
        int count = imp.second.count;
        
        if (count == 0) continue;
        
        // Get base coordinates for the building
        int x = BOARD_COORDS[position].first;
        int y = BOARD_COORDS[position].second - 15; // 50 pixels above the building
        
        // Draw each improvement
        for (int i = 0; i < count; i++) {
            int x_offset = i * IMPROVEMENT_SPACING; // Space between improvements
            
            if (i == 4) { // 5th improvement (index 4) is filled square
                XFillRectangle(display, window, gc, 
                              x + x_offset, y - IMPROVEMENT_SIZE, 
                              IMPROVEMENT_SIZE+1, IMPROVEMENT_SIZE+1);
            } else { // First 4 improvements are empty squares
                XDrawRectangle(display, window, gc, 
                              x + x_offset, y - IMPROVEMENT_SIZE, 
                              IMPROVEMENT_SIZE, IMPROVEMENT_SIZE);
            }
        }
    }
}

// Function to add improvements to a building
void addImprovements(int position, int count) {
    if (improvements.find(position) == improvements.end()) {
        std::cerr << "Position " << position << " cannot have improvements." << std::endl;
        return;
    }
    
    int newCount = improvements[position].count + count;
    if (newCount > 5) {
        std::cerr << "Cannot have more than 5 improvements on a building." << std::endl;
        newCount = 5;
    }
    
    improvements[position].count = newCount;
}

int main() {
    Display *display = XOpenDisplay(NULL);
    if (!display) {
        std::cerr << "Cannot open display" << std::endl;
        return 1;
    }

    int screen = DefaultScreen(display);
    Window window = XCreateSimpleWindow(display, RootWindow(display, screen),
                                100, 100, WIN_WIDTH, WIN_HEIGHT, 1,
                                BlackPixel(display, screen), WhitePixel(display, screen));
    XSelectInput(display, window, ExposureMask);
    XMapWindow(display, window);

    // Load fixed-width font
    Font font = XLoadFont(display, "6x13");
    if (!font) font = XLoadFont(display, "fixed");

    GC gc = XCreateGC(display, window, 0, NULL);
    XSetFont(display, gc, font);
    XSetForeground(display, gc, BlackPixel(display, screen));

    // Create test players
    players.push_back({'G', 1});  // Goose at position 0

    // Test adding some improvements
    addImprovements(1, 4); // Add 4 improvements to position 1
    addImprovements(6, 5); // Add 5 improvements to position 6
    addImprovements(8, 2); // Add 2 improvements to position 8

    // Main event loop
    while (true) {
        XEvent event;
        XNextEvent(display, &event);

        if (event.type == Expose) {
            // Draw board
            for (int i = 0; i < sizeof(board)/sizeof(board[0]); i++) {
                XDrawString(display, window, gc, TEXT_X, TEXT_Y + i * LINE_HEIGHT, 
                           board[i], strlen(board[i]));
            }
            // Draw players
            drawPlayers(display, window, gc);
            // Draw improvements
            drawImprovements(display, window, gc);
        }
    }

    XFreeGC(display, gc);
    XCloseDisplay(display);
    return 0;
}
