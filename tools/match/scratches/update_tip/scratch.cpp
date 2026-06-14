// update_tip @ 0x448c40 (fastcall, ret)

extern char* g_game_base; // data_4df904

struct FrontendWidget {
    char unknown_00[0x1a0];
    unsigned int widget_flags; // +0x1a0

    void hide_border_init();
    void unhide_border_init();
};

struct BorderManager {
    void unhide_all_borders();
};

struct TipMessageDefinition {
    unsigned int flags;        // +0x00
    float layout_y;            // +0x04
    float text_scale;          // +0x08
    float dismiss_seconds;     // +0x0c
    char* text;                // +0x10
};

class TipSlot {
public:
    void kill_tip_widgets();

    int active;                         // +0x00
    int previous_outer_owner;           // +0x04
    TipMessageDefinition* definition;   // +0x08
    FrontendWidget* widget_main;        // +0x0c
    FrontendWidget* widget_ok;          // +0x10
    FrontendWidget* widget_disable;     // +0x14
    float dismiss_progress;             // +0x18
    float dismiss_step;                 // +0x1c
};

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
