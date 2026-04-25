/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_x_animation_clip @ 0x405d60 */
/* selector: load_x_animation_clip */

int __thiscall load_x_animation_clip(int this, const char *ArgList, int *a3)
{
  const char *v3; // edi
  char *case_insensitive_substring; // eax
  _BYTE *v6; // eax
  int v7; // ecx
  int v8; // ebp
  bool v9; // cc
  char *v10; // esi
  int *v11; // edi
  _DWORD *v12; // eax
  char *v13; // eax
  char *v14; // esi
  char *v15; // eax
  char *v16; // ebx
  char *v18; // eax
  __int16 v19; // di
  char *v20; // [esp+10h] [ebp-194h] BYREF
  char v21; // [esp+17h] [ebp-18Dh]
  float v22; // [esp+18h] [ebp-18Ch]
  int v23; // [esp+1Ch] [ebp-188h] BYREF
  int v24; // [esp+20h] [ebp-184h]
  char v25[128]; // [esp+24h] [ebp-180h] BYREF
  char Buffer[256]; // [esp+A4h] [ebp-100h] BYREF

  v3 = ArgList;
  sprintf(Buffer, "%s", ArgList);
  case_insensitive_substring = find_case_insensitive_substring(asc_4A16A0, Buffer);
  v20 = find_case_insensitive_substring(asc_4A16A0, case_insensitive_substring + 1) + 1;
  *v20++ = 42;
  *v20++ = 46;
  *v20++ = 120;
  if ( is_archive_index_loaded() )
    *v20++ = 50;
  *v20++ = 0;
  enumerate_matching_archive_or_fs_entries(asc_4A169C, Buffer, &v23, unk_4B2F50);
  v6 = allocate_tracked_memory(v23 << 7, (int)aAnimKeyFrameBo);
  v7 = v23;
  v8 = 0;
  v24 = (int)v6;
  v9 = v23 <= 0;
  *(_DWORD *)(this + 24072) = 0;
  if ( !v9 )
  {
    v10 = unk_4B2F50;
    v11 = (int *)(v6 + 124);
    do
    {
      v12 = add_object_to_list(unk_4B7648);
      set_bod_object(v11 - 31, (int)v12);
      load_x_mesh(v10, (int *)*(v11 - 22), 0);
      v20 = v10;
      v20 = find_case_insensitive_substring(asc_4A16A0, v10) + 1;
      v20 = find_case_insensitive_substring(asc_4A16A0, v20) + 1;
      *v11 = parse_next_signed_int(&v20);
      v7 = v23;
      ++v8;
      v10 += 128;
      v11 += 32;
    }
    while ( v8 < v23 );
    v3 = ArgList;
  }
  clean_duplicate_vertices((int *)(this + 24072), v7);
  load_x_mesh(unk_4B2F50, a3, 0);
  request_object_vertices_copy((unsigned int *)a3);
  a3[4] |= (unsigned int)&unk_800000;
  sprintf(v25, "Anim:%s", v3);
  v13 = find_case_insensitive_substring(v25, *(char **)this);
  v14 = v13;
  if ( v13 )
  {
    v15 = find_case_insensitive_substring(aAnimend, v13);
    v16 = v15;
    if ( !v15 )
      return report_errorf("Cannot find AnimEnd: for %s \n", v3);
    v21 = *v15;
    *v15 = 0;
    v18 = find_case_insensitive_substring(aDuration, v14);
    v20 = v18;
    if ( v18 )
    {
      v20 = find_case_insensitive_substring(asc_4A1644, v18) + 1;
      v22 = 1.0 / (parse_next_float32(&v20) * 60.0);
    }
    else
    {
      v22 = 0.016666668;
    }
    v20 = find_case_insensitive_substring(aModeLoop, v14);
    v19 = v20 != nullptr;
    v20 = find_case_insensitive_substring(aModeOnce, v14);
    if ( v20 )
      v19 |= 4u;
    v20 = find_case_insensitive_substring(aModePingpong, v14);
    if ( v20 )
      v19 |= 2u;
    *v16 = v21;
  }
  else
  {
    report_errorf("Did not find Anim:%s in _Animation.txt. Using defaults", v3);
    v22 = 0.016666668;
    v19 = v24 | 1;
  }
  if ( v23 == 1 )
    v22 = 1.0;
  return request_object_animation(a3, v23, (_DWORD *)v24, v22, v19);
}

