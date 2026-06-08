#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Rutic X11 window
    const char *msg = "Hello, World!";

    Display *display = XOpenDisplay(NULL);
    // Nice error handling
    if (display == NULL) {
      fprintf(stderr, "Cannot open display\n");
      exit(EXIT_FAILURE);
    }

    int screen = DefaultScreen(display);
    unsigned long black = BlackPixel(display, screen),
        white = WhitePixel(display, screen);
    Window window = XCreateSimpleWindow(display, DefaultRootWindow(display),
                0, 0, 200, 300, 5, white, black);

    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    GC graphics_context = XCreateGC(display, window, 0,0);
    // White text
    XSetForeground(display, graphics_context, WhitePixel(display, screen));

    XEvent e;
    while (1) {
        XNextEvent(display, &e);

        if (e.type == Expose) {
            XFillRectangle(display, window, graphics_context, 20, 20, 10, 10);
            XDrawString(display, window, graphics_context, 10, 50, msg,
                strlen(msg));
        }

        if (e.type == KeyPress) break;
    }

    // Clean up
    XCloseDisplay(display);
    XFreeGC(display, graphics_context);
	XDestroyWindow(display, window);
    return EXIT_SUCCESS;
}