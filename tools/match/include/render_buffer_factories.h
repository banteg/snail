// Thin factory interfaces for the Direct3D-backed object render buffers.
#ifndef RENDER_BUFFER_FACTORIES_H
#define RENDER_BUFFER_FACTORIES_H

#include "object_render_types.h"

struct VertexBufferFactory {
    void* create_vertex_buffer(int vertex_count, int fvf); // @ 0x4114b0
};

struct IndexBufferFactory {
    ObjectIndexBuffer* create_index_buffer(int index_count); // @ 0x4115d0
};

extern VertexBufferFactory g_direct3d_renderer; // data_4f7458
extern IndexBufferFactory g_object_index_buffer_factory; // data_5000fc

#endif
