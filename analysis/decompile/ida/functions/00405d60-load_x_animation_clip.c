/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_x_animation_clip @ 0x405d60 */
/* selector: load_x_animation_clip */

// Void Windows `cRDirectX::LoadAnim(char*, cRObject*)`: owns the shared parse cursor while enumerating one mesh's X-animation keyframes into 0x80-byte BodBase-derived records, loads their borrowed ObjectList slots, parses duration/mode metadata, and asks the destination Object to retain the generated animation graph.
void __thiscall load_x_animation_clip(DirectXLoader *loader, char *mesh_name, Object *object)
{
  char *v3; // edi
  char *case_insensitive_substring; // eax
  XAnimationKeyframe *tracked_memory; // eax
  int v7; // ecx
  int v8; // ebp
  bool v9; // cc
  char *v10; // esi
  int32_t *p_frame_number; // edi
  Object *v12; // eax
  char *v13; // eax
  char *v14; // esi
  char *v15; // eax
  char *v16; // ebx
  char *v17; // eax
  int v18; // edi
  char *cursor; // [esp+10h] [ebp-194h] BYREF
  char v20; // [esp+17h] [ebp-18Dh]
  float progress_step; // [esp+18h] [ebp-18Ch]
  int unused; // [esp+1Ch] [ebp-188h] BYREF
  XAnimationKeyframe *keyframes; // [esp+20h] [ebp-184h]
  char v24[128]; // [esp+24h] [ebp-180h] BYREF
  char Buffer[256]; // [esp+A4h] [ebp-100h] BYREF

  v3 = mesh_name;
  sprintf(Buffer, "%s", mesh_name);
  case_insensitive_substring = find_case_insensitive_substring(asc_4A16A0, Buffer);
  cursor = find_case_insensitive_substring(asc_4A16A0, case_insensitive_substring + 1) + 1;
  *cursor++ = 42;
  *cursor++ = 46;
  *cursor++ = 120;
  if ( is_archive_index_loaded() )
    *cursor++ = 50;
  *cursor++ = 0;
  enumerate_matching_archive_or_fs_entries(asc_4A169C, (int)Buffer, (float *)&unused, (int)g_animation_directory);
  tracked_memory = (XAnimationKeyframe *)allocate_tracked_memory(unused << 7, (int)aAnimKeyFrameBo);
  v7 = unused;
  v8 = 0;
  keyframes = tracked_memory;
  v9 = unused <= 0;
  loader->duplicate_vertices.active_count = 0;
  if ( !v9 )
  {
    v10 = g_animation_directory;
    p_frame_number = &tracked_memory->frame_number;
    do
    {
      v12 = add_object_to_list(&g_object_list);
      set_bod_object((BodBase *)(p_frame_number - 31), v12);
      load_x_mesh(loader, v10, (Object *)*(p_frame_number - 22), 0);
      cursor = v10;
      cursor = find_case_insensitive_substring(asc_4A16A0, v10) + 1;
      cursor = find_case_insensitive_substring(asc_4A16A0, cursor) + 1;
      *p_frame_number = parse_next_signed_int(&cursor);
      v7 = unused;
      ++v8;
      v10 += 128;
      p_frame_number += 32;
    }
    while ( v8 < unused );
    v3 = mesh_name;
  }
  clean_duplicate_vertices(&loader->duplicate_vertices, v7);
  load_x_mesh(loader, g_animation_directory, object, 0);
  request_object_vertices_copy(object);
  object->flags |= (unsigned int)&unk_800000;
  sprintf(v24, "Anim:%s", v3);
  v13 = find_case_insensitive_substring(v24, loader->animation_bytes);
  v14 = v13;
  if ( v13 )
  {
    v15 = find_case_insensitive_substring(aAnimend, v13);
    v16 = v15;
    if ( !v15 )
    {
      report_errorf("Cannot find AnimEnd: for %s \n", v3);
      return;
    }
    v20 = *v15;
    *v15 = 0;
    v17 = find_case_insensitive_substring(aDuration, v14);
    cursor = v17;
    if ( v17 )
    {
      cursor = find_case_insensitive_substring(asc_4A1644, v17) + 1;
      progress_step = 1.0 / (parse_next_float32(&cursor) * 60.0);
    }
    else
    {
      progress_step = 0.016666668;
    }
    cursor = find_case_insensitive_substring(aModeLoop, v14);
    v18 = cursor != nullptr;
    cursor = find_case_insensitive_substring(aModeOnce, v14);
    if ( cursor )
      v18 |= 4u;
    cursor = find_case_insensitive_substring(aModePingpong, v14);
    if ( cursor )
      v18 |= 2u;
    *v16 = v20;
  }
  else
  {
    report_errorf("Did not find Anim:%s in _Animation.txt. Using defaults", v3);
    progress_step = 0.016666668;
    v18 = (unsigned int)keyframes | 1;
  }
  if ( unused == 1 )
    progress_step = 1.0;
  request_object_animation(object, unused, keyframes, progress_step, v18);
}
