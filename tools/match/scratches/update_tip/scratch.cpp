// update_tip @ 0x448c40 (fastcall, ret)

#include "border_manager.h"
#include "frontend_widget.h"
#include "game_root.h"
#include "tip_manager.h"

extern GameRoot* g_game; // data_4df904

void __fastcall update_tip(TipSlot* slot)
{
    if (g_game->subgame.subgame_pause_gate != 0) {
        slot->widget_main->hide_border_init();
        return;
    }

    slot->widget_main->unhide_border_init();

    FrontendWidget* button = slot->widget_ok;
    unsigned int flags;
    if (button != 0) {
        flags = button->widget_flags;
        if (((unsigned char)flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            g_game->players[0].frontend_state = slot->previous_outer_owner;
            slot->kill_tip_widgets();
            g_game->border_manager.unhide_all_borders();
            slot->active = 0;
            return;
        }
    }

    button = slot->widget_disable;
    if (button != 0) {
        flags = button->widget_flags;
        if (((unsigned char)flags & 0x20) != 0) {
            button->widget_flags = flags & ~0x20;
            g_game->players[0].frontend_state = slot->previous_outer_owner;
            slot->kill_tip_widgets();
            g_game->border_manager.unhide_all_borders();
            slot->active = 0;
            return;
        }
    }

    if ((slot->definition->flags & 2) != 0) {
        float progress = slot->dismiss_step + slot->dismiss_progress;
        slot->dismiss_progress = progress;
        if (progress > 1.0f) {
            slot->kill_tip_widgets();
            slot->active = 0;
        }
    }
}
