// draw_textured_quad_immediate @ 0x413030 (cdecl)

#include "direct3d_device8_view.h"
#include "sprite.h"
#include "vertex_buffer_view.h"

struct ImmediateVertex {
    float x;
    float y;
    float z;
    unsigned int color;
    float u;
    float v;
};

struct Direct3DDevice8Vtbl {
    char unknown_000[0xc8];
    int (__stdcall* SetRenderState)(Direct3DDevice8* self, int state, int value);
    char unknown_0cc[0x118 - 0xcc];
    int (__stdcall* DrawPrimitive)(Direct3DDevice8* self, int primitive_type, int start_vertex,
        int primitive_count);
    char unknown_11c[0x130 - 0x11c];
    int (__stdcall* SetVertexShader)(Direct3DDevice8* self, int shader);
    char unknown_134[0x14c - 0x134];
    int (__stdcall* SetStreamSource)(Direct3DDevice8* self, int stream, VertexBuffer* buffer,
        int stride);
};

extern Direct3DDevice8* g_d3d_device;      // data_502fec
extern RendererState* g_renderer_state;    // data_502fe0
extern int g_render_triangle_count;        // data_4f7450
extern int g_render_successful_primitive_count; // data_4f7454
extern int g_draw_primitive_call_count;    // data_503170

void bind_texture_ref(TextureRef* texture);
int sub_412e50(int blend_mode);
float square_root(float value);
float sine(float angle);
float cosine(float angle);
int report_errorf(const char* format, ...);

int draw_textured_quad_immediate(
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
    sub_412e50(blend_mode);

    ColorBGRA8 packed;
    packed.noop_this_constructor();
    packed.pack_color_rgba_u8(color);

    ImmediateVertex* vertices;
    g_renderer_state->sprite_vertex_buffer->vtbl->Lock(
        g_renderer_state->sprite_vertex_buffer, 0, sizeof(ImmediateVertex) * 4,
        (void**)&vertices, 0);

    if (rotation == 0.0f) {
        if (width == 0.0f) {
            vertices[0].x = x0;
            vertices[0].y = y0;
            vertices[0].z = 0.0f;
            vertices[0].u = u0;
            vertices[0].v = v0;
            vertices[0].color = *(unsigned int*)&packed;

            vertices[1].x = x1;
            vertices[1].y = y1;
            vertices[1].z = 0.0f;
            vertices[1].u = u1;
            vertices[1].v = v0;
            vertices[1].color = *(unsigned int*)&packed;

            vertices[2].x = x2;
            vertices[2].y = y2;
            vertices[2].z = 0.0f;
            vertices[2].u = u1;
            vertices[2].v = v1;
            vertices[2].color = *(unsigned int*)&packed;

            vertices[3].x = x3;
            vertices[3].y = y3;
            vertices[3].z = 0.0f;
            vertices[3].u = u0;
            vertices[3].v = v1;
            vertices[3].color = *(unsigned int*)&packed;
        } else {
            vertices[0].x = x0;
            vertices[0].y = y0;
            vertices[0].z = 0.0f;
            vertices[0].u = u0;
            vertices[0].v = v0;
            vertices[0].color = *(unsigned int*)&packed;

            float right = x0 + width;
            vertices[1].x = right;
            vertices[1].y = y0;
            vertices[1].z = 0.0f;
            vertices[1].u = u1;
            vertices[1].v = v0;
            vertices[1].color = *(unsigned int*)&packed;

            vertices[2].x = right;
            float bottom = y0 + height;
            vertices[2].y = bottom;
            vertices[2].z = 0.0f;
            vertices[2].u = u1;
            vertices[2].v = v1;
            vertices[2].color = *(unsigned int*)&packed;

            vertices[3].x = x0;
            vertices[3].y = bottom;
            vertices[3].z = 0.0f;
            vertices[3].u = u0;
            vertices[3].v = v1;
            vertices[3].color = *(unsigned int*)&packed;
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
        vertices[0].color = *(unsigned int*)&packed;

        vertices[1].x = center_x - cos_radius;
        vertices[1].y = center_y + sin_radius;
        vertices[1].z = 0.0f;
        vertices[1].u = u1;
        vertices[1].v = v0;
        vertices[1].color = *(unsigned int*)&packed;

        vertices[2].x = center_x - sin_radius;
        vertices[2].y = center_y - cos_radius;
        vertices[2].z = 0.0f;
        vertices[2].u = u1;
        vertices[2].v = v1;
        vertices[2].color = *(unsigned int*)&packed;

        vertices[3].x = center_x + cos_radius;
        vertices[3].y = center_y - sin_radius;
        vertices[3].z = 0.0f;
        vertices[3].u = u0;
        vertices[3].v = v1;
        vertices[3].color = *(unsigned int*)&packed;
    }

    g_renderer_state->sprite_vertex_buffer->vtbl->Unlock(g_renderer_state->sprite_vertex_buffer);
    g_d3d_device->vtbl->SetStreamSource(
        g_d3d_device, 0, g_renderer_state->sprite_vertex_buffer, sizeof(ImmediateVertex));
    g_d3d_device->vtbl->SetVertexShader(g_d3d_device, 0x142);
    int result = g_d3d_device->vtbl->DrawPrimitive(g_d3d_device, 6, 0, 2);
    g_render_triangle_count += 2;
    ++g_draw_primitive_call_count;
    if (result != 0) {
        return report_errorf("Draw Primitive Failed");
    }
    ++g_render_successful_primitive_count;
    return result;
}
