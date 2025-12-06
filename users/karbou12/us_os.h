// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include "karbou12.h"
#include "us_eeconfig.h"

#ifdef OS_DETECTION_ENABLE
extern void US_OS_eeconfig_migrate_mem(const us_user_config_u* bk, const uint32_t prev_ver);
extern void US_OS_eeconfig_init_mem(void);
extern bool US_OS_process_detected_host_os_user(os_variant_t detected_os);
extern bool US_OS_process_record_user(uint16_t keycode, keyrecord_t *record);
#endif
