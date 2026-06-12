// play_sound_effect @ 0x44dde0 (stdcall, ret 4)

void play_sound_effect_backend(int sample_id, float gain, float pitch, float pan);

void __stdcall play_sound_effect(int sample_id)
{
    play_sound_effect_backend(sample_id, 1.0f, -1.0f, 0.0f);
}
