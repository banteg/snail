// Shared star-field view, cross-checked by exact hide/unhide star field.
#ifndef STAR_FIELD_H
#define STAR_FIELD_H

#include "sprite.h"

class StarFieldEntry {
public:
    int active; // +0x00
    Vector3 position; // +0x04
    Vector3 velocity; // +0x10
    Sprite* sprite; // +0x1c
    float speed; // +0x20
    float phase; // +0x24
    float twinkle_scale; // +0x28
};

typedef char StarFieldEntry_must_be_0x2c[
    (sizeof(StarFieldEntry) == 0x2c) ? 1 : -1];

class StarField {
public:
    virtual int update_star_field_callback(); // vtable slot 0, points to update_star_field
    int destroy_star_field(); // @ 0x434270
    void open_star_field(int star_count); // @ 0x4342c0
    int initialize_star_field(); // @ 0x434310
    int hide_star_field(); // @ 0x434670
    int unhide_star_field(); // @ 0x4346b0
    void update_star_field(); // @ 0x4346f0
    void* update_star_positions(float fade); // @ 0x434800

    char pad_04[0x38 - 0x04];
    int state; // +0x38, star-field lifecycle state
    StarFieldEntry* entries; // +0x3c
    int count; // +0x40
    float fade; // +0x44
    float fade_step; // +0x48
};

typedef char StarField_must_be_0x4c[(sizeof(StarField) == 0x4c) ? 1 : -1];

#endif
