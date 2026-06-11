#include "platform.h"

// TODO: compile based on makefile OS target

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <btr_types.h>

typedef struct internal_state {
    Display* display;
    i32 screen;
    Window window;
    GC graphics_context;
} internal_state;

// Rutic X11 window
bool platform_init(
    platform_state* plat_state,
    i32 x,
    i32 y,
    i32 w,
    i32 h
) {
    plat_state->internal_state = malloc(sizeof(internal_state));
    internal_state* state = (internal_state*)plat_state->internal_state;

    state->display = XOpenDisplay(NULL);
    if (state->display == NULL) {
      fprintf(stderr, "Cannot open display\n");
      return false;
    }

    state->screen = DefaultScreen(state->display);

    // For testing
    u64 black = BlackPixel(state->display, state->screen),
        white = WhitePixel(state->display, state->screen);

    state->window = XCreateSimpleWindow(state->display, DefaultRootWindow(state->display),
                x, y, w, h, 5, white, black);

    XSelectInput(state->display, state->window, ExposureMask | KeyPressMask);
    XMapWindow(state->display, state->window);

    state->graphics_context = XCreateGC(state->display, state->window, 0,0);

    XSetForeground(state->display, state->graphics_context, WhitePixel(state->display, state->screen));

    return true;
}

bool platform_update(platform_state* plat_state) {
    internal_state* state = (internal_state*)plat_state->internal_state;

    const char* msg = "Hello, World!";

    XEvent e;
    while (1) {
        XNextEvent(state->display, &e);

        if (e.type == Expose) {
            XFillRectangle(state->display, state->window, state->graphics_context, 20, 20, 10, 10);
            XDrawString(state->display, state->window, state->graphics_context, 10, 50, msg,
                strlen(msg));
        }

        if (e.type == KeyPress) break;
    }

    // There's no way to fail for now
    return true;
}

void platform_shutdown(platform_state* plat_state) {
    internal_state* state = (internal_state*)plat_state->internal_state;

    XCloseDisplay(state->display);
    XFreeGC(state->display, state->graphics_context);
	XDestroyWindow(state->display, state->window);
	free(state);
}