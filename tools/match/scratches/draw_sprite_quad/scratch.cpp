// draw_sprite_quad @ 0x4137f0 (cdecl, ret)

#include "sprite.h"
#include "direct3d_device8_view.h"
#include "direct3d_renderer.h"
#include "transform_matrix.h"
#include "vector3.h"
#include "vertex_buffer_view.h"

typedef Vector3 Vec3;

struct SpriteVertex {
    float x;
    float y;
    float z;
    unsigned int color;
    float u;
    float v;
};

extern Direct3DDevice8* g_d3d_device;      // data_502fec
extern int g_render_triangle_count;        // data_4f7450
extern int g_draw_primitive_call_count;    // data_503170

extern "C" TransformMatrix* __stdcall D3DXMatrixTranslation(
    TransformMatrix* matrix, float x, float y, float z);

void bind_texture_ref(TextureRef* texture);
int configure_sprite_render_state(Sprite* sprite);
float cosine(float angle);
float sine(float angle);
int report_errorf(const char* format, ...);

int draw_sprite_quad(Vec3* position, Sprite* sprite)
{
    TransformMatrix transform;
    transform.position.z = 0.0f;
    transform.position.y = 0.0f;
    transform.position.x = 0.0f;
    transform.basis_forward_w = 0.0f;
    transform.basis_forward.y = 0.0f;
    transform.basis_forward.x = 0.0f;
    transform.basis_up_w = 0.0f;
    transform.basis_up.z = 0.0f;
    transform.basis_up.x = 0.0f;
    transform.basis_right_w = 0.0f;
    transform.basis_right.z = 0.0f;
    transform.basis_right.y = 0.0f;
    transform.position_w = 1.0f;
    transform.basis_forward.z = 1.0f;
    transform.basis_up.y = 1.0f;
    transform.basis_right.x = 1.0f;

    D3DXMatrixTranslation(&transform, position->x, position->y, position->z);
    g_d3d_device->vtbl->SetTransform(g_d3d_device, 2, &transform);

    float half_extent = (1.0f - sprite->progress) * sprite->size_start
        + sprite->size_end * sprite->progress;
    bind_texture_ref(sprite->texture_ref);
    configure_sprite_render_state(sprite);

    float alpha;
    if ((sprite->flags & 0x1000) != 0) {
        alpha = 1.0f;
    } else {
        alpha = (1.0f - sprite->progress) * sprite->color.a;
    }

    ColorBGRA8 packed;
    packed.noop_this_constructor();
    packed.pack_color_rgba_u8(&sprite->color);
    packed.a = (unsigned char)(int)(alpha * 255.0f);

    SpriteVertex* vertices;
    g_direct3d_renderer.renderer_state->sprite_vertex_buffer->vtbl->Lock(
        g_direct3d_renderer.renderer_state->sprite_vertex_buffer, 0,
        sizeof(SpriteVertex) * 4,
        (void**)&vertices, 0);

    if (sprite->facing_angle == 0.0f) {
        float negative_extent = -half_extent;
        vertices[0].x = negative_extent;
        vertices[0].y = half_extent;
        vertices[0].z = 0.0f;
        vertices[0].u = 0.0f;
        vertices[0].v = 0.0f;
        vertices[0].color = *(unsigned int*)&packed;

        vertices[1].x = half_extent;
        vertices[1].y = half_extent;
        vertices[1].z = 0.0f;
        vertices[1].u = 1.0f;
        vertices[1].v = 0.0f;
        vertices[1].color = *(unsigned int*)&packed;

        vertices[2].x = half_extent;
        vertices[2].y = negative_extent;
        vertices[2].z = 0.0f;
        vertices[2].u = 1.0f;
        vertices[2].v = 1.0f;
        vertices[2].color = *(unsigned int*)&packed;

        vertices[3].x = negative_extent;
        vertices[3].y = negative_extent;
    } else {
        float rot_x =
            cosine(sprite->facing_angle + 0.78539819f) * half_extent * 1.41400003f;
        float rot_y =
            sine(sprite->facing_angle + 0.78539819f) * half_extent * 1.41400003f;

        vertices[0].x = -rot_y;
        vertices[0].y = rot_x;
        vertices[0].z = 0.0f;
        vertices[0].u = 0.0f;
        vertices[0].v = 0.0f;
        vertices[0].color = *(unsigned int*)&packed;

        vertices[1].x = rot_x;
        vertices[1].y = rot_y;
        vertices[1].z = 0.0f;
        vertices[1].u = 1.0f;
        vertices[1].v = 0.0f;
        vertices[1].color = *(unsigned int*)&packed;

        vertices[2].x = rot_y;
        vertices[2].y = -rot_x;
        vertices[2].z = 0.0f;
        vertices[2].u = 1.0f;
        vertices[2].v = 1.0f;
        vertices[2].color = *(unsigned int*)&packed;

        vertices[3].x = -(rot_x * sprite->corner_scale);
        vertices[3].y = -(rot_y * sprite->corner_scale);
    }

    vertices[3].z = 0.0f;
    vertices[3].u = 0.0f;
    vertices[3].v = 1.0f;
    vertices[3].color = *(unsigned int*)&packed;

    g_direct3d_renderer.renderer_state->sprite_vertex_buffer->vtbl->Unlock(
        g_direct3d_renderer.renderer_state->sprite_vertex_buffer);
    g_d3d_device->vtbl->SetStreamSource(
        g_d3d_device, 0, g_direct3d_renderer.renderer_state->sprite_vertex_buffer,
        sizeof(SpriteVertex));
    g_d3d_device->vtbl->SetVertexShader(g_d3d_device, 0x142);
    int result = g_d3d_device->vtbl->DrawPrimitive(g_d3d_device, 6, 0, 2);
    g_render_triangle_count += 2;
    ++g_draw_primitive_call_count;
    if (result != 0) {
        result = report_errorf("Draw Primitive Failed");
    }
    return result;
}
