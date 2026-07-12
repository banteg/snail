// draw_frontend_widget @ 0x401130 (thiscall)

#include "border_manager.h"
#include "font_system.h"
#include "frontend_widget.h"
#include "runtime_config.h"

extern char* g_game_base; // data_4df904

int queue_axis_aligned_textured_quad_uv(
    int texture_id,
    float x,
    float y,
    float width,
    float height,
    unsigned int flags,
    Color4f* color,
    float u0,
    float v0,
    float u1,
    float v1,
    int layer,
    int blend);

void FrontendWidget::draw_frontend_widget()
{
    char* self = (char*)this;
    Color4f glow_color;
    Color4f shadow_color;
    Color4f slider_color;
    Color4f white;

    glow_color.noop_this_constructor();
    shadow_color.noop_this_constructor();
    slider_color.noop_this_constructor();
    white.noop_this_constructor();

    if (g_render_queue_active == 0)
        return;

    unsigned int flags = *(unsigned int*)(self + 0x1a0);
    if ((flags & 0x1000) != 0)
        return;

    int layer = 0;
    int glow_layer = 0;
    if ((g_runtime_config.render_flags & 0x80) != 0) {
        layer = 3;
        glow_layer = 3;
    }

    float layout_width = *(float*)(self + 0x248);
    float layout_height = *(float*)(self + 0x24c);

    if ((flags & 0x100000) != 0) {
        Color4f* color = (Color4f*)(self + 0x1dc);
        float slider = *(float*)(self + 0x180);
        if (slider > 0.0f) {
            queue_axis_aligned_textured_quad_uv(
                37,
                *(float*)(self + 0x240) + layout_width * 0.5f - 128.0f,
                *(float*)(self + 0x244) + 50.0f,
                slider * 256.0f,
                32.0f,
                0x1000000,
                color,
                0.0f,
                0.0f,
                slider,
                1.0f,
                layer,
                0);
        }
        if (slider < 1.0f) {
            queue_axis_aligned_textured_quad_uv(
                36,
                *(float*)(self + 0x240) + layout_width * 0.5f - 128.0f + slider * 256.0f,
                *(float*)(self + 0x244) + 50.0f,
                (1.0f - slider) * 256.0f,
                32.0f,
                0x1000000,
                color,
                slider,
                0.0f,
                1.0f,
                1.0f,
                layer,
                0);
        }
    }

    if (*(unsigned char*)(self + 0x5c) != 0) {
        float wobble = 0.0f;
        if (((BorderManager*)(g_game_base + 0xb4c))->delayed_widget_active != 0
            && this == ((BorderManager*)(g_game_base + 0xb4c))->delayed_widget) {
            wobble = sine(
                ((BorderManager*)(g_game_base + 0xb4c))->delayed_widget_progress
                * 3.1415927f) * 3.0f;
            if (*(unsigned char*)(self + 0x5d) == 0)
                wobble = wobble * -1.0f;
        }

        int texture = *(int*)(self + 0x270);
        if ((*(unsigned char*)(self + 0x1a0) & 2) != 0)
            texture = *(int*)(self + 0x60);

        float pad = *(float*)(self + 0x258) * 0.5f;
        queue_axis_aligned_textured_quad_uv(
            texture,
            *(float*)(self + 0x240) + wobble - pad,
            *(float*)(self + 0x244) - pad,
            *(float*)(self + 0x250) + *(float*)(self + 0x258),
            *(float*)(self + 0x254) + *(float*)(self + 0x258),
            0x1000000,
            (Color4f*)(self + 0x1dc),
            0.0f,
            0.0f,
            1.0f,
            1.0f,
            *(int*)(self + 0x274),
            0);
        return;
    }

    if ((*(unsigned int*)(self + 0x1a0) & 0x800) != 0) {
        float pad = *(float*)(self + 0x258) * 0.5f;
        queue_axis_aligned_textured_quad_uv(
            *(int*)(self + 0x270),
            *(float*)(self + 0x240) - pad,
            *(float*)(self + 0x244) - pad,
            *(float*)(self + 0x250) + *(float*)(self + 0x258),
            *(float*)(self + 0x254) + *(float*)(self + 0x258),
            0x1000000,
            (Color4f*)(self + 0x1dc),
            0.0f,
            0.0f,
            1.0f,
            1.0f,
            *(int*)(self + 0x274),
            0);

        if (*(float*)(self + 0x178) > 0.0f) {
            queue_axis_aligned_textured_quad_uv(
                *(int*)(self + 0x270),
                *(float*)(self + 0x240) + *(float*)(self + 0x178) - pad,
                *(float*)(self + 0x244) + *(float*)(self + 0x178) - pad,
                *(float*)(self + 0x250) + *(float*)(self + 0x258),
                *(float*)(self + 0x254) + *(float*)(self + 0x258),
                0x1000000,
                shadow_color.set_color_rgba(0.0f, 0.0f, 0.0f, 0.89999998f),
                0.0f,
                0.0f,
                1.0f,
                1.0f,
                2,
                0);
        }
    }

    if ((*(unsigned int*)(self + 0x1a0) & 0x400000) != 0)
        return;

    float x = *(float*)(self + 0x240);
    float y = *(float*)(self + 0x244);
    float width = layout_width;
    float height = layout_height;
    float edge = *(float*)(self + 0x230);
    float u0 = edge * 0.0078125f;
    float u1 = 1.0f - u0;

    if (*(unsigned char*)(self + 0x234) != 0) {
        edge = 4.0f;
        u0 = 0.1f;
        u1 = 0.89999998f;
        x += 4.0f;
        y += 3.0f;
        width -= 8.0f;
        height -= 6.0f;
    } else if (*(float*)(self + 0x220) < *(float*)(self + 0x230)) {
        float delta = *(float*)(self + 0x230) - *(float*)(self + 0x220);
        *(float*)(self + 0x22c) = delta;
        edge = *(float*)(self + 0x230);
        x += delta;
        y += delta;
        width -= delta + delta;
        height -= delta + delta;
        u0 = edge * 0.0078125f;
        u1 = 1.0f - u0;
    } else {
        edge = *(float*)(self + 0x220);
        u0 = 0.2f;
        u1 = 0.80000001f;
    }

    float top = y - edge;
    float left = x - edge;
    float right = x + width;
    float bottom = y + height;
    int texture = *(int*)(self + 0x48);
    Color4f* color = (Color4f*)(self + 0x1ac);

    queue_axis_aligned_textured_quad_uv(texture, left, top, edge, edge, 0x1000000, color, 0.0f, 0.0f, u0, u0, layer, 0);
    queue_axis_aligned_textured_quad_uv(texture, x, top, width, edge, 0x1000000, color, u0, 0.0f, u1, u0, layer, 0);
    queue_axis_aligned_textured_quad_uv(texture, right, top, edge, edge, 0x1000000, color, u1, 0.0f, 1.0f, u0, glow_layer, 0);
    queue_axis_aligned_textured_quad_uv(texture, left, y, edge, height, 0x1000000, color, 0.0f, u0, u0, u1, glow_layer, 0);
    queue_axis_aligned_textured_quad_uv(texture, x, y, width, height, 0x1000000, color, u0, u0, u1, u1, glow_layer, 0);
    queue_axis_aligned_textured_quad_uv(texture, right, y, edge, height, 0x1000000, color, u1, u0, 1.0f, u1, glow_layer, 0);
    queue_axis_aligned_textured_quad_uv(texture, left, bottom, edge, edge, 0x1000000, color, 0.0f, u1, u0, 1.0f, glow_layer, 0);
    queue_axis_aligned_textured_quad_uv(texture, x, bottom, width, edge, 0x1000000, color, u0, u1, u1, 1.0f, glow_layer, 0);
    queue_axis_aligned_textured_quad_uv(texture, right, bottom, edge, edge, 0x1000000, color, u1, u1, 1.0f, 1.0f, glow_layer, 0);

    if (((BorderManager*)(g_game_base + 0xb4c))->delayed_widget_active != 0
        && this == ((BorderManager*)(g_game_base + 0xb4c))->delayed_widget) {
        white.set_color_white();
        glow_color.store_color4f(
            white.r,
            white.g,
            white.b,
            1.0f - ((BorderManager*)(g_game_base + 0xb4c))->delayed_widget_progress);
        float glow_edge =
            (((BorderManager*)(g_game_base + 0xb4c))->delayed_widget_progress
                * 0.69999999f
             + 1.0f) * edge;
        queue_axis_aligned_textured_quad_uv(99, x - glow_edge, y - glow_edge, glow_edge, glow_edge, 0x1000000, &glow_color, 0.0f, 0.0f, u0, u0, 3, 0);
        queue_axis_aligned_textured_quad_uv(99, x, y - glow_edge, width, glow_edge, 0x1000000, &glow_color, u0, 0.0f, u1, u0, 3, 0);
        queue_axis_aligned_textured_quad_uv(99, right, y - glow_edge, glow_edge, glow_edge, 0x1000000, &glow_color, u1, 0.0f, 1.0f, u0, 3, 0);
        queue_axis_aligned_textured_quad_uv(99, x - glow_edge, y, glow_edge, height, 0x1000000, &glow_color, 0.0f, u0, u0, u1, 3, 0);
        queue_axis_aligned_textured_quad_uv(99, right, y, glow_edge, height, 0x1000000, &glow_color, u1, u0, 1.0f, u1, 3, 0);
        queue_axis_aligned_textured_quad_uv(99, x - glow_edge, bottom, glow_edge, glow_edge, 0x1000000, &glow_color, 0.0f, u1, u0, 1.0f, 3, 0);
        queue_axis_aligned_textured_quad_uv(99, x, bottom, width, glow_edge, 0x1000000, &glow_color, u0, u1, u1, 1.0f, 3, 0);
        queue_axis_aligned_textured_quad_uv(99, right, bottom, glow_edge, glow_edge, 0x1000000, &glow_color, u1, u1, 1.0f, 1.0f, 3, 0);
    }
}
