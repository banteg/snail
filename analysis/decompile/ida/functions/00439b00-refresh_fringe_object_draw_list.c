/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: refresh_fringe_object_draw_list @ 0x439b00 */
/* selector: refresh_fringe_object_draw_list */

// Copies the current track skirt tint into one fringe object and, once its world-z falls behind the live fringe threshold, unlinks the object from the active list and requeues it onto the shared draw-list bucket.
void __thiscall sub_439B00(int this)
{
  _DWORD *v2; // eax
  double v3; // st7
  int v4; // eax
  char *v5; // ecx
  int v6; // eax
  int v7; // eax
  int v8; // eax
  _DWORD v9[4]; // [esp+4h] [ebp-10h] BYREF

  v2 = get_track_skirt_color((int *)MEMORY[0x4DF904] + 119174, v9);
  v3 = *(float *)(this + 24);
  *(_DWORD *)(this + 40) = *v2;
  *(_DWORD *)(this + 44) = v2[1];
  *(_DWORD *)(this + 48) = v2[2];
  *(_DWORD *)(this + 52) = v2[3];
  if ( v3 < *((float *)MEMORY[0x4DF904] + 1100223) )
  {
    v4 = *(_DWORD *)(this + 4);
    v5 = (char *)MEMORY[0x4DF904] + 1448;
    if ( (v4 & 0x200) != 0 )
    {
      if ( (v4 & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
      }
      else
      {
        v6 = *(_DWORD *)(this + 12);
        if ( v6 )
          *(_DWORD *)(v6 + 8) = *(_DWORD *)(this + 8);
        v7 = *(_DWORD *)(this + 8);
        if ( v7 )
          *(_DWORD *)(v7 + 12) = *(_DWORD *)(this + 12);
        else
          *((_DWORD *)v5 + 1) = *(_DWORD *)(this + 12);
        *(_DWORD *)(this + 12) = *((_DWORD *)v5 + 2);
        *((_DWORD *)v5 + 2) = this;
        v8 = *(_DWORD *)(this + 4);
        BYTE1(v8) &= ~2u;
        *(_DWORD *)(this + 4) = v8;
      }
    }
    else
    {
      report_errorf(aListRemove);
    }
  }
}

