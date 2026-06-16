// render_object @ 0x4126c0 (cdecl)

#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

struct ObjectIndexBufferResource;
struct ColorBGRA8;

struct ObjectIndexBuffer {
    ObjectIndexBufferResource* buffer; // +0x00
};

struct RenderObjectDeviceVtbl {
    char unknown_000[0x94];
    int (__stdcall* SetTransform)(RenderObjectDevice* self, int state, TransformMatrix* matrix);
    char unknown_098[0xc8 - 0x98];
    int (__stdcall* SetRenderState)(RenderObjectDevice* self, int state, int value);
    char unknown_0cc[0xfc - 0xcc];
    int (__stdcall* SetTextureStageState)(RenderObjectDevice* self, int stage, int type, int value);
    char unknown_100[0x11c - 0x100];
    int (__stdcall* DrawIndexedPrimitive)(RenderObjectDevice* self, int primitive_type,
        int min_vertex_index, int vertex_count, int start_index, int primitive_count);
    char unknown_120[0x130 - 0x120];
    int (__stdcall* SetVertexShader)(RenderObjectDevice* self, int shader);
    char unknown_134[0x14c - 0x134];
    int (__stdcall* SetStreamSource)(RenderObjectDevice* self, int stream,
        ObjectVertexBuffer* vertex_buffer, int stride);
    char unknown_150[0x154 - 0x150];
    int (__stdcall* SetIndices)(RenderObjectDevice* self,
        ObjectIndexBufferResource* index_buffer, int base_vertex_index);
};

struct ObjectRenderView {
    char unknown_00[0x10];
    unsigned int flags; // +0x10
    int blend_mode; // +0x14
    TextureRef* override_texture_ref; // +0x18
    char unknown_1c[0x2c - 0x1c];
    int vertex_count; // +0x2c
    char unknown_30[0x64 - 0x30];
    int texture_group_count; // +0x64
    char unknown_68[0xc0 - 0x68];
    ObjectRenderBuffers* render_buffers; // +0xc0
    int grouped_vertex_count; // +0xc4
    ObjectIndexBuffer* index_buffer; // +0xc8
    int* group_index_starts; // +0xcc
    TextureRef** group_texture_refs; // +0xd0
    int* group_primitive_counts; // +0xd4
};

extern RenderObjectDevice* g_d3d_device; // data_502fec
extern int g_render_triangle_count; // data_4f7450
extern int g_draw_primitive_call_count; // data_503170
extern unsigned char g_object_render_pass_filter; // data_503260
extern TransformMatrix g_object_texture_transform_matrix; // data_5031d8

void refresh_object_vertex_buffer(ObjectRenderView* object); // @ 0x412250
int set_cull_mode(char cull_front); // @ 0x4129f0
int set_blend_mode(int blend_mode); // @ 0x412d00
ColorBGRA8* set_object_color(ObjectRenderView* object, Color4f color); // @ 0x4141d0
void bind_texture_ref(TextureRef* texture); // @ 0x414500
int render_object_toon(ObjectRenderView* object, TransformMatrix* matrix); // @ 0x4123e0

int render_object(
    ObjectRenderView* object,
    TransformMatrix* matrix,
    int texture_scroll_bits,
    float texture_v,
    Color4f* color,
    char after_sprites)
{
    unsigned int flags = object->flags;
    if ((flags & 0x80000) == 0 || (flags & 0x40000) != 0 || object->vertex_count == 0) {
        return flags;
    }

    refresh_object_vertex_buffer(object);

    TransformMatrix world = *matrix;
    g_d3d_device->vtbl->SetTransform(g_d3d_device, 0x100, &world);

    if ((object->flags & 0x100000) != 0)
        set_cull_mode(0);
    else
        set_cull_mode(1);

    for (int i = 0; i < object->texture_group_count; ++i) {
        unsigned char pass = g_object_render_pass_filter;
        TextureRef* texture = object->group_texture_refs[i];

        if (pass != 0) {
            if (pass == 1) {
                if (after_sprites != 1 && (texture->flags & 0x10000) == 0)
                    continue;
                if (after_sprites == pass && (texture->flags & 0x10000) != 0)
                    continue;
            } else if (pass == after_sprites && (texture->flags & 0x10000) == 0) {
                continue;
            }
        }

        if (texture == 0)
            continue;

        if ((object->flags & 8) != 0)
            bind_texture_ref(object->override_texture_ref);
        else
            bind_texture_ref(texture);

        if ((object->flags & 0x80) != 0) {
            *(int*)&g_object_texture_transform_matrix.basis_forward.x = texture_scroll_bits;
            g_object_texture_transform_matrix.basis_forward.y = 1.0f - texture_v;
            g_d3d_device->vtbl->SetTransform(
                g_d3d_device, 0x10, &g_object_texture_transform_matrix);
            g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 0x18, 2);
        } else {
            g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 0x18, 0);
        }

        if (color->a != 1.0f && (texture->flags & 0x10000) != 0) {
            set_blend_mode(object->blend_mode);
            if ((object->flags & 0x50) != 0) {
                object->flags &= ~0x40;
                set_object_color(object, *color);
            }
        } else {
            g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 0);
        }

        g_d3d_device->vtbl->SetStreamSource(
            g_d3d_device, 0, object->render_buffers->vertex_buffer, 0x18);
        g_d3d_device->vtbl->SetVertexShader(g_d3d_device, 0x142);
        g_d3d_device->vtbl->SetIndices(g_d3d_device, object->index_buffer->buffer, 0);
        g_d3d_device->vtbl->DrawIndexedPrimitive(
            g_d3d_device, 4, 0, object->grouped_vertex_count,
            object->group_index_starts[i], object->group_primitive_counts[i]);

        g_render_triangle_count += object->group_primitive_counts[i];
        ++g_draw_primitive_call_count;
    }

    return render_object_toon(object, matrix);
}
