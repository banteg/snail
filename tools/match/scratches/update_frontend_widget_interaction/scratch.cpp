// update_frontend_widget_interaction @ 0x402820 (thiscall)

#include "border_manager.h"
#include "font_system.h"
#include "frontend_widget.h"
#include "game_root.h"
#include "mouse_cursor_state.h"
#include "runtime_config.h"
#include "sound_effect_manager.h"
#include "tooltip_state.h"
#include "twinkle_manager.h"

extern char* g_game_base; // data_4df904

char read_pressed_text_input_key_code();
int sprintf(char* buffer, const char* format, ...);
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

void FrontendWidget::update_frontend_widget_interaction()
{
    previous_widget_flags = widget_flags;
    widget_flags &= 0xfffdffff;

    if ((widget_flags & 0x100000) != 0) {
        slider_hit_left = layout_width * 0.1f + layout_x + 4.0f - 12.0f;
        slider_hit_right = layout_width * 0.80000001f + layout_x - 4.0f;
        slider_hit_top = layout_height * 0.5f + layout_y - 6.0f;
        slider_hit_bottom = layout_height * 0.5f + layout_y + 32.0f - 6.0f;
    }

    slider_target_value =
        (slider_value - slider_target_value) * 0.80000001f + slider_target_value;

    unsigned int flags = widget_flags;
    if (flags == 0) {
        ((GameRoot*)g_game_base)->active_bod_list.remove_bod((BodNode*)this);
        tooltip.reset_tooltip();
        return;
    }
    if ((flags & 0x200) != 0) {
        widget_flags = flags & ~0x200u;
        ((GameRoot*)g_game_base)->active_bod_list.remove_bod((BodNode*)this);
        tooltip.reset_tooltip();
        widget_flags = 0;
        return;
    }

    if ((flags & 0x400) != 0) {
        teardown_progress = teardown_progress_step + teardown_progress;
        if (teardown_progress > 1.0f) {
            ((GameRoot*)g_game_base)->active_bod_list.remove_bod((BodNode*)this);
            tooltip.reset_tooltip();
            widget_flags = 0;
            return;
        }
        goto update_after_input;
    }

    if ((flags & 0x1000) != 0)
        return;

    if ((flags & 0x8000) != 0) {
        text_effect_target = 0.0f;
        widget_flags &= ~2u;
        goto update_after_input;
    }

    if ((flags & 2) != 0)
        hover_blend_target = 1.0f;

    if ((widget_flags & 0x2000000) != 0
        && mouse_history_warmup_frames == 0
        && (((GameRoot*)g_game_base)->players[0].mouse_cursor.saved_x != previous_mouse_x
            || ((GameRoot*)g_game_base)->players[0].mouse_cursor.saved_y != previous_mouse_y)) {
        widget_flags |= 0x4000000;
    }

    if ((widget_flags & 0x80000) != 0
        && ((GameRoot*)g_game_base)->players[0].mouse_cursor.is_mouse_captured()
        && read_pressed_text_input_key_code() == shortcut_key_code) {
        tooltip.reset_tooltip();
        if ((widget_flags & 0x1000000) != 0)
            widget_flags |= 0x20;
        else
            ((GameRoot*)g_game_base)->border_manager
                .queue_frontend_widget_flag_after_delay(this, 0x20);
    }

    if (((GameRoot*)g_game_base)->players[0].mouse_cursor.is_mouse_captured() == 0
        || border_mouse_test() == 0) {
        widget_flags &= 0xffdfffff;
        if (((widget_flags & 0x2000) == 0)
            && ((widget_flags & 4) != 0)) {
            unhighlight_border();
        }
        text_effect_target = 0.0f;
        if ((widget_flags & 4) != 0)
            widget_flags &= ~2u;
        goto update_after_input;
    }

    widget_flags |= 0x20000;
    if ((widget_flags & 4) != 0) {
        hover_blend_target = 1.0f;
        target_padding = hot_padding;
    }
    if ((widget_flags & 8) != 0)
        text_effect_target = 1.0f;
    if (((widget_flags & 2) == 0)
        && ((widget_flags & 4) != 0)) {
        if ((widget_flags & 0x40000) == 0)
            g_sound_effect_manager.play_sound_effect(9);
        widget_flags |= 2;
    }

    if ((widget_flags & 0x10) != 0) {
        GameInput* input = ((GameRoot*)g_game_base)->players[0].game_input;
        if (((GameRoot*)g_game_base)->border_manager.delayed_widget_active == 0
            && (input->input.pressed_buttons & 0x4000) != 0) {
            if ((widget_flags & 0x1000000) != 0) {
                widget_flags |= 0x20;
            } else {
                ((GameRoot*)g_game_base)->border_manager
                    .queue_frontend_widget_flag_after_delay(this, 0x20);
            }
            if ((widget_flags & 0x800000) == 0)
                g_sound_effect_manager.play_sound_effect(8);
            if ((tooltip.mode_flags & 0x20) == 0)
                tooltip.reset_tooltip();
        }
    }

    {
        GameInput* input = ((GameRoot*)g_game_base)->players[0].game_input;
        if ((widget_flags & 0x40) != 0
            && (((unsigned char*)&input->input.pressed_buttons)[1] & 0x80) != 0) {
            if ((widget_flags & 0x1000000) != 0)
                widget_flags |= 0x80;
            else
                ((GameRoot*)g_game_base)->border_manager
                    .queue_frontend_widget_flag_after_delay(this, 0x80);
            g_sound_effect_manager.play_sound_effect(8);
            tooltip.reset_tooltip();
        }
    }

update_after_input:
    if ((widget_flags & 0x8000) != 0) {
        widget_flags &= 0xffdfffff;
        unhighlight_border();
    }
    if ((widget_flags & 0x40000) != 0) {
        widget_flags &= 0xfffbffff;
        hover_blend_current = hover_blend_target;
        current_padding = target_padding;
        text_effect_current = text_effect_target;
    } else {
        hover_blend_current += (hover_blend_target - hover_blend_current) * 0.1f;
        current_padding += (target_padding - current_padding) * 0.1f;
        text_effect_current += (text_effect_target - text_effect_current) * 0.1f;
        float diff = text_effect_target - text_effect_current;
        if (diff < 0.0f)
            diff = -diff;
        if (diff < 0.1f)
            text_effect_current = text_effect_target;
    }

    if ((widget_flags & 0x2000) != 0
        && ((GameRoot*)g_game_base)->players[0].mouse_cursor.is_mouse_captured() != 0) {
        border_input_text();
        if ((widget_flags & 0x2000) == 0)
            ((GameRoot*)g_game_base)->border_manager.activate_all_borders();
    }

    twinkle_manager.update_twinkle_manager();
    tooltip.update_tooltip();
    char render_hot_text = (char)((widget_flags >> 8) & 1);
    layout_frontend_widget();

    if ((widget_flags & 0x1000) == 0) {
        float cold = 1.0f - hover_blend_current;
        current_fill_color.store_color4f(
            hover_blend_current * hot_fill_color.r + cold * idle_fill_color.r,
            hover_blend_current * hot_fill_color.g + cold * idle_fill_color.g,
            hover_blend_current * hot_fill_color.b + cold * idle_fill_color.b,
            hover_blend_current * hot_fill_color.a + cold * idle_fill_color.a);

        current_text_color.store_color4f(
            hover_blend_current * hot_text_color.r + cold * idle_text_color.r,
            hover_blend_current * hot_text_color.g + cold * idle_text_color.g,
            hover_blend_current * hot_text_color.b + cold * idle_text_color.b,
            hover_blend_current * hot_text_color.a + cold * idle_text_color.a);

        if ((widget_flags & 0x8000) != 0) {
            current_text_color.r *= 0.5f;
            current_text_color.g *= 0.5f;
            current_text_color.b *= 0.5f;
            current_text_color.a *= 0.5f;
            current_fill_color.r *= 0.5f;
            current_fill_color.g *= 0.5f;
            current_fill_color.b *= 0.5f;
            current_fill_color.a *= 0.5f;
        }

        if ((widget_flags & 0x800) == 0) {
            if ((widget_flags & 0x10000) != 0) {
                layout_x = frame_x;
                layout_y = frame_y;
                layout_width = frame_width;
                layout_height = frame_height;
            } else {
                layout_and_queue_wrapped_font_text(
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
                    g_runtime_config.render_flags & 1,
                    text_alignment,
                    anchor_x,
                    0x1000000,
                    &current_text_color,
                    0,
                    render_hot_text);
            }
        }
        draw_frontend_widget();
    }

    if (mouse_history_warmup_frames != 0)
        --mouse_history_warmup_frames;
    previous_mouse_x = ((GameRoot*)g_game_base)->players[0].mouse_cursor.saved_x;
    previous_mouse_y = ((GameRoot*)g_game_base)->players[0].mouse_cursor.saved_y;

    if ((widget_flags & 0x100000) != 0) {
        FrontendWidget* more = slider_more_widget;
        if ((more->widget_flags & 0x20) != 0) {
            more->widget_flags &= ~0x20u;
            slider_value += 0.2f;
            if (slider_value >= 0.89999998f)
                slider_value = 1.0f;
        }

        FrontendWidget* less = slider_less_widget;
        if ((less->widget_flags & 0x20) != 0) {
            less->widget_flags &= ~0x20u;
            slider_value -= 0.2f;
            if (slider_value <= 0.1f)
                slider_value = 0.0f;
        }

        if (slider_value == 0.0f)
            less->widget_flags |= 0x8000;
        else
            less->widget_flags &= ~0x8000u;

        if (slider_value == 1.0f)
            more->widget_flags |= 0x8000;
        else
            more->widget_flags &= ~0x8000u;

        FrontendWidget* value = slider_value_widget;
        value->current_text_color = current_text_color;
        value->hover_blend_target = hover_blend_target;
        value->hover_blend_current = hover_blend_current;
        sprintf(value->text_buffer, "%02i%%", (int)(slider_value * 100.0f + 0.1f));
    }
}
