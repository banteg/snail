// play_sound_effect_at_position @ 0x44dce0 (thiscall, ret 0x8)

#include "sound_effect_manager.h"
#include "vector3.h"

struct GameAudioListenerView {
    char unknown_000[0x22c];
    Vector3 listener_position; // +0x22c, active camera/listener origin
};

extern GameAudioListenerView* g_game_base; // data_4df904

void play_sound_effect_backend(int sample_id, float gain, float pitch, float pan);

void SoundEffectManager::play_sound_effect_at_position(int sound_id, const float* position)
{
    float distance;
    GameAudioListenerView* game = g_game_base;
    *(volatile float*)&distance = 1.0e10f;
    Vector3 delta;
    delta.x = position[0] - game->listener_position.x;
    delta.y = position[1] - game->listener_position.y;
    delta.z = position[2] - game->listener_position.z;

    Vector3 magnitude_delta = delta;
    float magnitude = magnitude_delta.vector_magnitude();
    if (magnitude < distance)
        distance = magnitude;

    if (distance <= 25.0f) {
        float gain = 1.0f - distance * 0.039999999f;
        float pan = position[0] * -0.25f;
        pan *= 100.0f;
        if (pan < -100.0f) {
            pan = -100.0f;
        } else if (pan > 100.0f) {
            pan = 100.0f;
        }
        play_sound_effect_backend(sound_id, gain, -1.0f, pan);
    }
}
