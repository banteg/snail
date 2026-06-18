/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_track_parcel @ 0x443730 */
/* selector: spawn_track_parcel */

// Allocates one live gameplay parcel slot from `game->track_parcels`, seeds its world position, sprite, and parcel-owner pointer, and returns the activated runtime slot.
char *__thiscall sub_443730(int *this, float *a2, int a3)
{
  char *v4; // eax
  char *v5; // esi
  _DWORD *v6; // edi
  _DWORD *v7; // eax
  int v8; // ecx
  _DWORD *v9; // eax
  _DWORD *v10; // ecx
  _DWORD *v11; // eax
  _DWORD v13[4]; // [esp+8h] [ebp-10h] BYREF

  v4 = allocate_track_parcel_slot(this + 4815136);
  v5 = v4;
  if ( !v4 )
    return nullptr;
  v6 = v4 + 16;
  *((_DWORD *)v4 + 14) = 1;
  *((float *)v4 + 4) = *a2;
  *((float *)v4 + 5) = a2[1];
  *((float *)v4 + 6) = a2[2];
  *((_DWORD *)v4 + 25) = this + 978393;
  v7 = allocate_sprite(g_sprite_manager, *(this + 978617), 121, -1, -1);
  *((_DWORD *)v5 + 21) = v7;
  v8 = v7[1];
  BYTE1(v8) |= 8u;
  v7[1] = v8;
  *(_DWORD *)(*((_DWORD *)v5 + 21) + 104) = 0;
  *(_DWORD *)(*((_DWORD *)v5 + 21) + 108) = 0;
  *(_DWORD *)(*((_DWORD *)v5 + 21) + 120) = 0;
  v9 = set_color_rgba(v13, 1065353216, 1065353216, 1065353216, 1065353216);
  v10 = (_DWORD *)(*((_DWORD *)v5 + 21) + 44);
  *v10 = *v9;
  v10[1] = v9[1];
  v10[2] = v9[2];
  v10[3] = v9[3];
  *(_DWORD *)(*((_DWORD *)v5 + 21) + 96) = 1065353216;
  *(_DWORD *)(*((_DWORD *)v5 + 21) + 100) = 1065353216;
  v11 = (_DWORD *)(*((_DWORD *)v5 + 21) + 72);
  *v11 = *v6;
  v11[1] = *((_DWORD *)v5 + 5);
  v11[2] = *((_DWORD *)v5 + 6);
  if ( ((__int64)a2[2] & 1) != 0 )
    *((_DWORD *)v5 + 23) = 0;
  else
    *((_DWORD *)v5 + 23) = 1056964608;
  *((_DWORD *)v5 + 24) = 1012010273;
  return v5;
}

