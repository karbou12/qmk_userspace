// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "us_key_override.h"
#include "us_keymap.h"
#include "us_keycodes.h"
#ifdef CUSTOM_KEY_OVERRIDE_ENABLE

#define ko_make_with_negmods(trigger_mods, trigger_key, replacement_key, negative_mask) \
    ko_make_with_layers_and_negmods(trigger_mods, trigger_key, replacement_key, ~0, negative_mask)

#ifdef POINTING_DEVICE_ENABLE
#define L_MOUSE AUTO_MOUSE_DEFAULT_LAYER
#define L_BASE     1 << (OS_MAC_BASE)   | 1 << (OS_WIN_BASE) | 1 << (L_MOUSE)
#else
#define L_BASE     1 << (OS_MAC_BASE)   | 1 << (OS_WIN_BASE)
#endif
#define L_RAISE    1 << (OS_MAC_RAISE)  | 1 << (OS_WIN_RAISE)
#define L_LOWER    1 << (OS_MAC_LOWER)  | 1 << (OS_WIN_LOWER)
#define L_ADJUST   1 << (OS_MAC_ADJUST) | 1 << (OS_WIN_ADJUST)
#define L_NON_BASE L_RAISE | L_LOWER | L_ADJUST

const key_override_t wheel_left_override   = ko_make_with_negmods(MOD_BIT(KC_LSFT), BASE_CW,  MS_WHLL, MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI));
const key_override_t wheel_right_override  = ko_make_with_negmods(MOD_BIT(KC_LSFT), BASE_CCW, MS_WHLR, MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI));

const key_override_t prev_history_override = ko_make_basic(MOD_BIT(KC_LALT), BASE_CCW, LGUI(KC_LBRC));
const key_override_t next_history_override = ko_make_basic(MOD_BIT(KC_LALT), BASE_CW,  LGUI(KC_RBRC));

const key_override_t app_prev_override     = ko_make_basic(MOD_BIT(KC_LGUI), BASE_CCW, LSG(KC_TAB));
const key_override_t app_next_override     = ko_make_basic(MOD_BIT(KC_LGUI), BASE_CW,  LGUI(KC_TAB));

const key_override_t tab_prev_override     = ko_make_basic(MOD_BIT(KC_LCTL), BASE_CCW, LCS(KC_TAB));
const key_override_t tab_next_override     = ko_make_basic(MOD_BIT(KC_LCTL), BASE_CW,  LCTL(KC_TAB));

const key_override_t raise_arrow_left_override  = ko_make_with_layers(MOD_BIT(KC_LCTL), RAISE_CCW, KC_LEFT, L_NON_BASE);
const key_override_t raise_arrow_right_override = ko_make_with_layers(MOD_BIT(KC_LCTL), RAISE_CW,  KC_RGHT, L_NON_BASE);

const key_override_t raise_arrow_up_override    = ko_make_with_layers(MOD_BIT(KC_LGUI), RAISE_CCW, KC_UP,   L_NON_BASE);
const key_override_t raise_arrow_down_override  = ko_make_with_layers(MOD_BIT(KC_LGUI), RAISE_CW,  KC_DOWN, L_NON_BASE);

const key_override_t lower_prev_space_override   = ko_make_with_layers(MOD_BIT(KC_LCTL), LOWER_CCW, LCTL(KC_LEFT), L_NON_BASE);
const key_override_t lower_next_space_override   = ko_make_with_layers(MOD_BIT(KC_LCTL), LOWER_CW,  LCTL(KC_RGHT), L_NON_BASE);

const key_override_t win_lower_prev_space_override   = ko_make_with_layers(MOD_BIT(KC_LCTL), WIN_LOWER_CCW, LGUI(KC_LEFT), L_NON_BASE);
const key_override_t win_lower_next_space_override   = ko_make_with_layers(MOD_BIT(KC_LCTL), WIN_LOWER_CW,  LGUI(KC_RGHT), L_NON_BASE);

// move app to prev/next space by BetterTouchTool
const key_override_t lower_app_prev_space_override   = ko_make_with_layers(MOD_BIT(KC_LGUI), LOWER_CCW, LCG(KC_LEFT), L_NON_BASE);
const key_override_t lower_app_next_space_override   = ko_make_with_layers(MOD_BIT(KC_LGUI), LOWER_CW,  LCG(KC_RGHT), L_NON_BASE);
// move app to next monitor by BetterTouchTool
const key_override_t lower_app_next_monitor_override = ko_make_with_layers(MOD_BIT(KC_LALT), LOWER_CW, LCAG(KC_RGHT), L_NON_BASE);

const key_override_t lower_zoom_out_override = ko_make_with_layers(MOD_BIT(KC_LSFT), LOWER_CCW, LAG(KC_MINS), L_NON_BASE);
const key_override_t lower_zoom_in_override  = ko_make_with_layers(MOD_BIT(KC_LSFT), LOWER_CW,  LAG(KC_6),   L_NON_BASE);

const key_override_t adjust_mouse_left_override  = ko_make_with_layers(MOD_BIT(KC_LCTL), ADJUST_CCW, MS_LEFT, L_NON_BASE);
const key_override_t adjust_mouse_right_override = ko_make_with_layers(MOD_BIT(KC_LCTL), ADJUST_CW,  MS_RGHT, L_NON_BASE);
const key_override_t adjust_mouse_down_override  = ko_make_with_layers(MOD_BIT(KC_LGUI), ADJUST_CCW, MS_DOWN, L_NON_BASE);
const key_override_t adjust_mouse_up_override    = ko_make_with_layers(MOD_BIT(KC_LGUI), ADJUST_CW,  MS_UP,   L_NON_BASE);

const key_override_t adjust_media_rewind_override  = ko_make_with_layers(MOD_BIT(KC_LSFT), ADJUST_CCW, KC_MRWD,   L_NON_BASE);
const key_override_t adjust_media_forward_override = ko_make_with_layers(MOD_BIT(KC_LSFT), ADJUST_CW,  KC_MFFD,   L_NON_BASE);

#ifdef CUSTOM_RGBMATRIX
const key_override_t ug_hue_down_override = ko_make_with_layers(MOD_BIT(KC_RSFT) | MOD_BIT(KC_RGUI), BASE_CCW, RM_HUED, L_BASE);
const key_override_t ug_hue_up_override   = ko_make_with_layers(MOD_BIT(KC_RSFT) | MOD_BIT(KC_RGUI), BASE_CW,  RM_HUEU, L_BASE);
const key_override_t ug_sat_down_override = ko_make_with_layers(MOD_BIT(KC_RCTL) | MOD_BIT(KC_RGUI), BASE_CCW, RM_SATD, L_BASE);
const key_override_t ug_sat_up_override   = ko_make_with_layers(MOD_BIT(KC_RCTL) | MOD_BIT(KC_RGUI), BASE_CW,  RM_SATU, L_BASE);
const key_override_t ug_val_down_override = ko_make_with_layers(MOD_BIT(KC_RALT) | MOD_BIT(KC_RGUI), BASE_CCW, RM_VALD, L_BASE);
const key_override_t ug_val_up_override   = ko_make_with_layers(MOD_BIT(KC_RALT) | MOD_BIT(KC_RGUI), BASE_CW,  RM_VALU, L_BASE);
#elif RGBLIGHT_LAYERS
const key_override_t ug_hue_down_override = ko_make_with_layers(MOD_BIT(KC_RSFT), BASE_CCW, UG_HUED, L_BASE);
const key_override_t ug_hue_up_override   = ko_make_with_layers(MOD_BIT(KC_RSFT), BASE_CW,  UG_HUEU, L_BASE);
const key_override_t ug_sat_down_override = ko_make_with_layers(MOD_BIT(KC_RCTL), BASE_CCW, UG_SATD, L_BASE);
const key_override_t ug_sat_up_override   = ko_make_with_layers(MOD_BIT(KC_RCTL), BASE_CW,  UG_SATU, L_BASE);
const key_override_t ug_val_down_override = ko_make_with_layers(MOD_BIT(KC_RALT), BASE_CCW, UG_VALD, L_BASE);
const key_override_t ug_val_up_override   = ko_make_with_layers(MOD_BIT(KC_RALT), BASE_CW,  UG_VALU, L_BASE);
#endif


#ifdef BACKLIGHT_ENABLE
const key_override_t backlight_down_override = ko_make_with_layers(MOD_BIT(KC_RGUI), BASE_CCW, BL_DOWN, L_BASE);
const key_override_t backlight_up_override   = ko_make_with_layers(MOD_BIT(KC_RGUI), BASE_CW,  BL_UP,   L_BASE);
#elif CUSTOM_RGBMATRIX
const key_override_t usr_def_hue_down_override = ko_make_with_layers_and_negmods(MOD_BIT(KC_RSFT), BASE_CCW, USR_RGB_LAYER_HUE_DOWN, L_BASE, MOD_BIT(KC_RGUI));
const key_override_t usr_def_hue_up_override   = ko_make_with_layers_and_negmods(MOD_BIT(KC_RSFT), BASE_CW,  USR_RGB_LAYER_HUE_UP,   L_BASE, MOD_BIT(KC_RGUI));
const key_override_t usr_def_sat_down_override = ko_make_with_layers_and_negmods(MOD_BIT(KC_RCTL), BASE_CCW, USR_RGB_LAYER_SAT_DOWN, L_BASE, MOD_BIT(KC_RGUI));
const key_override_t usr_def_sat_up_override   = ko_make_with_layers_and_negmods(MOD_BIT(KC_RCTL), BASE_CW,  USR_RGB_LAYER_SAT_UP,   L_BASE, MOD_BIT(KC_RGUI));
const key_override_t usr_def_val_down_override = ko_make_with_layers_and_negmods(MOD_BIT(KC_RALT), BASE_CCW, USR_RGB_LAYER_VAL_DOWN, L_BASE, MOD_BIT(KC_RGUI));
const key_override_t usr_def_val_up_override   = ko_make_with_layers_and_negmods(MOD_BIT(KC_RALT), BASE_CW,  USR_RGB_LAYER_VAL_UP,   L_BASE, MOD_BIT(KC_RGUI));
#endif

#if defined(RGBLIGHT_LAYERS) || defined(CUSTOM_RGBMATRIX)
const key_override_t usr_raise_hue_down_override = ko_make_with_layers(MOD_BIT(KC_RSFT), RAISE_CCW, USR_RGB_LAYER_HUE_DOWN, L_NON_BASE);
const key_override_t usr_raise_hue_up_override   = ko_make_with_layers(MOD_BIT(KC_RSFT), RAISE_CW,  USR_RGB_LAYER_HUE_UP,   L_NON_BASE);
const key_override_t usr_raise_sat_down_override = ko_make_with_layers(MOD_BIT(KC_RCTL), RAISE_CCW, USR_RGB_LAYER_SAT_DOWN, L_NON_BASE);
const key_override_t usr_raise_sat_up_override   = ko_make_with_layers(MOD_BIT(KC_RCTL), RAISE_CW,  USR_RGB_LAYER_SAT_UP,   L_NON_BASE);
const key_override_t usr_raise_val_down_override = ko_make_with_layers(MOD_BIT(KC_RALT), RAISE_CCW, USR_RGB_LAYER_VAL_DOWN, L_NON_BASE);
const key_override_t usr_raise_val_up_override   = ko_make_with_layers(MOD_BIT(KC_RALT), RAISE_CW,  USR_RGB_LAYER_VAL_UP,   L_NON_BASE);

const key_override_t usr_lower_hue_down_override = ko_make_with_layers(MOD_BIT(KC_RSFT), LOWER_CCW, USR_RGB_LAYER_HUE_DOWN, L_NON_BASE);
const key_override_t usr_lower_hue_up_override   = ko_make_with_layers(MOD_BIT(KC_RSFT), LOWER_CW,  USR_RGB_LAYER_HUE_UP,   L_NON_BASE);
const key_override_t usr_lower_sat_down_override = ko_make_with_layers(MOD_BIT(KC_RCTL), LOWER_CCW, USR_RGB_LAYER_SAT_DOWN, L_NON_BASE);
const key_override_t usr_lower_sat_up_override   = ko_make_with_layers(MOD_BIT(KC_RCTL), LOWER_CW,  USR_RGB_LAYER_SAT_UP,   L_NON_BASE);
const key_override_t usr_lower_val_down_override = ko_make_with_layers(MOD_BIT(KC_RALT), LOWER_CCW, USR_RGB_LAYER_VAL_DOWN, L_NON_BASE);
const key_override_t usr_lower_val_up_override   = ko_make_with_layers(MOD_BIT(KC_RALT), LOWER_CW,  USR_RGB_LAYER_VAL_UP,   L_NON_BASE);

const key_override_t win_usr_lower_hue_down_override = ko_make_with_layers(MOD_BIT(KC_RSFT), WIN_LOWER_CCW, USR_RGB_LAYER_HUE_DOWN, L_NON_BASE);
const key_override_t win_usr_lower_hue_up_override   = ko_make_with_layers(MOD_BIT(KC_RSFT), WIN_LOWER_CW,  USR_RGB_LAYER_HUE_UP,   L_NON_BASE);
const key_override_t win_usr_lower_sat_down_override = ko_make_with_layers(MOD_BIT(KC_RCTL), WIN_LOWER_CCW, USR_RGB_LAYER_SAT_DOWN, L_NON_BASE);
const key_override_t win_usr_lower_sat_up_override   = ko_make_with_layers(MOD_BIT(KC_RCTL), WIN_LOWER_CW,  USR_RGB_LAYER_SAT_UP,   L_NON_BASE);
const key_override_t win_usr_lower_val_down_override = ko_make_with_layers(MOD_BIT(KC_RALT), WIN_LOWER_CCW, USR_RGB_LAYER_VAL_DOWN, L_NON_BASE);
const key_override_t win_usr_lower_val_up_override   = ko_make_with_layers(MOD_BIT(KC_RALT), WIN_LOWER_CW,  USR_RGB_LAYER_VAL_UP,   L_NON_BASE);

const key_override_t usr_adjust_hue_down_override = ko_make_with_layers(MOD_BIT(KC_RSFT), ADJUST_CCW, USR_RGB_LAYER_HUE_DOWN, L_NON_BASE);
const key_override_t usr_adjust_hue_up_override   = ko_make_with_layers(MOD_BIT(KC_RSFT), ADJUST_CW,  USR_RGB_LAYER_HUE_UP,   L_NON_BASE);
const key_override_t usr_adjust_sat_down_override = ko_make_with_layers(MOD_BIT(KC_RCTL), ADJUST_CCW, USR_RGB_LAYER_SAT_DOWN, L_NON_BASE);
const key_override_t usr_adjust_sat_up_override   = ko_make_with_layers(MOD_BIT(KC_RCTL), ADJUST_CW,  USR_RGB_LAYER_SAT_UP,   L_NON_BASE);
const key_override_t usr_adjust_val_down_override = ko_make_with_layers(MOD_BIT(KC_RALT), ADJUST_CCW, USR_RGB_LAYER_VAL_DOWN, L_NON_BASE);
const key_override_t usr_adjust_val_up_override   = ko_make_with_layers(MOD_BIT(KC_RALT), ADJUST_CW,  USR_RGB_LAYER_VAL_UP,   L_NON_BASE);
#endif

const key_override_t *key_overrides[] = {
    &wheel_left_override,
    &wheel_right_override,
    &prev_history_override,
    &next_history_override,
    &app_prev_override,
    &app_next_override,
    &tab_prev_override,
    &tab_next_override,

    &raise_arrow_left_override,
    &raise_arrow_right_override,
    &raise_arrow_up_override,
    &raise_arrow_down_override,

    &lower_prev_space_override,
    &lower_next_space_override,
    &lower_app_prev_space_override,
    &lower_app_next_space_override,
    &lower_app_next_monitor_override,
    &lower_zoom_in_override,
    &lower_zoom_out_override,

    &adjust_mouse_left_override,
    &adjust_mouse_right_override,
    &adjust_mouse_down_override,
    &adjust_mouse_up_override,
    &adjust_media_rewind_override,
    &adjust_media_forward_override,

#if defined(RGBLIGHT_LAYERS) || defined(CUSTOM_RGBMATRIX)
    &ug_hue_down_override,
    &ug_hue_up_override,
    &ug_sat_down_override,
    &ug_sat_up_override,
    &ug_val_down_override,
    &ug_val_up_override,
#endif

#ifdef BACKLIGHT_ENABLE
    &backlight_down_override,
    &backlight_up_override,
#elif CUSTOM_RGBMATRIX
    &usr_def_hue_down_override,
    &usr_def_hue_up_override,
    &usr_def_sat_down_override,
    &usr_def_sat_up_override,
    &usr_def_val_down_override,
    &usr_def_val_up_override,
#endif

#if defined(RGBLIGHT_LAYERS) || defined(CUSTOM_RGBMATRIX)
    &usr_raise_hue_down_override,
    &usr_raise_hue_up_override,
    &usr_raise_sat_down_override,
    &usr_raise_sat_up_override,

    &usr_lower_hue_down_override,
    &usr_lower_hue_up_override,
    &usr_lower_sat_down_override,
    &usr_lower_sat_up_override,

    &usr_adjust_hue_down_override,
    &usr_adjust_hue_up_override,
    &usr_adjust_sat_down_override,
    &usr_adjust_sat_up_override,
#endif

    &win_lower_prev_space_override,
    &win_lower_next_space_override,
#if defined(RGBLIGHT_LAYERS) || defined(CUSTOM_RGBMATRIX)
    &win_usr_lower_hue_down_override,
    &win_usr_lower_hue_up_override,
    &win_usr_lower_sat_down_override,
    &win_usr_lower_sat_up_override,
#endif
};
const uint16_t key_overrides_raw_size = ARRAY_SIZE(key_overrides);

static bool is_init_or_default_key_override(const vial_key_override_entry_t *entry) {
    vial_key_override_entry_t init_entry = { 0 };
    if (memcmp(&init_entry, entry, sizeof(vial_key_override_entry_t)) == 0) {
        return true;
    }

    init_entry.layers = ~0;
    init_entry.options = ko_options_default;

    return (memcmp(&init_entry, entry, sizeof(vial_key_override_entry_t)) == 0) ? true : false;
}

void US_KO_keyboard_post_init_user(void) {
    // check already key_override is there
    {
        vial_key_override_entry_t entry = {0};
        if (dynamic_keymap_get_key_override(0, &entry) < 0) {
            return;
        }

        if (!is_init_or_default_key_override(&entry)) {
            return;
        }
    }

    const uint16_t key_overrides_num = MIN(key_overrides_raw_size, VIAL_KEY_OVERRIDE_ENTRIES);
#ifdef CONSOLE_ENABLE
    uprintf("%s : array size:%u, define size:%u\n", __FUNCTION__, key_overrides_raw_size, VIAL_KEY_OVERRIDE_ENTRIES);
#endif

    for (uint8_t i = 0; i < key_overrides_num; i++) {
        vial_key_override_entry_t entry = {0};
        entry.trigger = key_overrides[i]->trigger;
        entry.replacement = key_overrides[i]->replacement;
        entry.layers = key_overrides[i]->layers;
        entry.trigger_mods = key_overrides[i]->trigger_mods;
        entry.negative_mod_mask = key_overrides[i]->negative_mod_mask;
        entry.suppressed_mods = key_overrides[i]->suppressed_mods;
        entry.options = key_overrides[i]->options;
        entry.options |= vial_ko_enabled;

        // set to eeprom
        dynamic_keymap_set_key_override(i, &entry);
    }
}
#endif
