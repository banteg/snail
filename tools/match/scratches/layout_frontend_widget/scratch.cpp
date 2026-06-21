// layout_frontend_widget @ 0x4024a0 (thiscall, ret)

#include "frontend_widget.h"

extern unsigned int g_render_flags; // data_4df934

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

#define WIDGET_FLOAT_AT(widget, offset) (*(float*)((char*)(widget) + (offset)))

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
            int left_bits = *(int*)&widget->layout_x;
            int top_bits = *(int*)&widget->layout_y;
            layout_left_ptr = &widget->layout_x;
            layout_top_ptr = &widget->layout_y;
            *(int*)&widget->layout_anchor_x = left_bits;
            *(int*)&widget->layout_anchor_y = top_bits;
        } else if ((result & 0x10000) != 0) {
            result = *(int*)&widget->frame_x;
            int authored_top = *(int*)&widget->frame_y;
            layout_left_ptr = &widget->layout_x;
            layout_top_ptr = &widget->layout_y;
            *(int*)layout_left_ptr = result;
            int authored_width = *(volatile int*)&widget->frame_width;
            *(int*)&widget->layout_width = authored_width;
            result = *(int*)&widget->frame_height;
            *(int*)layout_top_ptr = authored_top;
            *(int*)&widget->layout_height = result;
        } else {
            layout_top_ptr = &widget->layout_y;
            layout_left_ptr = &widget->layout_x;
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
                widget->layout_mode,
                widget->layout_center_x,
                0x1000000,
                &widget->idle_text_color,
                1,
                0);
        }

        int layout_left_bits = *(int*)layout_left_ptr;
        *(int*)&widget->texture_hit_x = layout_left_bits;
        unsigned int flags = widget->widget_flags;
        int layout_top_bits = *(int*)layout_top_ptr;
        *(int*)&widget->texture_hit_y = layout_top_bits;
        if ((flags & 0x20000000) == 0) {
            float right = *layout_left_ptr + widget->hot_padding;
            right += widget->layout_width;
            if (right > 640.0f) {
                widget->texture_hit_x =
                    640.0f - widget->hot_padding - widget->layout_width;
            } else {
                if (*layout_left_ptr - widget->hot_padding < 0.0f) {
                    widget->texture_hit_x = widget->hot_padding;
                }
            }

            float bottom = widget->hot_padding + *layout_top_ptr;
            if (bottom > 480.0f) {
                widget->texture_hit_y = 480.0f - widget->hot_padding;
            } else {
                if (*layout_top_ptr - widget->hot_padding < 0.0f) {
                    widget->texture_hit_y = widget->hot_padding;
                }
            }

            float dx = widget->texture_hit_x - *layout_left_ptr;
            result = flags & 0x100000;
            widget->layout_center_x = dx + widget->layout_center_x;
            widget->layout_anchor_x = dx + widget->layout_anchor_x;
            widget->layout_anchor_y =
                widget->texture_hit_y - *layout_top_ptr + widget->layout_anchor_y;

            float clamped_left = widget->texture_hit_x;
            *layout_left_ptr = clamped_left;
            float clamped_top = widget->texture_hit_y;
            float clamped_top_local = clamped_top;
            *layout_top_ptr = clamped_top_local;

            if ((flags & 0x100000) != 0) {
                WIDGET_FLOAT_AT(widget, 0x184) =
                    widget->layout_width * 0.100000001f + clamped_left + 4.0f -
                    12.0f;
                WIDGET_FLOAT_AT(widget, 0x188) =
                    widget->layout_width * 0.80000001f + clamped_left - 4.0f;
                float slider_mid =
                    widget->layout_height * 0.5f + clamped_top_local;
                WIDGET_FLOAT_AT(widget, 0x18c) = slider_mid - 6.0f;
                WIDGET_FLOAT_AT(widget, 0x190) = slider_mid + 32.0f - 6.0f;
            }

            if (result == 0) {
                break;
            }

            widget->child_widget_1->layout_y = widget->texture_hit_y + 33.0f;
            widget->child_widget_1->layout_frontend_widget();
            widget->child_widget_0->layout_y = widget->texture_hit_y + 33.0f;
            widget->child_widget_0->layout_frontend_widget();
            widget->child_widget_2->layout_anchor_y =
                widget->texture_hit_y + 49.0f;
            widget = widget->child_widget_2;
        } else {
            break;
        }
    }

    return result;
}
