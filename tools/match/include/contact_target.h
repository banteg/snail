// Per-frame subgame contact target registry, partial.
#ifndef CONTACT_TARGET_H
#define CONTACT_TARGET_H

#include "vector3.h"

const int CONTACT_TARGET_CAPACITY = 256;

struct ContactTargetObject {
    void* vtable;            // +0x00, renderable/contact objects share this prefix
    int list_flags;          // +0x04, 0x1000 suppresses contact appends
};

struct ContactTargetEntry {
    int kind;                    // +0x00
    Vector3 position;            // +0x04
    float radius;                // +0x10
    ContactTargetObject* object; // +0x14
};
typedef char ContactTargetEntry_must_be_0x18[
    (sizeof(ContactTargetEntry) == 0x18) ? 1 : -1];

class ContactTargetRegistry {
public:
    void initialize_enemy_manager(); // @ 0x415e20, iOS cREnemyManager::Init()
    ContactTargetEntry* search_path_for_golb(
        const Vector3* position); // @ 0x415e30
    void append_subgame_contact_target(
        const Vector3* position,
        float radius,
        int kind,
        ContactTargetObject* object); // @ 0x415ef0

    int count;                    // +0x00
    ContactTargetEntry entries[CONTACT_TARGET_CAPACITY]; // +0x04, embedded frame storage
};

typedef char ContactTargetRegistry_must_be_0x1804[
    (sizeof(ContactTargetRegistry) == 0x1804) ? 1 : -1];

#endif
