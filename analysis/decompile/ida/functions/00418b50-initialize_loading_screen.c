/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_loading_screen @ 0x418b50 */
/* selector: initialize_loading_screen */

// Loads the loading-screen textures, seeds the full-screen quad and progress-bar quad, and resets the loader progress counters.
int __thiscall initialize_loading_screen(_DWORD *this)
{
  unsigned __int8 *v2; // edi
  int v3; // eax
  unsigned __int8 *v4; // edi
  int v5; // eax
  int result; // eax
  _DWORD *v7; // [esp+8Ch] [ebp-8h] BYREF
  int v8; // [esp+90h] [ebp-4h] BYREF

  unk_4DF9C4 = 1276;
  if ( is_archive_index_loaded() )
  {
    v2 = (unsigned __int8 *)get_archive_data_base();
    load_file_bytes_from_archive_or_fs(WideCharStr, v2, (#83 *)&v8);
    v3 = sub_4533C4(
           SLODWORD(flt_4DFAFC[36156]),
           v2,
           v8,
           0,
           0,
           1u,
           0,
           21,
           1u,
           3,
           3,
           -16711936,
           nullptr,
           nullptr,
           &flt_4DFAFC[36323]);
  }
  else
  {
    v3 = sub_453404(
           LODWORD(flt_4DFAFC[36156]),
           WideCharStr,
           0,
           0,
           1,
           0,
           21,
           1,
           3,
           3,
           -16711936,
           0,
           0,
           &flt_4DFAFC[36323]);
  }
  if ( v3 < 0 )
  {
    report_errorf(aFailedToCreate_0);
    sub_453467(LODWORD(flt_4DFAFC[36156]), aSpritesDebugTg, &flt_4DFAFC[36323]);
  }
  (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD))(*(_DWORD *)LODWORD(flt_4DFAFC[36156]) + 244))(
    LODWORD(flt_4DFAFC[36156]),
    0,
    LODWORD(flt_4DFAFC[36323]));
  (*(void (__stdcall **)(_DWORD, _DWORD, int, int))(*(_DWORD *)LODWORD(flt_4DFAFC[36156]) + 252))(
    LODWORD(flt_4DFAFC[36156]),
    0,
    16,
    3);
  (*(void (__stdcall **)(_DWORD, _DWORD, int, int))(*(_DWORD *)LODWORD(flt_4DFAFC[36156]) + 252))(
    LODWORD(flt_4DFAFC[36156]),
    0,
    17,
    3);
  (*(void (__stdcall **)(_DWORD, _DWORD, int, int))(*(_DWORD *)LODWORD(flt_4DFAFC[36156]) + 252))(
    LODWORD(flt_4DFAFC[36156]),
    0,
    13,
    3);
  (*(void (__stdcall **)(_DWORD, _DWORD, int, int))(*(_DWORD *)LODWORD(flt_4DFAFC[36156]) + 252))(
    LODWORD(flt_4DFAFC[36156]),
    0,
    14,
    3);
  if ( is_archive_index_loaded() )
  {
    v4 = (unsigned __int8 *)get_archive_data_base();
    load_file_bytes_from_archive_or_fs(aSpritesLoading_0, v4, (#83 *)&v8);
    v5 = sub_4533C4(
           SLODWORD(flt_4DFAFC[36156]),
           v4,
           v8,
           0,
           0,
           1u,
           0,
           21,
           1u,
           3,
           3,
           -16711936,
           nullptr,
           nullptr,
           &flt_4DFAFC[36321]);
  }
  else
  {
    v5 = sub_453404(
           LODWORD(flt_4DFAFC[36156]),
           aSpritesLoading_0,
           0,
           0,
           1,
           0,
           21,
           1,
           3,
           3,
           -16711936,
           0,
           0,
           &flt_4DFAFC[36321]);
  }
  if ( v5 < 0 )
  {
    report_errorf(aFailedToCreate_1);
    sub_453467(LODWORD(flt_4DFAFC[36156]), aSpritesDebugTg, &flt_4DFAFC[36321]);
  }
  (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD))(*(_DWORD *)LODWORD(flt_4DFAFC[36156]) + 244))(
    LODWORD(flt_4DFAFC[36156]),
    0,
    LODWORD(flt_4DFAFC[36321]));
  (*(void (__stdcall **)(_DWORD, _DWORD, int, int))(*(_DWORD *)LODWORD(flt_4DFAFC[36156]) + 252))(
    LODWORD(flt_4DFAFC[36156]),
    0,
    16,
    3);
  (*(void (__stdcall **)(_DWORD, _DWORD, int, int))(*(_DWORD *)LODWORD(flt_4DFAFC[36156]) + 252))(
    LODWORD(flt_4DFAFC[36156]),
    0,
    17,
    3);
  LODWORD(flt_4DFAFC[36322]) = sub_4114B0((int *)&flt_4DFAFC[24151], 4, 258);
  LODWORD(flt_4DFAFC[36330]) = sub_4114B0((int *)&flt_4DFAFC[24151], 4, 258);
  (*(void (__stdcall **)(_DWORD, _DWORD, int, _DWORD **, _DWORD))(**(_DWORD **)(LODWORD(flt_4DFAFC[36322]) + 8) + 44))(
    *(_DWORD *)(LODWORD(flt_4DFAFC[36322]) + 8),
    0,
    80,
    &v7,
    0);
  *v7 = 0;
  v7[1] = 0;
  v7[2] = 0;
  v7[3] = 0;
  v7[4] = 0;
  v7[5] = 1142947840;
  v7[6] = 0;
  v7[7] = 0;
  v7[8] = 1065353216;
  v7[9] = 0;
  v7[10] = 1142947840;
  v7[11] = 1139802112;
  v7[12] = 0;
  v7[13] = 1065353216;
  v7[14] = 1065353216;
  v7[15] = 0;
  v7[16] = 1139802112;
  v7[17] = 0;
  v7[18] = 0;
  v7[19] = 1065353216;
  (*(void (__stdcall **)(_DWORD))(**(_DWORD **)(LODWORD(flt_4DFAFC[36330]) + 8) + 48))(*(_DWORD *)(LODWORD(flt_4DFAFC[36330])
                                                                                                 + 8));
  result = sub_411E10();
  *(this + 2) = 0;
  *(this + 1) = 0;
  *this = 1;
  return result;
}

