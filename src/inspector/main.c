#include <stdlib.h>

#include "platform.h"

int main() {
    platform_state state;
    if (!platform_init(&state, 0, 0, 300, 200)) return EXIT_FAILURE;

    platform_update(&state);

    platform_shutdown(&state);
    return EXIT_SUCCESS;
}