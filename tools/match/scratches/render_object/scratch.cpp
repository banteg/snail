// render_object @ 0x4126c0 (cdecl)

#include "object_render_types.h"
#include "sprite.h"
#include "transform_matrix.h"

extern int g_render_triangle_count; // data_4f7450
extern int g_draw_primitive_call_count; // data_503170
extern unsigned char g_object_render_pass_filter; // data_503260
extern TransformMatrix g_object_texture_transform_matrix; // data_5031d8

int set_cull_mode(char cull_front); // @ 0x4129f0
void set_blend_mode(int blend_mode); // @ 0x412d00
void set_object_color(Object* object, tColour color); // @ 0x4141d0
void bind_texture_ref(TextureRef* texture); // @ 0x414500
int render_object_toon(Object* object, TransformMatrix* matrix); // @ 0x4123e0

int render_object(
    Object* object,
    TransformMatrix* matrix,
    float texture_u,
    float texture_v,
    tColour* color,
    char after_sprites)
{
    int result = object->flags;
    if ((result & OBJECT_FLAG_RENDER_BUFFERS_READY) != 0
        && (result & OBJECT_FLAG_RENDER_DISABLED) == 0) {
        result = object->vertex_count;
        if (result != 0) {
            refresh_object_vertex_buffer(object);

            TransformMatrix world = *matrix;
            g_d3d_device->vtbl->SetTransform(g_d3d_device, 0x100, &world);

            if ((object->flags & OBJECT_FLAG_DISABLE_CULLING) != 0)
                set_cull_mode(0);
            else
                set_cull_mode(1);

            char pass_side = after_sprites;
            tColour* tint = color;
            for (int i = 0; i < object->texture_group_count; ++i) {
                unsigned char pass = g_object_render_pass_filter;

                if (pass == 0) {
                    if (pass_side == 1 &&
                        (object->group_texture_refs[i]->flags & 0x10000) != 0)
                        continue;
                } else if (pass == 1 && pass_side == pass &&
                    (object->group_texture_refs[i]->flags & 0x10000) == 0) {
                    continue;
                }

                if (object->group_texture_refs[i] == 0)
                    continue;

                if ((object->flags & OBJECT_FLAG_USE_OVERRIDE_TEXTURE) != 0)
                    bind_texture_ref(object->override_texture_ref);
                else
                    bind_texture_ref(object->group_texture_refs[i]);

                if ((object->flags & OBJECT_FLAG_TEXTURE_TRANSFORM) != 0) {
                    g_object_texture_transform_matrix.basis_forward.x = texture_u;
                    g_object_texture_transform_matrix.basis_forward.y = 1.0f - texture_v;
                    g_d3d_device->vtbl->SetTransform(
                        g_d3d_device, 0x10, &g_object_texture_transform_matrix);
                    g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 0x18, 2);
                } else {
                    g_d3d_device->vtbl->SetTextureStageState(g_d3d_device, 0, 0x18, 0);
                }

                if (tint->a != 1.0f &&
                    (object->group_texture_refs[i]->flags & 0x10000) != 0) {
                    set_blend_mode(object->blend_mode);
                    if ((object->flags & (OBJECT_FLAG_REFRESH_TINT_EACH_DRAW
                            | OBJECT_FLAG_TINT_DIRTY)) != 0) {
                        object->flags &= ~OBJECT_FLAG_TINT_DIRTY;
                        set_object_color(object, *tint);
                    }
                } else {
                    g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x1b, 0);
                }

                g_d3d_device->vtbl->SetStreamSource(
                    g_d3d_device, 0, object->render_buffers->vertex_buffer, 0x18);
                g_d3d_device->vtbl->SetVertexShader(g_d3d_device, 0x142);
                g_d3d_device->vtbl->SetIndices(
                    g_d3d_device, object->index_buffer->buffer, 0);
                g_d3d_device->vtbl->DrawIndexedPrimitive(
                    g_d3d_device, 4, 0, object->grouped_vertex_count,
                    object->group_index_starts[i], object->group_primitive_counts[i]);

                g_render_triangle_count += object->group_primitive_counts[i];
                ++g_draw_primitive_call_count;
            }

            result = render_object_toon(object, matrix);
        }
    }
    return result;
}
