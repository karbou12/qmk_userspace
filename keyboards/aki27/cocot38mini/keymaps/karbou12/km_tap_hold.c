#include "quantum.h"

char chordal_hold_handedness(keypos_t key) {
    if (key.row == 3 && key.col == 4) { // center key
        return '*';
    }

    return (key.col < MATRIX_COLS / 2) ? 'L' : 'R';
}
