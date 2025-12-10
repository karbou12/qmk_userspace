// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "config.h"
#include "us_eeconfig.h"
#include "us_keycodes.h"
#include "us_rgb.h"
#include "us_os.h"
#include "us_pointing_device.h"
#include <quantum/nvm/eeprom/nvm_eeprom_eeconfig_internal.h> // for EECONFIG_USER

#ifdef POINTING_DEVICE_ENABLE
us_kb_config_t us_kb_config = {0};
#endif

#if (EECONFIG_USER_DATA_CALC_SIZE) > 0
us_user_config_t us_user_config = {0};
#endif

#ifdef CONSOLE_ENABLE
static void parse_version(const uint32_t version, uint16_t* parsed_version) {
    *parsed_version = version & 0xF;
    parsed_version++;
    *parsed_version = (version >> US_FW_VER_MINOR_OFFSET) & 0xF;
    parsed_version++;
    *parsed_version = (version >> US_FW_VER_MAJOR_OFFSET) & 0xFF;
}

void us_dump_eeconfig(const char* const func) {
    uint16_t version[3] = {0};

#ifdef POINTING_DEVICE_ENABLE
    parse_version(EECONFIG_KB_DATA_VERSION, version);
    uprintf("------------------------------------------------------------\n");
    uprintf("%s DUMP EEPROM KB DATA. ver:%04x (%u.%u.%u), size:%u, defined size:%u\n",
            func, EECONFIG_KB_DATA_VERSION, version[2], version[1], version[0],
            sizeof(us_kb_config), EECONFIG_KB_DATA_SIZE);
    uprintf("cpi_idx:%u, scrl_div:%u, rotation_angle:%u\n",
             us_kb_config.pd.cpi_idx, us_kb_config.pd.scrl_div, us_kb_config.pd.rotation_angle);
    uprintf("auto_mouse:%s\n", us_kb_config.pd.flags.auto_mouse ? "true" : "false");
    uprintf("scrl_inv:%s\n", us_kb_config.pd.flags.scrl_inv ? "true" : "false");
#endif

    parse_version(EECONFIG_USER_DATA_VERSION, version);
    uprintf("------------------------------------------------------------\n");
    uprintf("%s DUMP EEPROM USER DATA. ver:%04x (%u.%u.%u), size:%u, defined size:%u\n",
            func, EECONFIG_USER_DATA_VERSION, version[2], version[1], version[0],
            sizeof(us_user_config), EECONFIG_USER_DATA_SIZE);
#if defined(RGBLIGHT_LAYERS) || defined(CUSTOM_RGBMATRIX)
    us_hsvm_t* p = us_user_config.rgb.hsvm_layer;
    for (uint8_t i = 0; i < ARRAY_SIZE(us_user_config.rgb.hsvm_layer); i++, p++) {
        uprintf("id:%u, hue:%u, sat:%u, val:%u, mode:%u\n", i, p->hsv.h, p->hsv.s, p->hsv.v, p->mode);
    }
    uprintf("is_rgb_per_layer:%s\n", us_user_config.rgb.flags.is_rgb_per_layer ? "true" : "false");
    uprintf("is_auto_save_rgb:%s\n", us_user_config.rgb.flags.is_auto_save_rgb ? "true" : "false");
    uprintf("to_retain_val:%s\n", us_user_config.rgb.flags.to_retain_val ? "true" : "false");
#endif

#ifdef OS_DETECTION_ENABLE
    us_user_config_field_e* p_os = us_user_config.os.os_default_layer;
    for (uint8_t i = 0; i < ARRAY_SIZE(us_user_config.os.os_default_layer); i++, p_os++) {
        uprintf("id:%u, default layer:%u\n", i, *p_os);
    }
#endif
}
#endif

#if defined(RGBLIGHT_LAYERS) || defined(CUSTOM_RGBMATRIX) || defined(OS_DETECTION_ENABLE)
static uint32_t us_get_offset(const us_user_config_field_e field) {
    switch (field) {
#if defined(RGBLIGHT_LAYERS) || defined(CUSTOM_RGBMATRIX)
        case US_FIELD_LAYER0 ... (ARRAY_SIZE(us_user_config.rgb.hsvm_layer) - 1):
            return sizeof(us_hsvm_t) * field;
        case US_FIELD_FLAGS:
            return sizeof(us_hsvm_t) * ARRAY_SIZE(us_user_config.rgb.hsvm_layer);
#endif
#ifdef OS_DETECTION_ENABLE
        case US_FIELD_OS_UNSURE ... US_FIELD_OS_IOS:
#if defined(RGBLIGHT_LAYERS) || defined(CUSTOM_RGBMATRIX)
            return sizeof(us_hsvm_t) * ARRAY_SIZE(us_user_config.rgb.hsvm_layer) +
                   sizeof(uint8_t) +
                   sizeof(us_user_config_field_e) * (field - US_FIELD_OS_UNSURE);
#else
            return sizeof(us_user_config_field_e) * (field - US_FIELD_OS_UNSURE);
#endif
#endif
        default :
            return 0;
    }
}
#endif

#ifdef POINTING_DEVICE_ENABLE
uint8_t US_EECONFIG_get_pd_cpi_idx_from_mem(void) {
    return us_kb_config.pd.cpi_idx;
}

void US_EECONFIG_update_pd_cpi_idx_to_eeprom(const uint8_t cpi_idx) {
    us_kb_config.pd.cpi_idx = cpi_idx;
    eeconfig_update_kb_datablock_field(us_kb_config.pd, cpi_idx);
}

uint8_t US_EECONFIG_get_pd_scrl_div_from_mem(void) {
    return us_kb_config.pd.scrl_div;
}

void US_EECONFIG_update_pd_scrl_div_to_eeprom(const uint8_t scrl_div) {
    us_kb_config.pd.scrl_div = scrl_div;
    eeconfig_update_kb_datablock_field(us_kb_config.pd, scrl_div);
}

uint8_t US_EECONFIG_get_pd_rotation_angle_from_mem(void) {
    return us_kb_config.pd.rotation_angle;
}

void US_EECONFIG_update_pd_rotation_angle_to_eeprom(const uint8_t rotation_angle) {
    us_kb_config.pd.rotation_angle = rotation_angle;
    eeconfig_update_kb_datablock_field(us_kb_config.pd, rotation_angle);
}

bool US_EECONFIG_get_pd_auto_mouse_from_mem(void) {
    return us_kb_config.pd.flags.auto_mouse;
}

void US_EECONFIG_update_pd_auto_mouse_to_eeprom(const bool auto_mouse) {
    us_kb_config.pd.flags.auto_mouse = auto_mouse;
    eeconfig_update_kb_datablock_field(us_kb_config.pd, flag_raw);
}

bool US_EECONFIG_get_pd_scrl_inv_from_mem(void) {
    return us_kb_config.pd.flags.scrl_inv;
}

void US_EECONFIG_update_pd_scrl_inv_to_eeprom(const bool scrl_inv) {
    us_kb_config.pd.flags.scrl_inv = scrl_inv;
    eeconfig_update_kb_datablock_field(us_kb_config.pd, flag_raw);
}
#endif

#if defined(RGBLIGHT_LAYERS) || defined(CUSTOM_RGBMATRIX)
const us_hsvm_t* US_EECONFIG_get_hsvm_layer_from_mem(const us_user_config_field_e field) {
    if (sizeof(us_user_config.rgb.hsvm_layer) <= field) {
        return NULL;
    }
    return &us_user_config.rgb.hsvm_layer[field];
}

void US_EECONFIG_update_hsvm_layer_to_eeprom(const us_user_config_field_e field, const us_hsvm_t* hsvm_layer) {
    if (sizeof(us_user_config.rgb.hsvm_layer) <= field) {
        return;
    }
    us_user_config.rgb.hsvm_layer[field] = *hsvm_layer;
    eeconfig_update_user_datablock(hsvm_layer, us_get_offset(field), sizeof(us_hsvm_t));
}

bool US_EECONFIG_get_rgb_per_layer_from_mem(void) {
    return us_user_config.rgb.flags.is_rgb_per_layer;
}

void US_EECONFIG_update_rgb_per_layer_to_eeprom(const bool is_rgb_per_layer) {
    us_user_config.rgb.flags.is_rgb_per_layer = is_rgb_per_layer;
    eeconfig_update_user_datablock(&us_user_config.rgb.flag_raw, us_get_offset(US_FIELD_FLAGS), sizeof(uint8_t));
}

bool US_EECONFIG_get_auto_save_rgb_from_mem(void) {
    return us_user_config.rgb.flags.is_auto_save_rgb;
}

void US_EECONFIG_update_auto_save_rgb_to_eeprom(const bool is_auto_save_rgb) {
    us_user_config.rgb.flags.is_auto_save_rgb = is_auto_save_rgb;
    eeconfig_update_user_datablock(&us_user_config.rgb.flag_raw, us_get_offset(US_FIELD_FLAGS), sizeof(uint8_t));
}

bool US_EECONFIG_get_retain_val_from_mem(void) {
    return us_user_config.rgb.flags.to_retain_val;
}

void US_EECONFIG_update_retain_val_to_eeprom(const bool to_retain_val) {
    us_user_config.rgb.flags.to_retain_val = to_retain_val;
    eeconfig_update_user_datablock(&us_user_config.rgb.flag_raw, us_get_offset(US_FIELD_FLAGS), sizeof(uint8_t));
}
#endif

#ifdef OS_DETECTION_ENABLE
us_user_config_field_e US_EECONFIG_get_os_default_layer_from_mem() {
    const os_variant_t os = detected_host_os();
    switch (os) {
        case OS_UNSURE ... OS_IOS:
            return us_user_config.os.os_default_layer[os];
        default:
            return US_FIELD_LAYER0;
    }
}

void US_EECONFIG_update_os_default_layer_to_eeprom(const us_user_config_field_e field) {
    const os_variant_t os = detected_host_os();
    if ((sizeof(us_user_config.os.os_default_layer) <= os) || (DYNAMIC_KEYMAP_LAYER_COUNT <= field)) {
        return;
    }

    us_user_config.os.os_default_layer[os] = field;
    const us_user_config_field_e os_field = US_FIELD_OS_UNSURE + os;
    eeconfig_update_user_datablock(&field, us_get_offset(os_field), sizeof(field));
}
#endif

#if (EECONFIG_KB_DATA_SIZE) > 0
bool US_EECONFIG_migrate_kb_datablock(void) {
    const uint32_t prev_ver = eeprom_read_dword(EECONFIG_KEYBOARD);

    if (prev_ver < US_BASE_FW_VER_OF_USER_CONFIG_V1) {
#ifdef CONSOLE_ENABLE
        uprintf("%s : it may be the first vial install or very early version is installed.\n", __FUNCTION__);
#endif
        return false;
    }

    // backup current eeprom data.
    us_kb_config_u us_kb_config_bk;
    const uint32_t bk_size = sizeof(us_kb_config_t);

#if 1
    // here, use eeprom func directly because eeconfig_read_user_datablock just init memory if version is invalid.
    void *ee_start = (void *)(uintptr_t)(EECONFIG_KB_DATABLOCK);
    void *ee_end   = (void *)(uintptr_t)(EECONFIG_KB_DATABLOCK + bk_size);
    eeprom_read_block(&us_kb_config_bk, ee_start, ee_end - ee_start);
#else
    eeconfig_read_kb_datablock(&us_kb_config_bk, 0, bk_size);
#endif

    const us_kb_config_u us_kb_config_init = {0};
    if (memcmp(&us_kb_config_bk, &us_kb_config_init, bk_size) == 0) {
#ifdef CONSOLE_ENABLE
        uprintf("%s : global memory has no data.\n", __FUNCTION__);
#endif
        return false;
    }

    // migrate global memory
#ifdef POINTING_DEVICE_ENABLE
    US_PD_eeconfig_migrate_kb_mem(&us_kb_config_bk, prev_ver);
#endif

    // store global memory into eeprom user datablock
    US_EECONFIG_eeconfig_init_kb_datablock();

    return true;
}

void US_EECONFIG_eeconfig_init_kb_datablock(void) {
    eeconfig_update_kb_datablock(&us_kb_config, 0, sizeof(us_kb_config));
}
#endif

void US_EECONFIG_keyboard_post_init_kb(void) {
#if (EECONFIG_KB_DATA_SIZE) > 0
    eeconfig_read_kb_datablock(&us_kb_config, 0, sizeof(us_kb_config));
#endif
}

bool US_EECONFIG_process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case USR_RESET:
            if (record->event.pressed) {
#if (EECONFIG_KB_DATA_SIZE) > 0
                eeconfig_init_kb_datablock();
#endif
            }
            return true;
        default:
            return true;
    }
}

#if (EECONFIG_USER_DATA_CALC_SIZE) > 0
bool US_EECONFIG_migrate_user_datablock(void) {
    const uint32_t prev_ver = eeprom_read_dword(EECONFIG_USER);

    if (prev_ver < US_BASE_FW_VER_OF_USER_CONFIG_V1) {
#ifdef CONSOLE_ENABLE
        uprintf("%s : it may be the first vial install or very early version is installed.\n", __FUNCTION__);
#endif
        return false;
    }

    // backup current eeprom data.
    us_user_config_u us_user_config_bk;
    const uint32_t bk_size = (prev_ver < US_BASE_FW_VER_OF_USER_CONFIG_V2) ? sizeof(us_user_config_t_v1)
                                                                           : sizeof(us_user_config_t);

#if 1
    // here, use eeprom func directly because eeconfig_read_user_datablock just init memory if version is invalid.
    void *ee_start = (void *)(uintptr_t)(EECONFIG_USER_DATABLOCK);
    void *ee_end   = (void *)(uintptr_t)(EECONFIG_USER_DATABLOCK + bk_size);
    eeprom_read_block(&us_user_config_bk, ee_start, ee_end - ee_start);
#else
    eeconfig_read_user_datablock(&us_user_config_bk, 0, bk_size);
#endif

    const us_user_config_u us_user_config_init = {0};
    if (memcmp(&us_user_config_bk, &us_user_config_init, bk_size) == 0) {
#ifdef CONSOLE_ENABLE
        uprintf("%s : global memory has no data.\n", __FUNCTION__);
#endif
        return false;
    }

    // migrate global memory
#if defined(RGBLIGHT_LAYERS) || defined(CUSTOM_RGBMATRIX)
    US_RGB_eeconfig_migrate_mem(&us_user_config_bk, prev_ver);
#endif
#ifdef OS_DETECTION_ENABLE
    US_OS_eeconfig_migrate_mem(&us_user_config_bk, prev_ver);
#endif

    // store global memory into eeprom user datablock
    US_EECONFIG_eeconfig_init_user_datablock();

    return true;
}

void US_EECONFIG_eeconfig_init_user_datablock(void) {
    eeconfig_update_user_datablock(&us_user_config, 0, sizeof(us_user_config));
}
#endif

void US_EECONFIG_keyboard_post_init_user(void) {
#if (EECONFIG_USER_DATA_CALC_SIZE) > 0
    eeconfig_read_user_datablock(&us_user_config, 0, sizeof(us_user_config));
#endif
}

bool US_EECONFIG_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case USR_RESET:
            if (record->event.pressed) {
#ifdef RGBLIGHT_LAYER_BLINK
                rgblight_layers = km_blink_layers;
                rgblight_blink_layer_repeat(US_BLINK_RESET, 300, 3);
#endif
#if (EECONFIG_USER_DATA_CALC_SIZE) > 0
                eeconfig_init_user_datablock();
#endif
            }
            return true;
        default:
            return true;
    }
}
