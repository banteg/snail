// Android gameplay skies use a stationary vertex grid and animate its UVs.
#include <string.h>

#include "backdrop.h"
#include "direct3d_renderer.h"
#include "font_system.h"
#include "gl.h"
#include "profile.h"
#include "render_pipeline_state.h"
#include "rerror.h"
#include "rmath_random.h"

void backdrop_render_recovered(cRBackdrop* self) __asm__("_ZN10cRBackdrop25render_backdrop_recoveredEv");

namespace {
const float kTau = 6.2831855f;
BackdropDistortCell cells[MOBILE_BACKDROP_MAX_QUADS + 1][MOBILE_BACKDROP_MAX_QUADS + 1];
int quads = MOBILE_BACKDROP_MAX_QUADS;
VertexBuffer* sky_buffer;
float current_zoom;

bool is_space_sky(const cRTexture* texture)
{
    return texture && strncasecmp(texture->name, "Backgrounds/Space", 17) == 0;
}
} // namespace

void reset_mobile_backdrop()
{
    current_zoom = 0.0f;
    sky_buffer = nullptr;
}

// Android cRBackdrop::SetDistort (0003e46c). The period macro draws once
// for its zero check and again for its value. Both draws advance gRMathRand2.
void seed_mobile_backdrop(cRBackdrop* backdrop, float distort)
{
    quads = g_direct3d_renderer.present.back_buffer_width == 320 ? 8 : MOBILE_BACKDROP_MAX_QUADS;
    for (int y = 0; y <= quads; ++y) {
        for (int x = 0; x <= quads; ++x) {
            BackdropDistortCell& cell = cells[y][x];
            cell = {};
            if (x == 0 || y == 0 || x == quads || y == quads)
                continue;
            cell.phase = (float)gRMathRand2() * (1.0f / 32768.0f) * kTau;
            gRMathRand2();
            float period = ((float)gRMathRand2() * (2.0f / 32768.0f) + 3.0f) * 60.0f;
            cell.phase_step = (1.0f / period) * kTau;
            cell.x_offset = ((float)gRMathRand2() - 16384.0f) * (1.0f / 16384.0f) * distort * 0.9f;
            cell.y_offset = (distort * 0.9f) * ((float)gRMathRand2() - 16384.0f) * (1.0f / 16384.0f);
        }
    }
    // Desktop menu art still uses its padded 7x7 layout. Give it the same
    // seeded wave without consuming another sequence of random numbers.
    for (int y = 0; y <= 7; ++y)
        for (int x = 0; x <= 7; ++x)
            backdrop->distort_grid[y][x] = cells[y * quads / 7][x * quads / 7];
}

void advance_mobile_backdrop(cRBackdrop* backdrop)
{
    current_zoom += (backdrop->zoom - current_zoom) * 0.3f;
    if (backdrop->backdrop_change_queued) {
        backdrop->ChangeReal();
        backdrop->backdrop_change_queued = 0;
    }
    for (int y = 1; y < quads; ++y) {
        for (int x = 1; x < quads; ++x) {
            BackdropDistortCell& cell = cells[y][x];
            cell.phase += cell.phase_step;
            if (cell.phase > kTau)
                cell.phase -= kTau;
            cell.current_x_offset = Sin(cell.phase) * cell.x_offset;
            cell.current_y_offset = Cos(cell.phase) * cell.y_offset;
        }
    }
}

void cRBackdrop::render_backdrop()
{
    cRTexture* texture = active_primary_texture_id >= 0 && active_primary_texture_id < SPRITE_TEXTURE_CAPACITY
        ? g_sprite_texture_table[active_primary_texture_id] : nullptr;
    if (!g_port_ultimate || !is_space_sky(texture)) {
        backdrop_render_recovered(this);
        return;
    }
    if (!g_render_queue_active)
        return;
    if (g_font_queue_count == FONT_QUEUE_CAPACITY) {
        report_errorf("Font print buffer overflow Increase RFONT_PRINT_MAX in font.h");
        return;
    }
    cFontPrintBuffer& entry = g_font_queue[g_font_queue_count++];
    entry.flags = FONT_QUEUE_MOBILE_BACKDROP;
    entry.texture_id = active_primary_texture_id;
}

void draw_mobile_backdrop(int texture_id)
{
    cRTexture* texture = g_sprite_texture_table[texture_id];
    if (!is_space_sky(texture))
        return;
    // The Pro conversion fills its image. Desktop postal skies keep their
    // 320x240 window in a 512x256 atlas.
    bool pro = strncasecmp(texture->name, "Backgrounds/SpacePro", 20) == 0;
    float u_scale = pro ? 1.0f : 320.0f / 512.0f;
    float v_scale = pro ? 1.0f : 240.0f / 256.0f;
    float uv_step = (1.0f - 2.0f * current_zoom) / (float)quads;
    ObjectRenderVertex vertices[MOBILE_BACKDROP_MAX_QUADS + 1][MOBILE_BACKDROP_MAX_QUADS + 1];
    for (int y = 0; y <= quads; ++y) {
        for (int x = 0; x <= quads; ++x) {
            const BackdropDistortCell& cell = cells[y][x];
            vertices[y][x] = {
                (float)x * (640.0f / (float)quads), (float)y * (480.0f / (float)quads), 0.0f, 0xffffffff,
                (current_zoom + (float)x * uv_step + cell.current_x_offset / 640.0f) * u_scale,
                // Android JPEGs use bottom-up V. The converted TGA uploads top first.
                (current_zoom + (float)y * uv_step - cell.current_y_offset / 640.0f) * v_scale,
            };
        }
    }

    if (!sky_buffer)
        sky_buffer = g_direct3d_renderer.vertex_buffer_factory
            .create_vertex_buffer(6 * MOBILE_BACKDROP_MAX_QUADS * MOBILE_BACKDROP_MAX_QUADS, 0x142)->vertex_buffer;
    VertexBuffer* buffer = sky_buffer;
    ObjectRenderVertex* out;
    int triangles = 2 * quads * quads;
    if (!buffer || buffer->vtbl->Lock(buffer, 0, triangles * 3 * sizeof(*out), (void**)&out, 0) != 0)
        return;
    for (int x = 0; x < quads; ++x) {
        for (int y = 0; y < quads; ++y) {
            // The Android column strip splits each cell from bottom-left to top-right.
            *out++ = vertices[y][x];
            *out++ = vertices[y + 1][x];
            *out++ = vertices[y][x + 1];
            *out++ = vertices[y][x + 1];
            *out++ = vertices[y + 1][x];
            *out++ = vertices[y + 1][x + 1];
        }
    }
    buffer->vtbl->Unlock(buffer);
    g_d3d_device->vtbl->SetRenderState(g_d3d_device, 0x16, 1);
    bind_texture_ref(texture);
    set_immediate_blend_mode(0);
    g_d3d_device->vtbl->SetStreamSource(g_d3d_device, 0, buffer, sizeof(ObjectRenderVertex));
    g_d3d_device->vtbl->SetVertexShader(g_d3d_device, 0x142);
    if (g_d3d_device->vtbl->DrawPrimitive(g_d3d_device, 4, 0, triangles) == 0) {
        g_render_triangle_count += triangles;
        ++g_draw_primitive_call_count;
        ++g_render_successful_primitive_count;
    }
}
