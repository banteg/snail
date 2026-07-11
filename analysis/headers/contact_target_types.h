#ifndef CONTACT_TARGET_TYPES_H
#define CONTACT_TARGET_TYPES_H

typedef int int32_t;
typedef unsigned int uint32_t;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct ContactTargetObject {
    void* vtable;
    int32_t list_flags;
} ContactTargetObject;

typedef struct ContactTargetEntry {
    int32_t kind;
    Vec3 position;
    float radius;
    ContactTargetObject* object;
} ContactTargetEntry;

typedef struct EnemyManager {
    int32_t count;
    ContactTargetEntry entries[256];
} EnemyManager;

#endif
