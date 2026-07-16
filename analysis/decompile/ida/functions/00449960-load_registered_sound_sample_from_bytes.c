/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_registered_sound_sample_from_bytes @ 0x449960 */
/* selector: load_registered_sound_sample_from_bytes */

// Loads one sample from already-read archive bytes into the shared runtime sound-bank slot table via `BASS_SampleLoad(mem=1, ...)`, storing the resulting sample handle at the requested registered-sample index.
void __thiscall load_registered_sound_sample_from_bytes(
        AudioBackend *backend,
        char *bytes,
        int32_t byte_count,
        int32_t sample_id,
        int32_t normalization_class)
{
  int32_t v5; // eax

  v5 = g_bass_sample_load(1, bytes, 0, byte_count, normalization_class, 131088);
  g_registered_sound_sample_handles[sample_id] = v5;
  if ( !v5 )
    debug_report_stub();
}
