#include "Display.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <vector>
#include "GameBoard.h"

Display::Display() {}

void Display::showBoard(const GameBoard& gameBoard) const {
    Display* d = XOpenDisplay(NULL);
    if (d == NULL) {
        std::cerr << "Cannot open display" << std::endl;
        return;
    }

    int s = DefaultScreen(d);
    Window w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 800, 800, 1,
                                   BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapWindow(d, w);

    GC gc = XCreateGC(d, w, 0, NULL);
    XSetForeground(d, gc, BlackPixel(d, s));
    
    XEvent e;
    while (1) {
        XNextEvent(d, &e);
        if (e.type == Expose) {
            // Draw the board
            XDrawRectangle(d, w, gc, 50, 50, 700, 700);
            XDrawString(d, w, gc, 100, 100, "WATOPOLY BOARD", 14);
        }
        if (e.type == KeyPress) break;
    }

    XFreeGC(d, gc);
    XCloseDisplay(d);
}

void Display::showPlayerAssets(const Player* player) const {
    std::cout << "Player: " << player->getName() << " (Symbol: " << player->getSymbol() << ")\n";
    std::cout << "Position: " << player->getPosition() << "\n";
    std::cout << "Money: $" << player->getCash() << "\n";
    std::cout << "Assets Value: $" << player->getAsset() << "\n";
    std::cout << "Owned Residences: " << player->getOwnedResidences() << "\n";
    std::cout << "Owned Gyms: " << player->getOwnedGyms() << "\n";
    std::cout << "Cups: " << player->getOwnedCups() << "\n";
    std::cout << "Properties: ";
    for (const auto& property : player->getProperties()) {
        std::cout << property->getName() << " ";
    }
    std::cout << "\n";
}

void Display::showAllPlayers(const std::vector<Player*>& players) const {
    for (const auto& player : players) {
        showPlayerAssets(player);
        std::cout << "------------------------------------\n";
    }
}

void Display::showMessage(const std::string& message) const {
    std::cout << message << std::endl;
}
