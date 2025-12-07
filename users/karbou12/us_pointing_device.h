// Copyright 2020 Alexander Tulloh
// Copyright 2022 aki27 (@aki27kbd)
// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include "karbou12.h"

typedef union {
    uint32_t raw;
    struct {
        uint8_t cpi_idx;
        uint8_t scrl_div;
        uint8_t rotation_angle;
        bool auto_mouse: 1;
        bool scrl_inv: 1;
        bool scrl_mode: 1;
        // report_mouse_t last_mouse;
    };
} cocot_config_t;

extern cocot_config_t cocot_config;

bool cocot_get_scroll_mode(void);
void cocot_set_scroll_mode(bool mode);
