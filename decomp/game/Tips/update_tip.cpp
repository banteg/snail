// update_tip / cRTip::AI @ 0x448c40 (thiscall, ret)

#include "border_manager.h"
#include "frontend_widget.h"
#include "game_root.h"
#include "tip_manager.h"


void cRTip::AI()
{
    if (g_game->subgame.subgame_pause_gate != 0) {
        widget_main->HideInit();
        return;
    }

    widget_main->UnHideInit();

    FrontendWidget* button = widget_ok;
    unsigned int flags;
    if (button != 0) {
        flags = button->widget_flags;
        if (((unsigned char)flags
                & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED)
            != 0) {
            button->widget_flags =
                flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
            g_game->players[0].frontend_state = previous_outer_owner;
            UnInit();
            g_game->border_manager.UnHideBorders();
            active = 0;
            return;
        }
    }

    button = widget_disable;
    if (button != 0) {
        flags = button->widget_flags;
        if (((unsigned char)flags
                & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED)
            != 0) {
            button->widget_flags =
                flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
            g_game->players[0].frontend_state = previous_outer_owner;
            UnInit();
            g_game->border_manager.UnHideBorders();
            active = 0;
            return;
        }
    }

    if ((definition->flags & 2) != 0) {
        float progress = dismiss_step + dismiss_progress;
        dismiss_progress = progress;
        if (progress > 1.0f) {
            UnInit();
            active = 0;
        }
    }
}
