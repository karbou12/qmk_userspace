/* Copyright 2020 foostan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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
      * ├───┼───┼───┼───┼───┼───┤   ├───┼───┼───┼───┼───┼───┤
      * │   │   │   │   │   │   │   │   │   │   │   │   │   │
      * └───┴───┴───┴───┴───┴───┘   └───┴───┴───┴───┴───┴───┘
      */

    [0] = LAYOUT_wrapper(
        MAC_NOR40_BASE_LEFT_TOP,                     MAC_NOR40_BASE_RIGHT_TOP,
        MAC_NOR40_BASE_LEFT_MIDDLE,                  MAC_NOR40_BASE_RIGHT_MIDDLE,
        MAC_NOR40_BASE_LEFT_BOTTOM,                  MAC_NOR40_BASE_RIGHT_BOTTOM,
        QAZ_NONE_THUMBS, MAC_QAZ_BASE_LEFT_THUMBS,   MAC_QAZ_BASE_RIGHT_THUMBS, QAZ_NONE_THUMBS
    ),

    [1] = LAYOUT_wrapper(
        MAC_NOR40_RAISE_LEFT_TOP,                     MAC_NOR40_RAISE_RIGHT_TOP,
        MAC_NOR40_RAISE_LEFT_MIDDLE,                  MAC_NOR40_RAISE_RIGHT_MIDDLE,
        MAC_NOR40_RAISE_LEFT_BOTTOM,                  MAC_NOR40_RAISE_RIGHT_BOTTOM,
        QAZ_NONE_THUMBS, MAC_QAZ_RAISE_LEFT_THUMBS,   MAC_QAZ_RAISE_RIGHT_THUMBS, QAZ_NONE_THUMBS
    ),

    [2] = LAYOUT_wrapper(
        MAC_NOR40_LOWER_LEFT_TOP,                     MAC_NOR40_LOWER_RIGHT_TOP,
        MAC_NOR40_LOWER_LEFT_MIDDLE,                  MAC_NOR40_LOWER_RIGHT_MIDDLE,
        MAC_NOR40_LOWER_LEFT_BOTTOM,                  MAC_NOR40_LOWER_RIGHT_BOTTOM,
        QAZ_NONE_THUMBS, MAC_QAZ_LOWER_LEFT_THUMBS,   MAC_QAZ_LOWER_RIGHT_THUMBS, QAZ_NONE_THUMBS
    ),

    [3] = LAYOUT_wrapper(
        MAC_NOR40_ADJUST_LEFT_TOP,                     MAC_NOR40_ADJUST_RIGHT_TOP,
        MAC_NOR40_ADJUST_LEFT_MIDDLE,                  MAC_NOR40_ADJUST_RIGHT_MIDDLE,
        MAC_NOR40_ADJUST_LEFT_BOTTOM,                  MAC_NOR40_ADJUST_RIGHT_BOTTOM,
        QAZ_NONE_THUMBS, MAC_QAZ_ADJUST_LEFT_THUMBS,   MAC_QAZ_ADJUST_RIGHT_THUMBS, KC_NO, KC_NO, QK_BOOT
    ),

    [4] = LAYOUT_wrapper(
        WIN_NOR40_BASE_LEFT_TOP,                     WIN_NOR40_BASE_RIGHT_TOP,
        WIN_NOR40_BASE_LEFT_MIDDLE,                  WIN_NOR40_BASE_RIGHT_MIDDLE,
        WIN_NOR40_BASE_LEFT_BOTTOM,                  WIN_NOR40_BASE_RIGHT_BOTTOM,
        QAZ_NONE_THUMBS, WIN_QAZ_BASE_LEFT_THUMBS,   WIN_QAZ_BASE_RIGHT_THUMBS, QAZ_NONE_THUMBS
    ),

    [5] = LAYOUT_wrapper(
        WIN_NOR40_RAISE_LEFT_TOP,                     WIN_NOR40_RAISE_RIGHT_TOP,
        WIN_NOR40_RAISE_LEFT_MIDDLE,                  WIN_NOR40_RAISE_RIGHT_MIDDLE,
        WIN_NOR40_RAISE_LEFT_BOTTOM,                  WIN_NOR40_RAISE_RIGHT_BOTTOM,
        QAZ_NONE_THUMBS, WIN_QAZ_RAISE_LEFT_THUMBS,   WIN_QAZ_RAISE_RIGHT_THUMBS, QAZ_NONE_THUMBS
    ),

    [6] = LAYOUT_wrapper(
        WIN_NOR40_LOWER_LEFT_TOP,                     WIN_NOR40_LOWER_RIGHT_TOP,
        WIN_NOR40_LOWER_LEFT_MIDDLE,                  WIN_NOR40_LOWER_RIGHT_MIDDLE,
        WIN_NOR40_LOWER_LEFT_BOTTOM,                  WIN_NOR40_LOWER_RIGHT_BOTTOM,
        QAZ_NONE_THUMBS, WIN_QAZ_LOWER_LEFT_THUMBS,   WIN_QAZ_LOWER_RIGHT_THUMBS, QAZ_NONE_THUMBS
    ),

    [7] = LAYOUT_wrapper(
        WIN_NOR40_ADJUST_LEFT_TOP,                     WIN_NOR40_ADJUST_RIGHT_TOP,
        WIN_NOR40_ADJUST_LEFT_MIDDLE,                  WIN_NOR40_ADJUST_RIGHT_MIDDLE,
        WIN_NOR40_ADJUST_LEFT_BOTTOM,                  WIN_NOR40_ADJUST_RIGHT_BOTTOM,
        QAZ_NONE_THUMBS, WIN_QAZ_ADJUST_LEFT_THUMBS,   WIN_QAZ_ADJUST_RIGHT_THUMBS, KC_NO, KC_NO, QK_BOOT
    ),
  };
