/*
 * Copyright (c) 2021 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <sys/util.h>

#define DEBOUNCE_COUNTER_BITS 14
#define DEBOUNCE_COUNTER_MAX BIT_MASK(DEBOUNCE_COUNTER_BITS)

struct debounce_state {
    bool pressed : 1;
    bool changed : 1;
    uint16_t counter : DEBOUNCE_COUNTER_BITS;
};

struct debounce_config {
    /** Duration a switch must be pressed to latch as pressed. */
    uint32_t debounce_press_ms;
    /** Duration a switch must be released to latch as released. */
    uint32_t debounce_release_ms;
};

/**
 * Debounces one switch.
 *
 * @note For the timings in "config" to be accurate, this currently assumes that
 * it is called at 1 ms intervals.
 *
 * @param state The state for the switch to debounce.
 * @param active Is the switch currently pressed?
 * @param config Debounce settings.
 *
 * @post If the pressed state changed, sets the "changed" flag so that the next
 * call to debounce_did_change() returns true.
 */
void debounce_update(struct debounce_state *state, const bool active,
                     const struct debounce_config *config);

/**
 * @returns whether the switch is either latched as pressed or it is potentially
 * pressed but the debouncer has not yet made a decision. If this returns true,
 * the kscan driver should continue to poll at 1 ms intervals.
 */
bool debounce_is_active(const struct debounce_state *state);

/**
 * @returns whether the switch is latched as pressed.
 */
bool debounce_is_pressed(const struct debounce_state *state);

/**
 * @returns the "changed" flag and clears it.
 */
bool debounce_did_change(struct debounce_state *state);
