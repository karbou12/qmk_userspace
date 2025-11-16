// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include "us_version.h"

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 3000

#define EECONFIG_USER_DATA_SIZE 43 // keep the largest size ever.
#define EECONFIG_USER_DATA_VERSION US_CONCAT_VER(FVS(MAJOR), FVS(MINOR), FVS(PATCH))
