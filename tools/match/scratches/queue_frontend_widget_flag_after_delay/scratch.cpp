// queue_frontend_widget_flag_after_delay @ 0x403f60 (thiscall, ret 0x8)

#include "frontend_widget.h"

extern char* g_game_base; // data_4df904

class FrontendFade {
public:
    int begin_frontend_fade_out(int hold_state);

    int state; // +0x00
    int alpha_bits; // +0x04
    int field_08; // +0x08
    int field_0c; // +0x0c
    int hold_state; // +0x10
};

class BorderDelayLane {
public:
    char queue_frontend_widget_flag_after_delay(FrontendWidget* widget, int queued_flags);

    char unknown_00000[0x4359c];
    int delayed_widget_flags; // +0x4359c
    char delayed_widget_active; // +0x435a0
    char unknown_435a1[0x435a4 - 0x435a1];
    float delayed_widget_progress; // +0x435a4
    float delayed_widget_progress_step; // +0x435a8
    FrontendWidget* delayed_widget; // +0x435ac
};

char BorderDelayLane::queue_frontend_widget_flag_after_delay(
    FrontendWidget* widget, int queued_flags)
{
    char result = delayed_widget_active;
    if (result == 0) {
        if ((widget->widget_flags & 0x40000000) != 0)
            result = ((FrontendFade*)(g_game_base + 0x24))->begin_frontend_fade_out(0);
        delayed_widget = widget;
        delayed_widget_active = 1;
        delayed_widget_progress = 0.0f;
        delayed_widget_progress_step = 0.0833333358f;
        delayed_widget_flags = queued_flags;
    }
    return result;
}
