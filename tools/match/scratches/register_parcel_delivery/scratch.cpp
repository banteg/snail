// register_parcel_delivery @ 0x405040 (thiscall, ret)

#include "audio_system.h"
#include "completion.h"
#include "player.h"

extern char* g_game_base; // data_4df904

void Completion::register_parcel_delivery()
{
    if (delivered_parcel_count != parcel_target_count) {
        ((Player*)(g_game_base + 0x42fd7c))->add_subgoldy_score(SUBGOLDY_SCORE_PARCEL_DELIVER, 0);
        delivered_parcel_count += 1;
        g_sound_effect_manager.play_sound_effect(0x2d);
        if (delivered_parcel_count == parcel_target_count) {
            if (bonus_enabled != 0) {
                ((Player*)(g_game_base + 0x42fd7c))->add_subgoldy_score(SUBGOLDY_SCORE_BONUS, bonus_score);
                g_sound_effect_manager.play_sound_effect(0x31);
            }
            state = 3;
        }
    }
}
