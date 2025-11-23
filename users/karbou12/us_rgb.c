// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "us_keycodes.h"
#include "us_eeconfig.h"
#include "us_rgb.h"
#include "us_utils.h"
#include "us_status.h"

#ifdef RGBLIGHT_LAYERS
static bool us_is_keyboard_post_init_user_called = false;
static bool us_is_key_pressed_to_skip_rec_rgb = false;

static void us_set_rgblight_on_layer_of(const us_user_config_field_e field) {
    if (!us_is_keyboard_post_init_user_called) {
        return;
    }

    us_is_key_pressed_to_skip_rec_rgb = false;

    if (is_caps_word_on()) {
        return;
    }

    const us_hsvm_t* p = US_EECONFIG_get_hsvm_layer_from_mem(field);
    if (!p) {
        return;
    }

    uint8_t use_val = p->hsv.v;
    if (US_EECONFIG_get_retain_val_from_mem() && (field != US_FIELD_LAYER0)) {
        const us_hsvm_t* p_layer0 = US_EECONFIG_get_hsvm_layer_from_mem(US_FIELD_LAYER0);
        use_val = p_layer0->hsv.v;
    }

    US_DUMP_EECONFIG();
#ifdef CONSOLE_ENABLE
    uprintf("%s, field:%u, hue:%u, sat:%u, val:%u\n", __FUNCTION__, field, p->hsv.h, p->hsv.s, use_val);
#endif

    rgblight_sethsv_noeeprom(p->hsv.h, p->hsv.s, use_val);
    rgblight_mode_noeeprom(p->mode);
}

static void us_record_rgblight_on_layer_of(const us_user_config_field_e field) {
    if (!us_is_keyboard_post_init_user_called) {
        return;
    }

    if (!US_STATUS_can_record_rgblight()) {
        return;
    }

    if (is_caps_word_on()) {
        return;
    }

    US_DUMP_EECONFIG();
    us_hsvm_t cur_hsvm = {.hsv.h = rgblight_get_hue(), .hsv.s = rgblight_get_sat(),
                          .hsv.v = rgblight_get_val(), .mode = rgblight_get_mode()};

    const us_hsvm_t* p = US_EECONFIG_get_hsvm_layer_from_mem(field);
    if (!p) {
        return;
    }

    if ((cur_hsvm.hsv.h == p->hsv.h) && (cur_hsvm.hsv.s == p->hsv.s) && (cur_hsvm.mode == p->mode)) {
        if (((field == US_FIELD_LAYER0) && (cur_hsvm.hsv.v == p->hsv.v)) ||
            ((field != US_FIELD_LAYER0) && ((cur_hsvm.hsv.v == p->hsv.v) || US_EECONFIG_get_retain_val_from_mem()))) {
            return;
        }
    }

    US_EECONFIG_update_hsvm_layer_to_eeprom(field, &cur_hsvm);

    US_DUMP_EECONFIG();
}

// user key's func
static void us_update_hue_noeeprom(const bool is_increase) {
    if (is_increase) {
        rgblight_increase_hue_noeeprom();
    } else {
        rgblight_decrease_hue_noeeprom();
    }
}

static void us_update_sat_noeeprom(const bool is_increase) {
    if (is_increase) {
        rgblight_increase_sat_noeeprom();
    } else {
        rgblight_decrease_sat_noeeprom();
    }
}

static void us_update_val_noeeprom(const bool is_increase) {
    if (is_increase) {
        rgblight_increase_val_noeeprom();
    } else {
        rgblight_decrease_val_noeeprom();
    }
}

static bool us_is_rgblight_per_layer_enabled(keyrecord_t *record) {
    if (record) {
        return (record->event.pressed && rgblight_is_enabled() && US_EECONFIG_get_rgb_per_layer_from_mem());
    } else {
        return (rgblight_is_enabled() && US_EECONFIG_get_rgb_per_layer_from_mem());
    }
}

void US_RGB_eeconfig_init_mem(void) {
    us_hsvm_t* p = us_user_config.rgb.hsvm_layer;
    for (uint8_t i = 0; i < ARRAY_SIZE(us_user_config.rgb.hsvm_layer); i++, p++) {
        const rgblight_segment_t* const cur_seg = km_rgb_layers[i];
        p->hsv.h = cur_seg->hue;
        p->hsv.s = cur_seg->sat;
        p->hsv.v = cur_seg->val;
        p->mode = RGBLIGHT_MODE_STATIC_LIGHT;
    }

    us_user_config.rgb.flag_raw = 0u;
    us_user_config.rgb.flags.is_rgb_per_layer = true;
    us_user_config.rgb.flags.is_auto_save_rgb = true;
    us_user_config.rgb.flags.to_retain_val = true;
}

void US_RGB_eeconfig_migrate_mem(const us_user_config_u* bk, const uint32_t prev_ver) {
    if (!bk || prev_ver < US_BASE_FW_VER_OF_USER_CONFIG_V1) {
        return;
    }

    US_RGB_eeconfig_init_mem();
    us_hsvm_t* p = us_user_config.rgb.hsvm_layer;

    const us_hsvm_t* bk_p = (prev_ver < US_BASE_FW_VER_OF_USER_CONFIG_V2) ? bk->v1.rgb.hsvm_layer
                                                                          : bk->v2.rgb.hsvm_layer;

    for (uint8_t i = 0; i < ARRAY_SIZE(us_user_config.rgb.hsvm_layer); i++, p++, bk_p++) {
        p->hsv.h = bk_p->hsv.h;
        p->hsv.s = bk_p->hsv.s;
        p->hsv.v = bk_p->hsv.v;
        p->mode = bk_p->mode;
    }

    if (prev_ver < US_BASE_FW_VER_OF_USER_CONFIG_V2) {
        us_user_config.rgb.flags.is_rgb_per_layer = bk->v1.rgb.is_rgb_per_layer;
        us_user_config.rgb.flags.to_retain_val = bk->v1.rgb.to_retain_val;
    } else {
        us_user_config.rgb.flags.is_rgb_per_layer = bk->v2.rgb.flags.is_rgb_per_layer;
        us_user_config.rgb.flags.is_auto_save_rgb = bk->v2.rgb.flags.is_auto_save_rgb;
        us_user_config.rgb.flags.to_retain_val = bk->v2.rgb.flags.to_retain_val;
    }
}

void US_RGB_keyboard_post_init_user(void) {
    us_is_keyboard_post_init_user_called = true;
    rgblight_layers = km_blink_layers;

    rgblight_enable_noeeprom();
    us_set_rgblight_on_layer_of(US_UTIL_get_current_layer(layer_state));
};

layer_state_t US_RGB_default_layer_state_set_user(layer_state_t state) {
    if (!rgblight_is_enabled()) {
        return state;
    }

    if (!US_EECONFIG_get_rgb_per_layer_from_mem()) {
        us_set_rgblight_on_layer_of(US_FIELD_LAYER0);
        return state;
    }

#ifdef CONSOLE_ENABLE
    uprintf("============================================================\n");
    uprintf("%s def:%u, layer_state:%u, state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state), get_highest_layer(state));
#endif

    // store rgblight automatically if it is changed on vial.
    if (get_highest_layer(state) == 0 && get_highest_layer(layer_state) == 0 && get_highest_layer(default_layer_state) == 0) {
        us_record_rgblight_on_layer_of(US_FIELD_LAYER0);
    } else if (US_EECONFIG_get_auto_save_rgb_from_mem() && !us_is_key_pressed_to_skip_rec_rgb) {
        us_record_rgblight_on_layer_of(US_UTIL_get_current_layer(layer_state));
    }

    if (US_STATUS_can_set_rgblight()) {
        if (!US_STATUS_can_record_rgblight() && get_highest_layer(layer_state) != 0) {
            rgblight_layers = km_rgb_layers;
            rgblight_blink_layer_repeat(get_highest_layer(state), 300, 1);
            us_set_rgblight_on_layer_of(US_UTIL_get_current_layer(layer_state));
        } else {
            us_set_rgblight_on_layer_of(get_highest_layer(state));
        }
    }

    return state;
}

layer_state_t US_RGB_layer_state_set_user(layer_state_t state) {
    if (!rgblight_is_enabled()) {
        return state;
    }

    if (is_caps_word_on()) {
        return state;
    }

    if (!US_EECONFIG_get_rgb_per_layer_from_mem()) {
        us_set_rgblight_on_layer_of(US_FIELD_LAYER0);
        return state;
    }

#ifdef CONSOLE_ENABLE
    uprintf("============================================================\n");
    uprintf("%s def:%u, layer_state:%u, state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state), get_highest_layer(state));
#endif

    // store rgblight automatically if it is changed on vial.
    if (get_highest_layer(layer_state) == 0 && get_highest_layer(default_layer_state) == 0) {
        us_record_rgblight_on_layer_of(US_FIELD_LAYER0);
    } else if (US_EECONFIG_get_auto_save_rgb_from_mem() &&!us_is_key_pressed_to_skip_rec_rgb) {
        us_record_rgblight_on_layer_of(US_UTIL_get_current_layer(layer_state));
    }

    us_set_rgblight_on_layer_of(US_UTIL_get_current_layer(state));

    return state;
};

bool US_RGB_process_record_user(uint16_t keycode, keyrecord_t *record) {
    const uint8_t mod_state = get_mods();
    switch (keycode) {
        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
        case QK_PERSISTENT_DEF_LAYER ... QK_PERSISTENT_DEF_LAYER_MAX:
            if (us_is_rgblight_per_layer_enabled(record)) {
                if (get_highest_layer(layer_state) != US_FIELD_LAYER0) {
                    US_STATUS_set_change_layer_key_pressed_on_non_default_layer(true);
                }
            }
            return true;

        case USR_RESET:
            if (record->event.pressed) {
                if (us_is_rgblight_per_layer_enabled(record)) {
                    if (get_highest_layer(layer_state) != US_FIELD_LAYER0) {
                        US_STATUS_set_user_reset_key_pressed_on_non_default_layer(true);
                    }
                }
                set_single_default_layer(US_FIELD_LAYER0);
                us_set_rgblight_on_layer_of(US_UTIL_get_current_layer(layer_state));
            } else {
                US_STATUS_set_user_reset_key_pressed_on_non_default_layer(false);
            }
            return true;

        case USR_RGB_RETAIN_VAL_TOG:
            if (us_is_rgblight_per_layer_enabled(record)) {
                const bool cur_flag = US_EECONFIG_get_retain_val_from_mem();
                rgblight_layers = km_blink_layers;
                rgblight_blink_layer_repeat(cur_flag ? US_BLINK_OFF : US_BLINK_ON, 300, 2);
                US_EECONFIG_update_retain_val_to_eeprom(!cur_flag);
                if (US_UTIL_get_current_layer(layer_state) != US_FIELD_LAYER0) {
                    us_is_key_pressed_to_skip_rec_rgb = true;
                }
            }
            return false;

        case USR_RGB_LAYER_TOG:
            if (rgblight_is_enabled() && record->event.pressed) {
                const bool cur_flag = US_EECONFIG_get_rgb_per_layer_from_mem();
                rgblight_layers = km_blink_layers;
                rgblight_blink_layer_repeat(cur_flag ? US_BLINK_OFF : US_BLINK_ON, 300, 2);
                const bool next_flag = !cur_flag;
                US_EECONFIG_update_rgb_per_layer_to_eeprom(next_flag);
                if (next_flag) {
                    us_set_rgblight_on_layer_of(US_UTIL_get_current_layer(layer_state));
                } else {
                    us_set_rgblight_on_layer_of(US_FIELD_LAYER0);
                }
                if (US_UTIL_get_current_layer(layer_state) != US_FIELD_LAYER0) {
                    us_is_key_pressed_to_skip_rec_rgb = true;
                }
            }
            return false;

        case USR_RGB_LAYER_HUE_UP:
            if (us_is_rgblight_per_layer_enabled(record)) {
                us_update_hue_noeeprom(!(mod_state & MOD_MASK_SHIFT));
            }
            return true;

        case USR_RGB_LAYER_HUE_DOWN:
            if (us_is_rgblight_per_layer_enabled(record)) {
                us_update_hue_noeeprom(mod_state & MOD_MASK_SHIFT);
            }
            return true;

        case USR_RGB_LAYER_SAT_UP:
            if (us_is_rgblight_per_layer_enabled(record)) {
                us_update_sat_noeeprom(!(mod_state & MOD_MASK_SHIFT));
            }
            return true;

        case USR_RGB_LAYER_SAT_DOWN:
            if (us_is_rgblight_per_layer_enabled(record)) {
                us_update_sat_noeeprom(mod_state & MOD_MASK_SHIFT);
            }
            return true;

        case USR_RGB_LAYER_VAL_UP:
            if (us_is_rgblight_per_layer_enabled(record)) {
                us_update_val_noeeprom(!(mod_state & MOD_MASK_SHIFT));
            }
            return true;

        case USR_RGB_LAYER_VAL_DOWN:
            if (us_is_rgblight_per_layer_enabled(record)) {
                us_update_val_noeeprom(mod_state & MOD_MASK_SHIFT);
            }
            return true;

        case USR_RGB_AUTO_SAVE_TOG:
            if (us_is_rgblight_per_layer_enabled(record)) {
                const bool cur_flag = US_EECONFIG_get_auto_save_rgb_from_mem();
                rgblight_layers = km_blink_layers;
                rgblight_blink_layer_repeat(cur_flag ? US_BLINK_OFF : US_BLINK_ON, 300, 2);
                US_EECONFIG_update_auto_save_rgb_to_eeprom(!cur_flag);
            }
            return false;

        default:
            return true;
    }

    return true;
}

void US_RGB_post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
        case QK_PERSISTENT_DEF_LAYER ... QK_PERSISTENT_DEF_LAYER_MAX:
            if (!record->event.pressed) {
                US_STATUS_set_change_layer_key_pressed_on_non_default_layer(false);
            }
            break;

        case UG_NEXT ... RGB_M_TW:
            if (rgblight_is_enabled()) {
                us_record_rgblight_on_layer_of(US_FIELD_LAYER0);
                us_is_key_pressed_to_skip_rec_rgb = true;
            }
            break;

        case USR_RGB_LAYER_HUE_UP:
        case USR_RGB_LAYER_HUE_DOWN:
        case USR_RGB_LAYER_SAT_UP:
        case USR_RGB_LAYER_SAT_DOWN:
        case USR_RGB_LAYER_VAL_UP:
        case USR_RGB_LAYER_VAL_DOWN:
            if (us_is_rgblight_per_layer_enabled(NULL)) {
                us_record_rgblight_on_layer_of(US_UTIL_get_current_layer(layer_state));
                us_is_key_pressed_to_skip_rec_rgb = true;
            }
            break;

        default:
            break;
    }
}

void US_RGB_caps_word_set_user(bool active) {
    if (!US_EECONFIG_get_rgb_per_layer_from_mem()) {
        return;
    }

    if (active) {
        const rgblight_segment_t* const cur_seg = km_capsword_layer;
#ifdef CONSOLE_ENABLE
        uprintf("============================================================\n");
        uprintf("%s, active def:%u, layer_state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state));
#endif

        rgblight_sethsv_noeeprom(cur_seg->hue, cur_seg->sat, US_EECONFIG_get_hsvm_layer_from_mem(US_FIELD_LAYER0)->hsv.v);
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    } else {
#ifdef CONSOLE_ENABLE
        uprintf("%s, inactive def:%u, layer_state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state));
#endif
        us_set_rgblight_on_layer_of(US_UTIL_get_current_layer(layer_state));
    }
}
#endif
