/*
 * Copyright (c) 2021 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include "debounce.h"

static uint32_t get_threshold(const struct debounce_state *state,
                              const struct debounce_config *config) {
    return state->pressed ? config->debounce_release_ms : config->debounce_press_ms;
}

bool debounce_update(struct debounce_state *state, const bool active,
                     const struct debounce_config *config) {
    // This uses a variation of the integrator debouncing described at
    // https://www.kennethkuhn.com/electronics/debounce.c
    // Every update where "active" does not match the current state, we increment
    // a counter, otherwise we decrement it. When the counter reaches a
    // threshold, the state flips and we reset the counter.
    if (active == state->pressed) {
        if (state->counter > 0) {
            state->counter--;
        }

        return false;
    }

    const uint32_t flip_threshold = get_threshold(state, config);

    if (state->counter < flip_threshold) {
        state->counter++;
        return false;
    }

    state->pressed = !state->pressed;
    state->counter = 0;
    return true;
}

bool debounce_is_active(const struct debounce_state *state) {
    return state->pressed || state->counter > 0;
}

bool debounce_is_pressed(const struct debounce_state *state) { return state->pressed; }
