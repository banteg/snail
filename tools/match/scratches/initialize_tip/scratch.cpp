// initialize_tip @ 0x448a40 (thiscall, ret 0x8)

#include "frontend_widget.h"
#include "tip_manager.h"

extern char* g_game_base; // data_4df904
extern TipMessageDefinition g_default_tip_message; // data_4ac5c8

struct BorderManager {
    FrontendWidget* allocate_border();
};

void TipSlot::initialize_tip(TipMessageDefinition* definition_, int show_disable_button)
{
    active = 1;
    if (definition_ != 0)
        definition = definition_;
    else
        definition = &g_default_tip_message;

    widget_main = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
    TipMessageDefinition* current_definition = definition;
    float layout_y = current_definition->layout_y;
    int alignment = ((int)(char)~(current_definition->flags & 0xff) & 4) >> 1;
    Color4f color;
    widget_main->initialize_frontend_widget(
        2,
        current_definition->text,
        0x14,
        current_definition->layout_y,
        current_definition->text_scale,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        alignment,
        layout_y);

    TipMessageDefinition* live_definition = definition;
    if ((live_definition->flags & 2) != 0) {
        dismiss_progress = 0.0f;
        dismiss_step = 1.0f / (live_definition->dismiss_seconds * 60.0f);
    }

    if ((live_definition->flags & 1) != 0) {
        widget_ok = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        if (show_disable_button != 0) {
            TipMessageDefinition* buttons_definition = definition;
            float ok_y = buttons_definition->layout_y + 40.0f;
            widget_ok->initialize_frontend_widget(
                0x14,
                "OK",
                0x14,
                0.0f,
                0.0f,
                color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                2,
                ok_y);

            widget_disable = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
            float disable_y = definition->layout_y - 60.0f;
            widget_disable->initialize_frontend_widget(
                0x14,
                "Disable",
                0x14,
                0.0f,
                0.0f,
                color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                2,
                disable_y);
            widget_disable->stack_widget_below(widget_main);
            widget_ok->stack_widget_below(widget_main);
        } else {
            float ok_y = definition->layout_y;
            widget_ok->initialize_frontend_widget(
                0x14,
                "OK",
                0x14,
                0.0f,
                0.0f,
                color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                2,
                ok_y);
            widget_disable = 0;
            widget_ok->stack_widget_below(widget_main);
        }
    } else {
        widget_ok = 0;
        widget_disable = 0;
    }

    TipMessageDefinition* final_definition = definition;
    previous_outer_owner = *(int*)(g_game_base + 0x1b8);
    if ((final_definition->flags & 1) != 0)
        *(int*)(g_game_base + 0x1b8) = 0x16;
}
