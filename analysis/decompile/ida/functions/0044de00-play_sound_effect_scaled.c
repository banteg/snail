/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_sound_effect_scaled @ 0x44de00 */
/* selector: play_sound_effect_scaled */

// Thin gameplay sound wrapper that forwards one effect id and explicit gain into the shared audio backend, leaving pitch and pan on their default lanes.
void __stdcall sub_44DE00(int a1, float a2)
{
  play_sound_effect_backend(a1, a2, -1.0, 0.0);
}

