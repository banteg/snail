/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: uninitialize_game_data_archive @ 0x430ef0 */
/* selector: uninitialize_game_data_archive */

// Frees the tracked archive payload buffer, closes the loaded SnailMail.dat stream when present, and clears the global archive-index pointer.
int sub_430EF0()
{
  int result; // eax

  free_tracked_memory(MEMORY[0x53C7EC]);
  result = MEMORY[0x53C7F8];
  if ( MEMORY[0x53C7F8] )
    result = fclose(MEMORY[0x53C7F0]);
  MEMORY[0x53C7F8] = 0;
  return result;
}

