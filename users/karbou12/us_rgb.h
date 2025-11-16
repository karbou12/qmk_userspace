// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include "karbou12.h"
#include "us_eeconfig.h"

extern const rgblight_segment_t km_capsword_layer[];
extern const rgblight_segment_t km_reset_layer[];
extern const rgblight_segment_t km_turn_on_layer[];
extern const rgblight_segment_t km_turn_off_layer[];
extern const rgblight_segment_t km_set_default_layer[];
extern const rgblight_segment_t * const km_blink_layers[];
extern const rgblight_segment_t * const km_rgb_layers[];

typedef enum {
    US_BLINK_RESET = 0,
    US_BLINK_ON,
    US_BLINK_OFF,
    US_BLINK_DF
} us_blink_layer_e;

extern void US_RGB_eeconfig_migrate_mem(const us_user_config_u* bk, const uint32_t prev_ver);
extern void US_RGB_eeconfig_init_mem(void);
extern void US_RGB_keyboard_post_init_user(void);
extern layer_state_t US_RGB_default_layer_state_set_user(layer_state_t state);
extern layer_state_t US_RGB_layer_state_set_user(layer_state_t state);
extern bool US_RGB_process_record_user(uint16_t keycode, keyrecord_t *record);
extern void US_RGB_post_process_record_user(uint16_t keycode, keyrecord_t *record);
extern void US_RGB_caps_word_set_user(bool active);
