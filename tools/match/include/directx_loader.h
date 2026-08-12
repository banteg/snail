// Root-owned cRDirectX at cRGame +0x48e00. The object contains
// the animation script bytes, the complete fixed cached-mesh bank, and the
// duplicate-vertex workspace used while parsing animation clips.
#ifndef DIRECTX_LOADER_H
#define DIRECTX_LOADER_H

#include "duplicate_vertices.h"
#include "bod_types.h"
#include "object_render_types.h"

enum {
    DIRECTX_LOADER_CACHED_X_MESH_SLOT_COUNT = 0x80,
};

class CachedXMeshSlot : public BodBase {
public:
    CachedXMeshSlot* initialize_cached_x_mesh_slot(); // @ 0x408470

    char unknown_38[0x3c - 0x38];
    char name[0x80]; // +0x3c
};

class cRDirectX {
public:
    void Init(); // @ 0x405c90
    void Load(char* mesh_path, Object* object, int options_flags); // @ 0x405640
    int ModelAdd(char* mesh_name); // @ 0x405cc0
    void LoadAnim(char* mesh_name, Object* object); // @ 0x405d60

    char* animation_bytes; // +0x00
    int cached_x_mesh_count; // +0x04
    CachedXMeshSlot cached_x_mesh_slots[DIRECTX_LOADER_CACHED_X_MESH_SLOT_COUNT]; // +0x08
    cRDuplicateVertices duplicate_vertices; // +0x5e08
};

typedef char CachedXMeshSlot_must_be_0xbc[
    (sizeof(CachedXMeshSlot) == 0xbc) ? 1 : -1];
typedef char cRDirectX_must_be_0x5e10[
    (sizeof(cRDirectX) == 0x5e10) ? 1 : -1];

#endif
