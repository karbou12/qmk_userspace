// Copyright 2020 Alexander Tulloh
// Copyright 2022 aki27 (@aki27kbd)
// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include "karbou12.h"

#ifdef POINTING_DEVICE_ENABLE
extern void US_PD_matrix_init_kb(void);
extern void US_PD_eeconfig_init_kb_mem(void);
extern void US_PD_pointing_device_init_kb(void);
extern void US_PD_keyboard_post_init_kb(void);
extern layer_state_t US_PD_layer_state_set_kb(layer_state_t state);
extern bool US_PD_process_record_kb(uint16_t keycode, keyrecord_t* record);
extern report_mouse_t US_PD_pointing_device_task_kb(report_mouse_t mouse_report);
extern bool US_PD_is_mouse_record_kb(uint16_t keycode, keyrecord_t* record);
#endif
