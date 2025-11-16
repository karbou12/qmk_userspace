// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "us_utils.h"
#include "us_eeconfig.h"

uint8_t US_UTIL_get_current_layer(const layer_state_t state) {
    const uint8_t layer = get_highest_layer(state);
    return (layer == US_FIELD_LAYER0) ? get_highest_layer(default_layer_state) : layer;
}
