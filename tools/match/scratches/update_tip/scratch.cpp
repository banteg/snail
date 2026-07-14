// update_tip @ 0x448c40 (thiscall, ret)

#include "border_manager.h"
#include "frontend_widget.h"
#include "game_root.h"
#include "tip_manager.h"

extern GameRoot* g_game; // data_4df904

void Tip::update_tip()
{
    if (g_game->subgame.subgame_pause_gate != 0) {
        widget_main->hide_border_init();
        return;
    }

    widget_main->unhide_border_init();

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
            kill_tip_widgets();
            g_game->border_manager.unhide_all_borders();
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
            kill_tip_widgets();
            g_game->border_manager.unhide_all_borders();
            active = 0;
            return;
        }
    }

    if ((definition->flags & 2) != 0) {
        float progress = dismiss_step + dismiss_progress;
        dismiss_progress = progress;
        if (progress > 1.0f) {
            kill_tip_widgets();
            active = 0;
        }
    }
}
