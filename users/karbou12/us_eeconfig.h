// Copyright 2020 Alexander Tulloh
// Copyright 2022 aki27 (@aki27kbd)
// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include "karbou12.h"

#ifdef POINTING_DEVICE_ENABLE
typedef struct PACKED {
    uint8_t cpi_idx;
    uint8_t scrl_div;
    uint8_t rotation_angle;
    union {
        uint8_t flag_raw;
        struct {
            bool auto_mouse: 1;
            bool scrl_inv: 1;
            uint8_t dummy : 6;
        } flags;
    };
} us_pd_config_t_v1;

typedef struct PACKED {
    us_pd_config_t_v1 pd;
} us_kb_config_t_v1;
#define US_BASE_FW_VER_OF_KB_CONFIG_V1 US_CONCAT_VER(1, 0, 0)

typedef union {
    us_kb_config_t_v1 v1;
} us_kb_config_u;

#define US_KB_CONFIG_VERSION 1
#define US_KB_CONFIG_V_CONCAT(n) us_kb_config_t_v ## n
#define US_KB_CONFIG_V(n)  US_KB_CONFIG_V_CONCAT(n)
#define us_kb_config_t US_KB_CONFIG_V(US_KB_CONFIG_VERSION)

extern us_kb_config_t us_kb_config;
#endif

typedef enum {
    US_FIELD_LAYER0 = 0,
    US_FIELD_LAYER1,
    US_FIELD_LAYER2,
    US_FIELD_LAYER3,
    US_FIELD_LAYER4,
    US_FIELD_LAYER5,
    US_FIELD_LAYER6,
    US_FIELD_LAYER7,
    US_FIELD_LAYER8,
    US_FIELD_LAYER9,
    US_FIELD_LAYER10,
    US_FIELD_LAYER11,
    US_FIELD_LAYER12,
    US_FIELD_LAYER13,
    US_FIELD_LAYER14,
    US_FIELD_LAYER15,
    US_FIELD_FLAGS,
    US_FIELD_OS_UNSURE,
    US_FIELD_OS_LINUX,
    US_FIELD_OS_WINDOWS,
    US_FIELD_OS_MACOS,
    US_FIELD_OS_IOS,
    US_FIELD_ALL
} us_user_config_field_e;

#if defined(RGBLIGHT_LAYERS) || defined(CUSTOM_RGBMATRIX)
typedef struct PACKED {
    hsv_t hsv;
    uint8_t mode;
} us_hsvm_t;

typedef struct PACKED {
    us_hsvm_t hsvm_layer[DYNAMIC_KEYMAP_LAYER_COUNT];
    bool is_rgb_per_layer;
    bool to_retain_val;
} us_rgb_config_t_v1;

typedef struct PACKED {
    us_hsvm_t hsvm_layer[DYNAMIC_KEYMAP_LAYER_COUNT];
    union {
        uint8_t flag_raw;
        struct {
            bool is_rgb_per_layer : 1;
            bool is_auto_save_rgb : 1;
            bool to_retain_val : 1;
            uint8_t dummy : 5;
        } flags;
    };
} us_rgb_config_t_v2;
#endif

#ifdef OS_DETECTION_ENABLE
typedef struct PACKED {
    us_user_config_field_e os_default_layer[OS_IOS + 1];
} us_os_config_t_v1;

#define us_os_config_t_v2 us_os_config_t_v1
#endif

typedef struct PACKED {
#if defined(RGBLIGHT_LAYERS) || defined(CUSTOM_RGBMATRIX)
    us_rgb_config_t_v1 rgb;
#endif
#ifdef OS_DETECTION_ENABLE
    us_os_config_t_v1 os;
#endif
} us_user_config_t_v1;
#define US_BASE_FW_VER_OF_USER_CONFIG_V1 US_CONCAT_VER(0, 0, 5)

typedef struct PACKED {
#if defined(RGBLIGHT_LAYERS) || defined(CUSTOM_RGBMATRIX)
    us_rgb_config_t_v2 rgb;
#endif
#ifdef OS_DETECTION_ENABLE
    us_os_config_t_v2 os;
#endif
} us_user_config_t_v2;
#define US_BASE_FW_VER_OF_USER_CONFIG_V2 US_CONCAT_VER(1, 0, 0)

typedef union {
    us_user_config_t_v2 v2;
    us_user_config_t_v1 v1;
} us_user_config_u;

#define US_USER_CONFIG_VERSION 2
#define US_USER_CONFIG_V_CONCAT(n) us_user_config_t_v ## n
#define US_USER_CONFIG_V(n)  US_USER_CONFIG_V_CONCAT(n)
#define us_user_config_t US_USER_CONFIG_V(US_USER_CONFIG_VERSION)

extern us_user_config_t us_user_config;

#ifdef CONSOLE_ENABLE
extern void us_dump_eeconfig(const char* const func);
#define US_DUMP_EECONFIG() us_dump_eeconfig(__FUNCTION__)
#else
#define US_DUMP_EECONFIG()
#endif

#ifdef POINTING_DEVICE_ENABLE
extern uint8_t US_EECONFIG_get_pd_cpi_idx_from_mem(void);
extern void US_EECONFIG_update_pd_cpi_idx_to_eeprom(const uint8_t cpi_idx);

extern uint8_t US_EECONFIG_get_pd_scrl_div_from_mem(void);
extern void US_EECONFIG_update_pd_scrl_div_to_eeprom(const uint8_t scrl_div);

extern uint8_t US_EECONFIG_get_pd_rotation_angle_from_mem(void);
extern void US_EECONFIG_update_pd_rotation_angle_to_eeprom(const uint8_t rotation_angle);

extern bool US_EECONFIG_get_pd_auto_mouse_from_mem(void);
extern void US_EECONFIG_update_pd_auto_mouse_to_eeprom(const bool auto_mouse);

extern bool US_EECONFIG_get_pd_scrl_inv_from_mem(void);
extern void US_EECONFIG_update_pd_scrl_inv_to_eeprom(const bool scrl_inv);
#endif

#if defined(RGBLIGHT_LAYERS) || defined(CUSTOM_RGBMATRIX)
extern const us_hsvm_t* US_EECONFIG_get_hsvm_layer_from_mem(const us_user_config_field_e field);
extern void US_EECONFIG_update_hsvm_layer_to_eeprom(const us_user_config_field_e field, const us_hsvm_t* hsvm_layer);

extern bool US_EECONFIG_get_rgb_per_layer_from_mem(void);
extern void US_EECONFIG_update_rgb_per_layer_to_eeprom(const bool is_rgb_per_layer);

extern bool US_EECONFIG_get_auto_save_rgb_from_mem(void);
extern void US_EECONFIG_update_auto_save_rgb_to_eeprom(const bool is_rgb_per_layer);

extern bool US_EECONFIG_get_retain_val_from_mem(void);
extern void US_EECONFIG_update_retain_val_to_eeprom(const bool to_retain_val);
#endif

#ifdef OS_DETECTION_ENABLE
extern us_user_config_field_e US_EECONFIG_get_os_default_layer_from_mem(void);
extern void US_EECONFIG_update_os_default_layer_to_eeprom(const us_user_config_field_e field);
#endif

#if (EECONFIG_KB_DATA_SIZE) > 0
extern bool US_EECONFIG_migrate_kb_datablock(void);

// override func
extern void US_EECONFIG_eeconfig_init_kb_datablock(void);
#endif

extern void US_EECONFIG_keyboard_post_init_kb(void);
extern bool US_EECONFIG_process_record_kb(uint16_t keycode, keyrecord_t *record);

#if (EECONFIG_USER_DATA_CALC_SIZE) > 0
extern bool US_EECONFIG_migrate_user_datablock(void);

// override func
extern void US_EECONFIG_eeconfig_init_user_datablock(void);
#endif

extern void US_EECONFIG_keyboard_post_init_user(void);
extern bool US_EECONFIG_process_record_user(uint16_t keycode, keyrecord_t *record);
