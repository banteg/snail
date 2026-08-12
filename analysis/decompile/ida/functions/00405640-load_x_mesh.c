/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_x_mesh @ 0x405640 */
/* selector: load_x_mesh */

// Exact Windows `cRDirectX::Load(char*, cRObject*, int)`: loads one X mesh into an owned cRObject, preserves raw and signed-16-bit working counts, writes scalar UV and index lanes through the object-owned face array, then assigns each face material from a guarded local texture table. Android and iOS preserve the same authored owner and ABI.
void __thiscall load_x_mesh(cRDirectX *loader, char *mesh_path, Object *object, int32_t options_flags)
{
  char *archive_data_base; // esi
  char *case_insensitive_substring; // eax
  char *v6; // edi
  char *v7; // eax
  char *v8; // eax
  char *v9; // eax
  int v10; // ebx
  int32_t v11; // esi
  char *v12; // eax
  ObjectUv *tracked_memory; // eax
  ObjectUv *v14; // ebp
  float *p_u; // ebx
  int v16; // ebx
  int v17; // esi
  int v18; // ebx
  void *v19; // eax
  int v20; // ebx
  uint16_t v21; // cx
  TextureRef *texture_ref; // eax
  TextureRefFlags flags; // edx
  char *v24; // eax
  int v25; // esi
  void *v26; // eax
  char *v27; // esi
  int v28; // ebp
  TextureRef **v29; // ebx
  char *v30; // eax
  char *v31; // eax
  char k; // cl
  _BYTE *v33; // eax
  TextureRef *v34; // eax
  TextureRefFlags v35; // ecx
  TextureRefFlags v36; // ecx
  char *v37; // ebx
  int v38; // esi
  __int16 v39; // ax
  char *v40; // [esp+10h] [ebp-234h] BYREF
  int j; // [esp+14h] [ebp-230h]
  char *v42; // [esp+18h] [ebp-22Ch] BYREF
  int i; // [esp+1Ch] [ebp-228h]
  char *cursor; // [esp+20h] [ebp-224h] BYREF
  void *v45; // [esp+24h] [ebp-220h]
  char *v46; // [esp+28h] [ebp-21Ch] BYREF
  char *v47; // [esp+2Ch] [ebp-218h] BYREF
  int v48; // [esp+30h] [ebp-214h]
  char *searched; // [esp+34h] [ebp-210h]
  int v50; // [esp+38h] [ebp-20Ch]
  void *pointer; // [esp+3Ch] [ebp-208h]
  int out_size; // [esp+40h] [ebp-204h] BYREF
  char Buffer[256]; // [esp+44h] [ebp-200h] BYREF
  char texture_path[2]; // [esp+144h] [ebp-100h] BYREF
  char v55; // [esp+146h] [ebp-FEh] BYREF

  archive_data_base = (char *)get_archive_data_base();
  if ( is_archive_index_loaded() == 0 || mesh_path[strlen(mesh_path) - 1] == 50 )
    sprintf(Buffer, "X/%s", mesh_path);
  else
    sprintf(Buffer, "X/%s2", mesh_path);
  load_file_bytes_from_archive_or_fs(Buffer, archive_data_base, &out_size);
  archive_data_base[out_size - 2] = 0;
  case_insensitive_substring = find_case_insensitive_substring(aFrame, archive_data_base);
  v6 = case_insensitive_substring;
  searched = case_insensitive_substring;
  if ( case_insensitive_substring != nullptr )
  {
    v7 = find_case_insensitive_substring(aMesh, case_insensitive_substring);
    v47 = v7;
    if ( v7 == nullptr )
    {
      report_errorf("No 'VertexDuplicationIndices 'Data in %s", Buffer);
      v7 = nullptr;
    }
    v47 = find_case_insensitive_substring(asc_4A1568, v7);
    v8 = find_case_insensitive_substring(aMesh, v6);
    v40 = v8;
    if ( v8 == nullptr )
    {
      report_errorf("No 'Mesh 'Data in %s", Buffer);
      v8 = nullptr;
    }
    v40 = find_case_insensitive_substring(asc_4A1568, v8);
    v9 = find_case_insensitive_substring(aMeshmaterialli, v6);
    v46 = v9;
    if ( v9 == nullptr )
    {
      report_errorf("No 'MeshMaterialList 'Data in %s", Buffer);
      v9 = nullptr;
    }
    v46 = find_case_insensitive_substring(asc_4A1568, v9);
    parse_next_signed_int(&v46);
    LOWORD(v10) = parse_next_signed_int(&v46);
    j = parse_next_signed_int(&v47);
    v11 = (__int16)j;
    if ( v11 != parse_next_signed_int(&v40) )
      report_errorf("Mesh vertices count does not match vertext duplicate vertices count in %s", Buffer);
    parse_next_signed_int(&v47);
    v12 = find_case_insensitive_substring(aMeshtexturecoo, v6);
    cursor = v12;
    if ( v12 == nullptr )
    {
      report_errorf("No 'Mesh 'Data in %s", Buffer);
      v12 = cursor;
    }
    cursor = find_case_insensitive_substring(asc_4A1568, v12);
    if ( v11 != parse_next_signed_int(&cursor) )
      report_errorf("Mesh texture coords number does not match mesh vertext count in %s", Buffer);
    v10 = (__int16)v10;
    v48 = (__int16)v10;
    request_object_facequads(object, (__int16)v10);
    request_object_vertices(object, v11);
    pointer = allocate_tracked_memory(4 * v11, name);
    tracked_memory = (ObjectUv *)allocate_tracked_memory(8 * v11, aMeshTextureCoo_0);
    v14 = tracked_memory;
    if ( v11 > 0 )
    {
      p_u = &tracked_memory->u;
      for ( i = v11; i != 0; --i )
      {
        *p_u = parse_next_float32(&cursor);
        p_u[1] = parse_next_float32(&cursor);
        p_u += 2;
      }
      v10 = v48;
    }
    if ( (__int16)j > 0 )
    {
      v16 = 0;
      do
      {
        object->vertices[v16].x = parse_next_float32(&v40);
        object->vertices[v16].y = parse_next_float32(&v40);
        object->vertices[v16++].z = parse_next_float32(&v40);
        --v11;
      }
      while ( v11 != 0 );
      v10 = v48;
    }
    if ( v10 != parse_next_signed_int(&v40) )
      report_errorf("Mesh face count does not match material face count in %s", Buffer);
    if ( v10 > 0 )
    {
      v17 = 0;
      for ( j = v10; j != 0; --j )
      {
        object->facequads[v17].header_word = 0;
        v18 = parse_next_signed_int(&v40);
        v50 = parse_next_signed_int(&v40);
        i = parse_next_signed_int(&v40);
        v19 = (void *)parse_next_signed_int(&v40);
        v45 = v19;
        if ( v18 == 4 )
        {
          v20 = parse_next_signed_int(&v40);
          v19 = v45;
        }
        else
        {
          v20 = 0;
          object->facequads[v17].flags |= 0x80u;
        }
        object->facequads[v17].uv[2].u = v14[v50].u;
        object->facequads[v17].uv[2].v = v14[v50].v;
        object->facequads[v17].uv[1].u = v14[i].u;
        object->facequads[v17].uv[1].v = v14[i].v;
        object->facequads[v17].uv[0] = v14[(_DWORD)v19];
        object->facequads[v17++].uv[3] = v14[v20];
        object->facequads[v17 - 1].texture_ref = get_or_create_texture_ref(&g_texture_refs, ::texture_path, nullptr, 0);
        v21 = v50;
        texture_ref = object->facequads[v17 - 1].texture_ref;
        flags = texture_ref->flags;
        BYTE1(flags) = ((unsigned __int16)texture_ref->flags >> 8) | 0x10;
        texture_ref->flags = flags;
        object->facequads[v17 - 1].vertex_2 = v21;
        object->facequads[v17 - 1].vertex_1 = i;
        object->facequads[v17 - 1].vertex_0 = (unsigned __int16)v45;
        object->facequads[v17 - 1].vertex_3 = v20;
      }
      v10 = v48;
    }
    object->flags |= 0x100000u;
    free_tracked_memory(v14);
    free_tracked_memory(pointer);
    v24 = find_case_insensitive_substring(aMeshmaterialli_0, searched);
    v42 = v24;
    if ( v24 != nullptr )
    {
      v42 = find_case_insensitive_substring(asc_4A1568, v24);
      v25 = parse_next_signed_int(&v42);
      j = v25;
      searched = (char *)parse_next_signed_int(&v42);
      if ( searched == (char *)v10 )
      {
        v26 = allocate_tracked_memory(4 * v25, aDirectXMateria);
        v27 = v42;
        v28 = 0;
        v45 = v26;
        if ( j > 0 )
        {
          v29 = (TextureRef **)v26;
          do
          {
            v30 = find_case_insensitive_substring(aTexturefilenam, v27);
            if ( v30 != nullptr )
            {
              v27 = find_case_insensitive_substring(asc_4A1314, v30) + 1;
              qmemcpy(texture_path, "X/", sizeof(texture_path));
              v31 = &v55;
              for ( k = *v27; k != 46; ++v27 )
              {
                *v31 = k;
                k = v27[1];
                ++v31;
              }
              *v31 = 46;
              v33 = v31 + 1;
              *v33++ = 116;
              *v33++ = 103;
              *v33 = 97;
              v33[1] = 0;
              v34 = get_or_create_texture_ref(&g_texture_refs, texture_path, nullptr, 0);
              *v29 = v34;
              v35 = v34->flags;
              BYTE1(v35) = ((unsigned __int16)v34->flags >> 8) | 0x10;
              v34->flags = v35;
              if ( (options_flags & 2) != 0 )
              {
                v36 = (*v29)->flags;
                BYTE1(v36) |= 0x80u;
                (*v29)->flags = v36;
              }
            }
            else
            {
              if ( (options_flags & 2) == 0 )
                report_warningf("No TextureFilename for Material %i in %s", v28, Buffer);
              *v29 = get_or_create_texture_ref(&g_texture_refs, aSpritesDebugTg_0, nullptr, 0);
              v27 = v42;
            }
            ++v28;
            ++v29;
          }
          while ( v28 < j );
        }
        v37 = searched;
        if ( (int)searched > 0 )
        {
          v38 = 0;
          do
          {
            v39 = parse_next_signed_int(&v42);
            ++v38;
            --v37;
            object->facequads[v38 - 1].texture_ref = *((TextureRef **)v45 + v39);
          }
          while ( v37 != nullptr );
        }
        free_tracked_memory(v45);
      }
      else
      {
        report_errorf("No MeshMaterialList face number is not equal to Mesh face number in %s", Buffer);
      }
    }
    else
    {
      report_errorf("No MeshMaterialList { in %s", Buffer);
    }
  }
  else
  {
    report_errorf("No 'Frame ' Data in %s", Buffer);
  }
}
