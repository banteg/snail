// Thin factory interfaces for the Direct3D-backed object render buffers.
#ifndef RENDER_BUFFER_FACTORIES_H
#define RENDER_BUFFER_FACTORIES_H

#include "object_render_types.h"

struct IndexBufferFactory {
    ObjectIndexBuffer* create_index_buffer(int index_count); // @ 0x4115d0

    int count; // +0x00
    ObjectIndexBuffer buffers[0xbb8]; // +0x04
};

typedef char IndexBufferFactory_must_be_0x2ee4[
    (sizeof(IndexBufferFactory) == 0x2ee4) ? 1 : -1];

#endif
