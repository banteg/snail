// play_sound_effect_at_position @ 0x44dce0 (thiscall, ret 0x8)

#include "sound_effect_manager.h"
#include "game_root.h"


void play_sound_effect_backend(int sample_id, float gain, float pitch, float pan);

void SoundEffectManager::play_sound_effect_at_position(int sound_id, Vector3& position)
{
    float distance = 1.0e10f;
    for (int listener_index = 0; listener_index < 1; ++listener_index) {
        Vector3& listener_position =
            g_game->players[listener_index].camera.transform.position;
        Vector3 delta;
        delta.x = position.x - listener_position.x;
        delta.y = position.y - listener_position.y;
        delta.z = position.z - listener_position.z;

        Vector3 magnitude_delta = delta;
        float magnitude = magnitude_delta.vector_magnitude();
        if (magnitude < distance)
            distance = magnitude;
    }

    if (distance <= 25.0f) {
        float gain = 1.0f - distance * 0.039999999f;
        float pan = position.x * -0.25f;
        pan *= 100.0f;
        if (pan < -100.0f) {
            pan = -100.0f;
        } else if (pan > 100.0f) {
            pan = 100.0f;
        }
        play_sound_effect_backend(sound_id, gain, -1.0f, pan);
    }
}
