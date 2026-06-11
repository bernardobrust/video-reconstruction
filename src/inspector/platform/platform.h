#pragma once

#include <btr_types.h>

/*
    Internal state contains data about the window, depends on OS so it's a
    void*.
*/
typedef struct platform_state {
    void* internal_state;
} platform_state;

/*
    Platform functions implementations are dispatched according to the OS
    specified during compilation.

    For now we just need windowing and events.
*/

// All startup code including window creation
// false return indicates fatal failure
bool platform_init(
    platform_state* plat_state,
    i32 x,
    i32 y,
    i32 w,
    i32 h
);

bool platform_update(platform_state* plat_state);

void platform_shutdown(platform_state* plat_state);