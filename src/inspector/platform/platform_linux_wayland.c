#include "platform.h"

#ifdef PLATFORM_LINUX_WAYLAND

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <btr_types.h>

typedef struct internal_state {
    // TODO
} internal_state;

// Rutic Wayland window
bool platform_init(
    platform_state* plat_state,
    u16 x,
    u16 y,
    u16 w,
    u16 h
) {
    plat_state->internal_state = malloc(sizeof(internal_state));
    internal_state* state = (internal_state*)plat_state->internal_state;

    // TODO

    return true;
}

bool platform_update(platform_state* plat_state) {
    internal_state* state = (internal_state*)plat_state->internal_state;

    const char* msg = "Hello, World!";

    // TODO

    // There's no way to fail for now
    return true;
}

void platform_shutdown(platform_state* plat_state) {
    internal_state* state = (internal_state*)plat_state->internal_state;

    // TODO

	free(state);
}

#endif