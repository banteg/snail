/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: classify_archive_entry_extension @ 0x4050c0 */
/* selector: classify_archive_entry_extension */

// Copies one archive entry's filename suffix into the caller buffer and returns the rebuild classifier id: `1` for `TGA`, `2` for `WAV`, `3` for `MP3`, otherwise `0`.
int __cdecl sub_4050C0(char *a1, _BYTE *a2)
{
  char *v2; // eax
  char i; // cl
  char v5; // cl
  _BYTE *v6; // eax

  v2 = a1;
  for ( i = *a1; *v2; i = *v2 )
  {
    if ( i == 46 )
      break;
    ++v2;
    *a2++ = i;
  }
  *a2 = 0;
  if ( !*v2 )
    return 0;
  v5 = v2[1];
  v6 = v2 + 1;
  if ( v5 == 84 && v6[1] == 71 && v6[2] == 65 )
    return 1;
  if ( v5 == 87 && v6[1] == 65 && v6[2] == 86 )
    return 2;
  if ( v5 == 77 && v6[1] == 80 && v6[2] == 51 )
    return 3;
  else
    return 0;
}

