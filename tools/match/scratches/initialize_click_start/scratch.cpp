// initialize_click_start @ 0x442170 (thiscall, ret 0x4)

#include "player.h"
#include "game_root.h"

extern GameRoot* g_game; // data_4df904

int report_errorf(char* format, ...);

void ClickStart::initialize_click_start(Player* new_player)
{
    prompt = g_game->border_manager.allocate_border();
    tColour color;
    prompt->initialize_frontend_widget(0x400002, "Click to Start", 0x14, 0.0f,
        200.0f, color.set_color_rgba(1.0f, 1.0f, 1.0f, 0.0299999993f), 2, 0.0f);
    prompt->hide_border_init();

    int flags = list_flags;
    hide_prompt = 1;
    owner_player = new_player;
    if ((flags & 0x200) != 0) {
        report_errorf("List ADD");
    } else {
        BodNode** first_ref = &g_game->active_bod_list.first;
        BodNode* old_first = *first_ref;
        if (old_first == 0) {
            *first_ref = this;
            list_prev = 0;
            (*first_ref)->list_next = 0;
        } else {
            old_first->list_prev = this;
            BodNode* current = *first_ref;
            BodNode* inserted = current->list_prev;
            inserted->list_next = current;
            current = *first_ref;
            *first_ref = current->list_prev;
            (*first_ref)->list_prev = 0;
        }
        list_flags |= 0x200;
    }

    state = CLICK_START_STATE_WAITING_FOR_START;
    owner_player->startup_track_index = 0;
    render_arg_1c = 0;
    render_arg_20 = 0.0f;

    if (g_game->subgame.replay_launch_active != 0)
        prompt->hide_border_init();
    else
        prompt->unhide_border_init();
}
