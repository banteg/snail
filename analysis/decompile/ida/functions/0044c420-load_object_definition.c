/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_object_definition @ 0x44c420 */
/* selector: load_object_definition */

// Implements the staticized void `cRObject::Load(char*)` path: parses one authored object definition into the caller-owned Object slot, installs its owned vertex and facequad arrays, and borrows texture refs from the shared manager.
void __cdecl load_object_definition(char *path, Object *object)
{
  char *archive_data_base; // esi
  int32_t v3; // ebx
  char *v4; // eax
  char v5; // cl
  int32_t v6; // ebp
  int v7; // esi
  int v8; // eax
  int v9; // esi
  uint16_t v10; // bp
  uint16_t v11; // bx
  double v12; // st7
  uint16_t v13; // dx
  char *line_cursor; // [esp+Ch] [ebp-23Ch] BYREF
  char *cursor; // [esp+10h] [ebp-238h] BYREF
  float v16; // [esp+14h] [ebp-234h]
  float v17; // [esp+18h] [ebp-230h]
  float v18; // [esp+1Ch] [ebp-22Ch]
  int32_t v19; // [esp+20h] [ebp-228h]
  int32_t v20; // [esp+24h] [ebp-224h]
  float v21; // [esp+28h] [ebp-220h]
  float v22; // [esp+2Ch] [ebp-21Ch]
  float v23; // [esp+30h] [ebp-218h]
  float v24; // [esp+34h] [ebp-214h]
  float v25; // [esp+38h] [ebp-210h]
  float v26; // [esp+3Ch] [ebp-20Ch]
  float v27; // [esp+40h] [ebp-208h]
  int32_t byte_count; // [esp+44h] [ebp-204h] BYREF
  char texture_name[128]; // [esp+48h] [ebp-200h] BYREF
  char texture_path[128]; // [esp+C8h] [ebp-180h] BYREF
  char object_file_path[256]; // [esp+148h] [ebp-100h] BYREF

  archive_data_base = (char *)get_archive_data_base();
  sprintf(object_file_path, "%s/_Object.txt", path);
  load_file_bytes_from_archive_or_fs(object_file_path, archive_data_base, &byte_count);
  v3 = 0;
  v4 = archive_data_base;
  archive_data_base[byte_count - 2] = 0;
  texture_name[0] = 0;
  cursor = archive_data_base;
  v5 = *archive_data_base;
  v6 = 0;
  v20 = 0;
  v19 = 0;
  if ( v5 != 0 )
  {
    while ( 1 )
    {
      if ( *v4 == 42 )
      {
        do
          cursor = ++v4;
        while ( *v4 != 10 );
        cursor = ++v4;
        goto LABEL_20;
      }
      if ( *v4 != 91 )
        goto LABEL_18;
      if ( strings_equal_case_insensitive(v4, g_object_text_vertex_start) )
        break;
      if ( strings_equal_case_insensitive(cursor, g_object_text_facequad_start) )
      {
        skip_to_next_line(&cursor);
        line_cursor = cursor;
        if ( !strings_equal_case_insensitive(cursor, g_object_text_facequad_end) )
        {
          do
          {
            ++v3;
            skip_to_next_line(&line_cursor);
          }
          while ( !strings_equal_case_insensitive(line_cursor, g_object_text_facequad_end) );
          v20 = v3;
        }
        request_object_facequads(object, v3);
        if ( !strings_equal_case_insensitive(cursor, g_object_text_facequad_end) )
        {
          do
          {
            line_cursor = cursor;
            v9 = parse_next_int32(&line_cursor);
            v10 = parse_next_int32(&line_cursor);
            v11 = parse_next_int32(&line_cursor);
            v16 = COERCE_FLOAT(parse_next_int32(&line_cursor));
            v18 = COERCE_FLOAT(parse_next_int32(&line_cursor));
            v17 = parse_next_float32(&line_cursor);
            v21 = parse_next_float32(&line_cursor);
            v24 = parse_next_float32(&line_cursor);
            v27 = parse_next_float32(&line_cursor);
            v26 = parse_next_float32(&line_cursor);
            v22 = parse_next_float32(&line_cursor);
            v23 = parse_next_float32(&line_cursor);
            v25 = parse_next_float32(&line_cursor);
            parse_next_space_delimited_token(&line_cursor, texture_name);
            append_c_string(texture_name, g_object_text_tga_extension);
            copy_c_string(texture_path, path);
            append_c_string(texture_path, g_object_text_path_separator);
            append_c_string(texture_path, texture_name);
            v9 *= 48;
            *(_DWORD *)&object->facequads->_pad_0a[v9 + 2] = get_or_create_texture_ref(
                                                               &g_texture_refs,
                                                               texture_path,
                                                               nullptr,
                                                               0);
            skip_to_next_line(&cursor);
            v12 = v17;
            *(uint16_t *)((char *)&object->facequads->header_word + v9) = 0;
            *(uint16_t *)((char *)&object->facequads->vertex_0 + v9) = v10;
            v13 = LOWORD(v16);
            *(uint16_t *)((char *)&object->facequads->vertex_1 + v9) = v11;
            *(uint16_t *)((char *)&object->facequads->vertex_2 + v9) = v13;
            *(uint16_t *)((char *)&object->facequads->vertex_3 + v9) = LOWORD(v18);
            *(float *)((char *)&object->facequads->uv[0].u + v9) = v12;
            *(float *)((char *)&object->facequads->uv[0].v + v9) = v21;
            *(float *)((char *)&object->facequads->uv[1].u + v9) = v24;
            *(float *)((char *)&object->facequads->uv[1].v + v9) = v27;
            *(float *)((char *)&object->facequads->uv[2].u + v9) = v26;
            *(float *)((char *)&object->facequads->uv[2].v + v9) = v22;
            *(float *)((char *)&object->facequads->uv[3].u + v9) = v23;
            *(float *)((char *)&object->facequads->uv[3].v + v9) = v25;
          }
          while ( !strings_equal_case_insensitive(cursor, g_object_text_facequad_end) );
          v3 = v20;
          v6 = v19;
        }
        goto LABEL_18;
      }
LABEL_19:
      v4 = cursor;
LABEL_20:
      if ( *v4 == 0 )
        return;
    }
    skip_to_next_line(&cursor);
    line_cursor = cursor;
    if ( !strings_equal_case_insensitive(cursor, g_object_text_vertex_end) )
    {
      do
      {
        ++v6;
        skip_to_next_line(&line_cursor);
      }
      while ( !strings_equal_case_insensitive(line_cursor, g_object_text_vertex_end) );
      v19 = v6;
    }
    request_object_vertices(object, v6);
    for ( ; !strings_equal_case_insensitive(cursor, g_object_text_vertex_end); object->vertices[v8].z = v16 )
    {
      line_cursor = cursor;
      v7 = parse_next_int32(&line_cursor);
      v17 = parse_next_float32(&line_cursor);
      v18 = parse_next_float32(&line_cursor);
      v16 = parse_next_float32(&line_cursor);
      skip_to_next_line(&cursor);
      v8 = v7;
      object->vertices[v8].x = v17;
      object->vertices[v8].y = v18;
    }
LABEL_18:
    skip_to_next_line(&cursor);
    goto LABEL_19;
  }
}
