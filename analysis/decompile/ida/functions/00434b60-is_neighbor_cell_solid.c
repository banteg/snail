/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_neighbor_cell_solid @ 0x434b60 */
/* selector: is_neighbor_cell_solid */

bool __thiscall sub_434B60(_DWORD *this, _DWORD *a2, int a3, int a4)
{
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  int v8; // eax
  int v9; // ecx
  _DWORD *v10; // eax
  int v11; // esi
  bool result; // al

  v5 = get_track_cell_row_index(a2);
  v6 = a2[16] & 7;
  result = false;
  if ( (unsigned int)(v6 + a3) < 8 )
  {
    v7 = a4 + v5;
    if ( v7 >= 0 && v7 < *(this + 21) )
    {
      v8 = 21 * (a3 + v6 + 8 * v7);
      v9 = *((unsigned __int8 *)this + 4 * v8 + 3930884);
      v10 = this + v8;
      v11 = v9;
      if ( !is_sub_loc_empty((_BYTE *)v10 + 3930824) && v11 && v11 != 35 && v11 != 28 && v11 != 22 )
        return true;
    }
  }
  return result;
}

