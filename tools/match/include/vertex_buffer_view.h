// Shared Direct3D vertex-buffer ABI view.
#ifndef VERTEX_BUFFER_VIEW_H
#define VERTEX_BUFFER_VIEW_H

struct Direct3DVertexBuffer8;

struct Direct3DVertexBuffer8Vtbl {
    char unknown_00[0x2c];
    int (__stdcall* Lock)(Direct3DVertexBuffer8* self, unsigned int offset,
        unsigned int size, void** data, unsigned int flags);
    int (__stdcall* Unlock)(Direct3DVertexBuffer8* self);
};

struct Direct3DVertexBuffer8 {
    Direct3DVertexBuffer8Vtbl* vtbl;
};

typedef Direct3DVertexBuffer8 VertexBuffer;
typedef Direct3DVertexBuffer8 ObjectVertexBuffer;

struct RendererState {
    char unknown_00[0x08];
    VertexBuffer* sprite_vertex_buffer; // +0x08
};

typedef char VertexBuffer_must_be_0x04[
    (sizeof(VertexBuffer) == 0x04) ? 1 : -1];
typedef char Direct3DVertexBuffer8Vtbl_must_be_0x34[
    (sizeof(Direct3DVertexBuffer8Vtbl) == 0x34) ? 1 : -1];
typedef char RendererState_must_be_at_least_0x0c[
    (sizeof(RendererState) == 0x0c) ? 1 : -1];

#endif
