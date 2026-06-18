/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: register_sound_sample @ 0x432f10 */
/* selector: register_sound_sample */

// Registers one voice or sound-bank sample path into the shared 256-entry runtime sound table, loading bytes from the archive on first use and returning the assigned sample index.
int __cdecl register_sound_sample(char *ArgList, int a2)
{
  char *v2; // esi
  int v3; // eax

  v2 = ArgList;
  if ( g_archive_index_records )
  {
    load_file_bytes_from_archive_or_fs(ArgList, g_music_memory_buffer, (#83 *)&ArgList);
    load_registered_sound_sample_from_bytes((int)g_music_memory_buffer, (int)ArgList, g_registered_sound_sample_count, a2);
  }
  else
  {
    load_registered_sound_sample_from_path((int)ArgList, g_registered_sound_sample_count, a2);
  }
  rstrcpy_checked_ascii(&g_registered_sound_sample_names[128 * g_registered_sound_sample_count], v2);
  v3 = ++g_registered_sound_sample_count;
  if ( g_registered_sound_sample_count == 256 )
  {
    g_registered_sound_sample_count = 255;
    report_errorf(aRunOutOfSoundS);
    v3 = g_registered_sound_sample_count;
  }
  return v3 - 1;
}
