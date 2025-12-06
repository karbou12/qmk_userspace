// Copyright 2025 takashicompany (@takashicompany)
// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 9
#define VIAL_KEYBOARD_UID {0x6B, 0x7B, 0xD1, 0x10, 0x4E, 0x90, 0xAE, 0x6F}
#define VIAL_UNLOCK_COMBO_ROWS {0, 0}
#define VIAL_UNLOCK_COMBO_COLS {1, 11}

// keep the largest size ever for datablock area.
// it is required gravity45 only
// because gravity45 is released as officially and keep the largest size ever even if rgb or os setting is disable.
#define EECONFIG_USER_RGB_DATA_MIN_SIZE 4 * DYNAMIC_KEYMAP_LAYER_COUNT + 2
#define EECONFIG_USER_OS_DATA_MIN_SIZE 5

#define EECONFIG_USER_DATA_MIN_SIZE (EECONFIG_USER_RGB_DATA_MIN_SIZE + EECONFIG_USER_OS_DATA_MIN_SIZE)

#if defined(EECONFIG_USER_DATA_SIZE) && (EECONFIG_USER_DATA_MIN_SIZE > EECONFIG_USER_DATA_SIZE)
#undef EECONFIG_USER_DATA_SIZE
#define EECONFIG_USER_DATA_SIZE EECONFIG_USER_DATA_MIN_SIZE
#endif
