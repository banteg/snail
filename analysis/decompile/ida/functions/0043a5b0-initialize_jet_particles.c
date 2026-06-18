/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_jet_particles @ 0x43a5b0 */
/* selector: initialize_jet_particles */

void __thiscall initialize_jet_particles(char *gauge)
{
  char *slot_cursor; // esi
  int columns; // ebx
  _DWORD *sprite; // eax
  int flags; // edx
  _DWORD *velocity; // eax
  _DWORD *color; // eax
  _DWORD *sprite_color; // ecx
  int rows; // [esp+10h] [ebp-14h]
  int color_temp[4]; // [esp+14h] [ebp-10h] BYREF

  slot_cursor = gauge + 32;
  rows = 15;
  do
  {
    columns = 2;
    do
    {
      sprite = allocate_sprite(unk_790F30, 1, 158, -1, -1);
      *(_DWORD *)slot_cursor = sprite;
      flags = sprite[1];
      BYTE1(flags) |= 8u;
      sprite[1] = flags;
      *(_DWORD *)(*(_DWORD *)slot_cursor + 104) = 0;
      *(_DWORD *)(*(_DWORD *)slot_cursor + 108) = 0;
      *(_DWORD *)(*(_DWORD *)slot_cursor + 112) = 0;
      *(_DWORD *)(*(_DWORD *)slot_cursor + 116) = 0;
      *(_DWORD *)(*(_DWORD *)slot_cursor + 100) = 0;
      *(_DWORD *)(*(_DWORD *)slot_cursor + 96) = 0;
      velocity = (_DWORD *)(*(_DWORD *)slot_cursor + 84);
      velocity[2] = 0;
      velocity[1] = 0;
      *velocity = 0;
      *(_DWORD *)(*(_DWORD *)slot_cursor + 120) = 0;
      color = set_color_rgba(color_temp, 1065353216, 1065353216, 1065353216, 1065336439);
      sprite_color = (_DWORD *)(*(_DWORD *)slot_cursor + 44);
      slot_cursor += 16;
      --columns;
      *sprite_color = *color;
      sprite_color[1] = color[1];
      sprite_color[2] = color[2];
      sprite_color[3] = color[3];
      *((_DWORD *)slot_cursor - 3) = 0;
      *(_DWORD *)(*((_DWORD *)slot_cursor - 4) + 40) = 0;
      *((_DWORD *)slot_cursor - 2) = 0;
      *((_DWORD *)slot_cursor - 1) = 1042983595;
    }
    while ( columns );
    --rows;
  }
  while ( rows );
}
