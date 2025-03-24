#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <vector>
#include <cstring>

const int CELL_SIZE = 50; // Size of each cell
const int GRID_WIDTH = 10;  // Adjust based on board size
const int GRID_HEIGHT = 10; // Adjust based on board size

void drawText(Display* display, Window window, GC gc, int x, int y, const char* text) {
    XDrawString(display, window, gc, x, y, text, std::strlen(text));
}

void drawGrid(Display* display, Window window, GC gc) {
    for (int i = 0; i <= GRID_WIDTH; ++i) {
        XDrawLine(display, window, gc, i * CELL_SIZE, 0, i * CELL_SIZE, GRID_HEIGHT * CELL_SIZE);
    }
    for (int i = 0; i <= GRID_HEIGHT; ++i) {
        XDrawLine(display, window, gc, 0, i * CELL_SIZE, GRID_WIDTH * CELL_SIZE, i * CELL_SIZE);
    }
}

int main() {
    Display* display = XOpenDisplay(nullptr);
    if (!display) {
        std::cerr << "Failed to open X display\n";
        return 1;
    }

    int screen = DefaultScreen(display);
    Window window = XCreateSimpleWindow(display, RootWindow(display, screen), 
                                        100, 100, GRID_WIDTH * CELL_SIZE, GRID_HEIGHT * CELL_SIZE, 
                                        1, BlackPixel(display, screen), WhitePixel(display, screen));

    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    GC gc = XCreateGC(display, window, 0, nullptr);
    XSetForeground(display, gc, BlackPixel(display, screen));

    XEvent event;
    while (true) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            drawGrid(display, window, gc);
            drawText(display, window, gc, 20, 30, "Goose Nesting");
        } else if (event.type == KeyPress) {
            break;
        }
    }

    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
    return 0;
}
