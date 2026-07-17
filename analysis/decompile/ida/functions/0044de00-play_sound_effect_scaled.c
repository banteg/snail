/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_sound_effect_scaled @ 0x44de00 */
/* selector: play_sound_effect_scaled */

// Exact Windows `cRSound::PlayVolume(int, float)` member: forwards one effect id and explicit gain into the shared audio backend, leaving pitch and pan on their default lanes.
void __thiscall play_sound_effect_scaled(SoundEffectManager *manager, int32_t sound_id, float gain)
{
  play_sound_effect_backend(sound_id, gain, -1.0, 0.0);
}
