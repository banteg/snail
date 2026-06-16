// Shared star-field view, cross-checked by exact hide/unhide star field.
#ifndef STAR_FIELD_H
#define STAR_FIELD_H

#include "sprite.h"

class StarFieldEntry {
public:
    char pad_00[0x1c];
    Sprite* sprite; // +0x1c
    char pad_20[0x0c];
};

class StarField {
public:
    int hide_star_field(); // @ 0x434670
    int unhide_star_field(); // @ 0x4346b0

    char pad_00[0x38];
    int active; // +0x38
    StarFieldEntry* entries; // +0x3c
    int count; // +0x40
};

#endif
