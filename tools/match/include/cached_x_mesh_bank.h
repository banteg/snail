// Shared runtime cache for loaded X meshes at Game +0x48e00.
#ifndef CACHED_X_MESH_BANK_H
#define CACHED_X_MESH_BANK_H

#include "bod_types.h"

class CachedXMeshSlot : public BodBase {
public:
    CachedXMeshSlot* initialize_cached_x_mesh_slot(); // @ 0x408470

    char unknown_38[0x3c - 0x38];
    char name[0x80]; // +0x3c
};

class CachedXMeshBank {
public:
    void* unknown_00;
    int count; // +0x04
    CachedXMeshSlot slots[1]; // +0x08

    int load_x_mesh(char* mesh_path, void* object, unsigned char options_flags); // @ 0x405640
    int load_or_reuse_cached_x_mesh(char* mesh_name); // @ 0x405cc0
};

typedef char CachedXMeshSlot_must_be_0xbc[
    (sizeof(CachedXMeshSlot) == 0xbc) ? 1 : -1];
typedef char CachedXMeshBank_one_slot_must_be_0xc4[
    (sizeof(CachedXMeshBank) == 0xc4) ? 1 : -1];

#endif
