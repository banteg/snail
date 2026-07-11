/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_level_definitions @ 0x448900 */
/* selector: load_level_definitions */

// Implements `cRSMTracks::OpenLevels()` by enumerating LEVELS/*.TXT and parsing each name into the root-owned SubTracks scratch definition. Cross-port evidence proves the authored member is void; this pre-sync decompile still presents incidental EAX residue as an int32_t result.
int32_t __thiscall load_level_definitions(SMTracks *catalog)
{
  int32_t result; // eax
  int v2; // esi
  char *v3; // edi
  int v4; // [esp+4h] [ebp-4004h] BYREF
  _BYTE v5[16384]; // [esp+8h] [ebp-4000h] BYREF

  enumerate_matching_archive_or_fs_entries(aLevels, (int)aTxt, (float *)&v4, (int)v5);
  result = v4;
  v2 = 0;
  if ( v4 > 0 )
  {
    v3 = v5;
    do
    {
      load_level_definition_file((SubTracks *)((char *)g_game_base + 2246660), v3);
      result = v4;
      ++v2;
      v3 += 128;
    }
    while ( v2 < v4 );
  }
  return result;
}
