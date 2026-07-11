// Shared star-manager view, cross-checked by the exact lifecycle helpers.
// iOS symbols name the concrete owner cRStarManager; the curated Windows
// function names retain the established star_field wording.
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
    float travel_distance; // +0x24, advances by speed and wraps after 35
    float alpha_scale; // +0x28, per-entry multiplier for sprite alpha
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

    // +0x00..+0x37 is the constructed BodBase prefix. The virtual callback
    // declaration models its callback-table word, so only the inherited tail
    // remains explicit here instead of adding a second synthetic vptr.
    char bod_base_tail[0x38 - 0x04];
    int state; // +0x38, star-field lifecycle state
    StarFieldEntry* entries; // +0x3c
    int count; // +0x40
    float fade; // +0x44
    float fade_step; // +0x48
};

typedef char StarField_must_be_0x4c[(sizeof(StarField) == 0x4c) ? 1 : -1];

#endif
