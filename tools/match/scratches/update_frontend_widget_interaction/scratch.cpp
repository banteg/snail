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
    char* self = (char*)this;
    *(unsigned int*)(self + 0x1a4) = *(unsigned int*)(self + 0x1a0);
    *(unsigned int*)(self + 0x1a0) &= 0xfffdffff;

    if ((*(unsigned int*)(self + 0x1a0) & 0x100000) != 0) {
        *(float*)(self + 0x184) = *(float*)(self + 0x248) * 0.1f + *(float*)(self + 0x238) + 4.0f - 12.0f;
        *(float*)(self + 0x188) = *(float*)(self + 0x248) * 0.80000001f + *(float*)(self + 0x238) - 4.0f;
        *(float*)(self + 0x18c) = *(float*)(self + 0x24c) * 0.5f + *(float*)(self + 0x23c) - 6.0f;
        *(float*)(self + 0x190) = *(float*)(self + 0x24c) * 0.5f + *(float*)(self + 0x23c) + 32.0f - 6.0f;
    }

    *(float*)(self + 0x180) =
        (*(float*)(self + 0x17c) - *(float*)(self + 0x180)) * 0.80000001f
        + *(float*)(self + 0x180);

    unsigned int flags = *(unsigned int*)(self + 0x1a0);
    if (flags == 0) {
        ((GameRoot*)g_game_base)->active_bod_list.remove_bod((BodNode*)this);
        ((FrontendWidgetTooltip*)(self + 0x28c))->reset_tooltip();
        return;
    }
    if ((flags & 0x200) != 0) {
        *(unsigned int*)(self + 0x1a0) = flags & ~0x200u;
        ((GameRoot*)g_game_base)->active_bod_list.remove_bod((BodNode*)this);
        ((FrontendWidgetTooltip*)(self + 0x28c))->reset_tooltip();
        *(int*)(self + 0x1a0) = 0;
        return;
    }

    if ((flags & 0x400) != 0) {
        teardown_progress = teardown_progress_step + teardown_progress;
        if (teardown_progress > 1.0f) {
            ((GameRoot*)g_game_base)->active_bod_list.remove_bod((BodNode*)this);
            ((FrontendWidgetTooltip*)(self + 0x28c))->reset_tooltip();
            *(int*)(self + 0x1a0) = 0;
            return;
        }
        goto update_after_input;
    }

    if ((flags & 0x1000) != 0)
        return;

    if ((flags & 0x8000) != 0) {
        *(float*)(self + 0x224) = 0.0f;
        *(unsigned int*)(self + 0x1a0) &= ~2u;
        goto update_after_input;
    }

    if ((flags & 2) != 0)
        *(float*)(self + 0x20c) = 1.0f;

    if ((*(unsigned int*)(self + 0x1a0) & 0x2000000) != 0
        && mouse_history_warmup_frames == 0
        && (*(float*)(g_game_base + 0x29c) != previous_mouse_x
            || *(float*)(g_game_base + 0x2a0) != previous_mouse_y)) {
        *(unsigned int*)(self + 0x1a0) |= 0x4000000;
    }

    if ((*(unsigned int*)(self + 0x1a0) & 0x80000) != 0
        && ((MouseCursorState*)(g_game_base + 0x290))->is_mouse_captured()
        && read_pressed_text_input_key_code() == shortcut_key_code) {
        ((FrontendWidgetTooltip*)(self + 0x28c))->reset_tooltip();
        if ((*(unsigned int*)(self + 0x1a0) & 0x1000000) != 0)
            *(unsigned int*)(self + 0x1a0) |= 0x20;
        else
            ((BorderManager*)(g_game_base + 0xb4c))
                ->queue_frontend_widget_flag_after_delay(this, 0x20);
    }

    if (((MouseCursorState*)(g_game_base + 0x290))->is_mouse_captured() == 0
        || border_mouse_test() == 0) {
        *(unsigned int*)(self + 0x1a0) &= 0xffdfffff;
        if (((*(unsigned int*)(self + 0x1a0) & 0x2000) == 0)
            && ((*(unsigned int*)(self + 0x1a0) & 4) != 0)) {
            unhighlight_border();
        }
        *(float*)(self + 0x224) = 0.0f;
        if ((*(unsigned int*)(self + 0x1a0) & 4) != 0)
            *(unsigned int*)(self + 0x1a0) &= ~2u;
        goto update_after_input;
    }

    *(unsigned int*)(self + 0x1a0) |= 0x20000;
    if ((*(unsigned int*)(self + 0x1a0) & 4) != 0) {
        *(float*)(self + 0x20c) = 1.0f;
        *(float*)(self + 0x21c) = *(float*)(self + 0x218);
    }
    if ((*(unsigned int*)(self + 0x1a0) & 8) != 0)
        *(float*)(self + 0x224) = 1.0f;
    if (((*(unsigned int*)(self + 0x1a0) & 2) == 0)
        && ((*(unsigned int*)(self + 0x1a0) & 4) != 0)) {
        if ((*(unsigned int*)(self + 0x1a0) & 0x40000) == 0)
            g_sound_effect_manager.play_sound_effect(9);
        *(unsigned int*)(self + 0x1a0) |= 2;
    }

    if ((*(unsigned int*)(self + 0x1a0) & 0x10) != 0) {
        unsigned char* input = *(unsigned char**)(g_game_base + 0x28c);
        if (((BorderManager*)(g_game_base + 0xb4c))->delayed_widget_active == 0
            && (input[0x3d] & 0x40) != 0) {
            if ((*(unsigned int*)(self + 0x1a0) & 0x1000000) != 0) {
                *(unsigned int*)(self + 0x1a0) |= 0x20;
            } else {
                ((BorderManager*)(g_game_base + 0xb4c))
                    ->queue_frontend_widget_flag_after_delay(this, 0x20);
            }
            if ((*(unsigned int*)(self + 0x1a0) & 0x800000) == 0)
                g_sound_effect_manager.play_sound_effect(8);
            if ((tooltip.mode_flags & 0x20) == 0)
                tooltip.reset_tooltip();
        }
    }

    {
        unsigned char* input = *(unsigned char**)(g_game_base + 0x28c);
        if ((*(unsigned int*)(self + 0x1a0) & 0x40) != 0
            && (input[0x3d] & 0x80) != 0) {
            if ((*(unsigned int*)(self + 0x1a0) & 0x1000000) != 0)
                *(unsigned int*)(self + 0x1a0) |= 0x80;
            else
                ((BorderManager*)(g_game_base + 0xb4c))
                    ->queue_frontend_widget_flag_after_delay(this, 0x80);
            g_sound_effect_manager.play_sound_effect(8);
            tooltip.reset_tooltip();
        }
    }

update_after_input:
    if ((*(unsigned int*)(self + 0x1a0) & 0x8000) != 0) {
        *(unsigned int*)(self + 0x1a0) &= 0xffdfffff;
        unhighlight_border();
    }
    if ((*(unsigned int*)(self + 0x1a0) & 0x40000) != 0) {
        *(unsigned int*)(self + 0x1a0) &= 0xfffbffff;
        *(float*)(self + 0x210) = *(float*)(self + 0x20c);
        *(float*)(self + 0x220) = *(float*)(self + 0x21c);
        *(float*)(self + 0x228) = *(float*)(self + 0x224);
    } else {
        *(float*)(self + 0x210) += (*(float*)(self + 0x20c) - *(float*)(self + 0x210)) * 0.1f;
        *(float*)(self + 0x220) += (*(float*)(self + 0x21c) - *(float*)(self + 0x220)) * 0.1f;
        *(float*)(self + 0x228) += (*(float*)(self + 0x224) - *(float*)(self + 0x228)) * 0.1f;
        float diff = *(float*)(self + 0x224) - *(float*)(self + 0x228);
        if (diff < 0.0f)
            diff = -diff;
        if (diff < 0.1f)
            *(float*)(self + 0x228) = *(float*)(self + 0x224);
    }

    if ((*(unsigned int*)(self + 0x1a0) & 0x2000) != 0
        && ((MouseCursorState*)(g_game_base + 0x290))->is_mouse_captured() != 0) {
        border_input_text();
        if ((*(unsigned int*)(self + 0x1a0) & 0x2000) == 0)
            ((BorderManager*)(g_game_base + 0xb4c))->activate_all_borders();
    }

    twinkle_manager.update_twinkle_manager();
    ((FrontendWidgetTooltip*)(self + 0x28c))->update_tooltip();
    char render_hot_text = (char)((*(unsigned int*)(self + 0x1a0) >> 8) & 1);
    layout_frontend_widget();

    if ((*(unsigned int*)(self + 0x1a0) & 0x1000) == 0) {
        float cold = 1.0f - *(float*)(self + 0x210);
        ((Color4f*)(self + 0x1ac))->store_color4f(
            *(float*)(self + 0x210) * *(float*)(self + 0x1cc) + cold * *(float*)(self + 0x1bc),
            *(float*)(self + 0x210) * *(float*)(self + 0x1d0) + cold * *(float*)(self + 0x1c0),
            *(float*)(self + 0x210) * *(float*)(self + 0x1d4) + cold * *(float*)(self + 0x1c4),
            *(float*)(self + 0x210) * *(float*)(self + 0x1d8) + cold * *(float*)(self + 0x1c8));

        ((Color4f*)(self + 0x1dc))->store_color4f(
            *(float*)(self + 0x210) * *(float*)(self + 0x1fc) + cold * *(float*)(self + 0x1ec),
            *(float*)(self + 0x210) * *(float*)(self + 0x200) + cold * *(float*)(self + 0x1f0),
            *(float*)(self + 0x210) * *(float*)(self + 0x204) + cold * *(float*)(self + 0x1f4),
            *(float*)(self + 0x210) * *(float*)(self + 0x208) + cold * *(float*)(self + 0x1f8));

        if ((*(unsigned int*)(self + 0x1a0) & 0x8000) != 0) {
            ((Color4f*)(self + 0x1dc))->r *= 0.5f;
            ((Color4f*)(self + 0x1dc))->g *= 0.5f;
            ((Color4f*)(self + 0x1dc))->b *= 0.5f;
            ((Color4f*)(self + 0x1dc))->a *= 0.5f;
            ((Color4f*)(self + 0x1ac))->r *= 0.5f;
            ((Color4f*)(self + 0x1ac))->g *= 0.5f;
            ((Color4f*)(self + 0x1ac))->b *= 0.5f;
            ((Color4f*)(self + 0x1ac))->a *= 0.5f;
        }

        if ((*(unsigned int*)(self + 0x1a0) & 0x800) == 0) {
            if ((*(unsigned int*)(self + 0x1a0) & 0x10000) != 0) {
                *(float*)(self + 0x238) = *(float*)(self + 0x4c);
                *(float*)(self + 0x23c) = *(float*)(self + 0x50);
                *(float*)(self + 0x248) = *(float*)(self + 0x54);
                *(float*)(self + 0x24c) = *(float*)(self + 0x58);
            } else {
                layout_and_queue_wrapped_font_text(
                    self + 0x2cc,
                    *(int*)(self + 0x6ec),
                    *(float*)(self + 0x6f0),
                    *(float*)(self + 0x6f4),
                    *(float*)(self + 0x6f8),
                    &layout_x,
                    &layout_y,
                    &layout_width,
                    &layout_height,
                    *(float*)(self + 0x228),
                    g_runtime_config.render_flags & 1,
                    *(int*)(self + 0x25c),
                    *(float*)(self + 0x260),
                    0x1000000,
                    (Color4f*)(self + 0x1dc),
                    0,
                    render_hot_text);
            }
        }
        draw_frontend_widget();
    }

    if (mouse_history_warmup_frames != 0)
        --mouse_history_warmup_frames;
    previous_mouse_x = *(float*)(g_game_base + 0x29c);
    previous_mouse_y = *(float*)(g_game_base + 0x2a0);

    if ((*(unsigned int*)(self + 0x1a0) & 0x100000) != 0) {
        FrontendWidget* more = *(FrontendWidget**)(self + 0x71c);
        if ((*(unsigned int*)((char*)more + 0x1a0) & 0x20) != 0) {
            *(unsigned int*)((char*)more + 0x1a0) &= ~0x20u;
            *(float*)(self + 0x17c) += 0.2f;
            if (*(float*)(self + 0x17c) >= 0.89999998f)
                *(float*)(self + 0x17c) = 1.0f;
        }

        FrontendWidget* less = *(FrontendWidget**)(self + 0x718);
        if ((*(unsigned int*)((char*)less + 0x1a0) & 0x20) != 0) {
            *(unsigned int*)((char*)less + 0x1a0) &= ~0x20u;
            *(float*)(self + 0x17c) -= 0.2f;
            if (*(float*)(self + 0x17c) <= 0.1f)
                *(float*)(self + 0x17c) = 0.0f;
        }

        if (*(float*)(self + 0x17c) == 0.0f)
            *(unsigned int*)((char*)less + 0x1a0) |= 0x8000;
        else
            *(unsigned int*)((char*)less + 0x1a0) &= ~0x8000u;

        if (*(float*)(self + 0x17c) == 1.0f)
            *(unsigned int*)((char*)more + 0x1a0) |= 0x8000;
        else
            *(unsigned int*)((char*)more + 0x1a0) &= ~0x8000u;

        FrontendWidget* value = *(FrontendWidget**)(self + 0x720);
        *(Color4f*)((char*)value + 0x1dc) = *(Color4f*)(self + 0x1dc);
        *(float*)((char*)value + 0x20c) = *(float*)(self + 0x20c);
        *(float*)((char*)value + 0x210) = *(float*)(self + 0x210);
        sprintf((char*)value + 0x2cc, "%02i%%", (int)(*(float*)(self + 0x17c) * 100.0f + 0.1f));
    }
}
