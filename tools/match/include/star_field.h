// Shared star-field entry view, cross-checked by hide/unhide star field.
#ifndef STAR_FIELD_H
#define STAR_FIELD_H

#include "sprite.h"

class StarFieldEntry {
public:
    char pad_00[0x1c];
    Sprite* sprite; // +0x1c
    char pad_20[0x0c];
};

#endif
