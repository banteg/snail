/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_registered_sound_sample_default @ 0x449a60 */
/* selector: play_registered_sound_sample_default */

// Plays one registered runtime sample index through the default `BASS_SamplePlayEx` wrapper with the hard-coded playback parameters used by the warning-owned sample path.
int __stdcall sub_449A60(int a1)
{
  return MEMORY[0x7527B4](unk_7537E0[a1], 0, -1, -1, 101, 1);
}

