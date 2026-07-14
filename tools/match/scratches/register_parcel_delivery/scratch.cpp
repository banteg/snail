// register_parcel_delivery @ 0x405040 (thiscall, ret)

#include "audio_system.h"
#include "completion.h"
#include "game_root.h"
#include "player.h"

extern GameRoot* g_game; // data_4df904

void Completion::register_parcel_delivery()
{
    if (delivered_parcel_count != parcel_target_count) {
        g_game->subgame.player.add_subgoldy_score(SUBGOLDY_SCORE_PARCEL_DELIVER, 0);
        delivered_parcel_count += 1;
        g_sound_effect_manager.play_sound_effect(0x2d);
        if (delivered_parcel_count == parcel_target_count) {
            if (bonus_enabled != 0) {
                g_game->subgame.player.add_subgoldy_score(SUBGOLDY_SCORE_BONUS, bonus_score);
                g_sound_effect_manager.play_sound_effect(0x31);
            }
            state = COMPLETION_STATE_SUMMARY_PENDING;
        }
    }
}
