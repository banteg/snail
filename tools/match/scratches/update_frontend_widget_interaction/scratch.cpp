// update_frontend_widget_interaction @ 0x402820 (thiscall)

#include "border_manager.h"
#include "font_system.h"
#include "frontend_widget.h"
#include "mouse_cursor_state.h"
#include "tooltip_state.h"
#include "twinkle_manager.h"

extern char* g_game_base; // data_4df904
extern unsigned int g_render_flags; // data_4df934

int report_errorf(char* format, ...);
char read_pressed_text_input_key_code();
unsigned char __fastcall border_mouse_test(void* widget);
void play_sound_effect(int sound_id);
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

void queue_frontend_widget_flag_after_delay(void* manager, FrontendWidget* widget, int flag);

static void unlink_frontend_widget(FrontendWidget* widget)
{
    char* self = (char*)widget;
    char* free_anchor = g_game_base + 0x5a8;
    unsigned int list_flags = *(unsigned int*)(self + 0x04);

    if ((list_flags & 0x200) == 0) {
        report_errorf("List remove");
        ((TooltipState*)(self + 0x28c))->reset_tooltip();
        *(int*)(self + 0x1a0) = 0;
        return;
    }
    if ((list_flags & 0x40) != 0) {
        report_errorf("List remove next");
        ((TooltipState*)(self + 0x28c))->reset_tooltip();
        *(int*)(self + 0x1a0) = 0;
        return;
    }

    FrontendWidget* next = *(FrontendWidget**)(self + 0x0c);
    FrontendWidget* prev = *(FrontendWidget**)(self + 0x08);
    if (next != 0)
        *(FrontendWidget**)((char*)next + 0x08) = prev;
    if (prev != 0)
        *(FrontendWidget**)((char*)prev + 0x0c) = next;
    else
        *(FrontendWidget**)(free_anchor + 4) = next;

    *(FrontendWidget**)(self + 0x0c) = *(FrontendWidget**)(free_anchor + 8);
    *(FrontendWidget**)(free_anchor + 8) = widget;
    *(unsigned int*)(self + 0x04) &= ~0x200u;
    ((TooltipState*)(self + 0x28c))->reset_tooltip();
    *(int*)(self + 0x1a0) = 0;
}

void FrontendWidget::update_frontend_widget_interaction()
{
    char* self = (char*)this;
    *(unsigned int*)(self + 0x1a4) = *(unsigned int*)(self + 0x1a0);
    *(unsigned int*)(self + 0x1a0) &= 0xfffdffff;

    if ((*(unsigned int*)(self + 0x1a0) & 0x100000) != 0) {
        *(float*)(self + 0x198) = *(float*)(self + 0x248) * 0.1f + *(float*)(self + 0x240) + 4.0f - 12.0f;
        *(float*)(self + 0x19c) = *(float*)(self + 0x248) * 0.80000001f + *(float*)(self + 0x240) - 4.0f;
        *(float*)(self + 0x1a8) = *(float*)(self + 0x24c) * 0.5f + *(float*)(self + 0x244) - 6.0f;
        *(float*)(self + 0x1ac) = *(float*)(self + 0x24c) * 0.5f + *(float*)(self + 0x244) + 32.0f - 6.0f;
    }

    *(float*)(self + 0x180) =
        (*(float*)(self + 0x17c) - *(float*)(self + 0x180)) * 0.80000001f
        + *(float*)(self + 0x180);

    unsigned int flags = *(unsigned int*)(self + 0x1a0);
    if (flags == 0) {
        unlink_frontend_widget(this);
        return;
    }
    if ((flags & 0x200) != 0) {
        *(unsigned int*)(self + 0x1a0) = flags & ~0x200u;
        unlink_frontend_widget(this);
        return;
    }

    if ((flags & 0x400) != 0) {
        *(float*)(self + 0x6f0) = *(float*)(self + 0x6ec) + *(float*)(self + 0x6f0);
        if (*(float*)(self + 0x6f0) > 1.0f) {
            unlink_frontend_widget(this);
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
        && *(int*)(self + 0x264) == 0
        && (*(float*)(g_game_base + 0x29c) != *(float*)(self + 0x6e4)
            || *(float*)(g_game_base + 0x2a0) != *(float*)(self + 0x6e8))) {
        *(unsigned int*)(self + 0x1a0) |= 0x4000000;
    }

    if ((*(unsigned int*)(self + 0x1a0) & 0x80000) != 0
        && ((MouseCursorState*)(g_game_base + 0x290))->is_mouse_captured()
        && read_pressed_text_input_key_code() == *(char*)(self + 0x194)) {
        ((TooltipState*)(self + 0x28c))->reset_tooltip();
        if ((*(unsigned int*)(self + 0x1a0) & 0x1000000) != 0)
            *(unsigned int*)(self + 0x1a0) |= 0x20;
        else
            queue_frontend_widget_flag_after_delay(g_game_base + 0xb4c, this, 0x20);
    }

    if (((MouseCursorState*)(g_game_base + 0x290))->is_mouse_captured() == 0
        || border_mouse_test(this) == 0) {
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
            play_sound_effect(9);
        *(unsigned int*)(self + 0x1a0) |= 2;
    }

    if ((*(unsigned int*)(self + 0x1a0) & 0x10) != 0) {
        char* input = *(char**)(g_game_base + 0x28c);
        if (*(unsigned char*)(g_game_base + 0x440ec) != 0 || (input[0x3d] & 0x40) == 0) {
            if (((*(unsigned int*)(self + 0x1a0) & 0x40) != 0) && input[0x3d] < 0) {
                if ((*(unsigned int*)(self + 0x1a0) & 0x1000000) != 0)
                    *(unsigned int*)(self + 0x1a0) |= 0x80;
                else
                    queue_frontend_widget_flag_after_delay(g_game_base + 0xb4c, this, 0x80);
                play_sound_effect(8);
                ((TooltipState*)(self + 0x28c))->reset_tooltip();
            } else if ((*(unsigned int*)(self + 0x1a0) & 0x1000000) != 0) {
                *(unsigned int*)(self + 0x1a0) |= 0x20;
            } else {
                queue_frontend_widget_flag_after_delay(g_game_base + 0xb4c, this, 0x20);
                if ((*(unsigned int*)(self + 0x1a0) & 0x800000) == 0)
                    play_sound_effect(8);
                if ((((TooltipState*)(self + 0x28c))->reset_tooltip(), (*(unsigned int*)(self + 0x290) & 0x20) == 0))
                    ((TooltipState*)(self + 0x28c))->reset_tooltip();
            }
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

    ((TwinkleManager*)(self + 0x80))->update_twinkle_manager();
    ((TooltipState*)(self + 0x28c))->update_tooltip();
    char render_hot_text = (char)((*(unsigned int*)(self + 0x1a0) >> 8) & 1);
    layout_frontend_widget();

    if ((*(unsigned int*)(self + 0x1a0) & 0x1000) == 0) {
        float cold = 1.0f - *(float*)(self + 0x210);
        ((Color4f*)(self + 0x1dc))->store_color4f(
            *(float*)(self + 0x210) * *(float*)(self + 0x1bc) + cold * *(float*)(self + 0x1ac),
            *(float*)(self + 0x210) * *(float*)(self + 0x1c0) + cold * *(float*)(self + 0x1b0),
            *(float*)(self + 0x210) * *(float*)(self + 0x1c4) + cold * *(float*)(self + 0x1b4),
            *(float*)(self + 0x210) * *(float*)(self + 0x1c8) + cold * *(float*)(self + 0x1b8));

        ((Color4f*)(self + 0x1cc))->store_color4f(
            *(float*)(self + 0x210) * *(float*)(self + 0x1fc) + cold * *(float*)(self + 0x1ec),
            *(float*)(self + 0x210) * *(float*)(self + 0x200) + cold * *(float*)(self + 0x1f0),
            *(float*)(self + 0x210) * *(float*)(self + 0x204) + cold * *(float*)(self + 0x1f4),
            *(float*)(self + 0x210) * *(float*)(self + 0x208) + cold * *(float*)(self + 0x1f8));

        if ((*(unsigned int*)(self + 0x1a0) & 0x8000) != 0) {
            ((Color4f*)(self + 0x1cc))->r *= 0.5f;
            ((Color4f*)(self + 0x1cc))->g *= 0.5f;
            ((Color4f*)(self + 0x1cc))->b *= 0.5f;
            ((Color4f*)(self + 0x1cc))->a *= 0.5f;
            ((Color4f*)(self + 0x1dc))->r *= 0.5f;
            ((Color4f*)(self + 0x1dc))->g *= 0.5f;
            ((Color4f*)(self + 0x1dc))->b *= 0.5f;
            ((Color4f*)(self + 0x1dc))->a *= 0.5f;
        }

        if ((*(unsigned int*)(self + 0x1a0) & 0x800) == 0) {
            if ((*(unsigned int*)(self + 0x1a0) & 0x10000) != 0) {
                *(float*)(self + 0x240) = *(float*)(self + 0x238);
                *(float*)(self + 0x244) = *(float*)(self + 0x23c);
                *(float*)(self + 0x248) = *(float*)(self + 0x250);
                *(float*)(self + 0x24c) = *(float*)(self + 0x254);
            } else {
                layout_and_queue_wrapped_font_text(
                    self + 0x2cc,
                    *(int*)(self + 0x18),
                    *(float*)(self + 0x1c),
                    *(float*)(self + 0x6f4),
                    *(float*)(self + 0x6f8),
                    (float*)(self + 0x240),
                    (float*)(self + 0x244),
                    (float*)(self + 0x248),
                    (float*)(self + 0x24c),
                    *(float*)(self + 0x228),
                    g_render_flags & 1,
                    *(int*)(self + 0x25c),
                    *(float*)(self + 0x260),
                    0x1000000,
                    (Color4f*)(self + 0x1cc),
                    0,
                    render_hot_text);
            }
        }
        draw_frontend_widget();
    }

    if (*(int*)(self + 0x264) != 0)
        --*(int*)(self + 0x264);
    *(float*)(self + 0x6e4) = *(float*)(g_game_base + 0x29c);
    *(float*)(self + 0x6e8) = *(float*)(g_game_base + 0x2a0);

    if ((*(unsigned int*)(self + 0x1a0) & 0x100000) != 0) {
        FrontendWidget* more = *(FrontendWidget**)(self + 0x184);
        if ((*(unsigned int*)((char*)more + 0x1a0) & 0x20) != 0) {
            *(unsigned int*)((char*)more + 0x1a0) &= ~0x20u;
            *(float*)(self + 0x17c) += 0.2f;
            if (*(float*)(self + 0x17c) >= 0.89999998f)
                *(float*)(self + 0x17c) = 1.0f;
        }

        FrontendWidget* less = *(FrontendWidget**)(self + 0x188);
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

        FrontendWidget* value = *(FrontendWidget**)(self + 0x18c);
        *(Color4f*)((char*)value + 0x1cc) = *(Color4f*)(self + 0x1cc);
        *(float*)((char*)value + 0x20c) = *(float*)(self + 0x20c);
        *(float*)((char*)value + 0x210) = *(float*)(self + 0x210);
        sprintf((char*)value + 0x2cc, "%02i%%", (int)(*(float*)(self + 0x17c) * 100.0f + 0.1f));
    }
}
