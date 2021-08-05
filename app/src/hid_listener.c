/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <drivers/behavior.h>
#include <logging/log.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/event_manager.h>
#include <zmk/events/keycode_state_changed.h>
#include <zmk/hid.h>
#include <dt-bindings/zmk/hid_usage_pages.h>
#include <zmk/endpoints.h>

static int hid_listener_keycode_pressed(const struct zmk_keycode_state_changed *ev) {
    int err;
    LOG_DBG("usage_page 0x%02X keycode 0x%02X implicit_mods 0x%02X explicit_mods 0x%02X",
            ev->usage_page, ev->keycode, ev->implicit_modifiers, ev->explicit_modifiers);
    switch (ev->usage_page) {
    case HID_USAGE_KEY:
        err = zmk_hid_keyboard_press(ev->keycode);
        if (err) {
            LOG_ERR("Unable to press keycode");
            return err;
        }
        break;
    case HID_USAGE_CONSUMER:
        err = zmk_hid_consumer_press(ev->keycode);
        if (err) {
            LOG_ERR("Unable to press keycode");
            return err;
        }
        break;
    }
    zmk_hid_register_mods(ev->explicit_modifiers);
    zmk_hid_implicit_modifiers_press(ev->implicit_modifiers);
    return zmk_endpoints_send_report(ev->usage_page);
}

static int hid_listener_keycode_released(const struct zmk_keycode_state_changed *ev) {
    int err;
    LOG_DBG("usage_page 0x%02X keycode 0x%02X implicit_mods 0x%02X explicit_mods 0x%02X",
            ev->usage_page, ev->keycode, ev->implicit_modifiers, ev->explicit_modifiers);
    switch (ev->usage_page) {
    case HID_USAGE_KEY:
        err = zmk_hid_keyboard_release(ev->keycode);
        if (err) {
            LOG_ERR("Unable to release keycode");
            return err;
        }
        break;
    case HID_USAGE_CONSUMER:
        err = zmk_hid_consumer_release(ev->keycode);
        if (err) {
            LOG_ERR("Unable to release keycode");
            return err;
        }
    }
    zmk_hid_unregister_mods(ev->explicit_modifiers);
    // There is a minor issue with this code.
    // If LC(A) is pressed, then LS(B), then LC(A) is released, the shift for B will be released
    // prematurely. This causes if LS(B) to repeat like Bbbbbbbb when pressed for a long time.
    // Solving this would require keeping track of which key's implicit modifiers are currently
    // active and only releasing modifiers at that time.
    zmk_hid_implicit_modifiers_release();
    return zmk_endpoints_send_report(ev->usage_page);
}

int hid_listener(const zmk_event_t *eh) {
    const struct zmk_keycode_state_changed *kc_ev = as_zmk_keycode_state_changed(eh);
    if (kc_ev) {
        if (kc_ev->state) {
            hid_listener_keycode_pressed(kc_ev);
        } else {
            hid_listener_keycode_released(kc_ev);
        }
        return 0;
    }
    return 0;
}

ZMK_LISTENER(hid_listener, hid_listener);
ZMK_SUBSCRIPTION(hid_listener, zmk_keycode_state_changed);