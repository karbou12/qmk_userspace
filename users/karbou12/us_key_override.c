// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "us_key_override.h"
#include "us_keymap.h"
#include "us_keycodes.h"
#ifdef CUSTOM_KEY_OVERRIDE_ENABLE

#define ko_make_with_negmods(trigger_mods, trigger_key, replacement_key, negative_mask) \
    ko_make_with_layers_and_negmods(trigger_mods, trigger_key, replacement_key, ~0, negative_mask)

#define L_BASE     1 << (OS_MAC_BASE)   | 1 << (OS_WIN_BASE)
#define L_RAISE    1 << (OS_MAC_RAISE)  | 1 << (OS_WIN_RAISE)
#define L_LOWER    1 << (OS_MAC_LOWER)  | 1 << (OS_WIN_LOWER)
#define L_ADJUST   1 << (OS_MAC_ADJUST) | 1 << (OS_WIN_ADJUST)
#define L_NON_BASE L_RAISE | L_LOWER | L_ADJUST

#define CCW_BASE       MS_WHLD
#define CW_BASE        MS_WHLU
#define CCW_RAISE      LGUI(KC_PMNS)
#define CW_RAISE       LGUI(KC_PPLS)
#define WIN_CCW_RAISE  LCTL(KC_PMNS)
#define WIN_CW_RAISE   LCTL(KC_PPLS)
#define CCW_LOWER      KC_BRID
#define CW_LOWER       KC_BRIU
#define CCW_ADJUST     KC_VOLD
#define CW_ADJUST      KC_VOLU


const key_override_t wheel_left_override   = ko_make_with_negmods(MOD_BIT(KC_LSFT), CW_BASE,  MS_WHLL, MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI));
const key_override_t wheel_right_override  = ko_make_with_negmods(MOD_BIT(KC_LSFT), CCW_BASE, MS_WHLR, MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL) | MOD_BIT(KC_LGUI));

const key_override_t prev_history_override = ko_make_basic(MOD_BIT(KC_LALT), CCW_BASE, LGUI(KC_LBRC));
const key_override_t next_history_override = ko_make_basic(MOD_BIT(KC_LALT), CW_BASE,  LGUI(KC_RBRC));

const key_override_t app_prev_override     = ko_make_basic(MOD_BIT(KC_LGUI), CCW_BASE, LSG(KC_TAB));
const key_override_t app_next_override     = ko_make_basic(MOD_BIT(KC_LGUI), CW_BASE,  LGUI(KC_TAB));

const key_override_t tab_prev_override     = ko_make_with_negmods(MOD_BIT(KC_LCTL), CCW_BASE, LCS(KC_TAB),  MOD_BIT(KC_LALT));
const key_override_t tab_next_override     = ko_make_with_negmods(MOD_BIT(KC_LCTL), CW_BASE,  LCTL(KC_TAB), MOD_BIT(KC_LALT));

const key_override_t raise_arrow_left_override  = ko_make_with_layers_and_negmods(MOD_BIT(KC_LALT), CCW_RAISE, KC_LEFT, L_NON_BASE, MOD_BIT(KC_LCTL));
const key_override_t raise_arrow_right_override = ko_make_with_layers_and_negmods(MOD_BIT(KC_LALT), CW_RAISE,  KC_RGHT, L_NON_BASE, MOD_BIT(KC_LCTL));

const key_override_t raise_arrow_up_override    = ko_make_with_layers(MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL), CCW_RAISE, KC_UP,   L_NON_BASE);
const key_override_t raise_arrow_down_override  = ko_make_with_layers(MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL), CW_RAISE,  KC_DOWN, L_NON_BASE);

#ifdef BACKLIGHT_ENABLE
const key_override_t raise_backlight_down_override = ko_make_with_layers(MOD_BIT(KC_RGUI), CCW_RAISE, BL_DOWN, L_NON_BASE);
const key_override_t raise_backlight_up_override   = ko_make_with_layers(MOD_BIT(KC_RGUI), CW_RAISE,  BL_UP,   L_NON_BASE);
#endif

const key_override_t win_raise_arrow_left_override  = ko_make_with_layers_and_negmods(MOD_BIT(KC_LALT), WIN_CCW_RAISE, KC_LEFT, L_NON_BASE, MOD_BIT(KC_LCTL));
const key_override_t win_raise_arrow_right_override = ko_make_with_layers_and_negmods(MOD_BIT(KC_LALT), WIN_CW_RAISE,  KC_RGHT, L_NON_BASE, MOD_BIT(KC_LCTL));

const key_override_t win_raise_arrow_up_override    = ko_make_with_layers(MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL), WIN_CCW_RAISE, KC_UP,   L_NON_BASE);
const key_override_t win_raise_arrow_down_override  = ko_make_with_layers(MOD_BIT(KC_LALT) | MOD_BIT(KC_LCTL), WIN_CW_RAISE,  KC_DOWN, L_NON_BASE);

#ifdef BACKLIGHT_ENABLE
const key_override_t win_raise_backlight_down_override = ko_make_with_layers(MOD_BIT(KC_RGUI), WIN_CCW_RAISE, BL_DOWN, L_NON_BASE);
const key_override_t win_raise_backlight_up_override   = ko_make_with_layers(MOD_BIT(KC_RGUI), WIN_CW_RAISE,  BL_UP,   L_NON_BASE);
#endif

const key_override_t lower_prev_space_override   = ko_make_with_layers_and_negmods(MOD_BIT(KC_LALT), CCW_LOWER, LCTL(KC_LEFT), L_NON_BASE, MOD_BIT(KC_LSFT));
const key_override_t lower_next_space_override   = ko_make_with_layers_and_negmods(MOD_BIT(KC_LALT), CW_LOWER,  LCTL(KC_RGHT), L_NON_BASE, MOD_BIT(KC_LSFT));

// move app to prev/next space by BetterTouchTool
const key_override_t lower_app_prev_space_override   = ko_make_with_layers_and_negmods(MOD_BIT(KC_LSFT), CCW_LOWER, LCG(KC_LEFT), L_NON_BASE, MOD_BIT(KC_LALT));
const key_override_t lower_app_next_space_override   = ko_make_with_layers_and_negmods(MOD_BIT(KC_LSFT), CW_LOWER,  LCG(KC_RGHT), L_NON_BASE, MOD_BIT(KC_LALT));
// move app to next monitor by BetterTouchTool
const key_override_t lower_app_next_monitor_override = ko_make_with_layers(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LALT), CW_LOWER, LCAG(KC_RGHT), L_NON_BASE);

const key_override_t adjust_mouse_left_override  = ko_make_with_layers(MOD_BIT(KC_LALT), CCW_ADJUST, MS_LEFT, L_NON_BASE);
const key_override_t adjust_mouse_right_override = ko_make_with_layers(MOD_BIT(KC_LALT), CW_ADJUST,  MS_RGHT, L_NON_BASE);
const key_override_t adjust_mouse_down_override  = ko_make_with_layers(MOD_BIT(KC_LCTL), CCW_ADJUST, MS_DOWN, L_NON_BASE);
const key_override_t adjust_mouse_up_override    = ko_make_with_layers(MOD_BIT(KC_LCTL), CW_ADJUST,  MS_UP,   L_NON_BASE);

#ifdef CUSTOM_RGBMATRIX
const key_override_t ug_hue_down_override = ko_make_with_layers(MOD_BIT(KC_RSFT) | MOD_BIT(KC_RGUI), CCW_BASE, RM_HUED, L_BASE);
const key_override_t ug_hue_up_override   = ko_make_with_layers(MOD_BIT(KC_RSFT) | MOD_BIT(KC_RGUI), CW_BASE,  RM_HUEU, L_BASE);
const key_override_t ug_sat_down_override = ko_make_with_layers(MOD_BIT(KC_RCTL) | MOD_BIT(KC_RGUI), CCW_BASE, RM_SATD, L_BASE);
const key_override_t ug_sat_up_override   = ko_make_with_layers(MOD_BIT(KC_RCTL) | MOD_BIT(KC_RGUI), CW_BASE,  RM_SATU, L_BASE);
const key_override_t ug_val_down_override = ko_make_with_layers(MOD_BIT(KC_RALT) | MOD_BIT(KC_RGUI), CCW_BASE, RM_VALD, L_BASE);
const key_override_t ug_val_up_override   = ko_make_with_layers(MOD_BIT(KC_RALT) | MOD_BIT(KC_RGUI), CW_BASE,  RM_VALU, L_BASE);

const key_override_t usr_def_hue_down_override = ko_make_with_layers_and_negmods(MOD_BIT(KC_RSFT), CCW_BASE, USR_RGB_LAYER_HUE_DOWN, L_BASE, MOD_BIT(KC_RGUI));
const key_override_t usr_def_hue_up_override   = ko_make_with_layers_and_negmods(MOD_BIT(KC_RSFT), CW_BASE,  USR_RGB_LAYER_HUE_UP,   L_BASE, MOD_BIT(KC_RGUI));
const key_override_t usr_def_sat_down_override = ko_make_with_layers_and_negmods(MOD_BIT(KC_RCTL), CCW_BASE, USR_RGB_LAYER_SAT_DOWN, L_BASE, MOD_BIT(KC_RGUI));
const key_override_t usr_def_sat_up_override   = ko_make_with_layers_and_negmods(MOD_BIT(KC_RCTL), CW_BASE,  USR_RGB_LAYER_SAT_UP,   L_BASE, MOD_BIT(KC_RGUI));
const key_override_t usr_def_val_down_override = ko_make_with_layers_and_negmods(MOD_BIT(KC_RALT), CCW_BASE, USR_RGB_LAYER_VAL_DOWN, L_BASE, MOD_BIT(KC_RGUI));
const key_override_t usr_def_val_up_override   = ko_make_with_layers_and_negmods(MOD_BIT(KC_RALT), CW_BASE,  USR_RGB_LAYER_VAL_UP,   L_BASE, MOD_BIT(KC_RGUI));

#elif RGBLIGHT_LAYERS
const key_override_t ug_hue_down_override = ko_make_with_layers(MOD_BIT(KC_RSFT), CCW_BASE, UG_HUED, L_BASE);
const key_override_t ug_hue_up_override   = ko_make_with_layers(MOD_BIT(KC_RSFT), CW_BASE,  UG_HUEU, L_BASE);
const key_override_t ug_sat_down_override = ko_make_with_layers(MOD_BIT(KC_RCTL), CCW_BASE, UG_SATD, L_BASE);
const key_override_t ug_sat_up_override   = ko_make_with_layers(MOD_BIT(KC_RCTL), CW_BASE,  UG_SATU, L_BASE);
const key_override_t ug_val_down_override = ko_make_with_layers(MOD_BIT(KC_RALT), CCW_BASE, UG_VALD, L_BASE);
const key_override_t ug_val_up_override   = ko_make_with_layers(MOD_BIT(KC_RALT), CW_BASE,  UG_VALU, L_BASE);
#endif

#if defined(RGBLIGHT_LAYERS) || defined(CUSTOM_RGBMATRIX)
const key_override_t usr_raise_hue_down_override = ko_make_with_layers(MOD_BIT(KC_RSFT), CCW_RAISE, USR_RGB_LAYER_HUE_DOWN, L_NON_BASE);
const key_override_t usr_raise_hue_up_override   = ko_make_with_layers(MOD_BIT(KC_RSFT), CW_RAISE,  USR_RGB_LAYER_HUE_UP,   L_NON_BASE);
const key_override_t usr_raise_sat_down_override = ko_make_with_layers(MOD_BIT(KC_RCTL), CCW_RAISE, USR_RGB_LAYER_SAT_DOWN, L_NON_BASE);
const key_override_t usr_raise_sat_up_override   = ko_make_with_layers(MOD_BIT(KC_RCTL), CW_RAISE,  USR_RGB_LAYER_SAT_UP,   L_NON_BASE);
const key_override_t usr_raise_val_down_override = ko_make_with_layers(MOD_BIT(KC_RALT), CCW_RAISE, USR_RGB_LAYER_VAL_DOWN, L_NON_BASE);
const key_override_t usr_raise_val_up_override   = ko_make_with_layers(MOD_BIT(KC_RALT), CW_RAISE,  USR_RGB_LAYER_VAL_UP,   L_NON_BASE);

const key_override_t win_usr_raise_hue_down_override = ko_make_with_layers(MOD_BIT(KC_RSFT), WIN_CCW_RAISE, USR_RGB_LAYER_HUE_DOWN, L_NON_BASE);
const key_override_t win_usr_raise_hue_up_override   = ko_make_with_layers(MOD_BIT(KC_RSFT), WIN_CW_RAISE,  USR_RGB_LAYER_HUE_UP,   L_NON_BASE);
const key_override_t win_usr_raise_sat_down_override = ko_make_with_layers(MOD_BIT(KC_RCTL), WIN_CCW_RAISE, USR_RGB_LAYER_SAT_DOWN, L_NON_BASE);
const key_override_t win_usr_raise_sat_up_override   = ko_make_with_layers(MOD_BIT(KC_RCTL), WIN_CW_RAISE,  USR_RGB_LAYER_SAT_UP,   L_NON_BASE);
const key_override_t win_usr_raise_val_down_override = ko_make_with_layers(MOD_BIT(KC_RALT), WIN_CCW_RAISE, USR_RGB_LAYER_VAL_DOWN, L_NON_BASE);
const key_override_t win_usr_raise_val_up_override   = ko_make_with_layers(MOD_BIT(KC_RALT), WIN_CW_RAISE,  USR_RGB_LAYER_VAL_UP,   L_NON_BASE);

const key_override_t usr_lower_hue_down_override = ko_make_with_layers(MOD_BIT(KC_RSFT), CCW_LOWER, USR_RGB_LAYER_HUE_DOWN, L_NON_BASE);
const key_override_t usr_lower_hue_up_override   = ko_make_with_layers(MOD_BIT(KC_RSFT), CW_LOWER,  USR_RGB_LAYER_HUE_UP,   L_NON_BASE);
const key_override_t usr_lower_sat_down_override = ko_make_with_layers(MOD_BIT(KC_RCTL), CCW_LOWER, USR_RGB_LAYER_SAT_DOWN, L_NON_BASE);
const key_override_t usr_lower_sat_up_override   = ko_make_with_layers(MOD_BIT(KC_RCTL), CW_LOWER,  USR_RGB_LAYER_SAT_UP,   L_NON_BASE);
const key_override_t usr_lower_val_down_override = ko_make_with_layers(MOD_BIT(KC_RALT), CCW_LOWER, USR_RGB_LAYER_VAL_DOWN, L_NON_BASE);
const key_override_t usr_lower_val_up_override   = ko_make_with_layers(MOD_BIT(KC_RALT), CW_LOWER,  USR_RGB_LAYER_VAL_UP,   L_NON_BASE);

const key_override_t usr_adjust_hue_down_override = ko_make_with_layers(MOD_BIT(KC_RSFT), CCW_ADJUST, USR_RGB_LAYER_HUE_DOWN, L_NON_BASE);
const key_override_t usr_adjust_hue_up_override   = ko_make_with_layers(MOD_BIT(KC_RSFT), CW_ADJUST,  USR_RGB_LAYER_HUE_UP,   L_NON_BASE);
const key_override_t usr_adjust_sat_down_override = ko_make_with_layers(MOD_BIT(KC_RCTL), CCW_ADJUST, USR_RGB_LAYER_SAT_DOWN, L_NON_BASE);
const key_override_t usr_adjust_sat_up_override   = ko_make_with_layers(MOD_BIT(KC_RCTL), CW_ADJUST,  USR_RGB_LAYER_SAT_UP,   L_NON_BASE);
const key_override_t usr_adjust_val_down_override = ko_make_with_layers(MOD_BIT(KC_RALT), CCW_ADJUST, USR_RGB_LAYER_VAL_DOWN, L_NON_BASE);
const key_override_t usr_adjust_val_up_override   = ko_make_with_layers(MOD_BIT(KC_RALT), CW_ADJUST,  USR_RGB_LAYER_VAL_UP,   L_NON_BASE);
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

#ifdef BACKLIGHT_ENABLE
    &raise_backlight_down_override,
    &raise_backlight_up_override,
#endif

    &lower_prev_space_override,
    &lower_next_space_override,
    &lower_app_prev_space_override,
    &lower_app_next_space_override,
    &lower_app_next_monitor_override,

    &adjust_mouse_left_override,
    &adjust_mouse_right_override,
    &adjust_mouse_down_override,
    &adjust_mouse_up_override,

#if defined(RGBLIGHT_LAYERS) || defined(CUSTOM_RGBMATRIX)
    &ug_hue_down_override,
    &ug_hue_up_override,
    &ug_sat_down_override,
    &ug_sat_up_override,
    &ug_val_down_override,
    &ug_val_up_override,

#ifdef CUSTOM_RGBMATRIX
    &usr_def_hue_down_override,
    &usr_def_hue_up_override,
    &usr_def_sat_down_override,
    &usr_def_sat_up_override,
    &usr_def_val_down_override,
    &usr_def_val_up_override,
#endif

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

    &win_raise_arrow_left_override,
    &win_raise_arrow_right_override,
    &win_raise_arrow_up_override,
    &win_raise_arrow_down_override,
#ifdef BACKLIGHT_ENABLE
    &win_raise_backlight_down_override,
    &win_raise_backlight_up_override,
#endif
    &win_usr_raise_hue_down_override,
    &win_usr_raise_hue_up_override,
    &win_usr_raise_sat_down_override,
    &win_usr_raise_sat_up_override,
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
