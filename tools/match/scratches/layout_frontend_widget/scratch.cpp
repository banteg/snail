// layout_frontend_widget @ 0x4024a0 (thiscall, ret)

#include "font_system.h"
#include "frontend_widget.h"
#include "runtime_config.h"

void cRBorder::RePosition()
{
    int result;

    char shadow_enabled = (char)(
        (g_runtime_config.render_flags >> RUNTIME_RENDER_FONT_SHADOW_BIT) & 1);
    result = widget_flags;
    if ((result & FRONTEND_WIDGET_FLAG_SPRITE_MODE) != 0) {
        int left_bits = *(int*)&layout_x;
        int top_bits = *(int*)&layout_y;
        *(int*)&layout_anchor_x = left_bits;
        *(int*)&layout_anchor_y = top_bits;
    } else if ((result & FRONTEND_WIDGET_FLAG_USE_AUTHORED_RECT) != 0) {
        layout_x = frame_x;
        layout_y = frame_y;
        layout_width = frame_width;
        layout_height = frame_height;
    } else {
        FontType(
            text_buffer,
            font_id,
            font_scale,
            layout_anchor_x,
            layout_anchor_y,
            &layout_x,
            &layout_y,
            &layout_width,
            &layout_height,
            text_effect_current,
            shadow_enabled,
            layout_mode,
            layout_center_x,
            0x1000000,
            &idle_text_color,
            1,
            0);
    }

    texture_hit_x = layout_x;
    unsigned int flags = widget_flags;
    texture_hit_y = layout_y;
    if ((flags & FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN) == 0) {
        float right = layout_x + hot_padding;
        right += layout_width;
        if (right > 640.0f) {
            texture_hit_x =
                640.0f - hot_padding - layout_width;
        } else {
            if (layout_x - hot_padding < 0.0f) {
                texture_hit_x = hot_padding;
            }
        }

        float bottom = hot_padding + layout_y;
        if (bottom > 480.0f) {
            texture_hit_y = 480.0f - hot_padding;
        } else {
            if (layout_y - hot_padding < 0.0f) {
                texture_hit_y = hot_padding;
            }
        }

        float dx = texture_hit_x - layout_x;
        result = flags & FRONTEND_WIDGET_FLAG_SLIDER;
        layout_center_x = dx + layout_center_x;
        layout_anchor_x = dx + layout_anchor_x;
        layout_anchor_y =
            texture_hit_y - layout_y + layout_anchor_y;

        float clamped_left = texture_hit_x;
        layout_x = clamped_left;
        float clamped_top = texture_hit_y;
        layout_y = clamped_top;

        if ((flags & FRONTEND_WIDGET_FLAG_SLIDER) != 0) {
            slider_hit_left =
                layout_width * 0.100000001f + clamped_left + 4.0f -
                12.0f;
            slider_hit_right =
                layout_width * 0.80000001f + clamped_left - 4.0f;
            float slider_mid =
                layout_height * 0.5f + clamped_top;
            slider_hit_top = slider_mid - 6.0f;
            slider_hit_bottom = slider_mid + 32.0f - 6.0f;
        }

        if (result == 0) {
            return;
        }

        slider_more_widget->layout_y = texture_hit_y + 33.0f;
        slider_more_widget->RePosition();
        slider_less_widget->layout_y = texture_hit_y + 33.0f;
        slider_less_widget->RePosition();
        slider_value_widget->layout_anchor_y =
            texture_hit_y + 49.0f;
        slider_value_widget->RePosition();
    } else {
        return;
    }
}
