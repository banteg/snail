/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_sound_effect @ 0x44dde0 */
/* selector: play_sound_effect */

// Exact Windows `cRSound::Play(int)` member: forwards one effect id into the shared audio backend with the default volume, pitch, and pan parameters.
void __thiscall play_sound_effect(SoundEffectManager *manager, int32_t sound_id)
{
  play_sound_effect_backend(sound_id, 1.0, -1.0, 0.0);
}
