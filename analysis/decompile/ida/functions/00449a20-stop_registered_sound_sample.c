/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: stop_registered_sound_sample @ 0x449a20 */
/* selector: stop_registered_sound_sample */

// AudioBackend method that stops one registered runtime sample index by resolving it through the shared sound-bank table before calling BASS.
int __stdcall stop_registered_sound_sample(int a1)
{
  return g_bass_sample_stop(g_registered_sound_sample_handles[a1]);
}
