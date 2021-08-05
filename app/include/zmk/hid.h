/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <usb/usb_device.h>
#include <usb/class/usb_hid.h>

#include <zmk/keys.h>
#include <zmk/mouse.h>
#include <dt-bindings/zmk/hid_usage.h>
#include <dt-bindings/zmk/hid_usage_pages.h>

#define COLLECTION_REPORT 0x03

#define ZMK_HID_KEYBOARD_NKRO_SIZE 6

#define ZMK_HID_CONSUMER_NKRO_SIZE 6

static const uint8_t zmk_hid_report_desc[] = {
    /* USAGE_PAGE (Generic Desktop) */
    HID_GI_USAGE_PAGE, HID_USAGE_GD,
    /* USAGE (Keyboard) */
    HID_LI_USAGE, HID_USAGE_GD_KEYBOARD,
    /* COLLECTION (Application) */
    HID_MI_COLLECTION, COLLECTION_APPLICATION,
    /* REPORT ID (1) */
    HID_GI_REPORT_ID, 0x01,
    /* USAGE_PAGE (Keyboard/Keypad) */
    HID_GI_USAGE_PAGE, HID_USAGE_KEY,
    /* USAGE_MINIMUM (Keyboard LeftControl) */
    HID_LI_USAGE_MIN(1), HID_USAGE_KEY_KEYBOARD_LEFTCONTROL,
    /* USAGE_MAXIMUM (Keyboard Right GUI) */
    HID_LI_USAGE_MAX(1), HID_USAGE_KEY_KEYBOARD_RIGHT_GUI,
    /* LOGICAL_MINIMUM (0) */
    HID_GI_LOGICAL_MIN(1), 0x00,
    /* LOGICAL_MAXIMUM (1) */
    HID_GI_LOGICAL_MAX(1), 0x01,

    /* REPORT_SIZE (1) */
    HID_GI_REPORT_SIZE, 0x01,
    /* REPORT_COUNT (8) */
    HID_GI_REPORT_COUNT, 0x08,
    /* INPUT (Data,Var,Abs) */
    HID_MI_INPUT, 0x02,

    /* USAGE_PAGE (Keyboard/Keypad) */
    HID_GI_USAGE_PAGE, HID_USAGE_KEY,
    /* REPORT_SIZE (8) */
    HID_GI_REPORT_SIZE, 0x08,
    /* REPORT_COUNT (1) */
    HID_GI_REPORT_COUNT, 0x01,
    /* INPUT (Cnst,Var,Abs) */
    HID_MI_INPUT, 0x03,

    /* USAGE_PAGE (Keyboard/Keypad) */
    HID_GI_USAGE_PAGE, HID_USAGE_KEY,
    /* LOGICAL_MINIMUM (0) */
    HID_GI_LOGICAL_MIN(1), 0x00,
    /* LOGICAL_MAXIMUM (0xFF) */
    HID_GI_LOGICAL_MAX(1), 0xFF,
    /* USAGE_MINIMUM (Reserved) */
    HID_LI_USAGE_MIN(1), 0x00,
    /* USAGE_MAXIMUM (Keyboard Application) */
    HID_LI_USAGE_MAX(1), 0xFF,
    /* REPORT_SIZE (1) */
    HID_GI_REPORT_SIZE, 0x08,
    /* REPORT_COUNT (ZMK_HID_KEYBOARD_NKRO_SIZE) */
    HID_GI_REPORT_COUNT, ZMK_HID_KEYBOARD_NKRO_SIZE,
    /* INPUT (Data,Ary,Abs) */
    HID_MI_INPUT, 0x00,

    /* END_COLLECTION */
    HID_MI_COLLECTION_END,
    /* USAGE_PAGE (Consumer) */
    HID_GI_USAGE_PAGE, HID_USAGE_CONSUMER,
    /* USAGE (Consumer Control) */
    HID_LI_USAGE, HID_USAGE_CONSUMER_CONSUMER_CONTROL,
    /* Consumer Page */
    HID_MI_COLLECTION, COLLECTION_APPLICATION,
    /* REPORT ID (1) */
    HID_GI_REPORT_ID, 0x02,
    /* USAGE_PAGE (Consumer) */
    HID_GI_USAGE_PAGE, HID_USAGE_CONSUMER,
    /* LOGICAL_MINIMUM (0) */
    HID_GI_LOGICAL_MIN(1), 0x00,
    /* LOGICAL_MAXIMUM (0xFFFF) */
    HID_GI_LOGICAL_MAX(2), 0xFF, 0xFF, HID_LI_USAGE_MIN(1), 0x00,
    /* USAGE_MAXIMUM (0xFFFF) */
    HID_LI_USAGE_MAX(2), 0xFF, 0xFF,
    /* INPUT (Data,Ary,Abs) */
    /* REPORT_SIZE (16) */
    HID_GI_REPORT_SIZE, 0x10,
    /* REPORT_COUNT (ZMK_HID_CONSUMER_NKRO_SIZE) */
    HID_GI_REPORT_COUNT, ZMK_HID_CONSUMER_NKRO_SIZE, HID_MI_INPUT, 0x00,
    /* END COLLECTION */
    HID_MI_COLLECTION_END,

    0x05, 0x01,                                 /* Usage Page (Generic Desktop Ctrls) */
    0x09, 0x02,                                 /* Usage (Mouse) */
    0xA1, 0x01,                                 /* Collection (Application) */
    0x85, 0x04,                                 /*   Report ID (4) */
    0x09, 0x01,                                 /*   Usage (Pointer) */
    0xA1, 0x00,                                 /*   Collection (Physical) */
    0x05, 0x09,                                 /*     Usage Page (Button) */
    0x19, 0x01,                                 /*     Usage Minimum (0x01) */
    0x29, 0x10,                                 /*     Usage Maximum (0x10) */
    0x15, 0x00,                                 /*     Logical Minimum (0) */
    0x25, 0x01,                                 /*     Logical Maximum (1) */
    0x95, 0x10,                                 /*     Report Count (16) */
    0x75, 0x01,                                 /*     Report Size (1) */
    0x81, 0x02,                                 /*     Input (Data,Var,Abs,No Wrap,Linear,...) */
    0x05, 0x01,                                 /*     Usage Page (Generic Desktop Ctrls) */
    0x16, 0x01, 0x80,                           /*     Logical Minimum (-32767) */
    0x26, 0xFF, 0x7F,                           /*     Logical Maximum (32767) */
    0x75, 0x10,                                 /*     Report Size (8) */
    0x95, 0x02,                                 /*     Report Count (2) */
    0x09, 0x30,                                 /*     Usage (X) */
    0x09, 0x31,                                 /*     Usage (Y) */
    0x81, 0x06,                                 /*     Input (Data,Var,Rel,No Wrap,Linear,...) */
    0x15, 0x81,                                 /*     Logical Minimum (-127) */
    0x25, 0x7F,                                 /*     Logical Maximum (127) */
    0x75, 0x08,                                 /*     Report Count (8) */
    0x95, 0x01,                                 /*     Report Size (1) */
    0x09, 0x38,                                 /*     Usage (Wheel) */
    0x81, 0x06,                                 /*     Input (Data,Var,Rel,No Wrap,Linear,...) */
    0x05, 0x0C, /*     Usage Page (Consumer) */ // Horizontal wheel
    0x0A, 0x38, 0x02,                           /*     Usage (AC Pan) */
    0x15, 0x81,                                 /*     Logical Minimum (-127) */
    0x25, 0x7f,                                 /*     Logical Maximum (127) */
    0x95, 0x01,                                 /*     Report Count (1) */
    0x81, 0x06,                                 /*     Input (Data,Var,Rel,No Wrap,Linear,...) */
    0xC0,                                       /*   End Collection */
    0xC0,                                       /* End Collection */
};

// struct zmk_hid_boot_report
// {
//     uint8_t modifiers;
//     uint8_t _unused;
//     uint8_t keys[6];
// } __packed;

struct zmk_hid_keyboard_report_body {
    zmk_mod_flags_t modifiers;
    uint8_t _reserved;
    uint8_t keys[ZMK_HID_KEYBOARD_NKRO_SIZE];
} __packed;

struct zmk_hid_keyboard_report {
    uint8_t report_id;
    struct zmk_hid_keyboard_report_body body;
} __packed;

struct zmk_hid_consumer_report_body {
    uint16_t keys[ZMK_HID_CONSUMER_NKRO_SIZE];
} __packed;

struct zmk_hid_consumer_report {
    uint8_t report_id;
    struct zmk_hid_consumer_report_body body;
} __packed;

struct zmk_hid_mouse_report_body {
    zmk_mouse_button_flags_t buttons;
    int16_t x;
    int16_t y;
    int8_t wheel_vert;
    int8_t wheel_hor;
} __packed;

struct zmk_hid_mouse_report {
    uint8_t report_id;
    struct zmk_hid_mouse_report_body body;
} __packed;

zmk_mod_flags_t zmk_hid_get_explicit_mods();
int zmk_hid_register_mod(zmk_mod_t modifier);
int zmk_hid_unregister_mod(zmk_mod_t modifier);
int zmk_hid_register_mods(zmk_mod_flags_t explicit_modifiers);
int zmk_hid_unregister_mods(zmk_mod_flags_t explicit_modifiers);
int zmk_hid_implicit_modifiers_press(zmk_mod_flags_t implicit_modifiers);
int zmk_hid_implicit_modifiers_release();
int zmk_hid_keyboard_press(zmk_key_t key);
int zmk_hid_keyboard_release(zmk_key_t key);
void zmk_hid_keyboard_clear();

int zmk_hid_consumer_press(zmk_key_t key);
int zmk_hid_consumer_release(zmk_key_t key);
void zmk_hid_consumer_clear();

int zmk_hid_mouse_button_press(zmk_mouse_button_t button);
int zmk_hid_mouse_button_release(zmk_mouse_button_t button);
int zmk_hid_mouse_buttons_press(zmk_mouse_button_flags_t buttons);
int zmk_hid_mouse_buttons_release(zmk_mouse_button_flags_t buttons);
int zmk_hid_mouse_movement_press(int16_t x, int16_t y);
int zmk_hid_mouse_movement_release(int16_t x, int16_t y);
int zmk_hid_mouse_wheel_press(int8_t hor, int8_t vert);
int zmk_hid_mouse_wheel_release(int8_t hor, int8_t vert);
void zmk_hid_mouse_clear();

struct zmk_hid_keyboard_report *zmk_hid_get_keyboard_report();
struct zmk_hid_consumer_report *zmk_hid_get_consumer_report();
struct zmk_hid_mouse_report *zmk_hid_get_mouse_report();
