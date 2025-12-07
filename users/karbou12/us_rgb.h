// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include "karbou12.h"
#include "us_eeconfig.h"

#if defined(RGBLIGHT_LAYERS) || defined(RGB_MATRIX_ENABLE)
#define HSV_LAYER_END_SEGMENTS {0, 0, 0}
#define HSV_LAYER_SEGMENTS(...) \
        { __VA_ARGS__, HSV_LAYER_END_SEGMENTS }
#define HSV_LAYERS_LIST(...) \
        { __VA_ARGS__, NULL }

extern const hsv_t km_hsv_capsword[];
extern const hsv_t * const km_hsv_layers[];

#ifdef RGBLIGHT_LAYER_BLINK
extern const rgblight_segment_t km_reset_layer[];
extern const rgblight_segment_t km_turn_on_layer[];
extern const rgblight_segment_t km_turn_off_layer[];
extern const rgblight_segment_t km_set_default_layer[];
extern const rgblight_segment_t * const km_blink_layers[];

typedef enum {
    US_BLINK_RESET = 0,
    US_BLINK_ON,
    US_BLINK_OFF,
    US_BLINK_DF
} us_blink_layer_e;
#endif

extern void US_RGB_eeconfig_init_mem(void);
extern void US_RGB_eeconfig_migrate_mem(const us_user_config_u* bk, const uint32_t prev_ver);
extern void US_RGB_keyboard_post_init_user(void);
extern layer_state_t US_RGB_default_layer_state_set_user(layer_state_t state);
extern layer_state_t US_RGB_layer_state_set_user(layer_state_t state);
extern bool US_RGB_process_record_user(uint16_t keycode, keyrecord_t *record);
extern void US_RGB_post_process_record_user(uint16_t keycode, keyrecord_t *record);
#ifdef CAPS_WORD_ENABLE
extern void US_RGB_caps_word_set_user(bool active);
#endif
#ifdef RGB_MATRIX_ENABLE
extern bool US_RGB_rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max);
#endif
#endif
