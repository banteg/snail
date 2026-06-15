// Shared salt hazard list-anchor view. The slot body remains split because
// update_salt_hazard reads past the 0x98 pool stride into the next slot.
#ifndef SALT_HAZARD_TYPES_H
#define SALT_HAZARD_TYPES_H

struct SaltHazardSlot;

struct SaltListAnchor {
    char unknown_00[4];
    SaltHazardSlot* first;    // +0x04
    SaltHazardSlot* free_top; // +0x08
};

#endif
