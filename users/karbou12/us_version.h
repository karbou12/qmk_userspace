// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define US_FW_VER_MAJOR_OFFSET 8
#define US_FW_VER_MINOR_OFFSET 4

#define US_CONCAT_VER(M, m, p) ((M << US_FW_VER_MAJOR_OFFSET) | (m << US_FW_VER_MINOR_OFFSET) | p)
#define FUVS(x) US_FW_USER_VER_ ## x

#define US_FW_USER_VER_MAJOR 1
#define US_FW_USER_VER_MINOR 0
#define US_FW_USER_VER_PATCH 0

