/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_registered_sound_sample_from_path @ 0x449920 */
/* selector: load_registered_sound_sample_from_path */

// Loads one sample directly from a filesystem path into the shared runtime sound-bank slot table via `BASS_SampleLoad(mem=0, ...)`, storing the resulting sample handle at the requested registered-sample index.
int32_t __thiscall load_registered_sound_sample_from_path(
        AudioBackend *backend,
        char *path,
        int32_t sample_id,
        int32_t normalization_class)
{
  int32_t result; // eax

  result = g_bass_sample_load(0, path, 0, 0, normalization_class, 131088);
  g_registered_sound_sample_handles[sample_id] = result;
  if ( !result )
    return debug_report_stub();
  return result;
}
