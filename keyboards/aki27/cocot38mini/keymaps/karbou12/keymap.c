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
        MAC_QAZ_ADJUST_LEFT_TOP,                            MAC_QAZ_ADJUST_RIGHT_TOP,
        MAC_QAZ_ADJUST_LEFT_MIDDLE,                         MAC_QAZ_ADJUST_RIGHT_MIDDLE,
        MAC_QAZ_ADJUST_LEFT_BOTTOM,                         MAC_QAZ_ADJUST_RIGHT_BOTTOM,
        MAC_QAZ_ADJUST_LEFT_THUMBS_WO_DF, QK_BOOT, KC_MUTE, MAC_QAZ_ADJUST_RIGHT_THUMBS
    ),

    [4] = LAYOUT_wrapper(
        QAZ_NONE,                               QAZ_NONE,
        QAZ_NONE,                               MS_BTN1, MS_BTN2, MS_BTN3, KC_NO, KC_RCTL,
        QAZ_NONE,                               KC_NO, KC_NO, KC_NO, KC_RALT, KC_RSFT,
        CPI_SW, SCRL_MO, MS_BTN1, KC_NO, KC_NO, MS_BTN2, KC_NO, KC_NO
    ),

    [5] = LAYOUT_wrapper(
        QAZ_NONE,                      QAZ_NONE,
        QAZ_NONE,                      QAZ_NONE,
        QAZ_NONE,                      QAZ_NONE,
        QAZ_NONE_THUMBS, KC_NO, KC_NO, QAZ_NONE_THUMBS
    ),

    [6] = LAYOUT_wrapper(
        QAZ_NONE,                      QAZ_NONE,
        QAZ_NONE,                      QAZ_NONE,
        QAZ_NONE,                      QAZ_NONE,
        QAZ_NONE_THUMBS, KC_NO, KC_NO, QAZ_NONE_THUMBS
    ),

    [7] = LAYOUT_wrapper(
        QAZ_NONE,                      QAZ_NONE,
        QAZ_NONE,                      QAZ_NONE,
        QAZ_NONE,                      QAZ_NONE,
        QAZ_NONE_THUMBS, KC_NO, KC_NO, QAZ_NONE_THUMBS
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = ENCODER_MS_WHEEL,
    [1] = ENCODER_MAC_ZOOM,
    [2] = ENCODER_BRIGHT,
    [3] = ENCODER_VOL,
    [4] = ENCODER_MS_WHEEL,
    [5] = ENCODER_NO,
    [6] = ENCODER_NO,
    [7] = ENCODER_NO,
};
#endif
