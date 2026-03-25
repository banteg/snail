/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_sound_effect @ 0x44dde0 */
/* selector: play_sound_effect */

// Thin gameplay sound wrapper that forwards one effect id into the shared audio backend with the default volume, pitch, and pan parameters.
void __stdcall sub_44DDE0(int a1)
{
  play_sound_effect_backend(a1, 1.0, -1.0, 0.0);
}

