/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_level_definitions @ 0x448900 */
/* selector: load_level_definitions */

// Implements the void `cRSMTracks::OpenLevels()` member by enumerating LEVELS/*.TXT and parsing each name into the root-owned SubTracks scratch definition.
void __thiscall load_level_definitions(SMTracks *tracks)
{
  int v1; // esi
  char *v2; // edi
  int out_count; // [esp+4h] [ebp-4004h] BYREF
  EnumeratedEntryName filename[128]; // [esp+8h] [ebp-4000h] BYREF

  enumerate_matching_archive_or_fs_entries(aLevels, (char *)aTxt, &out_count, filename);
  v1 = 0;
  if ( out_count > 0 )
  {
    v2 = filename[0];
    do
    {
      load_level_definition_file(&g_game_base->subgame.level_definition_scratch, v2);
      ++v1;
      v2 += 128;
    }
    while ( v1 < out_count );
  }
}
