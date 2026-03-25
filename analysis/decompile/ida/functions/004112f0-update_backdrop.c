/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_backdrop @ 0x4112f0 */
/* selector: update_backdrop */

// Advances the shared backdrop renderer, updates its distortion grid, and dispatches the split or warped draw path. Cross-port Android and iOS symbols match this helper to `cRBackdrop::AI()`.
void __thiscall sub_4112F0(int this)
{
  float *v2; // ebx
  float *v3; // esi
  int v4; // edi
  double v5; // st7
  float v6; // [esp+4h] [ebp-8h]
  int v7; // [esp+8h] [ebp-4h]

  if ( *(_BYTE *)(this + 76) )
  {
    change_backdrop_real(this);
    *(_BYTE *)(this + 76) = 0;
  }
  v2 = (float *)(this + 88);
  v7 = 8;
  do
  {
    v3 = v2;
    v4 = 8;
    do
    {
      v6 = v3[1] + *v3;
      *v3 = v6;
      if ( v6 > 6.2831855 )
        *v3 = v6 - 6.2831855;
      v3[4] = sine(*v3) * v3[2];
      v5 = cosine(*v3) * v3[3];
      v3 += 48;
      --v4;
      *(v3 - 43) = v5;
    }
    while ( v4 );
    v2 += 6;
    --v7;
  }
  while ( v7 );
  if ( *(_DWORD *)(this + 60) != -1 && *(_DWORD *)(this + 1624) == 1 )
  {
    if ( *(_BYTE *)(this + 56) )
      draw_split_backdrop((int *)this);
    else
      render_backdrop(this);
  }
}

