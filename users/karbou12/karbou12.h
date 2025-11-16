// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include "quantum.h"

extern void eeconfig_init_user_datablock(void);
extern void keyboard_post_init_user(void);
extern bool process_detected_host_os_user(os_variant_t detected_os);
extern layer_state_t default_layer_state_set_user(layer_state_t state);
extern layer_state_t layer_state_set_user(layer_state_t state);
extern bool process_record_user(uint16_t keycode, keyrecord_t *record);
extern void post_process_record_user(uint16_t keycode, keyrecord_t *record);
extern void caps_word_set_user(bool active);
extern bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record);
