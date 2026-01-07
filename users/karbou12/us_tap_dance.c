// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "us_tap_dance.h"

#ifdef CUSTOM_TAP_DANCE_ENABLE
void US_TD_keyboard_post_init_user(void) {
    // check already tap dance is there
    {
        vial_tap_dance_entry_t td = {0};
        if (dynamic_keymap_get_tap_dance(0, &td) < 0) {
            return;
        }

        const vial_tap_dance_entry_t init_td = TAP_DANCE(KC_NO, KC_NO, KC_NO, KC_NO, TAPPING_TERM);
        if (memcmp(&init_td, &td, sizeof(vial_tap_dance_entry_t)) != 0) {
            return;
        }
    }

    // set to eeprom
    for (uint8_t i = 0; i < km_tap_dance_size; i++) {
        dynamic_keymap_set_tap_dance(i, &km_tap_dances[i]);
    }
}
#endif
