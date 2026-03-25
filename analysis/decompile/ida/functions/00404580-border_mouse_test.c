/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: border_mouse_test @ 0x404580 */
/* selector: border_mouse_test */

char __thiscall sub_404580(int this)
{
  int v1; // ebp
  int v2; // esi
  int v3; // edi
  int v4; // ebx
  __int64 v5; // rax
  float v7; // [esp+4h] [ebp-8h]
  float v8; // [esp+8h] [ebp-4h]

  if ( *(_BYTE *)(this + 92) )
  {
    if ( *((float *)MEMORY[0x4DF904] + 167) >= (double)*(float *)(this + 576)
      && *(float *)(this + 592) + *(float *)(this + 576) > *((float *)MEMORY[0x4DF904] + 167)
      && *((float *)MEMORY[0x4DF904] + 168) >= (double)*(float *)(this + 580)
      && *(float *)(this + 596) + *(float *)(this + 580) > *((float *)MEMORY[0x4DF904] + 168) )
    {
      v7 = (*((float *)MEMORY[0x4DF904] + 167) - *(float *)(this + 576)) / *(float *)(this + 592);
      v8 = (*((float *)MEMORY[0x4DF904] + 168) - *(float *)(this + 580)) / *(float *)(this + 596);
      v1 = get_sprite_texture_ref(*(_DWORD *)(this + 100));
      v2 = *(unsigned __int16 *)(v1 + 12);
      v3 = (__int64)((double)(unsigned __int16)v2 * v7);
      v4 = *(unsigned __int16 *)(v1 + 14);
      v5 = (__int64)((double)(unsigned __int16)v4 * v8);
      if ( v3 >= 0 )
      {
        if ( v3 > v2 - 1 )
          v3 = v2 - 1;
      }
      else
      {
        v3 = 0;
      }
      if ( (int)v5 >= 0 )
      {
        if ( (int)v5 > v4 - 1 )
          LODWORD(v5) = v4 - 1;
      }
      else
      {
        LODWORD(v5) = 0;
      }
      if ( !*(_BYTE *)(v5 * v2 + v3 + 6 + v1 + 2 * (v5 * v2 + v3 + 6)) )
        return 1;
    }
  }
  else if ( *(float *)(this + 568) - *(float *)(this + 540) < *((float *)MEMORY[0x4DF904] + 167)
         && *(float *)(this + 584) + *(float *)(this + 540) + *(float *)(this + 568) > *((float *)MEMORY[0x4DF904] + 167)
         && *(float *)(this + 572) - *(float *)(this + 540) < *((float *)MEMORY[0x4DF904] + 168)
         && *(float *)(this + 588) + *(float *)(this + 572) + *(float *)(this + 540) > *((float *)MEMORY[0x4DF904] + 168) )
  {
    return 1;
  }
  return 0;
}

