// initialize_tip / cRTip::Init @ 0x448a40 (thiscall, ret 0x8)

#include "border_manager.h"
#include "frontend_widget.h"
#include "game_root.h"
#include "tip_manager.h"

extern cRTipData g_default_tip_message; // data_4ac5c8 / iOS gTips

void cRTip::Init(cRTipData* definition_, int hide_disable_button)
{
    active = 1;
    if (definition_ != 0)
        definition = definition_;
    else
        definition = &g_default_tip_message;

    FrontendWidget*& main_widget = widget_main;
    main_widget = g_game->border_manager.GetBorder();
    int definition_flags = definition->flags;
    unsigned int alignment = (char)~definition_flags;
    tColour color;
    main_widget->Init(
        FRONTEND_WIDGET_FLAG_HIGHLIGHTED,
        definition->text,
        0x14,
        definition->anchor_x,
        definition->layout_y,
        color.Set(1.0f, 1.0f, 1.0f, 1.0f),
        (alignment & 4) >> 1,
        definition->anchor_x);

    cRTipData* live_definition = definition;
    if ((live_definition->flags & 2) != 0) {
        dismiss_progress = 0.0f;
        dismiss_step = 1.0f / (live_definition->dismiss_seconds * 60.0f);
    }

    if ((live_definition->flags & 1) != 0) {
        widget_ok = g_game->border_manager.GetBorder();
        if (hide_disable_button == 0) {
            widget_ok->Init(
                FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
                    | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
                "OK",
                0x14,
                0.0f,
                0.0f,
                color.Set(1.0f, 1.0f, 1.0f, 1.0f),
                2,
                definition->anchor_x + 40.0f);

            widget_disable = g_game->border_manager.GetBorder();
            widget_disable->Init(
                FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
                    | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
                "Disable",
                0x14,
                0.0f,
                0.0f,
                color.Set(1.0f, 1.0f, 1.0f, 1.0f),
                2,
                definition->anchor_x - 60.0f);
            widget_disable->SetBelow(widget_main);
            widget_ok->SetBelow(widget_main);
        } else {
            widget_ok->Init(
                FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
                    | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
                "OK",
                0x14,
                0.0f,
                0.0f,
                color.Set(1.0f, 1.0f, 1.0f, 1.0f),
                2,
                definition->anchor_x);
            widget_disable = 0;
            widget_ok->SetBelow(widget_main);
        }
    } else {
        widget_ok = 0;
        widget_disable = 0;
    }

    cRTipData* final_definition = definition;
    previous_outer_owner = g_game->players[0].frontend_state;
    if ((final_definition->flags & 1) != 0)
        g_game->players[0].frontend_state = 0x16;
}
