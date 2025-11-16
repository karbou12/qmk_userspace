// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "us_os.h"
#include "us_keycodes.h"
#include "us_eeconfig.h"
#include "us_utils.h"
#include "us_rgb.h"

#ifdef OS_DETECTION_ENABLE
void US_OS_eeconfig_migrate_mem(const us_user_config_u* bk, const uint32_t prev_ver) {
    if (!bk || prev_ver < US_BASE_FW_VER_OF_USER_CONFIG_V1) {
        return;
    }

    US_OS_eeconfig_init_mem();

    us_user_config_field_e* p = us_user_config.os.os_default_layer;
    const us_user_config_field_e* bk_p = (prev_ver < US_BASE_FW_VER_OF_USER_CONFIG_V2) ? bk->v1.os.os_default_layer
                                                                                       : bk->v2.os.os_default_layer;
    for (uint8_t i = 0; i < ARRAY_SIZE(us_user_config.os.os_default_layer); i++, p++, bk_p++) {
        *p = *bk_p;
    }
}

void US_OS_eeconfig_init_mem(void) {
    us_user_config_field_e* p = us_user_config.os.os_default_layer;
    for (uint8_t i = 0; i < ARRAY_SIZE(us_user_config.os.os_default_layer); i++, p++) {
        *p = 0;
    }
}

bool US_OS_process_detected_host_os_user(os_variant_t detected_os) {
    const us_user_config_field_e cur_layer = US_UTIL_get_current_layer(layer_state);
    const us_user_config_field_e os_layer = US_EECONFIG_get_os_default_layer_from_mem();

#ifdef CONSOLE_ENABLE
    uprintf("============================================================\n");
    uprintf("%s arg_os:%u, func_os:%u, df:%u, cur_layer:%u\n",
            __FUNCTION__, detected_os, detected_host_os(), os_layer, cur_layer);
#endif

    // if pdf may be set as non-zero, keep pdf. else, set os df.
    if (cur_layer == US_FIELD_LAYER0 && os_layer != US_FIELD_LAYER0) {
        set_single_default_layer(os_layer);
    }

    return true;
}

bool US_OS_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case USR_OS_DEFAULT_LAYER:
            if (record->event.pressed) {
                rgblight_blink_layer_repeat(US_BLINK_DF, 200, 3);

                const us_user_config_field_e cur_layer = US_UTIL_get_current_layer(layer_state);
                US_EECONFIG_update_os_default_layer_to_eeprom(cur_layer);

                set_single_default_layer(cur_layer);
            }
            return false;
        default:
            return true;
    }
    return true;
}
#endif
