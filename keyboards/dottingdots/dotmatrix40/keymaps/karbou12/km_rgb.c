// Copyright 2025 Tano Karbou (github: karbou12 / X: @karbou_12)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

#ifdef RGBLIGHT_LAYERS
const rgblight_segment_t PROGMEM km_layer0_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_YELLOW});
const rgblight_segment_t PROGMEM km_layer1_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_GREEN});
const rgblight_segment_t PROGMEM km_layer2_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_CYAN});
const rgblight_segment_t PROGMEM km_layer3_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_ORANGE});
const rgblight_segment_t PROGMEM km_layer4_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_SPRINGGREEN});
const rgblight_segment_t PROGMEM km_layer5_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_GREEN});
const rgblight_segment_t PROGMEM km_layer6_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_CHARTREUSE});
const rgblight_segment_t PROGMEM km_layer7_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_ORANGE});
const rgblight_segment_t PROGMEM km_layer8_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_PURPLE});
const rgblight_segment_t PROGMEM km_layer9_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_MAGENTA});
const rgblight_segment_t PROGMEM km_capsword_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_RED});
const rgblight_segment_t PROGMEM km_layerOFF_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_OFF});

const rgblight_segment_t * const PROGMEM km_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    km_layer0_layer,
    km_layer1_layer,
    km_layer2_layer,
    km_layer3_layer,
    km_layer4_layer,
    km_layer5_layer,
    km_layer6_layer,
    km_layer7_layer,
    km_layer8_layer,
    km_layer9_layer,
    km_capsword_layer
);

#ifdef RGBLIGHT_LAYER_BLINK
const rgblight_segment_t PROGMEM km_reset_layer[] =       RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_WHITE});
const rgblight_segment_t PROGMEM km_turn_on_layer[] =     RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_GOLD});
const rgblight_segment_t PROGMEM km_turn_off_layer[] =    RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_RED});
const rgblight_segment_t PROGMEM km_set_default_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_GREEN});

const rgblight_segment_t * const PROGMEM km_blink_layers[] = RGBLIGHT_LAYERS_LIST(
    km_reset_layer,
    km_turn_on_layer,
    km_turn_off_layer,
    km_set_default_layer
);
#endif
#endif
