// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "us_combo.h"

#ifdef CUSTOM_COMBO_ENABLE
void US_COMBO_keyboard_post_init_user(void) {
    // check already combo is there
    {
        vial_combo_entry_t combo = {0};
        if (dynamic_keymap_get_combo(0, &combo) < 0) {
            return;
        }

        const vial_combo_entry_t init_combo = {0};
        if (memcmp(&init_combo, &combo, sizeof(vial_combo_entry_t)) != 0) {
            return;
        }
    }

    extern combo_t key_combos[VIAL_COMBO_ENTRIES];
    extern uint16_t key_combos_keys[VIAL_COMBO_ENTRIES][5];

    for (uint8_t i = 0; i < km_combo_size; i++) {
        vial_combo_entry_t entry = {0};
        for (uint8_t j = 0; j < ARRAY_SIZE(entry.input); j++) {
            entry.input[j] = km_key_combos[i].keys[j];
            key_combos_keys[i][j] = km_key_combos[i].keys[j];
            if (km_key_combos[i].keys[j] == COMBO_END) {
                break;
            }
        }

        entry.output = km_key_combos[i].keycode;
        key_combos[i].keycode = km_key_combos[i].keycode;

        // set to eeprom
        if (dynamic_keymap_set_combo(i, &entry) < 0) {
            break;
        }
    }
}
#endif
