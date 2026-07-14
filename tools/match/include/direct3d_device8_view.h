// Shared Direct3DDevice8 ABI view.
#ifndef DIRECT3D_DEVICE8_VIEW_H
#define DIRECT3D_DEVICE8_VIEW_H

class Direct3DTexture8;
struct Direct3DDevice8;
struct Direct3DVertexBuffer8;
struct TransformMatrix;

struct D3DViewport8 {
    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int height;
    float min_z;
    float max_z;
};

typedef Direct3DVertexBuffer8 VertexBuffer;

struct Direct3DTexture8Vtbl {
    char unknown_000[0x08];
    int (__stdcall* Release)(Direct3DTexture8* self);
};

class Direct3DTexture8 {
public:
    Direct3DTexture8Vtbl* vtbl;
};

typedef char Direct3DTexture8_must_be_0x04[
    (sizeof(Direct3DTexture8) == 0x04) ? 1 : -1];

struct Direct3DDevice8Vtbl {
    char unknown_000[0x08];
    int (__stdcall* Release)(Direct3DDevice8* self);
    char unknown_00c[0x3c - 0x0c];
    int (__stdcall* Present)(Direct3DDevice8* self, void* source_rect,
        void* dest_rect, int dest_window_override, void* dirty_region);
    char unknown_040[0x5c - 0x40];
    int (__stdcall* CreateVertexBuffer)(Direct3DDevice8* self,
        unsigned int length, unsigned int usage, unsigned int fvf,
        unsigned int pool, Direct3DVertexBuffer8** out_buffer);
    char unknown_060[0x88 - 0x60];
    int (__stdcall* BeginScene)(Direct3DDevice8* self);
    int (__stdcall* EndScene)(Direct3DDevice8* self);
    int (__stdcall* Clear)(Direct3DDevice8* self, unsigned int count, void* rects,
        unsigned int flags, unsigned int color, float z, unsigned int stencil);
    int (__stdcall* SetTransform)(Direct3DDevice8* self, int state, TransformMatrix* matrix);
    int (__stdcall* GetTransform)(Direct3DDevice8* self, int state, TransformMatrix* matrix);
    int (__stdcall* MultiplyTransform)(
        Direct3DDevice8* self, int state, TransformMatrix* matrix);
    int (__stdcall* SetViewport)(Direct3DDevice8* self, D3DViewport8* viewport);
    int (__stdcall* GetViewport)(Direct3DDevice8* self, D3DViewport8* viewport);
    char unknown_0a8[0xc8 - 0xa8];
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
    int (__stdcall* DrawIndexedPrimitive)(Direct3DDevice8* self,
        unsigned int primitive_type, unsigned int min_vertex_index,
        unsigned int vertex_count, unsigned int start_index,
        unsigned int primitive_count);
    char unknown_120[0x130 - 0x120];
    int (__stdcall* SetVertexShader)(Direct3DDevice8* self, unsigned int shader);
    char unknown_134[0x14c - 0x134];
    int (__stdcall* SetStreamSource)(Direct3DDevice8* self, unsigned int stream,
        VertexBuffer* buffer, unsigned int stride);
    char unknown_150[0x154 - 0x150];
    int (__stdcall* SetIndices)(
        Direct3DDevice8* self, void* index_buffer, unsigned int base_vertex_index);
};

struct Direct3DDevice8 {
    Direct3DDevice8Vtbl* vtbl;
};

typedef char Direct3DDevice8_must_be_0x04[
    (sizeof(Direct3DDevice8) == 0x04) ? 1 : -1];
typedef char D3DViewport8_must_be_0x18[
    (sizeof(D3DViewport8) == 0x18) ? 1 : -1];
typedef char Direct3DDevice8Vtbl_must_cover_0x158[
    (sizeof(Direct3DDevice8Vtbl) == 0x158) ? 1 : -1];

extern Direct3DDevice8* g_d3d_device; // data_502fec

#endif
