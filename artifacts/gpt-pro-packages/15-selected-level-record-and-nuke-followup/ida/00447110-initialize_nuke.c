/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_nuke @ 0x447110 */
/* selector: initialize_nuke */

// Spawns the 25-sprite ring effect used by ring/special-effect collision kinds `2` and `6`, seeds its orbit height and phase step from the owning player and global tick delta, and immediately dispatches the first update. Cross-port Android symbols match this helper to `cRNuke::Init()`.
int __thiscall sub_447110(int this)
{
  _DWORD *v2; // esi
  int v3; // ebp
  double v4; // st7
  _DWORD *v5; // eax
  int v6; // edx
  _DWORD *v7; // eax
  _DWORD *v8; // eax

  if ( !*(_DWORD *)this )
  {
    v2 = (_DWORD *)(this + 24);
    v3 = 25;
    *(float *)(this + 12) = *(float *)(*(_DWORD *)(this + 4) + 112) - 5.0;
    v4 = *((float *)MEMORY[0x4DF904] + 119188) + *((float *)MEMORY[0x4DF904] + 119188);
    *(_DWORD *)(this + 16) = 0;
    *(_DWORD *)(this + 20) = 1037465424;
    *(_DWORD *)this = 1;
    *(float *)(this + 8) = v4;
    do
    {
      v5 = allocate_sprite(unk_790F30, *(_DWORD *)(*(_DWORD *)(this + 4) + 896), 131, -1, -1);
      *v2 = v5;
      v6 = v5[1];
      BYTE1(v6) |= 8u;
      ++v2;
      v5[1] = v6;
      *(_DWORD *)(*(v2 - 1) + 104) = 0;
      *(_DWORD *)(*(v2 - 1) + 108) = 0;
      *(_DWORD *)(*(v2 - 1) + 96) = 1077936128;
      *(_DWORD *)(*(v2 - 1) + 100) = 1077936128;
      v7 = (_DWORD *)(*(v2 - 1) + 84);
      v7[2] = 0;
      v7[1] = 0;
      *v7 = 0;
      v8 = (_DWORD *)(*(v2 - 1) + 72);
      --v3;
      v8[2] = 0;
      v8[1] = 0;
      *v8 = 0;
      *(_DWORD *)(*(v2 - 1) + 120) = 0;
    }
    while ( v3 );
  }
  return update_nuke((float *)this);
}

