/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_registered_sound_sample_backend @ 0x449a80 */
/* selector: play_registered_sound_sample_backend */

// Forwards one registered runtime sample index plus normalized playback scalars into the raw `BASS_SamplePlayEx` lane that the SFX and voice wrappers share.
void __stdcall sub_449A80(int a1, float a2, float a3)
{
  if ( a2 >= 0.0 && (a2 > 1.0 || a2 != 0.0) )
    MEMORY[0x7527B4](unk_7537E0[a1], 0, (__int64)a3, -1, 101, 0);
}

