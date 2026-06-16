#ifndef OBJECT_RENDER_TYPES_H
#define OBJECT_RENDER_TYPES_H

struct ObjectVertexBufferVtbl;

struct ObjectVertexBuffer {
    ObjectVertexBufferVtbl* vtbl;
};

struct ObjectRenderBuffers {
    char unknown_00[0x08];
    ObjectVertexBuffer* vertex_buffer; // +0x08
};

struct ObjectRenderVertex {
    float x;
    float y;
    float z;
    unsigned int diffuse;
    float u;
    float v;
};

struct ObjectGroupedVertex {
    float x;              // +0x00
    float y;              // +0x04
    float z;              // +0x08
    unsigned int diffuse; // +0x0c
    float u;              // +0x10
    float v;              // +0x14, stored as 1.0 - source v
    int source_vertex;    // +0x18
};

struct RenderObjectDeviceVtbl;

struct RenderObjectDevice {
    RenderObjectDeviceVtbl* vtbl;
};

#endif
