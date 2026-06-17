// update_tip @ 0x448c40 (fastcall, ret)

#include "border_manager.h"
#include "frontend_widget.h"
#include "tip_manager.h"

extern char* g_game_base; // data_4df904

void __fastcall update_tip(TipSlot* slot)
{
    if (*(g_game_base + 0x74621) != 0) {
        slot->widget_main->hide_border_init();
        return;
    }

    slot->widget_main->unhide_border_init();

    FrontendWidget* button = slot->widget_ok;
    unsigned int flags;
    if ((button != 0 && (flags = button->widget_flags, ((unsigned char)flags & 0x20) != 0))
        || ((button = slot->widget_disable) != 0
            && (flags = button->widget_flags, ((unsigned char)flags & 0x20) != 0))) {
        button->widget_flags = flags & ~0x20;
        *(int*)(g_game_base + 0x1b8) = slot->previous_outer_owner;
        slot->kill_tip_widgets();
        ((BorderManager*)(g_game_base + 0xb4c))->unhide_all_borders();
        slot->active = 0;
        return;
    } else if ((slot->definition->flags & 2) != 0) {
        float progress = slot->dismiss_step + slot->dismiss_progress;
        slot->dismiss_progress = progress;
        if (progress > 1.0f) {
            slot->kill_tip_widgets();
            slot->active = 0;
        }
    }
}
