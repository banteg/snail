/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_registered_sound_sample_from_bytes @ 0x449960 */
/* selector: load_registered_sound_sample_from_bytes */

// Loads one sample from already-read archive bytes into the shared runtime sound-bank slot table via `BASS_SampleLoad(mem=1, ...)`, storing the resulting sample handle at the requested registered-sample index.
int32_t __stdcall load_registered_sound_sample_from_bytes(char *a1, int32_t a2, int a3, int32_t a4)
{
  int32_t result; // eax

  result = g_bass_sample_load(1, a1, 0, a2, a4, 131088);
  g_registered_sound_sample_handles[a3] = result;
  if ( !result )
    return debug_report_stub();
  return result;
}
