/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: allocate_sprite @ 0x44e2a0 */
/* selector: allocate_sprite */

void *__thiscall sub_44E2A0(_DWORD *this, int a2, int a3, int a4, int a5)
{
  int v5; // esi
  int v7; // eax
  int v8; // ecx
  int v9; // edi
  int v10; // ecx

  v5 = *(this + 135006);
  if ( !v5 )
    return &unk_814CB0;
  *(this + 135006) = *(_DWORD *)(v5 + 12);
  *(_DWORD *)(v5 + 8) = a2;
  v7 = *(this + a2 + 135001);
  if ( v7 )
    *(_DWORD *)(v7 + 16) = v5;
  *(_DWORD *)(v5 + 16) = 0;
  *(_DWORD *)(v5 + 12) = *(this + a2 + 135001);
  *(this + a2 + 135001) = v5;
  initialize_sprite((_DWORD *)v5);
  v8 = (1 << (a2 + 24)) | *(_DWORD *)(v5 + 4);
  *(_DWORD *)(v5 + 4) = v8;
  *(float *)(v5 + 28) = unk_78FF90[a3];
  if ( a5 == -1 )
  {
    if ( a4 != -1 )
    {
      *(_DWORD *)(v5 + 4) = v8 | 0x10;
      *(float *)(v5 + 32) = unk_78FF90[a4];
    }
  }
  else
  {
    *(_DWORD *)(v5 + 4) = v8 | 0x20;
    *(float *)(v5 + 32) = unk_78FF90[a4];
    *(float *)(v5 + 36) = unk_78FF90[a5];
  }
  *(_DWORD *)(v5 + 100) = 0;
  *(_DWORD *)(v5 + 156) = a3;
  *(_DWORD *)(v5 + 172) = 0;
  *(_DWORD *)(v5 + 176) = 0;
  *(_DWORD *)(v5 + 160) = *(_DWORD *)(LODWORD(unk_78FF90[a3]) + 144);
  if ( (*(_DWORD *)LODWORD(unk_78FF90[a3]) & 0x2000) != 0 )
  {
    v9 = *(_DWORD *)(v5 + 4) | 0x2000;
    *(_DWORD *)(v5 + 4) = v9;
    v10 = v9;
    *(_DWORD *)(v5 + 176) = *(_DWORD *)(LODWORD(unk_78FF90[a3]) + 148);
    if ( (*(_DWORD *)LODWORD(unk_78FF90[a3]) & 0x4000) != 0 )
    {
      BYTE1(v10) = BYTE1(v9) | 0x40;
      *(_DWORD *)(v5 + 4) = v10;
    }
  }
  return (void *)v5;
}

