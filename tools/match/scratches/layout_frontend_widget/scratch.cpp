// layout_frontend_widget @ 0x4024a0 (thiscall, ret)

#include "font_system.h"
#include "frontend_widget.h"
#include "runtime_config.h"

void cRBorder::RePosition()
{
    cRBorder* widget = this;
    int result;

    while (true) {
        char shadow_enabled = (char)(
            (g_runtime_config.render_flags >> RUNTIME_RENDER_FONT_SHADOW_BIT) & 1);
        result = widget->widget_flags;

        float* layout_left_ptr;
        float* layout_top_ptr;
        if ((result & FRONTEND_WIDGET_FLAG_SPRITE_MODE) != 0) {
            int left_bits = *(int*)&widget->layout_x;
            int top_bits = *(int*)&widget->layout_y;
            layout_left_ptr = &widget->layout_x;
            layout_top_ptr = &widget->layout_y;
            *(int*)&widget->layout_anchor_x = left_bits;
            *(int*)&widget->layout_anchor_y = top_bits;
        } else if ((result & FRONTEND_WIDGET_FLAG_USE_AUTHORED_RECT) != 0) {
            layout_left_ptr = &widget->layout_x;
            layout_top_ptr = &widget->layout_y;
            widget->layout_x = widget->frame_x;
            widget->layout_y = widget->frame_y;
            widget->layout_width = widget->frame_width;
            widget->layout_height = widget->frame_height;
        } else {
            layout_top_ptr = &widget->layout_y;
            layout_left_ptr = &widget->layout_x;
            FontType(
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
                shadow_enabled,
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
        if ((flags & FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN) == 0) {
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
            result = flags & FRONTEND_WIDGET_FLAG_SLIDER;
            widget->layout_center_x = dx + widget->layout_center_x;
            widget->layout_anchor_x = dx + widget->layout_anchor_x;
            widget->layout_anchor_y =
                widget->texture_hit_y - *layout_top_ptr + widget->layout_anchor_y;

            float clamped_left = widget->texture_hit_x;
            *layout_left_ptr = clamped_left;
            float clamped_top = widget->texture_hit_y;
            float clamped_top_local = clamped_top;
            *layout_top_ptr = clamped_top_local;

            if ((flags & FRONTEND_WIDGET_FLAG_SLIDER) != 0) {
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

            widget->slider_more_widget->layout_y = widget->texture_hit_y + 33.0f;
            widget->slider_more_widget->RePosition();
            widget->slider_less_widget->layout_y = widget->texture_hit_y + 33.0f;
            widget->slider_less_widget->RePosition();
            widget->slider_value_widget->layout_anchor_y =
                widget->texture_hit_y + 49.0f;
            widget = widget->slider_value_widget;
        } else {
            break;
        }
    }

}
