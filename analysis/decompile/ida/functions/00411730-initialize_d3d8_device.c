/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_d3d8_device @ 0x411730 */
/* selector: initialize_d3d8_device */

int __thiscall initialize_d3d8_device(int this, char a2)
{
  int v3; // eax
  int v4; // edx
  int v5; // ecx
  int v6; // ecx
  int v7; // edx
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int result; // eax
  _DWORD v12[3]; // [esp+8h] [ebp-10h] BYREF
  int v13; // [esp+14h] [ebp-4h]

  v3 = Direct3DCreate8(220);
  *(_DWORD *)(this + 48016) = v3;
  if ( !v3 )
    abort_startup_with_3d_error();
  if ( (*(int (__stdcall **)(_DWORD, _DWORD, _DWORD *))(**(_DWORD **)(this + 48016) + 32))(
         *(_DWORD *)(this + 48016),
         0,
         v12) < 0 )
    abort_startup_with_3d_error();
  v4 = v13;
  *(_DWORD *)(this + 48288) = v13;
  memset((void *)(this + 48024), 0, 0x34u);
  v5 = *(_DWORD *)(this + 48312);
  *(_DWORD *)(this + 48052) = 1;
  *(_DWORD *)(this + 48044) = 4;
  *(_DWORD *)(this + 48056) = 1;
  *(_DWORD *)(this + 48060) = v5;
  v6 = MEMORY[0x4DFAF0];
  *(_DWORD *)(this + 48032) = v4;
  *(_DWORD *)(this + 48048) = v6;
  v7 = *(_DWORD *)(this + 48316);
  *(_DWORD *)(this + 48024) = *(_DWORD *)(this + 48292);
  v8 = *(_DWORD *)(this + 48296);
  *(_DWORD *)(this + 48040) = v7;
  *(_DWORD *)(this + 48028) = v8;
  *(_DWORD *)(this + 48068) = 0;
  if ( a2 )
    *(_DWORD *)(this + 48072) = 1;
  else
    *(_DWORD *)(this + 48072) = 0;
  v9 = *(_DWORD *)(this + 48016);
  *(_DWORD *)(this + 48300) = 64;
  if ( (*(int (__stdcall **)(int, _DWORD, int, _DWORD, int, int, int))(*(_DWORD *)v9 + 60))(
         v9,
         0,
         1,
         MEMORY[0x4DFAF0],
         64,
         this + 48024,
         this + 48020) < 0 )
  {
    v10 = *(_DWORD *)(this + 48016);
    *(_DWORD *)(this + 48300) = 32;
    if ( (*(int (__stdcall **)(int, _DWORD, int, _DWORD, int, int, int))(*(_DWORD *)v10 + 60))(
           v10,
           0,
           1,
           MEMORY[0x4DFAF0],
           32,
           this + 48024,
           this + 48020) < 0 )
      abort_startup_with_3d_error();
  }
  sub_449C00();
  sub_4118B0((_DWORD **)this);
  result = sub_414600((_DWORD **)this);
  *(_BYTE *)(this + 48012) = 1;
  return result;
}

