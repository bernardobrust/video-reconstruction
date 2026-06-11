#include <stdlib.h>
#include <stdio.h>

#include "platform.h"

int main() {
    platform_state state;
    if (!platform_init(&state, 0, 0, 300, 200)) return EXIT_FAILURE;

    while (platform_update(&state)) {
        // Update
        // Render
    }

    platform_shutdown(&state);
    return EXIT_SUCCESS;
}