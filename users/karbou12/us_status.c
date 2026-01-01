// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "us_status.h"

static bool us_is_change_layer_key_pressed_on_non_default_layer = false;
static bool us_is_user_reset_key_pressed_on_non_default_layer = false;

void US_STATUS_set_change_layer_key_pressed_on_non_default_layer(const bool is_pressed) {
    us_is_change_layer_key_pressed_on_non_default_layer = is_pressed;
}

void US_STATUS_set_user_reset_key_pressed_on_non_default_layer(const bool is_pressed) {
    us_is_user_reset_key_pressed_on_non_default_layer = is_pressed;
}

bool US_STATUS_can_set_rgb(void) {
    return us_is_user_reset_key_pressed_on_non_default_layer ? false : true;
}

bool US_STATUS_can_record_rgb(void) {
    return (us_is_change_layer_key_pressed_on_non_default_layer ||
            us_is_user_reset_key_pressed_on_non_default_layer) ? false : true;
}
