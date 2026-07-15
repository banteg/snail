// Authored cRStarManager owner, cross-checked by the complete lifecycle.
// Curated Windows function names retain the established star_field wording.
#ifndef STAR_MANAGER_H
#define STAR_MANAGER_H

#include "sprite.h"

class StarManagerEntry {
public:
    int active; // +0x00
    Vector3 position; // +0x04
    Vector3 velocity; // +0x10
    Sprite* sprite; // +0x1c
    float speed; // +0x20
    float travel_distance; // +0x24, advances by speed and wraps after 35
    float alpha_scale; // +0x28, per-entry multiplier for sprite alpha
};

typedef char StarManagerEntry_must_be_0x2c[
    (sizeof(StarManagerEntry) == 0x2c) ? 1 : -1];

class StarManager {
public:
    virtual void update_star_field_callback(); // vtable slot 0, points to update_star_field
    void destroy_star_field(); // @ 0x434270, cRStarManager::UnInit
    void open_star_field(int star_count); // @ 0x4342c0, cRStarManager::Open
    void initialize_star_field(); // @ 0x434310, cRStarManager::Init
    void hide_star_field(); // @ 0x434670, cRStarManager::Hide
    void unhide_star_field(); // @ 0x4346b0, cRStarManager::UnHide
    void update_star_field(); // @ 0x4346f0, cRStarManager::AI
    void update_star_positions(float fade); // @ 0x434800, cRStarManager::UpdateStars

    // +0x00..+0x37 is the constructed BodBase prefix. The virtual callback
    // declaration models its callback-table word, so only the inherited tail
    // remains explicit here instead of adding a second synthetic vptr.
    char bod_base_tail[0x38 - 0x04];
    int state; // +0x38, star-manager lifecycle state
    StarManagerEntry* entries; // +0x3c
    int count; // +0x40
    float fade; // +0x44
    float fade_step; // +0x48
};

typedef char StarManager_must_be_0x4c[
    (sizeof(StarManager) == 0x4c) ? 1 : -1];

#endif
