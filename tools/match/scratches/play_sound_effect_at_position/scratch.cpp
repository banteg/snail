// play_sound_effect_at_position @ 0x44dce0 (stdcall, ret 0x8)

extern char* g_game_base; // data_4df904

struct Vector3 {
    float x;
    float y;
    float z;

    float vector_magnitude(); // @ 0x44ccf0, thiscall, returns st0
};

void play_sound_effect_backend(int sample_id, float gain, float pitch, float pan);

void __stdcall play_sound_effect_at_position(int sound_id, const float* position)
{
    float distance = 1.0e10f;
    float* game = (float*)g_game_base;
    Vector3 delta;
    delta.x = position[0] - game[139];
    delta.y = position[1] - game[140];
    delta.z = position[2] - game[141];

    float magnitude = delta.vector_magnitude();
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
