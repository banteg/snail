/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_registered_sound_sample_from_path @ 0x449920 */
/* selector: load_registered_sound_sample_from_path */

// Loads one sample directly from a filesystem path into the shared runtime sound-bank slot table via `BASS_SampleLoad(mem=0, ...)`, storing the resulting sample handle at the requested registered-sample index.
int __stdcall load_registered_sound_sample_from_path(int a1, int a2, int a3)
{
  int result; // eax

  result = g_bass_sample_load(0, a1, 0, 0, a3, 131088);
  g_registered_sound_sample_handles[a2] = result;
  if ( !result )
    return debug_report_stub("Bass Sample Load Fail %s\n", a1);
  return result;
}
