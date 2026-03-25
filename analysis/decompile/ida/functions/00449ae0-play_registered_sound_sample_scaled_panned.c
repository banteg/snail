/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_registered_sound_sample_scaled_panned @ 0x449ae0 */
/* selector: play_registered_sound_sample_scaled_panned */

// Plays one registered runtime sample through the BASS sample backend with the supplied normalized gain scale and explicit pan override.
void __stdcall sub_449AE0(int a1, float a2, float a3, float a4)
{
  if ( a2 >= 0.0 && (a2 > 1.0 || a2 != 0.0) )
    MEMORY[0x7527B4](unk_7537E0[a1], 0, (__int64)a3, -1, (__int64)a4, 0);
}

