
/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <zephyr.h>
#include <zmk/event_manager.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

struct zmk_mouse_state_changed {
  uint32_t x;
  uint32_t y;
  bool state;
  int64_t timestamp;
};

ZMK_EVENT_DECLARE(zmk_mouse_state_changed);

static inline struct zmk_mouse_state_changed_event *
zmk_mouse_state_changed_from_encoded(uint32_t encoded, bool pressed,
                                     int64_t timestamp) {

  uint32_t x = (encoded & 0xFFFF0000) >> 16;
  uint32_t y = encoded & 0x0000FFFF;
  LOG_DBG("x: 0x%02X y: 0x%02X", x, y);
  zmk_hid_mouse_movement_release(x, y);

  return new_zmk_mouse_state_changed((struct zmk_mouse_state_changed){
      .x = x, .y = y, .state = pressed, .timestamp = timestamp});
}
