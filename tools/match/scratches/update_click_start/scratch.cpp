// update_click_start @ 0x442290 (thiscall, ret)

#include "click_start.h"
#include "audio_system.h"
#include "game_root.h"
#include "input_state.h"

extern char* g_game_base; // data_4df904

int report_errorf(char* format, ...);
void set_math_random_seed(int seed);
void* set_input_controller_pointer_authored_xy(int slot, float authored_x, float authored_y);

void ClickStartController::update_click_start()
{
    if (((GameRoot*)g_game_base)->subgame.subgame_pause_gate != 0)
        return;

    FrontendWidget* widget = prompt;
    if (hide_prompt != 0)
        widget->hide_border_init();
    else
        widget->unhide_border_init();

    int current_state = state;
    if ((unsigned int)current_state > 4)
        return;

    switch (current_state) {
    case 0:
    case 1:
        return;
    case 2: {
        *(g_game_base + 0x4f270) = 1;
        if (*(int*)(g_game_base + 0x1066bf4) > 8)
            *(int*)(g_game_base + 0x1066bf4) = 8;

        char replay_active = *(g_game_base + 0x1066be8);
        if (replay_active != 0) {
            int replay_index = *(int*)(g_game_base + 0x1066bf4);
            char* replay_record = *(char**)(g_game_base + 0x1066bec);
            int replay_offset = replay_index * 3;
            if ((replay_record[(replay_offset << 1) + 0x74] & 0x20) == 0)
                return;
        } else {
            GameInput* input = ((GameRoot*)g_game_base)->players[0].game_input;
            if (hide_prompt != 0 || (input->input.pressed_buttons & 0x4000) == 0)
                return;
        }

        player->startup_track_index = *(int*)(g_game_base + 0x1066bf4);
        state = 3;

        if (*(g_game_base + 0x1066be8) == 0) {
            int flag_offset = *(int*)(g_game_base + 0x1066bf4) * 6;
            *(unsigned char*)(g_game_base + 0x104719c + flag_offset) |= 0x20;
            *(unsigned short*)(g_game_base + 0x104719c + flag_offset) &= 0xfffe;
            *(int*)(g_game_base + 0x104714c) = *(int*)(g_game_base + 0x1066bf4);
        }

        set_input_controller_pointer_authored_xy(0, 320.0f, 240.0f);
        set_input_controller_pointer_authored_xy(1, 320.0f, 240.0f);
        g_sound_effect_manager.play_sound_effect(8);
        break;
    }
    case 3:
        set_math_random_seed(*(int*)(g_game_base + 0x1047190));
        state = 4;
        teardown_progress = 0.0f;
        teardown_progress_step = 0.0166666675f;
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(prompt);
        // fall through
    case 4: {
        transform.position.y = teardown_progress * 16.0f + transform.position.y;
        teardown_progress = teardown_progress_step + teardown_progress;

        BodList* list = (BodList*)(g_game_base + 0x5a8);
        int flags = list_flags;
        if ((flags & 0x200) == 0) {
            report_errorf("List remove");
            state = 0;
            return;
        }
        if ((flags & 0x40) != 0) {
            report_errorf("List remove NEXTBOD");
            state = 0;
            return;
        }

        BodNode* next = list_next;
        if (next != 0)
            next->list_prev = list_prev;

        BodNode* prev = list_prev;
        if (prev != 0)
            prev->list_next = list_next;
        else
            list->first = list_next;

        list_next = list->free_top;
        list->free_top = this;

        int updated_flags = list_flags;
        state = 0;
        updated_flags &= ~0x200;
        list_flags = updated_flags;
        break;
    }
    default:
        return;
    }
}
