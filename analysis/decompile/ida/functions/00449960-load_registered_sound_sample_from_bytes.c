/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_registered_sound_sample_from_bytes @ 0x449960 */
/* selector: load_registered_sound_sample_from_bytes */

// Loads one sample from already-read archive bytes into the shared runtime sound-bank slot table via `BASS_SampleLoad(mem=1, ...)`, storing the resulting sample handle at the requested registered-sample index.
int __stdcall load_registered_sound_sample_from_bytes(int a1, int a2, int a3, int a4)
{
  int result; // eax

  result = g_bass_sample_load(1, a1, 0, a2, a4, 131088);
  g_registered_sound_sample_handles[a3] = result;
  if ( !result )
    return debug_report_stub("***ERROR:Bass Sample Load Memory Fail\n");
  return result;
}
