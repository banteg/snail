// Shared Direct3DDevice8 ABI view.
#ifndef DIRECT3D_DEVICE8_VIEW_H
#define DIRECT3D_DEVICE8_VIEW_H

class Direct3DTexture8;
struct Direct3DDevice8;
struct Direct3DVertexBuffer8;
struct TransformMatrix;

typedef Direct3DVertexBuffer8 VertexBuffer;

struct Direct3DDevice8Vtbl {
    char unknown_000[0x3c];
    int (__stdcall* Present)(Direct3DDevice8* self, void* source_rect,
        void* dest_rect, int dest_window_override, void* dirty_region);
    char unknown_040[0x88 - 0x40];
    int (__stdcall* BeginScene)(Direct3DDevice8* self);
    int (__stdcall* EndScene)(Direct3DDevice8* self);
    int (__stdcall* Clear)(Direct3DDevice8* self, unsigned int count, void* rects,
        unsigned int flags, unsigned int color, float z, unsigned int stencil);
    int (__stdcall* SetTransform)(Direct3DDevice8* self, int state, TransformMatrix* matrix);
    char unknown_098[0xc8 - 0x98];
    int (__stdcall* SetRenderState)(Direct3DDevice8* self, int state, int value);
    char unknown_0cc[0xf4 - 0xcc];
    int (__stdcall* SetTexture)(Direct3DDevice8* self, unsigned int stage,
        Direct3DTexture8* texture);
    char unknown_0f8[0xfc - 0xf8];
    int (__stdcall* SetTextureStageState)(Direct3DDevice8* self, unsigned int stage,
        unsigned int type, unsigned int value);
    char unknown_100[0x118 - 0x100];
    int (__stdcall* DrawPrimitive)(Direct3DDevice8* self, unsigned int primitive_type,
        unsigned int start_vertex, unsigned int primitive_count);
    char unknown_11c[0x130 - 0x11c];
    int (__stdcall* SetVertexShader)(Direct3DDevice8* self, unsigned int shader);
    char unknown_134[0x14c - 0x134];
    int (__stdcall* SetStreamSource)(Direct3DDevice8* self, unsigned int stream,
        VertexBuffer* buffer, unsigned int stride);
};

struct Direct3DDevice8 {
    Direct3DDevice8Vtbl* vtbl;
};

typedef char Direct3DDevice8_must_be_0x04[
    (sizeof(Direct3DDevice8) == 0x04) ? 1 : -1];
typedef char Direct3DDevice8Vtbl_must_cover_0x150[
    (sizeof(Direct3DDevice8Vtbl) == 0x150) ? 1 : -1];

#endif
