// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include "karbou12.h"

#ifdef CUSTOM_TAP_DANCE_ENABLE
#define TAP_DANCE(tp, hld, dbl_tp, tp_hld, term) \
  {.on_tap = (tp), .on_hold = (hld), .on_double_tap = (dbl_tp), \
   .on_tap_hold = (tp_hld), .custom_tapping_term = term}
extern const vial_tap_dance_entry_t km_tap_dances[];
extern const uint16_t km_tap_dance_size;
void US_TD_keyboard_post_init_user(void);
#endif
