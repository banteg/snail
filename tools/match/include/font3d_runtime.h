// Fixed-capacity 3D-font glyph materialization state.
#ifndef FONT3D_RUNTIME_H
#define FONT3D_RUNTIME_H

#include "bod_types.h"

enum {
    FONT_GLYPH_CAPACITY = 128,
};

extern BodBase g_font3d_bods[FONT_GLYPH_CAPACITY]; // data_7754e8
extern float g_font3d_scales[FONT_GLYPH_CAPACITY]; // data_7770e8

#endif
