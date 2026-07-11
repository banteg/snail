// flush_row_event_display @ 0x404830 (thiscall, ret)

#include "border_manager.h"
#include "completion.h"
#include "player.h"

extern char* g_game_base; // data_4df904

void Completion::flush_row_event_display()
{
    if (state != 0) {
        if (delivered_parcel_count != parcel_target_count) {
            while (delivered_parcel_count < parcel_target_count) {
                ((Player*)(g_game_base + 0x42fd7c))->add_subgoldy_score(SUBGOLDY_SCORE_PARCEL_DELIVER, 0);
                delivered_parcel_count += 1;
            }

            if (bonus_enabled != 0) {
                ((Player*)(g_game_base + 0x42fd7c))->add_subgoldy_score(bonus_score, 0);
            }
        }

        delivered_parcel_count += 1;

        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(widget_a);
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(delivered_count_widget);
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(widget_d);
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(bonus_widget);
        ((BorderManager*)(g_game_base + 0xb4c))->kill_border(continue_widget);

        if (*(int*)(g_game_base + 0x430060) != display_token)
            *(int*)(g_game_base + 0x430060) = display_token;

    }
    state = 0;
}
