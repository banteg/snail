// play_movement_state_sound @ 0x43afd0 (thiscall, ret)

#include "audio_system.h"
#include "player.h"

extern char* g_game_base; // data_4df904

int next_math_random_value();
double __fastcall normalize_vector(Vector3* vector);

void Player::play_movement_state_sound()
{
    unsigned int flags = movement_flags;
    int sound_id;

    if ((flags & 7) != 0) {
        int variant = (int)((float)next_math_random_value() * 0.000061035156f);
        movement_sound_variant_sample = variant;
        sound_id = variant + 17;
    } else if ((flags & 0x18) != 0) {
        int variant = (int)((float)next_math_random_value() * 0.000091552734f);
        movement_sound_variant_sample = variant;
        sound_id = variant + 19;
    } else {
        if ((flags & 0x60) == 0)
            return;
        int variant = (int)((float)next_math_random_value() * 0.000091552734f);
        movement_sound_variant_sample = variant;
        sound_id = variant + 22;
    }

    if (sound_id != -1) {
        if (attachment_exit_pending) {
            Vector3 vector;
            Vector3 normalized_vector;

            vector.x = *(float*)(g_game_base + 0x18c) - position.x;
            vector.y = *(float*)(g_game_base + 0x190) - position.y;
            vector.z = *(float*)(g_game_base + 0x194) - position.z;

            normalized_vector = vector;
            float distance = (float)normalize_vector(&normalized_vector);
            float volume = 1.0f - distance * 0.016666668f;
            if (volume < 0.0f) {
                volume = 0.0f;
            } else if (volume > 1.0f) {
                volume = 1.0f;
            }
            g_sound_effect_manager.play_sound_effect_scaled(sound_id, volume);
        } else {
            g_sound_effect_manager.play_sound_effect(sound_id);
        }
    }
}
