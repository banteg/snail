/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_loading_screen @ 0x418e80 */
/* selector: update_loading_screen */

// Advances the normalized loader percentage, draws the loading background, and clips the LoadingBarOn fill quad into the recovered 192x289 to 448x321 window.
int __thiscall sub_418E80(int *this)
{
  int result; // eax
  int v3; // ecx
  int v4; // edi
  double v5; // st7
  double v6; // st7
  double v7; // st6
  double v8; // st7
  int v9; // [esp+88h] [ebp-8h] BYREF
  float v10; // [esp+8Ch] [ebp-4h]

  result = *this;
  if ( !*this )
    return result;
  ++*(this + 2);
  v3 = unk_4DF9C4;
  if ( !unk_4DF9C4 )
  {
    v3 = 1;
    unk_4DF9C4 = 1;
  }
  v9 = 100 * *(this + 2) / v3;
  v4 = v9;
  if ( v9 >= 0 )
  {
    if ( v9 <= 100 )
      goto LABEL_9;
    v4 = 100;
  }
  else
  {
    v4 = 0;
  }
  v9 = v4;
LABEL_9:
  result = v4 - *(this + 1);
  if ( result >= 1 )
  {
    v10 = (double)v9 * 0.92000002;
    if ( v4 > 98 )
      v10 = 100.0;
    (*(void (__stdcall **)(int, _DWORD, _DWORD, int, int, int, _DWORD))(*(_DWORD *)MEMORY[0x502FEC] + 144))(
      MEMORY[0x502FEC],
      0,
      0,
      2,
      -16777216,
      1065353216,
      0);
    (*(void (__stdcall **)(int))(*(_DWORD *)MEMORY[0x502FEC] + 136))(MEMORY[0x502FEC]);
    (*(void (__stdcall **)(int, _DWORD, int))(*(_DWORD *)MEMORY[0x502FEC] + 244))(MEMORY[0x502FEC], 0, MEMORY[0x503288]);
    (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 252))(MEMORY[0x502FEC], 0, 13, 3);
    (*(void (__stdcall **)(int, _DWORD, int, int))(*(_DWORD *)MEMORY[0x502FEC] + 252))(MEMORY[0x502FEC], 0, 14, 3);
    (*(void (__stdcall **)(int, _DWORD, _DWORD, int))(*(_DWORD *)MEMORY[0x502FEC] + 332))(
      MEMORY[0x502FEC],
      0,
      *(_DWORD *)(MEMORY[0x503284] + 8),
      20);
    (*(void (__stdcall **)(int, int))(*(_DWORD *)MEMORY[0x502FEC] + 304))(MEMORY[0x502FEC], 258);
    (*(void (__stdcall **)(int, int, _DWORD, int))(*(_DWORD *)MEMORY[0x502FEC] + 280))(MEMORY[0x502FEC], 6, 0, 2);
    (*(void (__stdcall **)(_DWORD, _DWORD, int, int *, _DWORD))(**(_DWORD **)(MEMORY[0x5032A4] + 8) + 44))(
      *(_DWORD *)(MEMORY[0x5032A4] + 8),
      0,
      80,
      &v9,
      0);
    v5 = v10;
    *(_DWORD *)v9 = 1128267776;
    *(_DWORD *)(v9 + 4) = 1133543424;
    v6 = v5 * 2.5599999 + 192.0;
    *(_DWORD *)(v9 + 8) = 0;
    *(_DWORD *)(v9 + 12) = 0;
    *(_DWORD *)(v9 + 16) = 0;
    *(float *)(v9 + 20) = v6;
    v7 = v10 * 0.0099999998;
    *(_DWORD *)(v9 + 24) = 1133543424;
    *(_DWORD *)(v9 + 28) = 0;
    v10 = v7;
    *(float *)(v9 + 32) = v7;
    *(_DWORD *)(v9 + 36) = 0;
    *(float *)(v9 + 40) = v6;
    v8 = v10;
    *(_DWORD *)(v9 + 44) = 1134592000;
    *(_DWORD *)(v9 + 48) = 0;
    *(float *)(v9 + 52) = v8;
    *(_DWORD *)(v9 + 56) = 1065353216;
    *(_DWORD *)(v9 + 60) = 1128267776;
    *(_DWORD *)(v9 + 64) = 1134592000;
    *(_DWORD *)(v9 + 68) = 0;
    *(_DWORD *)(v9 + 72) = 0;
    *(_DWORD *)(v9 + 76) = 1065353216;
    (*(void (__stdcall **)(_DWORD))(**(_DWORD **)(MEMORY[0x5032A4] + 8) + 48))(*(_DWORD *)(MEMORY[0x5032A4] + 8));
    (*(void (__stdcall **)(int, _DWORD, int))(*(_DWORD *)MEMORY[0x502FEC] + 244))(MEMORY[0x502FEC], 0, MEMORY[0x503280]);
    (*(void (__stdcall **)(int, _DWORD, _DWORD, int))(*(_DWORD *)MEMORY[0x502FEC] + 332))(
      MEMORY[0x502FEC],
      0,
      *(_DWORD *)(MEMORY[0x5032A4] + 8),
      20);
    (*(void (__stdcall **)(int, int))(*(_DWORD *)MEMORY[0x502FEC] + 304))(MEMORY[0x502FEC], 258);
    (*(void (__stdcall **)(int, int, _DWORD, int))(*(_DWORD *)MEMORY[0x502FEC] + 280))(MEMORY[0x502FEC], 6, 0, 2);
    (*(void (__stdcall **)(int))(*(_DWORD *)MEMORY[0x502FEC] + 140))(MEMORY[0x502FEC]);
    result = sub_413520();
    *(this + 1) = v4;
  }
  return result;
}

