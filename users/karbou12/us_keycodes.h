// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include "karbou12.h"

enum custom_keycodes {
    USR_RESET = QK_KB_0,
#ifdef POINTING_DEVICE_ENABLE
    CPI_SW,
    SCRL_SW,
    ROT_R15,
    ROT_L15,
    SCRL_MO,
    SCRL_TO,
    SCRL_IN,
    AM_TOG,
#endif
#if defined(RGBLIGHT_LAYERS) || defined(RGB_MATRIX_ENABLE)
    USR_RGB_LAYER_TOG,
    USR_RGB_RETAIN_VAL_TOG,
    USR_RGB_LAYER_HUE_UP,
    USR_RGB_LAYER_HUE_DOWN,
    USR_RGB_LAYER_SAT_UP,
    USR_RGB_LAYER_SAT_DOWN,
    USR_RGB_LAYER_VAL_UP,
    USR_RGB_LAYER_VAL_DOWN,
    USR_RGB_AUTO_SAVE_TOG,
#endif
#ifdef OS_DETECTION_ENABLE
    USR_OS_DEFAULT_LAYER,
#endif
    NEW_USR_SAFE_RANGE,
};
