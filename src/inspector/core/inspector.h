#pragma once

#include <btr_types.h>

// Just window data for now
typedef struct inspector_config {
    u16 initial_x, initial_y, initial_w, initial_h;
} inspector_config;

bool inspector_create(inspector_config* config);
bool inspector_run();
bool inspector_shutdown();