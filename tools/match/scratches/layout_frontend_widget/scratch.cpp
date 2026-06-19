// layout_frontend_widget @ 0x4024a0 (thiscall, ret)

#include "sprite.h"

extern unsigned int g_render_flags; // data_4df934

class FrontendWidget;

float* layout_and_queue_wrapped_font_text(
    char* text,
    int font_id,
    float text_scale,
    float x,
    float y,
    float* out_x,
    float* out_y,
    float* out_width,
    float* out_height,
    float text_wave_amplitude,
    char text_wave_enabled,
    int horizontal_align,
    float anchor_x,
    unsigned int flags,
    Color4f* color_arg,
    char measure_only,
    char pulse_alpha);

class FrontendWidget {
public:
    int layout_frontend_widget();

    char unknown_000[0x4c];
    float authored_left; // +0x04c
    float authored_top; // +0x050
    float authored_width; // +0x054
    float authored_height; // +0x058
    char unknown_05c[0x184 - 0x05c];
    float slider_hit_left; // +0x184
    float slider_hit_right; // +0x188
    float slider_hit_top; // +0x18c
    float slider_hit_bottom; // +0x190
    char unknown_194[0x1a0 - 0x194];
    unsigned int widget_flags; // +0x1a0
    char unknown_1a4[0x1ec - 0x1a4];
    Color4f idle_text_color; // +0x1ec
    char unknown_1fc[0x218 - 0x1fc];
    float hot_padding; // +0x218
    char unknown_21c[0x228 - 0x21c];
    float text_effect_current; // +0x228
    char unknown_22c[0x238 - 0x22c];
    float layout_left; // +0x238
    float layout_top; // +0x23c
    float clamped_left; // +0x240
    float clamped_top; // +0x244
    float layout_width; // +0x248
    float layout_height; // +0x24c
    char unknown_250[0x25c - 0x250];
    int text_alignment; // +0x25c
    float anchor_x; // +0x260
    char unknown_264[0x2cc - 0x264];
    char text_buffer[0x420]; // +0x2cc
    int font_id; // +0x6ec
    float font_scale; // +0x6f0
    float layout_anchor_x; // +0x6f4
    float layout_anchor_y; // +0x6f8
    char unknown_6fc[0x718 - 0x6fc];
    FrontendWidget* slider_less_widget; // +0x718
    FrontendWidget* slider_more_widget; // +0x71c
    FrontendWidget* slider_value_widget; // +0x720
};

int FrontendWidget::layout_frontend_widget()
{
    FrontendWidget* widget = this;
    int result;

    while (true) {
        char text_wave_enabled = (char)((g_render_flags >> 8) & 1);
        result = widget->widget_flags;

        float* layout_left_ptr;
        float* layout_top_ptr;
        if ((result & 0x800) != 0) {
            int left_bits = *(int*)&widget->layout_left;
            int top_bits = *(int*)&widget->layout_top;
            layout_left_ptr = &widget->layout_left;
            layout_top_ptr = &widget->layout_top;
            *(int*)&widget->layout_anchor_x = left_bits;
            *(int*)&widget->layout_anchor_y = top_bits;
        } else if ((result & 0x10000) != 0) {
            result = *(int*)&widget->authored_left;
            int authored_top = *(int*)&widget->authored_top;
            int authored_width = *(int*)&widget->authored_width;
            layout_left_ptr = &widget->layout_left;
            layout_top_ptr = &widget->layout_top;
            *(int*)&widget->layout_width = authored_width;
            *(int*)layout_left_ptr = result;
            int authored_height = *(int*)&widget->authored_height;
            *(int*)layout_top_ptr = authored_top;
            *(int*)&widget->layout_height = authored_height;
        } else {
            layout_top_ptr = &widget->layout_top;
            layout_left_ptr = &widget->layout_left;
            result = (int)layout_and_queue_wrapped_font_text(
                widget->text_buffer,
                widget->font_id,
                widget->font_scale,
                widget->layout_anchor_x,
                widget->layout_anchor_y,
                layout_left_ptr,
                layout_top_ptr,
                &widget->layout_width,
                &widget->layout_height,
                widget->text_effect_current,
                text_wave_enabled,
                widget->text_alignment,
                widget->anchor_x,
                0x1000000,
                &widget->idle_text_color,
                1,
                0);
        }

        int layout_left_bits = *(int*)layout_left_ptr;
        int layout_top_bits = *(int*)layout_top_ptr;
        *(int*)&widget->clamped_left = layout_left_bits;
        unsigned int flags = widget->widget_flags;
        *(int*)&widget->clamped_top = layout_top_bits;
        if ((flags & 0x20000000) == 0) {
            float right = *layout_left_ptr + widget->hot_padding;
            right += widget->layout_width;
            if (right > 640.0f) {
                widget->clamped_left =
                    640.0f - widget->hot_padding - widget->layout_width;
            } else {
                if (*layout_left_ptr - widget->hot_padding < 0.0f) {
                    widget->clamped_left = widget->hot_padding;
                }
            }

            float bottom = widget->hot_padding + *layout_top_ptr;
            if (bottom > 480.0f) {
                widget->clamped_top = 480.0f - widget->hot_padding;
            } else {
                if (*layout_top_ptr - widget->hot_padding < 0.0f) {
                    widget->clamped_top = widget->hot_padding;
                }
            }

            float dx = widget->clamped_left - *layout_left_ptr;
            result = flags;
            result &= 0x100000;
            widget->anchor_x = dx + widget->anchor_x;
            widget->layout_anchor_x = dx + widget->layout_anchor_x;
            widget->layout_anchor_y =
                widget->clamped_top - *layout_top_ptr + widget->layout_anchor_y;

            float clamped_left = widget->clamped_left;
            *layout_left_ptr = clamped_left;
            float clamped_top = widget->clamped_top;
            float clamped_top_local = clamped_top;
            *layout_top_ptr = clamped_top_local;

            if (result != 0) {
                widget->slider_hit_left =
                    widget->layout_width * 0.100000001f + clamped_left + 4.0f -
                    12.0f;
                widget->slider_hit_right =
                    widget->layout_width * 0.80000001f + clamped_left - 4.0f;
                float slider_mid =
                    widget->layout_height * 0.5f + clamped_top_local;
                widget->slider_hit_top = slider_mid - 6.0f;
                widget->slider_hit_bottom = slider_mid + 32.0f - 6.0f;
            }

            if (result == 0) {
                break;
            }

            widget->slider_more_widget->layout_top = widget->clamped_top + 33.0f;
            widget->slider_more_widget->layout_frontend_widget();
            widget->slider_less_widget->layout_top = widget->clamped_top + 33.0f;
            widget->slider_less_widget->layout_frontend_widget();
            widget->slider_value_widget->layout_anchor_y =
                widget->clamped_top + 49.0f;
            widget = widget->slider_value_widget;
        } else {
            break;
        }
    }

    return result;
}
