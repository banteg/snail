/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_level_definitions @ 0x448900 */
/* selector: load_level_definitions */

// Composes level descriptors and segment sequences from LEVELS/*.TXT.
int load_level_definitions()
{
  int result; // eax
  int v1; // esi
  int *v2; // edi
  int v3; // [esp+4h] [ebp-4004h] BYREF
  int v4[4096]; // [esp+8h] [ebp-4000h] BYREF

  enumerate_matching_archive_or_fs_entries(aLevels, aTxt, &v3, v4);
  result = v3;
  v1 = 0;
  if ( v3 > 0 )
  {
    v2 = v4;
    do
    {
      load_level_definition_file((char *)MEMORY[0x4DF904] + 2246660, (char *)v2);
      result = v3;
      ++v1;
      v2 += 32;
    }
    while ( v1 < v3 );
  }
  return result;
}

