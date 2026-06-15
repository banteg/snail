// register_parcel_delivery @ 0x405040 (thiscall, ret)

#include "player.h"

extern char* g_game_base; // data_4df904

struct SoundEffectManager {
    void play_sound_effect(int sound_id);
};

extern SoundEffectManager g_sound_effect_manager;

class RowEventDisplayController {
public:
    void register_parcel_delivery();

    char unknown_00[0x14];
    int state;                  // +0x14
    char unknown_18[0x4];
    int parcel_target_count;    // +0x1c
    int bonus_enabled;          // +0x20
    char unknown_24[0x4];
    int delivered_parcel_count; // +0x28
    char unknown_2c[0x1c];
    int bonus_score;            // +0x48
};

void RowEventDisplayController::register_parcel_delivery()
{
    if (delivered_parcel_count != parcel_target_count) {
        ((Player*)(g_game_base + 0x42fd7c))->add_subgoldy_score(4, 0);
        delivered_parcel_count += 1;
        g_sound_effect_manager.play_sound_effect(0x2d);
        if (delivered_parcel_count == parcel_target_count) {
            if (bonus_enabled != 0) {
                ((Player*)(g_game_base + 0x42fd7c))->add_subgoldy_score(5, bonus_score);
                g_sound_effect_manager.play_sound_effect(0x31);
            }
            state = 3;
        }
    }
}
