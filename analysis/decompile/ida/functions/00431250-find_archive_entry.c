/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: find_archive_entry @ 0x431250 */
/* selector: find_archive_entry */

int __cdecl sub_431250(char *a1)
{
  int v1; // eax
  int v2; // ebx
  char **i; // edi
  char *v4; // edx
  char *v5; // esi
  char v6; // cl
  char v7; // al

  if ( !MEMORY[0x53C7F8] )
    return 0;
  v1 = *(_DWORD *)MEMORY[0x53C7F8];
  v2 = 0;
  if ( *(int *)MEMORY[0x53C7F8] <= 0 )
    return 0;
  for ( i = (char **)(MEMORY[0x53C7F8] + 4); ; i += 3 )
  {
    v4 = *i;
    v5 = a1;
    v6 = **i;
    if ( v6 )
    {
      do
      {
        v7 = *v5;
        if ( !*v5 )
          break;
        if ( v7 >= 97 && v7 <= 122 )
          v7 -= 32;
        if ( v6 != v7 )
          break;
        v6 = v4[1];
        ++v5;
        ++v4;
      }
      while ( v6 );
      v1 = *(_DWORD *)MEMORY[0x53C7F8];
    }
    if ( !*v4 && !*v5 )
      break;
    if ( ++v2 >= v1 )
      return 0;
  }
  return MEMORY[0x53C7F8] + 12 * v2 + 4;
}

