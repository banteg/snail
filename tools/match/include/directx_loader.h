#ifndef DIRECTX_LOADER_H
#define DIRECTX_LOADER_H

#include "duplicate_vertices.h"
#include "object_render_types.h"

class DirectXLoader {
public:
    void* initialize_directx_loader(); // @ 0x405c90
    int load_x_mesh(char* mesh_path, Object* object, unsigned char options_flags); // @ 0x405640
    ObjectAnimation* load_x_animation_clip(char* mesh_name, Object* object); // @ 0x405d60

    char* animation_bytes; // +0x00
    int field_04;          // +0x04
    char pad_008[0x5e08 - 0x008];
    DuplicateVertexBuffer duplicate_vertices; // +0x5e08
};

#endif
