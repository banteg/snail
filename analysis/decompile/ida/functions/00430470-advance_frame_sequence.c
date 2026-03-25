/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: advance_frame_sequence @ 0x430470 */
/* selector: advance_frame_sequence */

// Advances one frame-sequence block by its fractional step, handling wrap, restart, reverse, and ping-pong flags before publishing the current frame payload pointer.
int __thiscall sub_430470(int this)
{
  int v1; // esi
  int v2; // edi
  int result; // eax
  int v4; // edx
  double v5; // st7
  unsigned __int8 v7; // c0
  unsigned __int8 v8; // c3
  int v9; // eax
  int v10; // esi

  v1 = *(_DWORD *)(this + 224);
  v2 = *(_DWORD *)(this + 92);
  result = 48 * v1;
  *(_DWORD *)(this + 236) = *(_DWORD *)(48 * v1 + v2 + 12);
  v4 = *(_DWORD *)(this + 220);
  if ( (v4 & 0x11) == 0 )
  {
    v5 = *(float *)(this + 232) + *(float *)(this + 228);
    *(float *)(this + 228) = v5;
    if ( !(v7 | v8) )
    {
      *(float *)(this + 228) = v5 - 1.0;
      if ( (v4 & 8) == 0 )
      {
        v9 = v1 + 1;
        v10 = *(_DWORD *)(this + 84);
        *(_DWORD *)(this + 224) = v9;
        if ( v9 != v10 )
          goto LABEL_15;
        if ( (v4 & 4) != 0 )
        {
          *(_DWORD *)(this + 224) = v10 - 2;
          *(_DWORD *)(this + 220) = v4 | 8;
          goto LABEL_15;
        }
        if ( (v4 & 2) != 0 )
        {
LABEL_14:
          *(_DWORD *)(this + 224) = 0;
          goto LABEL_15;
        }
LABEL_13:
        *(_DWORD *)(this + 220) = v4 | 1;
        goto LABEL_14;
      }
      *(_DWORD *)(this + 224) = v1 - 1;
      if ( !v1 )
      {
        if ( (v4 & 4) != 0 )
        {
          *(_DWORD *)(this + 224) = 1;
          *(_DWORD *)(this + 220) = v4 & 0xFFFFFFF7;
          goto LABEL_15;
        }
        if ( (v4 & 2) != 0 )
        {
          *(_DWORD *)(this + 224) = *(_DWORD *)(this + 84) - 1;
          goto LABEL_15;
        }
        goto LABEL_13;
      }
    }
LABEL_15:
    result = *(_DWORD *)(48 * *(_DWORD *)(this + 224) + v2 + 12);
    *(_DWORD *)(this + 236) = result;
  }
  return result;
}

