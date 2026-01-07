/*
Copyright 2024 aki27

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "quantum.h"
#include "us_keymap.h"
#include "us_keycodes.h"
#include "us_tap_dance.h"

#define COCOT_SCROLL_INV_DEFAULT false

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┐             ┌───┬───┬───┬───┬───┐
      * │   │   │   │   │   │             │   │   │   │   │   │
      * ├───┼───┼───┼───┼───┤             ├───┼───┼───┼───┼───┤
      * │   │   │   │   │   │             │   │   │   │   │   │
      * ├───┼───┼───┼───┼───┤             ├───┼───┼───┼───┼───┤
      * │   │   │   │   │   │             │   │   │   │   │   │
      * └───┴───┼───┼───┼───┤ ┌───┐ ┌───┐ ├───┼───┼───┼───┴───┘
      *         │   │   │   │ │ C │ │ E │ │   │   │   │
      *         └───┴───┴───┘ └───┘ └───┘ └───┴───┴───┘
      */

    [0] = LAYOUT_wrapper(
        MAC_QAZ_BASE_LEFT_TOP,                    MAC_QAZ_BASE_RIGHT_TOP,
        MAC_QAZ_BASE_LEFT_MIDDLE,                 MAC_QAZ_BASE_RIGHT_MIDDLE,
        MAC_QAZ_BASE_LEFT_BOTTOM,                 MAC_QAZ_BASE_RIGHT_BOTTOM,
        MAC_QAZ_BASE_LEFT_THUMBS, KC_NO, MS_BTN1, MAC_QAZ_BASE_RIGHT_THUMBS
    ),

    [1] = LAYOUT_wrapper(
        MAC_QAZ_RAISE_LEFT_TOP,                        MAC_QAZ_RAISE_RIGHT_TOP,
        MAC_QAZ_RAISE_LEFT_MIDDLE,                     MAC_QAZ_RAISE_RIGHT_MIDDLE,
        MAC_QAZ_RAISE_LEFT_BOTTOM,                     MAC_QAZ_RAISE_RIGHT_BOTTOM,
        MAC_QAZ_RAISE_LEFT_THUMBS, KC_NO, LGUI(KC_P0), MAC_QAZ_RAISE_RIGHT_THUMBS
    ),

    [2] = LAYOUT_wrapper(
        MAC_QAZ_LOWER_LEFT_TOP,                  MAC_QAZ_LOWER_RIGHT_TOP,
        MAC_QAZ_LOWER_LEFT_MIDDLE,               MAC_QAZ_LOWER_RIGHT_MIDDLE,
        MAC_QAZ_LOWER_LEFT_BOTTOM,               MAC_QAZ_LOWER_RIGHT_BOTTOM,
        MAC_QAZ_LOWER_LEFT_THUMBS, KC_NO, KC_NO, MAC_QAZ_LOWER_RIGHT_THUMBS
    ),

    [3] = LAYOUT_wrapper(
        MAC_QAZ_ADJUST_LEFT_TOP,                      MAC_QAZ_ADJUST_RIGHT_TOP,
        MAC_QAZ_ADJUST_LEFT_MIDDLE,                   MAC_QAZ_ADJUST_RIGHT_MIDDLE,
        MAC_QAZ_ADJUST_LEFT_BOTTOM,                   MAC_QAZ_ADJUST_RIGHT_BOTTOM,
        MAC_QAZ_ADJUST_LEFT_THUMBS, QK_BOOT, KC_MUTE, MAC_QAZ_ADJUST_RIGHT_THUMBS
    ),

    [4] = LAYOUT_wrapper(
        WIN_QAZ_BASE_LEFT_TOP,                    WIN_QAZ_BASE_RIGHT_TOP,
        WIN_QAZ_BASE_LEFT_MIDDLE,                 WIN_QAZ_BASE_RIGHT_MIDDLE,
        WIN_QAZ_BASE_LEFT_BOTTOM,                 WIN_QAZ_BASE_RIGHT_BOTTOM,
        WIN_QAZ_BASE_LEFT_THUMBS, KC_NO, MS_BTN1, WIN_QAZ_BASE_RIGHT_THUMBS
    ),

    [5] = LAYOUT_wrapper(
        WIN_QAZ_RAISE_LEFT_TOP,                        WIN_QAZ_RAISE_RIGHT_TOP,
        WIN_QAZ_RAISE_LEFT_MIDDLE,                     WIN_QAZ_RAISE_RIGHT_MIDDLE,
        WIN_QAZ_RAISE_LEFT_BOTTOM,                     WIN_QAZ_RAISE_RIGHT_BOTTOM,
        WIN_QAZ_RAISE_LEFT_THUMBS, KC_NO, LCTL(KC_0),  WIN_QAZ_RAISE_RIGHT_THUMBS
    ),

    [6] = LAYOUT_wrapper(
        WIN_QAZ_LOWER_LEFT_TOP,                  WIN_QAZ_LOWER_RIGHT_TOP,
        WIN_QAZ_LOWER_LEFT_MIDDLE,               WIN_QAZ_LOWER_RIGHT_MIDDLE,
        WIN_QAZ_LOWER_LEFT_BOTTOM,               WIN_QAZ_LOWER_RIGHT_BOTTOM,
        WIN_QAZ_LOWER_LEFT_THUMBS, KC_NO, KC_NO, WIN_QAZ_LOWER_RIGHT_THUMBS
    ),

    [7] = LAYOUT_wrapper(
        WIN_QAZ_ADJUST_LEFT_TOP,                      WIN_QAZ_ADJUST_RIGHT_TOP,
        WIN_QAZ_ADJUST_LEFT_MIDDLE,                   WIN_QAZ_ADJUST_RIGHT_MIDDLE,
        WIN_QAZ_ADJUST_LEFT_BOTTOM,                   WIN_QAZ_ADJUST_RIGHT_BOTTOM,
        WIN_QAZ_ADJUST_LEFT_THUMBS, QK_BOOT, KC_MUTE, WIN_QAZ_ADJUST_RIGHT_THUMBS
    ),

    [8] = LAYOUT_wrapper(
        QAZ_NONE,                               QAZ_NONE,
        QAZ_NONE,                               MS_BTN1, MS_BTN2, MS_BTN3, KC_NO, KC_RCTL,
        QAZ_NONE,                               KC_NO, KC_NO, KC_NO, KC_RALT, KC_RSFT,
        CPI_SW, TD(0), MS_BTN1, KC_NO, KC_NO, MS_BTN2, KC_NO, KC_NO
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = ENCODER_MS_WHEEL,
    [1] = ENCODER_MAC_ZOOM,
    [2] = ENCODER_BRIGHT,
    [3] = ENCODER_VOL,
    [4] = ENCODER_MS_WHEEL,
    [5] = ENCODER_WIN_ZOOM,
    [6] = ENCODER_BRIGHT,
    [7] = ENCODER_VOL,
    [8] = ENCODER_MS_WHEEL,
};
#endif

#ifdef COMBO_ENABLE
static const uint16_t PROGMEM km_combo1[] = COMBO_KEY_MS_ACL0;
static const uint16_t PROGMEM km_combo2[] = COMBO_KEY_MS_ACL2;
const combo_t km_key_combos[] = {
    COMBO(km_combo1, COMBO_OUT_MS_ACL0),
    COMBO(km_combo2, COMBO_OUT_MS_ACL2),
};
const uint16_t km_combo_size = ARRAY_SIZE(km_key_combos);
#endif

#ifdef TAP_DANCE_ENABLE
const vial_tap_dance_entry_t km_tap_dances[] = {
    TAP_DANCE(LCTL(KC_UP), SCRL_MO, LCTL(KC_DOWN), KC_NO, 200)
};
const uint16_t km_tap_dance_size = ARRAY_SIZE(km_tap_dances);
#endif
