#include "watopoly-display.h"
#include <iostream>
#include <cstring>
#include <unistd.h>

// Board layout (ASCII art)
const char *WatopolyDisplay::board[] = {
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

// Base coordinates for each board position (0-39)
const std::pair<int, int> WatopolyDisplay::BOARD_COORDS[40] = {
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

WatopolyDisplay::WatopolyDisplay() {
    display = XOpenDisplay(NULL);
    if (!display) {
        throw std::runtime_error("Cannot open display");
    }

    int screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen),
                                100, 100, WIN_WIDTH, WIN_HEIGHT, 1,
                                BlackPixel(display, screen), WhitePixel(display, screen));
    XSelectInput(display, window, ExposureMask);
    XMapWindow(display, window);

    // Process initial events
    XFlush(display);
    XEvent event;
    while (XPending(display)) {
        XNextEvent(display, &event);
    }

    // Load font
    font = XLoadFont(display, "6x13");
    if (!font) font = XLoadFont(display, "fixed");

    gc = XCreateGC(display, window, 0, NULL);
    XSetFont(display, gc, font);
    XSetForeground(display, gc, BlackPixel(display, screen));
}

WatopolyDisplay::~WatopolyDisplay() {
    XFreeGC(display, gc);
    XCloseDisplay(display);
}

void WatopolyDisplay::draw() {
    drawBoard();
    XSync(display, False);  // Force immediate display update
}

void WatopolyDisplay::reset() {
    players.clear();
    improvements.clear();
    draw();
}

void WatopolyDisplay::addPlayer(char symbol, int position) {
    players[symbol] = position;
    draw();
}

void WatopolyDisplay::removePlayer(char symbol) {
    players.erase(symbol);
    draw();
}

void WatopolyDisplay::movePlayer(char symbol, int position) {
    if (players.find(symbol) != players.end()) {
        players[symbol] = position;
        draw();
    }
}

void WatopolyDisplay::addImprovement(int position) {
    if (improvements.find(position) != improvements.end()) {
        if (improvements[position] < 5) {
            improvements[position]++;
        }
    } else {
        improvements[position] = 1;
    }
    draw();
}

void WatopolyDisplay::removeImprovement(int position) {
    if (improvements.find(position) != improvements.end() && improvements[position] > 0) {
        improvements[position]--;
        draw();
    }
}

void WatopolyDisplay::setImprovements(int position, int count) {
    if (count >= 0 && count <= 5) {
        improvements[position] = count;
        draw();
    }
}

void WatopolyDisplay::drawPlayers() {
    std::map<int, int> position_counts; // Tracks how many players are at each position
    
    XSetForeground(display, gc, BlackPixel(display, DefaultScreen(display)));
    
    for (const auto &player : players) {
        if (player.second < 0 || player.second >= 40) continue;
        
        // Count players at this position
        int count = position_counts[player.second]++;
        if (count >= 6) continue; // Max 6 players per position
        
        // Calculate offset for this player
        int x_offset = count * PLAYER_OFFSET;
        
        // Get base coordinates
        int x = BOARD_COORDS[player.second].first + x_offset;
        int y = BOARD_COORDS[player.second].second;
        
        // Draw player symbol
        char symbolStr[2] = {player.first, '\0'};
        XDrawString(display, window, gc, x, y, symbolStr, 1);
    }
}

void WatopolyDisplay::drawImprovements() {
    XSetForeground(display, gc, BlackPixel(display, DefaultScreen(display)));
    
    for (const auto &imp : improvements) {
        int position = imp.first;
        int count = imp.second;
        
        if (count == 0) continue;
        
        // Get base coordinates for the building
        int x = BOARD_COORDS[position].first;
        int y = BOARD_COORDS[position].second - 15; // 15 pixels above the building
        
        // Draw each improvement
        for (int i = 0; i < count; i++) {
            int x_offset = i * IMPROVEMENT_SPACING;
            
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

void WatopolyDisplay::drawBoard() {
    XClearWindow(display, window);
    
    // Set text color
    XSetForeground(display, gc, BlackPixel(display, DefaultScreen(display)));
    
    // Draw board ASCII art
    for (int i = 0; i < sizeof(board)/sizeof(board[0]); i++) {
        XDrawString(display, window, gc, 
                   TEXT_X, 
                   TEXT_Y + (i * LINE_HEIGHT), 
                   board[i], 
                   strlen(board[i]));
    }
    
    // Draw game elements
    drawPlayers();
    drawImprovements();
    
    XFlush(display);
}