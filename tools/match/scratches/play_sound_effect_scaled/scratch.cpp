// play_sound_effect_scaled @ 0x44de00 (stdcall, ret 8)

void play_sound_effect_backend(int sample_id, float gain, float pitch, float pan);

void __stdcall play_sound_effect_scaled(int sample_id, float gain)
{
    play_sound_effect_backend(sample_id, gain, -1.0f, 0.0f);
}
