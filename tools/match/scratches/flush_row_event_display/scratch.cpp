// flush_row_event_display @ 0x404830 (thiscall, ret)

#include "completion.h"
#include "game_root.h"

extern GameRoot* g_game; // data_4df904

void Completion::flush_row_event_display()
{
    if (state != COMPLETION_STATE_INACTIVE) {
        if (delivered_parcel_count != parcel_target_count) {
            while (delivered_parcel_count < parcel_target_count) {
                g_game->subgame.player.add_subgoldy_score(SUBGOLDY_SCORE_PARCEL_DELIVER, 0);
                delivered_parcel_count += 1;
            }

            if (bonus_enabled != 0) {
                g_game->subgame.player.add_subgoldy_score(bonus_score, 0);
            }
        }

        delivered_parcel_count += 1;

        g_game->border_manager.kill_border(title_widget);
        g_game->border_manager.kill_border(delivered_count_widget);
        g_game->border_manager.kill_border(bonus_icon_widget);
        g_game->border_manager.kill_border(bonus_summary_widget);
        g_game->border_manager.kill_border(continue_widget);

        if (g_game->subgame.player.total_score != display_token)
            g_game->subgame.player.total_score = display_token;

    }
    state = COMPLETION_STATE_INACTIVE;
}
