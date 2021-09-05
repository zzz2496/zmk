/*
 * Copyright (c) 2021 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <zephyr.h>
#include <dt-bindings/zmk/mouse.h>

typedef uint16_t zmk_mouse_button_flags_t;
typedef uint16_t zmk_mouse_button_t;

struct mouse_config {
    int delay_ms;
    int time_to_max_speed_ms;
    // acceleration exponent 0: uniform speed
    // acceleration exponent 1: uniform acceleration
    // acceleration exponent 2: uniform jerk
    int acceleration_exponent;
};

struct vector2d {
    float x;
    float y;
};

struct k_work_q *zmk_mouse_work_q();
int zmk_mouse_init();