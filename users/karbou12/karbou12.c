// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "karbou12.h"
#include "us_tap_hold.h"
#include "us_eeconfig.h"
#include "us_key_override.h"
#include "us_os.h"
#include "us_rgb.h"
#include "us_pointing_device.h"
#include <quantum/nvm/eeprom/nvm_eeprom_eeconfig_internal.h> // for EECONFIG_USER

#ifdef USE_UINT16_KEYCODE_FOR_VIAL
uint16_t g_us_vial_keycode16 = KC_NO;
#endif

#ifdef CONSOLE_ENABLE
#if (EECONFIG_USER_DATA_CALC_SIZE) > 0
static uint32_t eeconfig_init_ver = 0;
static uint32_t post_init_ver = 0;
#endif
#endif

#ifdef POINTING_DEVICE_ENABLE
void matrix_init_kb(void) {
    US_PD_matrix_init_kb();
    matrix_init_user();
}

void eeconfig_init_kb(void) {
    US_PD_eeconfig_init_kb();
    eeconfig_init_user();
}

void pointing_device_init_kb(void) {
    US_PD_pointing_device_init_kb();
    // no need to call init_user() because it is called after init_kb() in eeconfig_init_quantum().
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    const layer_state_t ret_state = US_PD_layer_state_set_kb(state);
    return layer_state_set_user(ret_state);
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (!process_record_user(keycode, record)) {
        return false;
    } else if (!US_PD_process_record_kb(keycode, record)) {
        return false;
    }
    return true;
}

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    const report_mouse_t ret_mouse_report = US_PD_pointing_device_task_kb(mouse_report);
    return pointing_device_task_user(ret_mouse_report);
}

bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (!US_PD_is_mouse_record_kb(keycode, record)) {
        return false;
    }
    return is_mouse_record_user(keycode, record);
}
#endif

#if (EECONFIG_USER_DATA_CALC_SIZE) > 0
void eeconfig_init_user_datablock(void) {
#ifdef CONSOLE_ENABLE
    eeconfig_init_ver = eeprom_read_dword(EECONFIG_USER);
    uprintf("============================================================\n");
    uprintf("%s, def:%u, layer_state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state));
    uprintf("%s, eeconfig:%s, prev ver:%04lx, cur ver:%04x, vial:%lu\n",
            __FUNCTION__, eeconfig_is_user_datablock_valid() ? "valid" : "invalid", eeconfig_init_ver, EECONFIG_USER_DATA_VERSION, VIAL_PROTOCOL_VERSION);
#endif

    // init global memory
#if defined(RGBLIGHT_LAYERS) || defined(RGB_MATRIX_ENABLE)
    US_RGB_eeconfig_init_mem();
#endif
#ifdef OS_DETECTION_ENABLE
    US_OS_eeconfig_init_mem();
#endif

    US_DUMP_EECONFIG();

    // store global memory into eeprom user datablock
    US_EECONFIG_eeconfig_init_user_datablock();
}
#endif

void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
#if (EECONFIG_USER_DATA_CALC_SIZE) > 0
    post_init_ver = eeprom_read_dword(EECONFIG_USER);
#endif
    uprintf("============================================================\n");
    uprintf("%s, def:%u, layer_state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state));
#if (EECONFIG_USER_DATA_CALC_SIZE) > 0
    uprintf("%s, eeconfig:%s, prev ver:%04lx, cur ver:%04x, vial:%lu\n",
            __FUNCTION__, eeconfig_is_user_datablock_valid() ? "valid" : "invalid", post_init_ver, EECONFIG_USER_DATA_VERSION, VIAL_PROTOCOL_VERSION);
#endif
#endif

    US_DUMP_EECONFIG();

#if (EECONFIG_USER_DATA_CALC_SIZE) > 0
    if (!eeconfig_is_user_datablock_valid()) {
        if (!US_EECONFIG_migrate_user_datablock()) {
            eeconfig_init_user_datablock();
        }
    }

    // read eeprom user datablock into global memory
    US_EECONFIG_keyboard_post_init_user();
#endif

    US_DUMP_EECONFIG();

#ifdef CUSTOM_KEY_OVERRIDE_ENABLE
    US_KO_keyboard_post_init_user();
#endif

    // init rgblight
#if defined(RGBLIGHT_LAYERS) || defined(RGB_MATRIX_ENABLE)
    US_RGB_keyboard_post_init_user();
#endif

    US_DUMP_EECONFIG();
#ifdef CUSTOM_KEY_OVERRIDE_ENABLE
    vial_init();
#endif
}

#ifdef OS_DETECTION_ENABLE
bool process_detected_host_os_user(os_variant_t detected_os) {
#ifdef CONSOLE_ENABLE
    uprintf("============================================================\n");
    uprintf("%s, def:%u, layer_state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state));
    uprintf("%s, eeconfig:%s, prev ver:%04lx, cur ver:%04x, vial:%lu\n",
            __FUNCTION__, eeconfig_is_user_datablock_valid() ? "valid" : "invalid", eeprom_read_dword(EECONFIG_USER), EECONFIG_USER_DATA_VERSION, VIAL_PROTOCOL_VERSION);
    uprintf("%s, init ver:%04lx, post ver:%04lx\n", __FUNCTION__, eeconfig_init_ver, post_init_ver);
#endif

    US_DUMP_EECONFIG();

    if (!US_OS_process_detected_host_os_user(detected_os)) {
        return false;
    }

    return true;
}
#endif

layer_state_t default_layer_state_set_user(layer_state_t state) {
#if defined(RGBLIGHT_LAYERS) || defined(RGB_MATRIX_ENABLE)
    layer_state_t ret_state = US_RGB_default_layer_state_set_user(state);
    return ret_state;
#else
    return state;
#endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
#if defined(RGBLIGHT_LAYERS) || defined(RGB_MATRIX_ENABLE)
    layer_state_t ret_state = US_RGB_layer_state_set_user(state);
    return ret_state;
#else
    return state;
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!US_EECONFIG_process_record_user(keycode, record)) {
        return false;
#if defined(RGBLIGHT_LAYERS) || defined(RGB_MATRIX_ENABLE)
    } else if (!US_RGB_process_record_user(keycode, record)) {
        return false;
#endif
#ifdef OS_DETECTION_ENABLE
    } else if (!US_OS_process_record_user(keycode, record)) {
        return false;
#endif
    }
    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
#if defined(RGBLIGHT_LAYERS) || defined(RGB_MATRIX_ENABLE)
    US_RGB_post_process_record_user(keycode, record);
#endif
}

#ifdef CAPS_WORD_ENABLE
void caps_word_set_user(bool active) {
#if defined(RGBLIGHT_LAYERS) || defined(RGB_MATRIX_ENABLE)
    US_RGB_caps_word_set_user(active);
#endif
}
#endif

#ifdef CUSTOM_HOLD_ON_OTHER_KEY_PRESS_PER_KEY_ENABLE
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    return US_TH_get_hold_on_other_key_press(keycode, record);
}
#endif

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    return US_RGB_rgb_matrix_indicators_advanced_user(led_min, led_max);
}
#endif
