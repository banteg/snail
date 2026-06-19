// Shared Direct3D vertex-buffer wrappers, partial.
//
// The vtable shape is scratch-local because Lock uses the caller's vertex
// payload type. The stable shared part is the vtbl pointer and renderer slot.
#ifndef VERTEX_BUFFER_VIEW_H
#define VERTEX_BUFFER_VIEW_H

struct VertexBufferVtbl;

struct VertexBuffer {
    VertexBufferVtbl* vtbl;
};

struct RendererState {
    char unknown_00[0x08];
    VertexBuffer* sprite_vertex_buffer; // +0x08
};

typedef char VertexBuffer_must_be_0x04[
    (sizeof(VertexBuffer) == 0x04) ? 1 : -1];
typedef char RendererState_must_be_at_least_0x0c[
    (sizeof(RendererState) == 0x0c) ? 1 : -1];

#endif
