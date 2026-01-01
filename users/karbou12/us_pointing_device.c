// Copyright 2020 Alexander Tulloh
// Copyright 2022 aki27 (@aki27kbd)
// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "us_pointing_device.h"
#include <math.h>
#include "us_keycodes.h"
#include "us_eeconfig.h"

#ifdef POINTING_DEVICE_ENABLE

// Invert vertical scroll direction
#ifndef COCOT_SCROLL_INV_DEFAULT
#    define COCOT_SCROLL_INV_DEFAULT true
#endif

#ifndef COCOT_CPI_OPTIONS
#    define COCOT_CPI_OPTIONS { 200, 400, 800, 1600, 3200 }
#    ifndef COCOT_CPI_DEFAULT
#       define COCOT_CPI_DEFAULT 3
#    endif
#endif
#ifndef COCOT_CPI_DEFAULT
#    define COCOT_CPI_DEFAULT 3
#endif

#ifndef COCOT_SCROLL_DIVIDERS
#    define COCOT_SCROLL_DIVIDERS { 1, 2, 3, 4, 5, 6 }
#    ifndef COCOT_SCROLL_DIV_DEFAULT
#       define COCOT_SCROLL_DIV_DEFAULT 4
#    endif
#endif
#ifndef COCOT_SCROLL_DIV_DEFAULT
#    define COCOT_SCROLL_DIV_DEFAULT 4
#endif

#ifndef COCOT_ROTATION_ANGLE
#    define COCOT_ROTATION_ANGLE { -90, -75, -60, -45, -30, -15, 0, 15, 30, 45, 60, 75, 90 }
#    ifndef COCOT_ROTATION_DEFAULT
#       define COCOT_ROTATION_DEFAULT 3
#    endif
#endif
#ifndef COCOT_ROTATION_DEFAULT
#    define COCOT_ROTATION_DEFAULT 3
#endif
#ifndef COCOT_AUTO_MOUSE_MODE
#    define COCOT_AUTO_MOUSE_MODE true
#endif

const static uint16_t us_cpi_array[] = COCOT_CPI_OPTIONS;
const static uint16_t us_scrl_div_array[] = COCOT_SCROLL_DIVIDERS;
const static uint16_t us_angle_array[] = COCOT_ROTATION_ANGLE;
const static uint8_t us_cpi_array_size = ARRAY_SIZE(us_cpi_array);
const static uint8_t us_scrl_div_array_size = ARRAY_SIZE(us_scrl_div_array);
const static uint8_t us_angle_array_size = ARRAY_SIZE(us_angle_array);

static bool us_is_scrl_mode = false;

void US_PD_eeconfig_migrate_kb_mem(const us_kb_config_u* bk, const uint32_t prev_ver) {
    if (!bk || prev_ver < US_BASE_FW_VER_OF_KB_CONFIG_V1) {
        return;
    }

    US_PD_eeconfig_init_kb_mem();

    us_kb_config.pd.cpi_idx = bk->v1.pd.cpi_idx;
    us_kb_config.pd.scrl_div = bk->v1.pd.scrl_div;
    us_kb_config.pd.rotation_angle = bk->v1.pd.rotation_angle;

    us_kb_config.pd.flags.scrl_inv = bk->v1.pd.flags.scrl_inv;
    us_kb_config.pd.flags.auto_mouse = bk->v1.pd.flags.auto_mouse;
}

void US_PD_matrix_init_kb(void) {
    // is safe to just read CPI setting since matrix init
    // comes before pointing device init.
    if (eeconfig_is_enabled()) {
        US_EECONFIG_keyboard_post_init_kb();
    }
}

void US_PD_eeconfig_init_kb_mem(void) {
    us_kb_config.pd.cpi_idx = COCOT_CPI_DEFAULT;
    us_kb_config.pd.scrl_div = COCOT_SCROLL_DIV_DEFAULT;
    us_kb_config.pd.rotation_angle = COCOT_ROTATION_DEFAULT;

    us_kb_config.pd.flag_raw = 0u;
    us_kb_config.pd.flags.scrl_inv = COCOT_SCROLL_INV_DEFAULT;
    us_kb_config.pd.flags.auto_mouse = COCOT_AUTO_MOUSE_MODE;
}

void US_PD_pointing_device_init_kb(void) {
    US_EECONFIG_keyboard_post_init_kb();
}

void US_PD_keyboard_post_init_kb(void) {
    const uint8_t cpi_idx = US_EECONFIG_get_pd_cpi_idx_from_mem();
    if (us_cpi_array_size <= cpi_idx) {
        US_EECONFIG_update_pd_cpi_idx_to_eeprom(COCOT_CPI_DEFAULT);
    }

    const uint8_t scrl_div_idx = US_EECONFIG_get_pd_scrl_div_from_mem();
    if (us_scrl_div_array_size <= scrl_div_idx) {
        US_EECONFIG_update_pd_scrl_div_to_eeprom(COCOT_SCROLL_DIV_DEFAULT);
    }

    const uint8_t rotation_angle_idx = US_EECONFIG_get_pd_rotation_angle_from_mem();
    if (us_angle_array_size <= rotation_angle_idx) {
        US_EECONFIG_update_pd_rotation_angle_to_eeprom(COCOT_ROTATION_DEFAULT);
    }

    pointing_device_set_cpi(us_cpi_array[US_EECONFIG_get_pd_cpi_idx_from_mem()]);
    set_auto_mouse_enable(US_EECONFIG_get_pd_auto_mouse_from_mem());
}

layer_state_t US_PD_layer_state_set_kb(layer_state_t state) {
    switch(get_highest_layer(remove_auto_mouse_layer(state, true))) {
        case SCRL_MODE_LAYER_BEGIN ... SCRL_MODE_LAYER_END:
            us_is_scrl_mode = true;
            state = remove_auto_mouse_layer(state, false);
            set_auto_mouse_enable(false);
            break;
        case SCRL_MODE_LAYER_END + 1 ... DYNAMIC_KEYMAP_LAYER_COUNT - 1:
            us_is_scrl_mode = false;
            break;
        default:
            us_is_scrl_mode = false;
            set_auto_mouse_enable(US_EECONFIG_get_pd_auto_mouse_from_mem() ? true : false);

            break;
    }
    return state;
};

bool US_PD_process_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
#ifndef MOUSEKEY_ENABLE
        // process MS_BTN1~8 by myself
        // See process_action() in quantum/action.c for details.
        case MS_BTN1 ... MS_BTN8: {
            extern void register_button(bool, enum mouse_buttons);
            register_button(record->event.pressed, MOUSE_BTN_MASK(keycode - MS_BTN1));
            return false;
        }
#endif
        case CPI_SW:
            if (record->event.pressed) {
                const uint8_t cur_idx = US_EECONFIG_get_pd_cpi_idx_from_mem();
                const uint8_t next_idx = (cur_idx + 1) % us_cpi_array_size;
                US_EECONFIG_update_pd_cpi_idx_to_eeprom(next_idx);

                pointing_device_set_cpi(us_cpi_array[next_idx]);
            }
            break;

        case SCRL_SW:
            if (record->event.pressed) {
                const uint8_t cur_idx = US_EECONFIG_get_pd_scrl_div_from_mem();
                const uint8_t next_idx = (cur_idx + 1) % us_scrl_div_array_size;
                US_EECONFIG_update_pd_scrl_div_to_eeprom(next_idx);
            }
            break;

        case ROT_R15:
            if (record->event.pressed) {
                const uint8_t cur_idx = US_EECONFIG_get_pd_rotation_angle_from_mem();
                const uint8_t next_idx = (cur_idx + 1) % us_angle_array_size;
                US_EECONFIG_update_pd_rotation_angle_to_eeprom(next_idx);
            }
            break;

        case ROT_L15:
            if (record->event.pressed) {
                const uint8_t cur_idx = US_EECONFIG_get_pd_rotation_angle_from_mem();
                const uint8_t next_idx = (us_angle_array_size + cur_idx - 1) % us_angle_array_size;
                US_EECONFIG_update_pd_rotation_angle_to_eeprom(next_idx);
            }
            break;

        case SCRL_MO:
            us_is_scrl_mode ^= 1;
            break;

        case SCRL_TO:
            if (record->event.pressed) {
                us_is_scrl_mode ^= 1;
            }
            break;

        case SCRL_IN:
            if (record->event.pressed) {
                const bool cur_val = US_EECONFIG_get_pd_scrl_inv_from_mem();
                US_EECONFIG_update_pd_scrl_inv_to_eeprom(!cur_val);
            }
            break;

        case AM_TOG:
            if(record->event.pressed) {
                const bool cur_flag = US_EECONFIG_get_pd_auto_mouse_from_mem();
                const bool next_flag = !cur_flag;
                US_EECONFIG_update_pd_auto_mouse_to_eeprom(next_flag);

                set_auto_mouse_enable(next_flag);
            }
            return false;
    }

    return true;
}

report_mouse_t US_PD_pointing_device_task_kb(report_mouse_t mouse_report) {
    static float x_accumulator = 0.0;
    static float y_accumulator = 0.0;
    static float prev_x = 0.0, prev_y = 0.0;

    float sensitivity = 0.5;           // Movement sensitivity
    float smoothing_factor = 0.7;     // Smoothing factor
    float sensitivity_multiplier = 1.5; // Base sensitivity multiplier

    // Apply rotation angle adjustment
    double rad = us_angle_array[US_EECONFIG_get_pd_rotation_angle_from_mem()] * (M_PI / 180) * -1;
    float rotated_x = -(mouse_report.x * cos(rad) - mouse_report.y * sin(rad)); // Reverse X-direction
    float rotated_y = mouse_report.x * sin(rad) + mouse_report.y * cos(rad);

    // Apply smoothing to the rotated values
    float smoothed_x = prev_x * smoothing_factor + rotated_x * (1.0 - smoothing_factor);
    float smoothed_y = prev_y * smoothing_factor + rotated_y * (1.0 - smoothing_factor);
    prev_x = smoothed_x;
    prev_y = smoothed_y;

    // Calculate the magnitude of movement
    float movement_magnitude = sqrt(smoothed_x * smoothed_x + smoothed_y * smoothed_y);

    // Dynamic multiplier: slower for small movements, faster for large
    float dynamic_multiplier = 1.0 + movement_magnitude / 10.0; // Adjust divisor for desired scaling
    dynamic_multiplier = fmin(fmax(dynamic_multiplier, 0.5), 3.0); // Clamp between 0.5 and 3.0

    // Apply dynamic multiplier to smoothed values
    smoothed_x *= sensitivity_multiplier * dynamic_multiplier;
    smoothed_y *= sensitivity_multiplier * dynamic_multiplier;

    // Scroll mode handling
    if (us_is_scrl_mode) {
        static int h_acm = 0, v_acm = 0;

        // Determine scroll direction
        if (abs((int)smoothed_x) > abs((int)smoothed_y)) {
            smoothed_y = 0; // Horizontal scroll
        } else {
            smoothed_x = 0; // Vertical scroll
        }

        // Accumulate scroll values
        if (US_EECONFIG_get_pd_scrl_inv_from_mem()) {
            h_acm += smoothed_x;
            v_acm -= smoothed_y;
        } else {
            h_acm -= smoothed_x;
            v_acm += smoothed_y;
        }

        // Calculate scroll values with division factor
        const uint8_t scrl_div = US_EECONFIG_get_pd_scrl_div_from_mem();
        int8_t h_scroll = h_acm >> us_scrl_div_array[scrl_div];
        int8_t v_scroll = v_acm >> us_scrl_div_array[scrl_div];

        // Apply scroll to mouse report
        if (h_scroll != 0) {
            mouse_report.h += h_scroll;
            h_acm -= h_scroll << us_scrl_div_array[scrl_div];
        }
        if (v_scroll != 0) {
            mouse_report.v += v_scroll;
            v_acm -= v_scroll << us_scrl_div_array[scrl_div];
        }

        // Reset X/Y movement in scroll mode
        mouse_report.x = 0;
        mouse_report.y = 0;
    } else {
        // Movement smoothing and accumulation for normal mode
        x_accumulator += smoothed_x * sensitivity;
        y_accumulator += smoothed_y * sensitivity;

        if (fabs(x_accumulator) >= 1.0) {
            mouse_report.x = (int8_t)x_accumulator;
            x_accumulator -= mouse_report.x;
        } else {
            mouse_report.x = 0;
        }

        if (fabs(y_accumulator) >= 1.0) {
            mouse_report.y = (int8_t)y_accumulator;
            y_accumulator -= mouse_report.y;
        } else {
            mouse_report.y = 0;
        }
    }

    return mouse_report;
}

bool US_PD_is_mouse_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch(keycode) {
      case KC_LCTL:
        return true;
      case KC_LSFT:
        return true;
      case SCRL_MO:
        return true;
      default:
        return false;
    }
}
#endif
