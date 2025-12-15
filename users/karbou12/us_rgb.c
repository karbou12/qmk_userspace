// Copyright 2022 aki27 (@aki27kbd)
// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "us_keycodes.h"
#include "us_eeconfig.h"
#include "us_rgb.h"
#include "us_utils.h"
#include "us_status.h"
#include <lib/lib8tion/lib8tion.h>
#include <limits.h>

#if defined(RGBLIGHT_LAYERS) || defined(CUSTOM_RGBMATRIX)

#ifdef USE_UINT16_KEYCODE_FOR_VIAL
extern uint16_t g_us_vial_keycode16;
#endif

static bool us_is_keyboard_post_init_user_called = false;
static bool us_is_key_pressed_to_skip_rec_rgb = false;

#ifdef CUSTOM_RGBMATRIX
static uint8_t us_led_min = 0;
static uint8_t us_led_max = 0;
#endif

#ifdef RGBLIGHT_LAYER_BLINK
static rgblight_segment_t PROGMEM df_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_TURQUOISE});
static const rgblight_segment_t * const PROGMEM df_blink_layers[] = RGBLIGHT_LAYERS_LIST(
    df_layer
);
#endif

#ifdef CUSTOM_RGBMATRIX
#define GET_LIMITED_RGB_VAL(v) (v < RGB_MATRIX_MAXIMUM_BRIGHTNESS) ? v : RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define GET_STATIC_MODE() RGB_MATRIX_SOLID_COLOR
#else
#define GET_LIMITED_RGB_VAL(v) (v < RGBLIGHT_LIMIT_VAL) ? v : RGBLIGHT_LIMIT_VAL
#define GET_STATIC_MODE() RGBLIGHT_MODE_STATIC_LIGHT
#endif

static bool us_is_rgb_enabled(void) {
#ifdef CUSTOM_RGBMATRIX
    return rgb_matrix_is_enabled();
#else
    return rgblight_is_enabled();
#endif
}

static void us_rgb_enable_noeeprom(void) {
#ifdef CUSTOM_RGBMATRIX
    rgb_matrix_enable_noeeprom();
#else
    rgblight_enable_noeeprom();
#endif
}

static void us_set_hsvm_noeeprom(const uint8_t hue, const uint8_t sat, const uint8_t val, uint8_t mode) {
#ifdef CUSTOM_RGBMATRIX
    if (us_led_max == 0) {
        return;
    }

    const hsv_t hsv = {hue, sat, val};
    const rgb_t rgb = hsv_to_rgb(hsv);

    for (uint8_t i = us_led_min; i < us_led_max; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }

    rgb_matrix_mode_noeeprom(mode);
#else
    rgblight_sethsv_noeeprom(hue, sat, val);
    rgblight_mode_noeeprom(mode);
#endif
}

static void us_set_rgb_on_layer_of(const us_user_config_field_e field) {
    if (!us_is_keyboard_post_init_user_called) {
        return;
    }

    us_is_key_pressed_to_skip_rec_rgb = false;

#ifdef CAPS_WORD_ENABLE
    if (is_caps_word_on()) {
        return;
    }
#endif

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

    us_set_hsvm_noeeprom(p->hsv.h, p->hsv.s, use_val, p->mode);
}

static void us_record_rgb_on_layer_of(const us_user_config_field_e field) {
    if (!us_is_keyboard_post_init_user_called) {
        return;
    }

    if (!US_STATUS_can_record_rgb()) {
        return;
    }

#ifdef CAPS_WORD_ENABLE
    if (is_caps_word_on()) {
        return;
    }
#endif

    US_DUMP_EECONFIG();

    const us_hsvm_t* p = US_EECONFIG_get_hsvm_layer_from_mem(field);
    if (!p) {
        return;
    }

#ifdef CUSTOM_RGBMATRIX
    US_EECONFIG_update_hsvm_layer_to_eeprom(field, p);
#else
    us_hsvm_t cur_hsvm = {.hsv.h = rgblight_get_hue(), .hsv.s = rgblight_get_sat(),
                          .hsv.v = rgblight_get_val(), .mode = rgblight_get_mode()};

    if ((cur_hsvm.hsv.h == p->hsv.h) && (cur_hsvm.hsv.s == p->hsv.s) && (cur_hsvm.mode == p->mode)) {
        if (((field == US_FIELD_LAYER0) && (cur_hsvm.hsv.v == p->hsv.v)) ||
            ((field != US_FIELD_LAYER0) && ((cur_hsvm.hsv.v == p->hsv.v) || US_EECONFIG_get_retain_val_from_mem()))) {
            return;
        }
    }

    US_EECONFIG_update_hsvm_layer_to_eeprom(field, &cur_hsvm);
#endif

    US_DUMP_EECONFIG();
}

// user key's func
#ifdef USE_UINT16_KEYCODE_FOR_VIAL
static void us_update_hue(const bool is_increase) {
    if (is_increase) {
#ifdef CUSTOM_RGBMATRIX
        rgb_matrix_increase_hue();
#else
        rgblight_increase_hue();
#endif
    } else {
#ifdef CUSTOM_RGBMATRIX
        rgb_matrix_decrease_hue();
#else
        rgblight_decrease_hue();
#endif
    }
}

static void us_update_sat(const bool is_increase) {
    if (is_increase) {
#ifdef CUSTOM_RGBMATRIX
        rgb_matrix_increase_sat();
#else
        rgblight_increase_sat();
#endif
    } else {
#ifdef CUSTOM_RGBMATRIX
        rgb_matrix_decrease_sat();
#else
        rgblight_decrease_sat();
#endif
    }
}

static void us_update_val(const bool is_increase) {
    if (is_increase) {
#ifdef CUSTOM_RGBMATRIX
        rgb_matrix_increase_val();
#else
        rgblight_increase_val();
#endif
    } else {
#ifdef CUSTOM_RGBMATRIX
        rgb_matrix_decrease_val();
#else
        rgblight_decrease_val();
#endif
    }
}
#endif

#ifdef CUSTOM_RGBMATRIX
typedef enum {
    US_HUE = 0,
    US_SAT,
    US_VAL
} us_hsv_e;

static void us_update_hsv_noeeprom_for_rgb_matrix(const bool is_increase, const us_hsv_e type) {
    const us_user_config_field_e field = US_UTIL_get_current_layer(layer_state);
    const us_hsvm_t* p = US_EECONFIG_get_hsvm_layer_from_mem(field);
    if (!p) {
        return;
    }

    us_hsvm_t new_hsvm = {
        .hsv.h = (type != US_HUE) ? p->hsv.h
               : is_increase ? p->hsv.h + RGB_MATRIX_HUE_STEP : p->hsv.h - RGB_MATRIX_HUE_STEP,
        .hsv.s = (type != US_SAT) ? p->hsv.s
               : is_increase ? qadd8(p->hsv.s, RGB_MATRIX_SAT_STEP) : qsub8(p->hsv.s, RGB_MATRIX_SAT_STEP),
        .hsv.v = (type != US_VAL) ? p->hsv.v
               : is_increase ? GET_LIMITED_RGB_VAL(qadd8(p->hsv.v, RGB_MATRIX_VAL_STEP)) : qsub8(p->hsv.v, RGB_MATRIX_VAL_STEP),
        .mode = p->mode};

    US_EECONFIG_update_hsvm_layer_to_eeprom(field, &new_hsvm);
}
#endif

static void us_update_hue_noeeprom(const bool is_increase) {
#ifdef CUSTOM_RGBMATRIX
    us_update_hsv_noeeprom_for_rgb_matrix(is_increase, US_HUE);
#else
    if (is_increase) {
        rgblight_increase_hue_noeeprom();
    } else {
        rgblight_decrease_hue_noeeprom();
    }
#endif
}

static void us_update_sat_noeeprom(const bool is_increase) {
#ifdef CUSTOM_RGBMATRIX
    us_update_hsv_noeeprom_for_rgb_matrix(is_increase, US_SAT);
#else
    if (is_increase) {
        rgblight_increase_sat_noeeprom();
    } else {
        rgblight_decrease_sat_noeeprom();
    }
#endif
}

static void us_update_val_noeeprom(const bool is_increase) {
#ifdef CUSTOM_RGBMATRIX
    us_update_hsv_noeeprom_for_rgb_matrix(is_increase, US_VAL);
#else
    if (is_increase) {
        rgblight_increase_val_noeeprom();
    } else {
        rgblight_decrease_val_noeeprom();
    }
#endif
}

static bool us_is_rgb_per_layer_enabled(keyrecord_t *record) {
    if (record) {
        return (record->event.pressed && us_is_rgb_enabled() && US_EECONFIG_get_rgb_per_layer_from_mem());
    } else {
        return (us_is_rgb_enabled() && US_EECONFIG_get_rgb_per_layer_from_mem());
    }
}

void US_RGB_eeconfig_init_mem(void) {
    us_hsvm_t* p = us_user_config.rgb.hsvm_layer;
    for (uint8_t i = 0; i < ARRAY_SIZE(us_user_config.rgb.hsvm_layer); i++, p++) {
        const hsv_t* const cur_seg = km_hsv_layers[i];
        p->hsv.h = cur_seg->h;
        p->hsv.s = cur_seg->s;
        p->hsv.v = GET_LIMITED_RGB_VAL(cur_seg->v);
        p->mode = GET_STATIC_MODE();
    }

    us_user_config.rgb.flag_raw = 0u;
    us_user_config.rgb.flags.is_rgb_per_layer = true;
#ifdef CUSTOM_RGBMATRIX
    us_user_config.rgb.flags.is_auto_save_rgb = false;
#else
    us_user_config.rgb.flags.is_auto_save_rgb = true;
#endif
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
        p->hsv.v = GET_LIMITED_RGB_VAL(bk_p->hsv.v);
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
#ifdef RGBLIGHT_LAYERS_BLINK
    rgblight_layers = km_blink_layers;
#endif

    us_rgb_enable_noeeprom();
    us_set_rgb_on_layer_of(US_UTIL_get_current_layer(layer_state));
};

layer_state_t US_RGB_default_layer_state_set_user(layer_state_t state) {
    if (!us_is_rgb_enabled()) {
        return state;
    }

    if (!US_EECONFIG_get_rgb_per_layer_from_mem()) {
        us_set_rgb_on_layer_of(US_FIELD_LAYER0);
        return state;
    }

#ifdef CONSOLE_ENABLE
    uprintf("============================================================\n");
    uprintf("%s def:%u, layer_state:%u, state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state), get_highest_layer(state));
#endif

#ifndef CUSTOM_RGBMATRIX
    // store rgblight automatically if it is changed on vial.
    if (get_highest_layer(state) == 0 && get_highest_layer(layer_state) == 0 && get_highest_layer(default_layer_state) == 0) {
        us_record_rgb_on_layer_of(US_FIELD_LAYER0);
    } else if (US_EECONFIG_get_auto_save_rgb_from_mem() && !us_is_key_pressed_to_skip_rec_rgb) {
        us_record_rgb_on_layer_of(US_UTIL_get_current_layer(layer_state));
    }
#endif

    if (US_STATUS_can_set_rgb()) {
        const us_user_config_field_e field = get_highest_layer(state);
        if (!US_STATUS_can_record_rgb() && get_highest_layer(layer_state) != 0) {
#ifdef RGBLIGHT_LAYER_BLINK
            const us_hsvm_t* p = US_EECONFIG_get_hsvm_layer_from_mem(field);

            if (p) {
                uint8_t use_val = p->hsv.v;
                if (US_EECONFIG_get_retain_val_from_mem() && (field != US_FIELD_LAYER0)) {
                    const us_hsvm_t* p_layer0 = US_EECONFIG_get_hsvm_layer_from_mem(US_FIELD_LAYER0);
                    use_val = p_layer0->hsv.v;
                }
                df_layer->hue = p->hsv.h;
                df_layer->sat = p->hsv.s;
                df_layer->val = use_val;
            }
            rgblight_layers = df_blink_layers;
            rgblight_blink_layer_repeat(0, 300, 1);
#endif
            us_set_rgb_on_layer_of(US_UTIL_get_current_layer(layer_state));
        } else {
            us_set_rgb_on_layer_of(field);
        }
    }

    return state;
}

layer_state_t US_RGB_layer_state_set_user(layer_state_t state) {
    if (!us_is_rgb_enabled()) {
        return state;
    }

#ifdef CAPS_WORD_ENABLE
    if (is_caps_word_on()) {
        return state;
    }
#endif

    if (!US_EECONFIG_get_rgb_per_layer_from_mem()) {
        us_set_rgb_on_layer_of(US_FIELD_LAYER0);
        return state;
    }

#ifdef CONSOLE_ENABLE
    uprintf("============================================================\n");
    uprintf("%s def:%u, layer_state:%u, state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state), get_highest_layer(state));
#endif

#ifndef CUSTOM_RGBMATRIX
    // store rgblight automatically if it is changed on vial.
    if (get_highest_layer(layer_state) == 0 && get_highest_layer(default_layer_state) == 0) {
        us_record_rgb_on_layer_of(US_FIELD_LAYER0);
    } else if (US_EECONFIG_get_auto_save_rgb_from_mem() &&!us_is_key_pressed_to_skip_rec_rgb) {
        us_record_rgb_on_layer_of(US_UTIL_get_current_layer(layer_state));
    }
#endif

    us_set_rgb_on_layer_of(US_UTIL_get_current_layer(state));

    return state;
};

bool US_RGB_process_record_user(uint16_t keycode, keyrecord_t *record) {
    const uint8_t mod_state = get_mods();

#ifdef USE_UINT16_KEYCODE_FOR_VIAL
    if (g_us_vial_keycode16 != KC_NO) {
#ifdef CONSOLE_ENABLE
        uprintf("%s: keycode:%x g_keycode:%x\n", __FUNCTION__, keycode, g_us_vial_keycode16);
#endif
        if (record->event.type == ENCODER_CW_EVENT || record->event.type == ENCODER_CCW_EVENT) {
            if (IS_QK_LIGHTING(g_us_vial_keycode16)) {
                switch (g_us_vial_keycode16) {
                    case UG_HUEU:
                    case RM_HUEU:
                        us_update_hue(!(mod_state & MOD_MASK_SHIFT));
                        break;
                    case UG_HUED:
                    case RM_HUED:
                        us_update_hue(mod_state & MOD_MASK_SHIFT);
                        break;

                    case UG_SATU:
                    case RM_SATU:
                        us_update_sat(!(mod_state & MOD_MASK_SHIFT));
                        break;

                    case UG_SATD:
                    case RM_SATD:
                        us_update_sat(mod_state & MOD_MASK_SHIFT);
                        break;

                    case UG_VALU:
                    case RM_VALU:
                        us_update_val(!(mod_state & MOD_MASK_SHIFT));
                        break;

                    case UG_VALD:
                    case RM_VALD:
                        us_update_val(mod_state & MOD_MASK_SHIFT);
                        break;

                    default:
                        break;
                }
#ifndef CUSTOM_RGBMATRIX
                if (us_is_rgb_enabled()) {
                    us_record_rgb_on_layer_of(US_FIELD_LAYER0);
                    us_is_key_pressed_to_skip_rec_rgb = true;
                }
#endif
                return true;
            } else if (IS_QK_KB(g_us_vial_keycode16) || IS_QK_USER(g_us_vial_keycode16)) {
                keycode = g_us_vial_keycode16;
                if (us_is_rgb_per_layer_enabled(NULL)) {
                    switch(g_us_vial_keycode16) {
                        case USR_RGB_LAYER_HUE_UP:
                            us_update_hue_noeeprom(!(mod_state & MOD_MASK_SHIFT));
                            break;
                        case USR_RGB_LAYER_HUE_DOWN:
                            us_update_hue_noeeprom(mod_state & MOD_MASK_SHIFT);
                            break;
                        case USR_RGB_LAYER_SAT_UP:
                            us_update_sat_noeeprom(!(mod_state & MOD_MASK_SHIFT));
                            break;
                        case USR_RGB_LAYER_SAT_DOWN:
                            us_update_sat_noeeprom(mod_state & MOD_MASK_SHIFT);
                            break;
                        case USR_RGB_LAYER_VAL_UP:
                            us_update_val_noeeprom(!(mod_state & MOD_MASK_SHIFT));
                            break;
                        case USR_RGB_LAYER_VAL_DOWN:
                            us_update_val_noeeprom(mod_state & MOD_MASK_SHIFT);
                            break;
                        default:
                            break;
                    }
                }
                if (us_is_rgb_per_layer_enabled(NULL)) {
                    us_record_rgb_on_layer_of(US_UTIL_get_current_layer(layer_state));
                    us_is_key_pressed_to_skip_rec_rgb = true;
                }
                return true;
            }
        } else {
            g_us_vial_keycode16 = KC_NO;
        }
    }
#endif

    switch (keycode) {
        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
        case QK_PERSISTENT_DEF_LAYER ... QK_PERSISTENT_DEF_LAYER_MAX:
            if (us_is_rgb_per_layer_enabled(record)) {
                if (get_highest_layer(layer_state) != US_FIELD_LAYER0) {
                    US_STATUS_set_change_layer_key_pressed_on_non_default_layer(true);
                }
            }
            return true;

        case USR_RESET:
            if (record->event.pressed) {
                if (us_is_rgb_per_layer_enabled(record)) {
                    US_STATUS_set_user_reset_key_pressed_on_non_default_layer(true);
                }
                set_single_default_layer(US_FIELD_LAYER0);
                us_set_rgb_on_layer_of(US_UTIL_get_current_layer(layer_state));
            } else {
                US_STATUS_set_user_reset_key_pressed_on_non_default_layer(false);
            }
            return true;

        case USR_RGB_RETAIN_VAL_TOG:
            if (us_is_rgb_per_layer_enabled(record)) {
                const bool cur_flag = US_EECONFIG_get_retain_val_from_mem();
#ifdef RGBLIGHT_LAYER_BLINK
                rgblight_layers = km_blink_layers;
                rgblight_blink_layer_repeat(cur_flag ? US_BLINK_OFF : US_BLINK_ON, 300, 2);
#endif
                US_EECONFIG_update_retain_val_to_eeprom(!cur_flag);
                us_set_rgb_on_layer_of(US_UTIL_get_current_layer(layer_state));
                if (US_UTIL_get_current_layer(layer_state) != US_FIELD_LAYER0) {
                    us_is_key_pressed_to_skip_rec_rgb = true;
                }
            }
            return false;

        case USR_RGB_LAYER_TOG:
            if (us_is_rgb_enabled() && record->event.pressed) {
                const bool cur_flag = US_EECONFIG_get_rgb_per_layer_from_mem();
#ifdef RGBLIGHT_LAYER_BLINK
                rgblight_layers = km_blink_layers;
                rgblight_blink_layer_repeat(cur_flag ? US_BLINK_OFF : US_BLINK_ON, 300, 2);
#endif
                const bool next_flag = !cur_flag;
                US_EECONFIG_update_rgb_per_layer_to_eeprom(next_flag);
                if (next_flag) {
                    us_set_rgb_on_layer_of(US_UTIL_get_current_layer(layer_state));
                } else {
                    us_set_rgb_on_layer_of(US_FIELD_LAYER0);
                }
                if (US_UTIL_get_current_layer(layer_state) != US_FIELD_LAYER0) {
                    us_is_key_pressed_to_skip_rec_rgb = true;
                }
            }
            return false;

        case USR_RGB_LAYER_HUE_UP:
            if (us_is_rgb_per_layer_enabled(record)) {
                us_update_hue_noeeprom(!(mod_state & MOD_MASK_SHIFT));
            }
            return true;

        case USR_RGB_LAYER_HUE_DOWN:
            if (us_is_rgb_per_layer_enabled(record)) {
                us_update_hue_noeeprom(mod_state & MOD_MASK_SHIFT);
            }
            return true;

        case USR_RGB_LAYER_SAT_UP:
            if (us_is_rgb_per_layer_enabled(record)) {
                us_update_sat_noeeprom(!(mod_state & MOD_MASK_SHIFT));
            }
            return true;

        case USR_RGB_LAYER_SAT_DOWN:
            if (us_is_rgb_per_layer_enabled(record)) {
                us_update_sat_noeeprom(mod_state & MOD_MASK_SHIFT);
            }
            return true;

        case USR_RGB_LAYER_VAL_UP:
            if (us_is_rgb_per_layer_enabled(record)) {
                us_update_val_noeeprom(!(mod_state & MOD_MASK_SHIFT));
            }
            return true;

        case USR_RGB_LAYER_VAL_DOWN:
            if (us_is_rgb_per_layer_enabled(record)) {
                us_update_val_noeeprom(mod_state & MOD_MASK_SHIFT);
            }
            return true;

#ifndef CUSTOM_RGBMATRIX
        case USR_RGB_AUTO_SAVE_TOG:
            if (us_is_rgb_per_layer_enabled(record)) {
                const bool cur_flag = US_EECONFIG_get_auto_save_rgb_from_mem();
#ifdef RGBLIGHT_LAYER_BLINK
                rgblight_layers = km_blink_layers;
                rgblight_blink_layer_repeat(cur_flag ? US_BLINK_OFF : US_BLINK_ON, 300, 2);
#endif
                US_EECONFIG_update_auto_save_rgb_to_eeprom(!cur_flag);
            }
            return false;
#endif

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
#ifndef CUSTOM_RGBMATRIX
            if (us_is_rgb_enabled()) {
                us_record_rgb_on_layer_of(US_FIELD_LAYER0);
                us_is_key_pressed_to_skip_rec_rgb = true;
            }
#endif
            break;

        case USR_RGB_LAYER_HUE_UP:
        case USR_RGB_LAYER_HUE_DOWN:
        case USR_RGB_LAYER_SAT_UP:
        case USR_RGB_LAYER_SAT_DOWN:
        case USR_RGB_LAYER_VAL_UP:
        case USR_RGB_LAYER_VAL_DOWN:
            if (us_is_rgb_per_layer_enabled(NULL)) {
                us_record_rgb_on_layer_of(US_UTIL_get_current_layer(layer_state));
                us_is_key_pressed_to_skip_rec_rgb = true;
            }
            break;

        default:
            break;
    }
}

#ifdef CAPS_WORD_ENABLE
void US_RGB_caps_word_set_user(bool active) {
    if (!US_EECONFIG_get_rgb_per_layer_from_mem()) {
        return;
    }

    if (active) {
#ifdef CONSOLE_ENABLE
        uprintf("============================================================\n");
        uprintf("%s, active def:%u, layer_state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state));
#endif

        const hsv_t* const cur_seg = km_hsv_capsword;
        us_set_hsvm_noeeprom(cur_seg->h, cur_seg->s, US_EECONFIG_get_hsvm_layer_from_mem(US_FIELD_LAYER0)->hsv.v,
                GET_STATIC_MODE());
    } else {
#ifdef CONSOLE_ENABLE
        uprintf("%s, inactive def:%u, layer_state:%u\n", __FUNCTION__, get_highest_layer(default_layer_state), get_highest_layer(layer_state));
#endif
        us_set_rgb_on_layer_of(US_UTIL_get_current_layer(layer_state));
    }
}
#endif

#ifdef CUSTOM_RGBMATRIX
bool US_RGB_rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (!us_is_keyboard_post_init_user_called) {
        return true;
    }
    us_led_min = MIN(us_led_min, led_min);
    us_led_max = MAX(us_led_max, led_max);

    us_is_key_pressed_to_skip_rec_rgb = false;

    const hsv_t* const p_capsword = is_caps_word_on() ? km_hsv_capsword : NULL;

    const us_user_config_field_e field = US_EECONFIG_get_rgb_per_layer_from_mem() ? US_UTIL_get_current_layer(layer_state) : US_FIELD_LAYER0;
    const us_hsvm_t* p = US_EECONFIG_get_hsvm_layer_from_mem(field);
    if (!p) {
        return true;
    }

    uint8_t use_val = p->hsv.v;
    if (p_capsword || (US_EECONFIG_get_retain_val_from_mem() && (field != US_FIELD_LAYER0))) {
        const us_hsvm_t* p_layer0 = US_EECONFIG_get_hsvm_layer_from_mem(US_FIELD_LAYER0);
        use_val = p_layer0->hsv.v;
    }

    const hsv_t hsv = {p_capsword ? p_capsword->h : p->hsv.h, p_capsword ? p_capsword->s : p->hsv.s, use_val};
    const rgb_t rgb = hsv_to_rgb(hsv);

    for (uint8_t i = led_min; i < led_max; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }

    return false;
};
#endif
#endif
