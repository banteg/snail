// initialize_tip @ 0x448a40 (thiscall, ret 0x8)

#include "border_manager.h"
#include "frontend_widget.h"
#include "game_root.h"
#include "tip_manager.h"

extern GameRoot* g_game; // data_4df904
extern TipMessageDefinition g_default_tip_message; // data_4ac5c8

void TipSlot::initialize_tip(TipMessageDefinition* definition_, int hide_disable_button)
{
    active = 1;
    if (definition_ != 0)
        definition = definition_;
    else
        definition = &g_default_tip_message;

    widget_main = g_game->border_manager.allocate_border();
    int definition_flags = definition->flags;
    unsigned int alignment = (int)(char)~definition_flags;
    alignment &= 4;
    Color4f color;
    widget_main->initialize_frontend_widget(
        2,
        definition->text,
        0x14,
        definition->layout_y,
        definition->text_scale,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        alignment >> 1,
        definition->layout_y);

    TipMessageDefinition* live_definition = definition;
    int live_flags = live_definition->flags;
    if ((live_flags & 2) != 0) {
        dismiss_progress = 0.0f;
        dismiss_step = 1.0f / (live_definition->dismiss_seconds * 60.0f);
    }

    if ((live_flags & 1) != 0) {
        widget_ok = g_game->border_manager.allocate_border();
        if (hide_disable_button == 0) {
            widget_ok->initialize_frontend_widget(
                0x14,
                "OK",
                0x14,
                0.0f,
                0.0f,
                color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                2,
                definition->layout_y + 40.0f);

            widget_disable = g_game->border_manager.allocate_border();
            widget_disable->initialize_frontend_widget(
                0x14,
                "Disable",
                0x14,
                0.0f,
                0.0f,
                color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                2,
                definition->layout_y - 60.0f);
            widget_disable->stack_widget_below(widget_main);
            widget_ok->stack_widget_below(widget_main);
        } else {
            widget_ok->initialize_frontend_widget(
                0x14,
                "OK",
                0x14,
                0.0f,
                0.0f,
                color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                2,
                definition->layout_y);
            widget_disable = 0;
            widget_ok->stack_widget_below(widget_main);
        }
    } else {
        widget_ok = 0;
        widget_disable = 0;
    }

    TipMessageDefinition* final_definition = definition;
    previous_outer_owner = g_game->players[0].frontend_state;
    if ((final_definition->flags & 1) != 0)
        g_game->players[0].frontend_state = 0x16;
}
