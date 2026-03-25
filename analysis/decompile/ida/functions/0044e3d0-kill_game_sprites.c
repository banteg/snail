/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: kill_game_sprites @ 0x44e3d0 */
/* selector: kill_game_sprites */

void sub_44E3D0()
{
  int *v0; // edi
  int v1; // ecx
  int v2; // esi

  v0 = unk_814C94;
  do
  {
    v1 = *v0;
    if ( *v0 )
    {
      do
      {
        v2 = *(_DWORD *)(v1 + 12);
        if ( (*(_DWORD *)(v1 + 4) & 0x800) != 0 )
          kill_sprite(v1);
        v1 = v2;
      }
      while ( v2 );
    }
    ++v0;
  }
  while ( (int)v0 < (int)&unk_814CA8 );
}

