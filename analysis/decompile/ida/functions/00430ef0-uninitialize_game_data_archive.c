/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: uninitialize_game_data_archive @ 0x430ef0 */
/* selector: uninitialize_game_data_archive */

// Frees the tracked archive payload buffer, closes the loaded SnailMail.dat stream when present, and clears the global archive-index pointer.
int __cdecl uninitialize_game_data_archive()
{
  int result; // eax

  free_tracked_memory(g_archive_data_base);
  result = (int)g_archive_index_records;
  if ( g_archive_index_records )
    result = fclose(g_archive_file);
  g_archive_index_records = nullptr;
  return result;
}
