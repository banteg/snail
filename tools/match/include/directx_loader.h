// Root-owned DirectX/X-file loader at GameRoot +0x48e00. The object contains
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

class DirectXLoader {
public:
    void initialize_directx_loader(); // @ 0x405c90
    void load_x_mesh(char* mesh_path, Object* object, unsigned char options_flags); // @ 0x405640
    int load_or_reuse_cached_x_mesh(char* mesh_name); // @ 0x405cc0
    void load_x_animation_clip(char* mesh_name, Object* object); // @ 0x405d60

    char* animation_bytes; // +0x00
    int cached_x_mesh_count; // +0x04
    CachedXMeshSlot cached_x_mesh_slots[DIRECTX_LOADER_CACHED_X_MESH_SLOT_COUNT]; // +0x08
    DuplicateVertexBuffer duplicate_vertices; // +0x5e08
};

typedef char CachedXMeshSlot_must_be_0xbc[
    (sizeof(CachedXMeshSlot) == 0xbc) ? 1 : -1];
typedef char DirectXLoader_must_be_0x5e10[
    (sizeof(DirectXLoader) == 0x5e10) ? 1 : -1];

#endif
