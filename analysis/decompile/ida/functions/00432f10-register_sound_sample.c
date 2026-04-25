/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: register_sound_sample @ 0x432f10 */
/* selector: register_sound_sample */

// Registers one voice or sound-bank sample path into the shared 256-entry runtime sound table, loading bytes from the archive on first use and returning the assigned sample index.
int __cdecl sub_432F10(char *ArgList, int a2)
{
  char *v2; // esi
  int v3; // eax

  v2 = ArgList;
  if ( MEMORY[0x53C7F8] )
  {
    load_file_bytes_from_archive_or_fs(ArgList, MEMORY[0x53C7E8], (#83 *)&ArgList);
    load_registered_sound_sample_from_bytes((int)MEMORY[0x53C7E8], (int)ArgList, MEMORY[0x5108B0], a2);
  }
  else
  {
    load_registered_sound_sample_from_path((int)ArgList, MEMORY[0x5108B0], a2);
  }
  rstrcpy_checked_ascii(&MEMORY[0x5088B0][128 * MEMORY[0x5108B0]], v2);
  v3 = ++MEMORY[0x5108B0];
  if ( MEMORY[0x5108B0] == 256 )
  {
    MEMORY[0x5108B0] = 255;
    report_errorf(aRunOutOfSoundS);
    v3 = MEMORY[0x5108B0];
  }
  return v3 - 1;
}

