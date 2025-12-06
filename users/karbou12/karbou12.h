// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include "quantum.h"

#if (EECONFIG_USER_DATA_CALC_SIZE) > 0
extern void eeconfig_init_user_datablock(void);
#endif

extern void keyboard_post_init_user(void);

#ifdef OS_DETECTION_ENABLE
extern bool process_detected_host_os_user(os_variant_t detected_os);
#endif

extern layer_state_t default_layer_state_set_user(layer_state_t state);
extern layer_state_t layer_state_set_user(layer_state_t state);
extern bool process_record_user(uint16_t keycode, keyrecord_t *record);
extern void post_process_record_user(uint16_t keycode, keyrecord_t *record);

#ifdef CAPS_WORD_ENABLE
extern void caps_word_set_user(bool active);
#endif

#ifdef CUSTOM_HOLD_ON_OTHER_KEY_PRESS_PER_KEY_ENABLE
extern bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record);
#endif
