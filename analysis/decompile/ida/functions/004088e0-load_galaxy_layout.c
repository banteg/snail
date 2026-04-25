/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_galaxy_layout @ 0x4088e0 */
/* selector: load_galaxy_layout */

// Loads `Galaxy/_Galaxy.txt`, rescales the authored galaxy-point tables, and populates the runtime galaxy route records with star counts, authored positions, and placeholder level labels.
int __thiscall sub_4088E0(_DWORD *this)
{
  int *v1; // eax
  double v3; // st7
  float *v4; // eax
  double v5; // st7
  int v6; // ebx
  _BYTE *v7; // eax
  _DWORD *v8; // ebp
  _DWORD *v9; // edi
  char *v10; // eax
  char *v11; // eax
  char *v12; // eax
  char *v13; // edx
  char i; // cl
  int v15; // ebp
  int result; // eax
  int v17; // [esp+0h] [ebp-E4h]
  char *v18; // [esp+10h] [ebp-D4h] BYREF
  int v19; // [esp+14h] [ebp-D0h]
  int v20; // [esp+18h] [ebp-CCh]
  _DWORD *v21; // [esp+1Ch] [ebp-C8h]
  char *v22; // [esp+20h] [ebp-C4h]
  char Buffer[64]; // [esp+24h] [ebp-C0h] BYREF
  char ArgList[128]; // [esp+64h] [ebp-80h] BYREF

  v1 = &dword_4A1D18;
  *(_BYTE *)this = 0;
  *(this + 3) = 1;
  do
  {
    v3 = *((float *)v1 - 1) * 0.80000001;
    v1 += 2;
    *((float *)v1 - 3) = v3;
    *((float *)v1 - 2) = (*((float *)v1 - 2) * 0.80000001 - 240.0) * 0.93000001 + 250.0;
  }
  while ( (int)v1 < (int)&aMissingInGalax[4] );
  v4 = (float *)&unk_4A1C50;
  do
  {
    v5 = *(v4 - 1) * 0.80000001;
    v4 += 2;
    *(v4 - 3) = v5;
    *(v4 - 2) = (*(v4 - 2) * 0.80000001 - 240.0) * 0.93000001 + 250.0;
  }
  while ( (int)v4 < (int)flt_4A1CA0 );
  v6 = 0;
  *(this + 17372) = (char *)MEMORY[0x4DF904] + 476696;
  v7 = (_BYTE *)get_archive_data_base();
  v8 = &unk_4A1C50;
  v22 = load_file_bytes_from_archive_or_fs(aGalaxyGalaxyTx, v7, nullptr);
  v19 = 0;
  v20 = 0;
  v21 = &unk_4A1C50;
  v9 = this + 17005;
  while ( 1 )
  {
    sprintf(Buffer, "Galaxy%i:", v19);
    v10 = find_case_insensitive_substring(Buffer, v22);
    v18 = v10;
    if ( !v10 )
      return report_errorf("Cannot find Galaxy %i in _Galaxy.txt", v17);
    v11 = find_case_insensitive_substring(asc_4A1644, v10) + 1;
    v18 = v11;
    if ( *v11 != 34 )
      break;
    v12 = v11 + 1;
    v13 = (char *)(v9 - 33);
    v18 = v12;
    for ( i = *v12; *v12 != 34; i = *v12 )
    {
      *v13++ = i;
      v18 = ++v12;
    }
    *v13 = 0;
    v18 = find_case_insensitive_substring(aStarnumber, v12);
    v18 = find_case_insensitive_substring(asc_4A2094, v18) + 1;
    *(v9 - 1) = parse_next_signed_int(&v18);
    *v9 = 1065353216;
    v9[1] = 1065353216;
    v9[2] = 1065353216;
    v9[3] = 1061997773;
    v9[4] = *(v8 - 1);
    v9[5] = *v8;
    v9[6] = 0;
    if ( (int)*(v9 - 1) > 0 )
    {
      v15 = 0;
      do
      {
        *(this + 168 * *(this + 3) + 5) = v19;
        *(this + 168 * *(this + 3) + 7) = dword_4A1D1C[2 * v20 + 2 * (v15 / *(v9 - 1))];
        *(this + 168 * *(this + 3) + 8) = dword_4A1D20[2 * v20 + 2 * (v15 / *(v9 - 1))];
        *(this + 168 * *(this + 3) + 9) = 0;
        sprintf(ArgList, "LEVEL %i MISSING", *(this + 3));
        rstrcpy_checked_ascii((char *)this + 672 * *(this + 3) + 48, ArgList);
        rstrcpy_checked_ascii((char *)this + 672 * *(this + 3) + 176, ArgList);
        ++v6;
        ++*(this + 3);
        v15 += 10;
      }
      while ( v6 < *(v9 - 1) );
      v8 = v21;
      v6 = 0;
    }
    v8 += 2;
    v9 += 40;
    ++v19;
    v21 = v8;
    v20 += 10;
    if ( (int)v8 >= (int)flt_4A1CA0 )
    {
      *(this + 5) = 0;
      *(this + 7) = dword_4A1D14;
      result = dword_4A1D18;
      *(this + 8) = dword_4A1D18;
      *(this + 9) = 0;
      *((_BYTE *)this + 48) = 0;
      *((_BYTE *)this + 176) = 0;
      return result;
    }
  }
  return report_errorf(aMissingInGalax);
}

