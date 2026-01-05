// Copyright 2025 takashicompany (@takashicompany)
// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "us_keymap.h"
#include "us_keycodes.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┬───┐            ┌───┬───┬───┬───┬───┬───┐
      * │ESC│ Q │ W │ E │ R │ T │            │ Y │ U │ I │ O │ P │BSP│
      * ├───┼───┼───┼───┼───┼───┤  ┌──────┐  ├───┼───┼───┼───┼───┼───┤
      * │CTL│ A │ S │ D │ F │ G │  │Center│  │ H │ J │ K │ L │ENT│ENT│
      * ├───┼───┼───┼───┼───┼───┤  └──────┘  ├───┼───┼───┼───┼───┼───┤
      * │SFT│ Z │ X │ C │ V │ B │            │ N │ M │ , │ . │BSP│DEL│
      * └───┴───┼───┼───┼───┼───┤            ├───┼───┼───┼───┼───┴───┘
      *         │CTL│GUI│LN2│TAB│            │SPC│LG1│ALT│GUI│
      *         └───┴───┴───┴───┘            └───┴───┴───┴───┘
      */

    [0] = LAYOUT_wrapper(
        MAC_QAZ40_BASE_LEFT_TOP,                  MAC_QAZ40_BASE_RIGHT_TOP,
        MAC_QAZ40_BASE_LEFT_MIDDLE,     KC_NO,    MAC_QAZ40_BASE_RIGHT_MIDDLE,
        MAC_QAZ40_BASE_LEFT_BOTTOM,               MAC_QAZ40_BASE_RIGHT_BOTTOM,
        MAC_QAZ_BASE_LEFT_THUMBS,   KC_NO, KC_NO, MAC_QAZ_BASE_RIGHT_THUMBS
    ),

    [1] = LAYOUT_wrapper(
        MAC_QAZ40_RAISE_LEFT_TOP,                  MAC_QAZ40_RAISE_RIGHT_TOP,
        MAC_QAZ40_RAISE_LEFT_MIDDLE,   USR_RESET,  MAC_QAZ40_RAISE_RIGHT_MIDDLE,
        MAC_QAZ40_RAISE_LEFT_BOTTOM,               MAC_QAZ40_RAISE_RIGHT_BOTTOM,
        MAC_QAZ_RAISE_LEFT_THUMBS,   KC_NO, KC_NO, MAC_QAZ_RAISE_RIGHT_THUMBS
    ),

    [2] = LAYOUT_wrapper(
        MAC_QAZ40_LOWER_LEFT_TOP,                  MAC_QAZ40_LOWER_RIGHT_TOP,
        MAC_QAZ40_LOWER_LEFT_MIDDLE,   USR_RESET,  MAC_QAZ40_LOWER_RIGHT_MIDDLE,
        MAC_QAZ40_LOWER_LEFT_BOTTOM,               MAC_QAZ40_LOWER_RIGHT_BOTTOM,
        MAC_QAZ_LOWER_LEFT_THUMBS,   KC_NO, KC_NO, MAC_QAZ_LOWER_RIGHT_THUMBS
    ),

    [3] = LAYOUT_wrapper(
        MAC_QAZ40_ADJUST_LEFT_TOP,                  MAC_QAZ40_ADJUST_RIGHT_TOP,
        MAC_QAZ40_ADJUST_LEFT_MIDDLE,   QK_BOOT,    MAC_QAZ40_ADJUST_RIGHT_MIDDLE,
        MAC_QAZ40_ADJUST_LEFT_BOTTOM,               MAC_QAZ40_ADJUST_RIGHT_BOTTOM,
        MAC_QAZ_ADJUST_LEFT_THUMBS,   KC_NO, KC_NO, MAC_QAZ_ADJUST_RIGHT_THUMBS
    ),

    [4] = LAYOUT_wrapper(
        WIN_QAZ40_BASE_LEFT_TOP,                  WIN_QAZ40_BASE_RIGHT_TOP,
        WIN_QAZ40_BASE_LEFT_MIDDLE,     KC_NO,    WIN_QAZ40_BASE_RIGHT_MIDDLE,
        WIN_QAZ40_BASE_LEFT_BOTTOM,               WIN_QAZ40_BASE_RIGHT_BOTTOM,
        WIN_QAZ_BASE_LEFT_THUMBS,   KC_NO, KC_NO, WIN_QAZ_BASE_RIGHT_THUMBS
    ),

    [5] = LAYOUT_wrapper(
        WIN_QAZ40_RAISE_LEFT_TOP,                  WIN_QAZ40_RAISE_RIGHT_TOP,
        WIN_QAZ40_RAISE_LEFT_MIDDLE,   USR_RESET,  WIN_QAZ40_RAISE_RIGHT_MIDDLE,
        WIN_QAZ40_RAISE_LEFT_BOTTOM,               WIN_QAZ40_RAISE_RIGHT_BOTTOM,
        WIN_QAZ_RAISE_LEFT_THUMBS,   KC_NO, KC_NO, WIN_QAZ_RAISE_RIGHT_THUMBS
    ),

    [6] = LAYOUT_wrapper(
        WIN_QAZ40_LOWER_LEFT_TOP,                  WIN_QAZ40_LOWER_RIGHT_TOP,
        WIN_QAZ40_LOWER_LEFT_MIDDLE,   USR_RESET,  WIN_QAZ40_LOWER_RIGHT_MIDDLE,
        WIN_QAZ40_LOWER_LEFT_BOTTOM,               WIN_QAZ40_LOWER_RIGHT_BOTTOM,
        WIN_QAZ_LOWER_LEFT_THUMBS,   KC_NO, KC_NO, WIN_QAZ_LOWER_RIGHT_THUMBS
    ),

    [7] = LAYOUT_wrapper(
        WIN_QAZ40_ADJUST_LEFT_TOP,                  WIN_QAZ40_ADJUST_RIGHT_TOP,
        WIN_QAZ40_ADJUST_LEFT_MIDDLE,   QK_BOOT,    WIN_QAZ40_ADJUST_RIGHT_MIDDLE,
        WIN_QAZ40_ADJUST_LEFT_BOTTOM,               WIN_QAZ40_ADJUST_RIGHT_BOTTOM,
        WIN_QAZ_ADJUST_LEFT_THUMBS,   KC_NO, KC_NO, WIN_QAZ_ADJUST_RIGHT_THUMBS
    ),

    [8] = LAYOUT_wrapper(
        QAZ40_NONE,                      QAZ40_NONE,
        QAZ40_NONE,           KC_NO,     QAZ40_NONE,
        QAZ40_NONE,                      QAZ40_NONE,
        QAZ_NONE_THUMBS, KC_NO, KC_NO, QAZ_NONE_THUMBS
    )
};

#ifdef COMBO_ENABLE
static const uint16_t PROGMEM km_combo1[] = COMBO_KEY_MS_ACL0;
static const uint16_t PROGMEM km_combo2[] = COMBO_KEY_MS_ACL2;
const combo_t km_key_combos[] = {
    COMBO(km_combo1, COMBO_OUT_MS_ACL0),
    COMBO(km_combo2, COMBO_OUT_MS_ACL2),
};
const uint16_t km_combo_size = ARRAY_SIZE(km_key_combos);
#endif
