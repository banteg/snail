// set_object_color @ 0x4141d0 (cdecl)

#include "sprite.h"

struct ColorBGRA8 {
    ColorBGRA8* noop_this_constructor();       // @ 0x44db50
    ColorBGRA8* pack_color_rgba_u8(Color4f*);  // @ 0x44dbf0

    unsigned char b;
    unsigned char g;
    unsigned char r;
    unsigned char a;
};

struct ObjectRenderVertex {
    float x;
    float y;
    float z;
    unsigned int diffuse;
    float u;
    float v;
};

struct ObjectVertexBuffer;

struct ObjectVertexBufferVtbl {
    char unknown_00[0x2c];
    int (__stdcall* Lock)(ObjectVertexBuffer* self, int offset, int size,
        ObjectRenderVertex** vertices, int flags);
    int (__stdcall* Unlock)(ObjectVertexBuffer* self);
};

struct ObjectVertexBuffer {
    ObjectVertexBufferVtbl* vtbl;
};

struct ObjectRenderBuffers {
    char unknown_00[0x08];
    ObjectVertexBuffer* vertex_buffer; // +0x08
};

struct ObjectColorRenderView {
    char unknown_00[0x10];
    unsigned int flags; // +0x10
    char unknown_14[0xc0 - 0x14];
    ObjectRenderBuffers* render_buffers; // +0xc0
    int grouped_vertex_count; // +0xc4
};

extern int g_object_grouped_vertex_cursor; // data_5031bc

ColorBGRA8* set_object_color(ObjectColorRenderView* object, Color4f color)
{
    ColorBGRA8 out;
    ObjectRenderVertex* vertices;

    out.noop_this_constructor();
    ColorBGRA8* result = out.pack_color_rgba_u8(&color);

    if ((object->flags & 0x80000) != 0) {
        object->render_buffers->vertex_buffer->vtbl->Lock(
            object->render_buffers->vertex_buffer, 0, g_object_grouped_vertex_cursor * 0x18,
            &vertices, 0);

        int i = 0;
        if (object->grouped_vertex_count > 0) {
            int offset = 0;
            do {
                ++i;
                *(unsigned int*)((char*)vertices + offset + 0x0c) =
                    *(unsigned int*)&out;
                offset += 0x18;
            } while (i < object->grouped_vertex_count);
        }

        return (ColorBGRA8*)object->render_buffers->vertex_buffer->vtbl->Unlock(
            object->render_buffers->vertex_buffer);
    }

    return result;
}
