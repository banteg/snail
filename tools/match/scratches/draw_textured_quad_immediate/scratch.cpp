// draw_textured_quad_immediate @ 0x413030 (cdecl)

#include "direct3d_device8_view.h"
#include "direct3d_renderer.h"
#include "object_render_types.h"
#include "sprite.h"
#include "vertex_buffer_view.h"

extern Direct3DDevice8* g_d3d_device;      // data_502fec
extern int g_render_triangle_count;        // data_4f7450
extern int g_render_successful_primitive_count; // data_4f7454
extern int g_draw_primitive_call_count;    // data_503170

void bind_texture_ref(TextureRef* texture);
int set_immediate_blend_mode(int blend_mode);
float square_root(float value);
float sine(float angle);
float cosine(float angle);
int report_errorf(const char* format, ...);

void draw_textured_quad_immediate(
    TextureRef* texture,
    float x0,
    float y0,
    float x1,
    float y1,
    float x2,
    float y2,
    float x3,
    float y3,
    float width,
    float height,
    float u0,
    float v0,
    float u1,
    float v1,
    Color4f* color,
    int blend_mode,
    float rotation)
{
    g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x16, 1);
    bind_texture_ref(texture);
    set_immediate_blend_mode(blend_mode);

    ColorBGRA8 packed;
    packed.noop_this_constructor();
    packed.pack_color_rgba_u8(color);

    ObjectRenderVertex* vertices;
    g_direct3d_renderer.renderer_state->vertex_buffer->vtbl->Lock(
        g_direct3d_renderer.renderer_state->vertex_buffer, 0,
        sizeof(ObjectRenderVertex) * 4,
        (void**)&vertices, 0);

    if (rotation == 0.0f) {
        if (width == 0.0f) {
            vertices[0].x = x0;
            vertices[0].y = y0;
            vertices[0].z = 0.0f;
            vertices[0].u = u0;
            vertices[0].v = v0;
            vertices[0].diffuse = *(unsigned int*)&packed;

            vertices[1].x = x1;
            vertices[1].y = y1;
            vertices[1].z = 0.0f;
            vertices[1].u = u1;
            vertices[1].v = v0;
            vertices[1].diffuse = *(unsigned int*)&packed;

            vertices[2].x = x2;
            vertices[2].y = y2;
            vertices[2].z = 0.0f;
            vertices[2].u = u1;
            vertices[2].v = v1;
            vertices[2].diffuse = *(unsigned int*)&packed;

            vertices[3].x = x3;
            vertices[3].y = y3;
            vertices[3].z = 0.0f;
            vertices[3].u = u0;
            vertices[3].v = v1;
            vertices[3].diffuse = *(unsigned int*)&packed;
        } else {
            vertices[0].x = x0;
            vertices[0].y = y0;
            vertices[0].z = 0.0f;
            vertices[0].u = u0;
            vertices[0].v = v0;
            vertices[0].diffuse = *(unsigned int*)&packed;

            float right = x0 + width;
            vertices[1].x = right;
            vertices[1].y = y0;
            vertices[1].z = 0.0f;
            vertices[1].u = u1;
            vertices[1].v = v0;
            vertices[1].diffuse = *(unsigned int*)&packed;

            vertices[2].x = right;
            float bottom = y0 + height;
            vertices[2].y = bottom;
            vertices[2].z = 0.0f;
            vertices[2].u = u1;
            vertices[2].v = v1;
            vertices[2].diffuse = *(unsigned int*)&packed;

            vertices[3].x = x0;
            vertices[3].y = bottom;
            vertices[3].z = 0.0f;
            vertices[3].u = u0;
            vertices[3].v = v1;
            vertices[3].diffuse = *(unsigned int*)&packed;
        }
    } else {
        float half_width = width * 0.5f;
        float center_x = x0 + half_width;
        float half_height = height * 0.5f;
        float center_y = y0 + half_height;
        float radius = square_root(half_width * half_width + half_height * half_height)
            * 1.41400003f;
        float sin_radius = sine(rotation) * radius;
        float cos_radius = cosine(rotation) * radius;

        vertices[0].x = center_x + sin_radius;
        vertices[0].y = center_y + cos_radius;
        vertices[0].z = 0.0f;
        vertices[0].u = u0;
        vertices[0].v = v0;
        vertices[0].diffuse = *(unsigned int*)&packed;

        vertices[1].x = center_x - cos_radius;
        vertices[1].y = center_y + sin_radius;
        vertices[1].z = 0.0f;
        vertices[1].u = u1;
        vertices[1].v = v0;
        vertices[1].diffuse = *(unsigned int*)&packed;

        vertices[2].x = center_x - sin_radius;
        vertices[2].y = center_y - cos_radius;
        vertices[2].z = 0.0f;
        vertices[2].u = u1;
        vertices[2].v = v1;
        vertices[2].diffuse = *(unsigned int*)&packed;

        vertices[3].x = center_x + cos_radius;
        vertices[3].y = center_y - sin_radius;
        vertices[3].z = 0.0f;
        vertices[3].u = u0;
        vertices[3].v = v1;
        vertices[3].diffuse = *(unsigned int*)&packed;
    }

    g_direct3d_renderer.renderer_state->vertex_buffer->vtbl->Unlock(
        g_direct3d_renderer.renderer_state->vertex_buffer);
    g_d3d_device->vtbl->SetStreamSource(
        g_d3d_device, 0, g_direct3d_renderer.renderer_state->vertex_buffer,
        sizeof(ObjectRenderVertex));
    g_d3d_device->vtbl->SetVertexShader(g_d3d_device, 0x142);
    int result = g_d3d_device->vtbl->DrawPrimitive(g_d3d_device, 6, 0, 2);
    g_render_triangle_count += 2;
    ++g_draw_primitive_call_count;
    if (result != 0) {
        report_errorf("Draw Primitive Failed");
        return;
    }
    ++g_render_successful_primitive_count;
}
