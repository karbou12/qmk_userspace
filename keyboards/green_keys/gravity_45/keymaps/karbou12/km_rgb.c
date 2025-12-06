// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
#include "us_rgb.h"

#ifdef RGBLIGHT_LAYERS
const hsv_t PROGMEM km_hsv_layer0[]   = HSV_LAYER_SEGMENTS({HSV_TURQUOISE});
const hsv_t PROGMEM km_hsv_layer1[]   = HSV_LAYER_SEGMENTS({HSV_CYAN});
const hsv_t PROGMEM km_hsv_layer2[]   = HSV_LAYER_SEGMENTS({HSV_MAGENTA});
const hsv_t PROGMEM km_hsv_layer3[]   = HSV_LAYER_SEGMENTS({HSV_GREEN});
const hsv_t PROGMEM km_hsv_layer4[]   = HSV_LAYER_SEGMENTS({HSV_YELLOW});
const hsv_t PROGMEM km_hsv_layer5[]   = HSV_LAYER_SEGMENTS({HSV_PURPLE});
const hsv_t PROGMEM km_hsv_layer6[]   = HSV_LAYER_SEGMENTS({HSV_AZURE});
const hsv_t PROGMEM km_hsv_layer7[]   = HSV_LAYER_SEGMENTS({HSV_SPRINGGREEN});
const hsv_t PROGMEM km_hsv_layer8[]   = HSV_LAYER_SEGMENTS({HSV_ORANGE});
const hsv_t PROGMEM km_hsv_capsword[] = HSV_LAYER_SEGMENTS({HSV_RED});
const hsv_t PROGMEM km_hsv_OFF[]      = HSV_LAYER_SEGMENTS({HSV_OFF});

const hsv_t * const PROGMEM km_hsv_layers[] = HSV_LAYERS_LIST(
    km_hsv_layer0,
    km_hsv_layer1,
    km_hsv_layer2,
    km_hsv_layer3,
    km_hsv_layer4,
    km_hsv_layer5,
    km_hsv_layer6,
    km_hsv_layer7,
    km_hsv_layer8,
    km_hsv_capsword
);

#ifdef RGBLIGHT_LAYER_BLINK
const rgblight_segment_t PROGMEM km_reset_layer[] =       RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_WHITE});
const rgblight_segment_t PROGMEM km_turn_on_layer[] =     RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_GOLD});
const rgblight_segment_t PROGMEM km_turn_off_layer[] =    RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_RED});
const rgblight_segment_t PROGMEM km_set_default_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_GREEN});

const rgblight_segment_t * const PROGMEM km_blink_layers[] = RGBLIGHT_LAYERS_LIST(
    km_reset_layer,
    km_turn_on_layer,
    km_turn_off_layer,
    km_set_default_layer
);
#endif
#endif
