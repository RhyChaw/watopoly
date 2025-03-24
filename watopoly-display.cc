/*
 * watopoly-display.cc - display the Watopoly board as shown in the assignment spec
 * using X11 graphics.
 */

#include <X11/Xlib.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define BORDER_WIDTH 2
#define CELL_SIZE 80

// Function to create a simple window
Window create_simple_window(Display* display, int width, int height, int x, int y) {
  int screen_num = DefaultScreen(display);
  int win_border_width = BORDER_WIDTH;
  Window win;

  // Create a simple window
  win = XCreateSimpleWindow(display, RootWindow(display, screen_num),
                          x, y, width, height, win_border_width,
                          BlackPixel(display, screen_num),
                          WhitePixel(display, screen_num));

  // Make the window actually appear on the screen
  XMapWindow(display, win);

  // Flush all pending requests to the X server
  XFlush(display);

  return win;
}

// Function to create a graphics context
GC create_gc(Display* display, Window win, int reverse_video, int dashed) {
  GC gc;
  unsigned long valuemask = 0;
  XGCValues values;
  unsigned int line_width = 1;
  int line_style = dashed ? LineOnOffDash : LineSolid; // Determine if dashed or solid line
  int cap_style = CapButt;
  int join_style = JoinBevel;
  int screen_num = DefaultScreen(display);

  gc = XCreateGC(display, win, valuemask, &values);
  if (gc == nullptr) {
    std::cerr << "XCreateGC: Failed to create GC" << std::endl;
    exit(1);
  }

  // Set foreground and background colors
  if (reverse_video) {
    XSetForeground(display, gc, WhitePixel(display, screen_num));
    XSetBackground(display, gc, BlackPixel(display, screen_num));
  } else {
    XSetForeground(display, gc, BlackPixel(display, screen_num));
    XSetBackground(display, gc, WhitePixel(display, screen_num));
  }

  // Define the style of lines
  XSetLineAttributes(display, gc, line_width, line_style, cap_style, join_style);

  // Define the fill style
  XSetFillStyle(display, gc, FillSolid);
  XSetDashes(display, gc, 0, "\4\4", 2); // Dash pattern (for dashed lines)

  return gc;
}

// Function to draw a cell with text
void draw_cell(Display* display, Window win, GC gc, XFontStruct* font_info, 
               int x, int y, int width, int height, const char* text) {
    // Draw rectangle
    XDrawRectangle(display, win, gc, x, y, width, height);
    
    // Draw text if provided
    if (text) {
        int text_width = XTextWidth(font_info, text, strlen(text));
        int font_height = font_info->ascent + font_info->descent;
        int text_x = x + (width - text_width) / 2;
        int text_y = y + (height + font_height) / 2;
        
        XDrawString(display, win, gc, text_x, text_y, text, strlen(text));
    }
}

// Function to draw a horizontal row of cells
void draw_horizontal_row(Display* display, Window win, GC gc, XFontStruct* font_info,
                         int x, int y, int cell_width, int cell_height, int num_cells,
                         const char* texts[], int dashed) {
    for (int i = 0; i < num_cells; i++) {
        draw_cell(display, win, gc, font_info, 
                  x + i * cell_width, y, cell_width, cell_height, 
                  texts ? texts[i] : nullptr);
    }
}

// Function to draw a vertical column of cells
void draw_vertical_column(Display* display, Window win, GC gc, XFontStruct* font_info,
                          int x, int y, int cell_width, int cell_height, int num_cells,
                          const char* texts[], int dashed) {
    for (int i = 0; i < num_cells; i++) {
        draw_cell(display, win, gc, font_info, 
                  x, y + i * cell_height, cell_width, cell_height, 
                  texts ? texts[i] : nullptr);
    }
}

int main(int argc, char* argv[]) {
    Display* display;
    Window win;
    GC gc;
    XFontStruct* font_info;
    const char* display_name = getenv("DISPLAY");
    const char* font_name = "fixed";
    
    // Open connection with the X server
    display = XOpenDisplay(display_name);
    if (display == nullptr) {
        std::cerr << argv[0] << ": Cannot connect to X server '" 
                  << (display_name ? display_name : "nullptr") << "'" << std::endl;
        exit(1);
    }
    
    // Create a window
    win = create_simple_window(display, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);
    
    // Create a graphics context for solid lines (top and bottom rows)
    gc = create_gc(display, win, 0, 1); // 0 for solid lines
    
    // Load font
    font_info = XLoadQueryFont(display, font_name);
    if (!font_info) {
        std::cerr << "XLoadQueryFont: Failed loading font '" << font_name << "'" << std::endl;
        exit(1);
    }
    
    // Set the font
    XSetFont(display, gc, font_info->fid);
    
    // Define colors
    Colormap cmap = DefaultColormap(display, DefaultScreen(display));
    XColor color;
    unsigned long colors[5];
    const char* color_names[5] = {"white", "black", "red", "green", "blue"};
    
    for (int i = 0; i < 5; i++) {
        XParseColor(display, cmap, color_names[i], &color);
        XAllocColor(display, cmap, &color);
        colors[i] = color.pixel;
    }
    
    // Setup Watopoly board
    int board_width = CELL_SIZE * 11;
    int board_height = CELL_SIZE * 11;
    int board_x = (WINDOW_WIDTH - board_width) / 2;
    int board_y = (WINDOW_HEIGHT - board_height) / 2;
    
    // Corner cell texts
    const char* corner_texts[4] = { 
        "DC TIMS LINE",
        "COLLECT OSAP",
        "GO TO TIMS", 
        "GOOSE NESTING", 
    };
    
    // Top row texts (from left to right)
    const char* top_row_texts[9] = {
        "EV1", "NEEDLES HALL", "EV2", "EV3", "V1", "PHYS", "B1", "CIF", "B2"
    };
    
    // Right column texts (from top to bottom)
    const char* right_col_texts[9] = {
        "EIT", "ESC", "SLC", "C2", "REV", "NEEDLES HALL", "MC",  "COOP FEE", "DC"
    };
    
    // Bottom row texts (from right to left)
    const char* bottom_row_texts[9] = {
        "AL", "SLC", "ML","TUITION", "MKV", "ECH", "NEEDLES HALL", "PAS", "HH"
    };
    
    // Left column texts (from bottom to top)
    const char* left_col_texts[9] = {
        "RCH", "PAC", "DWE", "CPH", "UWP", "LHI", "SLC", "BMH", "OPT"
    };
    
    // Draw the board outline
    XSetForeground(display, gc, colors[1]); // black
    XDrawRectangle(display, win, gc, board_x, board_y, board_width, board_height);
    
    // Draw corner cells
    draw_cell(display, win, gc, font_info, 
              board_x, board_y + board_height - CELL_SIZE, 
              CELL_SIZE, CELL_SIZE, corner_texts[0]);
    
    draw_cell(display, win, gc, font_info, 
              board_x + board_width - CELL_SIZE, board_y + board_height - CELL_SIZE, 
              CELL_SIZE, CELL_SIZE, corner_texts[1]);
    
    draw_cell(display, win, gc, font_info, 
              board_x + board_width - CELL_SIZE, board_y, 
              CELL_SIZE, CELL_SIZE, corner_texts[2]);
    
    draw_cell(display, win, gc, font_info, 
              board_x, board_y, 
              CELL_SIZE, CELL_SIZE, corner_texts[3]);
    
    // Draw top row (from left to right) as solid line
    gc = create_gc(display, win, 0, 0); // solid line
    draw_horizontal_row(display, win, gc, font_info,
                       board_x + CELL_SIZE, board_y, 
                       CELL_SIZE, CELL_SIZE, 9, top_row_texts, 0);
    
    // Draw right column (from top to bottom) as dotted line
    gc = create_gc(display, win, 0, 1); // solid line
    draw_vertical_column(display, win, gc, font_info,
        board_x + board_width - CELL_SIZE, board_y + CELL_SIZE,
        CELL_SIZE, CELL_SIZE, 9, right_col_texts, 0);
        
    // Draw bottom row (from right to left) as solid line
    gc = create_gc(display, win, 0, 0); // solid line
    for (int i = 0; i < 9; i++) {
        draw_cell(display, win, gc, font_info,
                 board_x + board_width - CELL_SIZE * (i + 2), board_y + board_height - CELL_SIZE,
                 CELL_SIZE, CELL_SIZE, bottom_row_texts[i]);
    }
    
    // Draw left column (from bottom to top) as dotted line
    gc = create_gc(display, win, 0, 1); // dotted line
    for (int i = 0; i < 9; i++) {
        draw_cell(display, win, gc, font_info,
                 board_x, board_y + board_height - CELL_SIZE * (i + 2),
                 CELL_SIZE, CELL_SIZE, left_col_texts[i]);
    }
    
    // Draw center Watopoly text
    XSetForeground(display, gc, colors[2]); // red
    const char* title = "WATOPOLY";
    int title_width = XTextWidth(font_info, title, strlen(title));
    int title_x = board_x + (board_width - title_width) / 2;
    int title_y = board_y + board_height / 2;
    XDrawString(display, win, gc, title_x, title_y, title, strlen(title));
    
    // Flush all pending requests to the X server
    XFlush(display);
    
    // Wait for user to press a key before exiting
    XEvent event;
    XNextEvent(display, &event);

    // Cleanup
    XFreeGC(display, gc);
    XFreeFont(display, font_info);
    XCloseDisplay(display);

    return 0;
}
