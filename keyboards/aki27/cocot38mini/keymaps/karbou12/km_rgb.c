#include "quantum.h"
#include "us_rgb.h"

#ifdef CUSTOM_RGBMATRIX
const hsv_t PROGMEM km_hsv_layer0[] = HSV_LAYER_SEGMENTS({HSV_CYAN});
const hsv_t PROGMEM km_hsv_layer1[] = HSV_LAYER_SEGMENTS({HSV_YELLOW});
const hsv_t PROGMEM km_hsv_layer2[] = HSV_LAYER_SEGMENTS({HSV_GREEN});
const hsv_t PROGMEM km_hsv_layer3[] = HSV_LAYER_SEGMENTS({HSV_CORAL});
const hsv_t PROGMEM km_hsv_layer4[] = HSV_LAYER_SEGMENTS({HSV_MAGENTA});
const hsv_t PROGMEM km_hsv_layer5[] = HSV_LAYER_SEGMENTS({HSV_PURPLE});
const hsv_t PROGMEM km_hsv_layer6[] = HSV_LAYER_SEGMENTS({HSV_CHARTREUSE});
const hsv_t PROGMEM km_hsv_layer7[] = HSV_LAYER_SEGMENTS({HSV_ORANGE});
const hsv_t PROGMEM km_hsv_layer8[] = HSV_LAYER_SEGMENTS({HSV_PURPLE});
const hsv_t PROGMEM km_hsv_matrix_layer[] = HSV_LAYER_SEGMENTS({HSV_YELLOW});
const hsv_t PROGMEM km_hsv_capsword[] = HSV_LAYER_SEGMENTS({HSV_RED});
const hsv_t PROGMEM km_hsv_off[] = HSV_LAYER_SEGMENTS({HSV_OFF});

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
    km_hsv_matrix_layer,
    km_hsv_capsword
);
#endif
