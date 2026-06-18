// Thin factory interfaces for the Direct3D-backed object render buffers.
#ifndef RENDER_BUFFER_FACTORIES_H
#define RENDER_BUFFER_FACTORIES_H

#include "object_render_types.h"

struct VertexBufferFactory {
    ObjectRenderBuffers* create_vertex_buffer(int vertex_count, int fvf); // @ 0x4114b0

    int count; // +0x00
    ObjectRenderBuffers buffers[0xbb8]; // +0x04
};

struct IndexBufferFactory {
    ObjectIndexBuffer* create_index_buffer(int index_count); // @ 0x4115d0

    int count; // +0x00
    ObjectIndexBuffer buffers[0xbb8]; // +0x04
};

typedef char VertexBufferFactory_must_be_0x8ca4[
    (sizeof(VertexBufferFactory) == 0x8ca4) ? 1 : -1];
typedef char IndexBufferFactory_must_be_0x2ee4[
    (sizeof(IndexBufferFactory) == 0x2ee4) ? 1 : -1];

extern VertexBufferFactory g_direct3d_renderer; // data_4f7458
extern IndexBufferFactory g_object_index_buffer_factory; // data_5000fc

#endif
