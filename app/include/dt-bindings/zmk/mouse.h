/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */
#pragma once

/* Mouse press behavior */
/* Left click */
#define MB1 (0x01)
#define LCLK (MB1)

/* Right click */
#define MB2 (0x02)
#define RCLK (MB2)

/* Middle click */
#define MB3 (0x04)
#define MCLK (MB3)

#define MB4 (0x08)

#define MB5 (0x10)

#define MB6 (0x20)

#define MB7 (0x40)

#define MB8 (0x80)

#define MB9 (0x0100)

#define MB10 (0x0200)

#define MB11 (0x0400)

#define MB12 (0x0800)

#define MB13 (0x1000)

#define MB14 (0x2000)

#define MB15 (0x4000)

#define MB16 (0x8000)

/* Mouse move behavior */

#define MOVE_UP (0x0000FFFF)

#define MOVE_DOWN (0x00000001)

#define MOVE_VERT(vert) ((vert * (INT16_MAX / 100)))

#define MOVE_LEFT (0xFFFF0000)

#define MOVE_RIGHT (0x00010000)

#define MOVE_HOR(hor) ((hor * (INT16_MAX / 100)) << 16)

#define MOVE(hor, vert) (((hor * (INT16_MAX / 100)) << 16) + ((vert * (INT16_MAX / 100))))

/* Mouse wheel behavior */

#define WHEEL_UP (0x0001)

#define WHEEL_DOWN (0x00FF)

#define WHEEL_LEFT (0xFF00)

#define WHEEL_RIGHT (0x0100)
