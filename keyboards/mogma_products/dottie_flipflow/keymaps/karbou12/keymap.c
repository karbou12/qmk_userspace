// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "us_keymap.h"
#include "us_keycodes.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┬───┐   ┌───┬───┬───┬───┬───┬───┐
      * │   │   │   │   │   │   │   │   │   │   │   │   │   │
      * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
      * │   │   │   │   │   │   │   │   │   │   │   │   │   │
      * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
      * │   │   │   │   │   │   │   │   │   │   │   │   │   │
      * └───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┘
      *     │   │   │   │   │   │   │   │   │   │   │   │
      *     └───┴───┴───┴───┴───┘   └───┴───┴───┴───┴───┘
      */

    [0] = LAYOUT_wrapper(
        WIN_QAZ40_BASE_LEFT_TOP,                  WIN_QAZ40_BASE_RIGHT_TOP,
        WIN_QAZ40_BASE_LEFT_MIDDLE,               WIN_QAZ40_BASE_RIGHT_MIDDLE,
        WIN_QAZ40_BASE_LEFT_BOTTOM,               WIN_QAZ40_BASE_RIGHT_BOTTOM,
        KC_NO, KC_NO, WIN_QAZ_BASE_LEFT_THUMBS,   WIN_QAZ_BASE_RIGHT_THUMBS, KC_NO, KC_NO
    ),

    [1] = LAYOUT_wrapper(
        WIN_QAZ40_RAISE_LEFT_TOP,                  WIN_QAZ40_RAISE_RIGHT_TOP,
        WIN_QAZ40_RAISE_LEFT_MIDDLE,               WIN_QAZ40_RAISE_RIGHT_MIDDLE,
        WIN_QAZ40_RAISE_LEFT_BOTTOM,               WIN_QAZ40_RAISE_RIGHT_BOTTOM,
        KC_NO, KC_NO, WIN_QAZ_RAISE_LEFT_THUMBS,   WIN_QAZ_RAISE_RIGHT_THUMBS, KC_NO, KC_NO
    ),

    [2] = LAYOUT_wrapper(
        WIN_QAZ40_LOWER_LEFT_TOP,                  WIN_QAZ40_LOWER_RIGHT_TOP,
        WIN_QAZ40_LOWER_LEFT_MIDDLE,               WIN_QAZ40_LOWER_RIGHT_MIDDLE,
        WIN_QAZ40_LOWER_LEFT_BOTTOM,               WIN_QAZ40_LOWER_RIGHT_BOTTOM,
        KC_NO, KC_NO, WIN_QAZ_LOWER_LEFT_THUMBS,   WIN_QAZ_LOWER_RIGHT_THUMBS, KC_NO, KC_NO
    ),

    [3] = LAYOUT_wrapper(
        WIN_QAZ40_ADJUST_LEFT_TOP,                  WIN_QAZ40_ADJUST_RIGHT_TOP,
        WIN_QAZ40_ADJUST_LEFT_MIDDLE,               WIN_QAZ40_ADJUST_RIGHT_MIDDLE,
        WIN_QAZ40_ADJUST_LEFT_BOTTOM,               WIN_QAZ40_ADJUST_RIGHT_BOTTOM,
        KC_NO, KC_NO, WIN_QAZ_ADJUST_LEFT_THUMBS,   WIN_QAZ_ADJUST_RIGHT_THUMBS, KC_NO, QK_BOOT
    ),

    [4] = LAYOUT_wrapper(
        MAC_QAZ40_BASE_LEFT_TOP,                  MAC_QAZ40_BASE_RIGHT_TOP,
        MAC_QAZ40_BASE_LEFT_MIDDLE,               MAC_QAZ40_BASE_RIGHT_MIDDLE,
        MAC_QAZ40_BASE_LEFT_BOTTOM,               MAC_QAZ40_BASE_RIGHT_BOTTOM,
        KC_NO, KC_NO, MAC_QAZ_BASE_LEFT_THUMBS,   MAC_QAZ_BASE_RIGHT_THUMBS, KC_NO, KC_NO
    ),

    [5] = LAYOUT_wrapper(
        MAC_QAZ40_RAISE_LEFT_TOP,                  MAC_QAZ40_RAISE_RIGHT_TOP,
        MAC_QAZ40_RAISE_LEFT_MIDDLE,               MAC_QAZ40_RAISE_RIGHT_MIDDLE,
        MAC_QAZ40_RAISE_LEFT_BOTTOM,               MAC_QAZ40_RAISE_RIGHT_BOTTOM,
        KC_NO, KC_NO, MAC_QAZ_RAISE_LEFT_THUMBS,   MAC_QAZ_RAISE_RIGHT_THUMBS, KC_NO, KC_NO
    ),

    [6] = LAYOUT_wrapper(
        MAC_QAZ40_LOWER_LEFT_TOP,                  MAC_QAZ40_LOWER_RIGHT_TOP,
        MAC_QAZ40_LOWER_LEFT_MIDDLE,               MAC_QAZ40_LOWER_RIGHT_MIDDLE,
        MAC_QAZ40_LOWER_LEFT_BOTTOM,               MAC_QAZ40_LOWER_RIGHT_BOTTOM,
        KC_NO, KC_NO, MAC_QAZ_LOWER_LEFT_THUMBS,   MAC_QAZ_LOWER_RIGHT_THUMBS, KC_NO, KC_NO
    ),

    [7] = LAYOUT_wrapper(
        MAC_QAZ40_ADJUST_LEFT_TOP,                  MAC_QAZ40_ADJUST_RIGHT_TOP,
        MAC_QAZ40_ADJUST_LEFT_MIDDLE,               MAC_QAZ40_ADJUST_RIGHT_MIDDLE,
        MAC_QAZ40_ADJUST_LEFT_BOTTOM,               MAC_QAZ40_ADJUST_RIGHT_BOTTOM,
        KC_NO, KC_NO, MAC_QAZ_ADJUST_LEFT_THUMBS,   MAC_QAZ_ADJUST_RIGHT_THUMBS, KC_NO, QK_BOOT
    )
};
