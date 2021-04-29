/*
 * Copyright (c) 2021 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT zmk_behavior_mouse_move

#include <device.h>
#include <drivers/behavior.h>
#include <logging/log.h>

#include <zmk/event_manager.h>
#include <zmk/events/keycode_state_changed.h>
#include <zmk/behavior.h>
#include <zmk/events/mouse_state_changed.h>
#include <zmk/endpoints.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static int behavior_mouse_move_init(const struct device *dev) { return 0; };

static int mouse_is_moving_semaphore = 0;

void mouse_timer_cb(struct k_timer *dummy);

K_TIMER_DEFINE(mouse_timer, mouse_timer_cb, NULL);

void mouse_timer_cb(struct k_timer *dummy)
{
    if (mouse_is_moving_semaphore) {
        // considering that mouse report structure hasn't changed
        zmk_endpoints_send_mouse_report();
        k_timer_start(&mouse_timer, K_MSEC(10), K_NO_WAIT);
    }
}

static int on_keymap_binding_pressed(struct zmk_behavior_binding *binding,
                                     struct zmk_behavior_binding_event event) {
    LOG_DBG("position %d keycode 0x%02X", event.position, binding->param1);
    int res = ZMK_EVENT_RAISE(zmk_mouse_state_changed_from_encoded(binding->param1, true,
                                                                event.timestamp));
    mouse_is_moving_semaphore += 1;
    k_timer_start(&mouse_timer, K_MSEC(10), K_NO_WAIT);
    return res;
}

static int on_keymap_binding_released(struct zmk_behavior_binding *binding,
                                      struct zmk_behavior_binding_event event) {
    LOG_DBG("position %d keycode 0x%02X", event.position, binding->param1);

    // race condition?
    mouse_is_moving_semaphore -= 1;
    /* k_timer_stop(&mouse_timer); */
    return ZMK_EVENT_RAISE(zmk_mouse_state_changed_from_encoded(binding->param1, false,
                                                                event.timestamp));
}

static const struct behavior_driver_api behavior_mouse_move_driver_api = {
    .binding_pressed = on_keymap_binding_pressed, .binding_released = on_keymap_binding_released};

#define KP_INST(n)                                                                                 \
    DEVICE_AND_API_INIT(behavior_mouse_move_##n, DT_INST_LABEL(n), behavior_mouse_move_init, NULL, \
                        NULL, APPLICATION, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,                    \
                        &behavior_mouse_move_driver_api);

DT_INST_FOREACH_STATUS_OKAY(KP_INST)
