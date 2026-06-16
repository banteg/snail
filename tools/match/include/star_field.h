// Shared star-field view, cross-checked by exact hide/unhide star field.
#ifndef STAR_FIELD_H
#define STAR_FIELD_H

#include "sprite.h"

class StarFieldEntry {
public:
    int active; // +0x00
    char pad_04[0x1c - 0x04];
    Sprite* sprite; // +0x1c
    char pad_20[0x0c];
};

class StarField {
public:
    int destroy_star_field(); // @ 0x434270
    void open_star_field(int star_count); // @ 0x4342c0
    int initialize_star_field(); // @ 0x434310
    int hide_star_field(); // @ 0x434670
    int unhide_star_field(); // @ 0x4346b0
    void update_star_field(); // @ 0x4346f0
    void* update_star_positions(float fade); // @ 0x434800

    char pad_00[0x38];
    int state; // +0x38, star-field lifecycle state
    StarFieldEntry* entries; // +0x3c
    int count; // +0x40
    float fade; // +0x44
    float fade_step; // +0x48
};

#endif
