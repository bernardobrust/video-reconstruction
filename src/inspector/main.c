#include <stdlib.h>

#include "platform.h"

int main() {
    platform_state state;
    if (!platform_init(&state, 0, 0, 300, 200)) return EXIT_FAILURE;

// TODO: Port these latter, keep as example
/*
    const char* msg = "Hello, World!";

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
*/

    platform_shutdown(&state);

    return EXIT_SUCCESS;
}