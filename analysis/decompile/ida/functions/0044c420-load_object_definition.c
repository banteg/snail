/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_object_definition @ 0x44c420 */
/* selector: load_object_definition */

char *__cdecl sub_44C420(char *a1, int *a2)
{
  char *v2; // esi
  int v3; // ebx
  char *result; // eax
  char v5; // cl
  int v6; // ebp
  int v7; // esi
  int v8; // eax
  int v9; // esi
  __int16 v10; // bp
  __int16 v11; // bx
  double v12; // st7
  __int16 v13; // dx
  char *v14; // [esp+Ch] [ebp-23Ch] BYREF
  char *v15; // [esp+10h] [ebp-238h] BYREF
  float v16; // [esp+14h] [ebp-234h]
  float v17; // [esp+18h] [ebp-230h]
  float v18; // [esp+1Ch] [ebp-22Ch]
  int v19; // [esp+20h] [ebp-228h]
  int v20; // [esp+24h] [ebp-224h]
  float v21; // [esp+28h] [ebp-220h]
  float v22; // [esp+2Ch] [ebp-21Ch]
  float v23; // [esp+30h] [ebp-218h]
  float v24; // [esp+34h] [ebp-214h]
  float v25; // [esp+38h] [ebp-210h]
  float v26; // [esp+3Ch] [ebp-20Ch]
  float v27; // [esp+40h] [ebp-208h]
  int v28; // [esp+44h] [ebp-204h] BYREF
  _BYTE v29[128]; // [esp+48h] [ebp-200h] BYREF
  char v30[128]; // [esp+C8h] [ebp-180h] BYREF
  char Buffer[256]; // [esp+148h] [ebp-100h] BYREF

  v2 = (char *)get_archive_data_base();
  sprintf(Buffer, "%s/_Object.txt", a1);
  load_file_bytes_from_archive_or_fs(Buffer, v2, (#83 *)&v28);
  v3 = 0;
  result = v2;
  v2[v28 - 2] = 0;
  v29[0] = 0;
  v15 = v2;
  v5 = *v2;
  v6 = 0;
  v20 = 0;
  v19 = 0;
  if ( v5 )
  {
    while ( 1 )
    {
      if ( *result == 42 )
      {
        do
          v15 = ++result;
        while ( *result != 10 );
        v15 = ++result;
        goto LABEL_20;
      }
      if ( *result != 91 )
        goto LABEL_18;
      if ( strings_equal_case_insensitive(result, aVertexStart) )
        break;
      if ( strings_equal_case_insensitive(v15, aFacequadStart) )
      {
        skip_to_next_line(&v15);
        v14 = v15;
        if ( !strings_equal_case_insensitive(v15, aFacequadEnd) )
        {
          do
          {
            ++v3;
            skip_to_next_line(&v14);
          }
          while ( !strings_equal_case_insensitive(v14, aFacequadEnd) );
          v20 = v3;
        }
        request_object_facequads(a2, v3);
        if ( !strings_equal_case_insensitive(v15, aFacequadEnd) )
        {
          do
          {
            v14 = v15;
            v9 = parse_next_int32(&v14);
            v10 = parse_next_int32(&v14);
            v11 = parse_next_int32(&v14);
            v16 = COERCE_FLOAT(parse_next_int32(&v14));
            v18 = COERCE_FLOAT(parse_next_int32(&v14));
            v17 = parse_next_float32(&v14);
            v21 = parse_next_float32(&v14);
            v24 = parse_next_float32(&v14);
            v27 = parse_next_float32(&v14);
            v26 = parse_next_float32(&v14);
            v22 = parse_next_float32(&v14);
            v23 = parse_next_float32(&v14);
            v25 = parse_next_float32(&v14);
            parse_next_space_delimited_token(&v14, v29);
            append_c_string(v29, aTga_0);
            copy_c_string(v30, a1);
            append_c_string(v30, asc_4ACCE0);
            append_c_string(v30, v29);
            v9 *= 48;
            *(_DWORD *)(a2[23] + v9 + 12) = get_or_create_texture_ref(&dword_4B7790, v30, 0, 0);
            skip_to_next_line(&v15);
            v12 = v17;
            *(_WORD *)(a2[23] + v9) = 0;
            *(_WORD *)(a2[23] + v9 + 2) = v10;
            v13 = LOWORD(v16);
            *(_WORD *)(a2[23] + v9 + 4) = v11;
            *(_WORD *)(a2[23] + v9 + 6) = v13;
            *(_WORD *)(a2[23] + v9 + 8) = LOWORD(v18);
            *(float *)(a2[23] + v9 + 16) = v12;
            *(float *)(a2[23] + v9 + 20) = v21;
            *(float *)(a2[23] + v9 + 24) = v24;
            *(float *)(a2[23] + v9 + 28) = v27;
            *(float *)(a2[23] + v9 + 32) = v26;
            *(float *)(a2[23] + v9 + 36) = v22;
            *(float *)(a2[23] + v9 + 40) = v23;
            *(float *)(a2[23] + v9 + 44) = v25;
          }
          while ( !strings_equal_case_insensitive(v15, aFacequadEnd) );
          v3 = v20;
          v6 = v19;
        }
        goto LABEL_18;
      }
LABEL_19:
      result = v15;
LABEL_20:
      if ( !*result )
        return result;
    }
    skip_to_next_line(&v15);
    v14 = v15;
    if ( !strings_equal_case_insensitive(v15, aVertexEnd) )
    {
      do
      {
        ++v6;
        skip_to_next_line(&v14);
      }
      while ( !strings_equal_case_insensitive(v14, aVertexEnd) );
      v19 = v6;
    }
    request_object_vertices(a2, v6);
    for ( ; !strings_equal_case_insensitive(v15, aVertexEnd); *(float *)(a2[14] + v8 + 8) = v16 )
    {
      v14 = v15;
      v7 = parse_next_int32(&v14);
      v17 = parse_next_float32(&v14);
      v18 = parse_next_float32(&v14);
      v16 = parse_next_float32(&v14);
      skip_to_next_line(&v15);
      v8 = 12 * v7;
      *(float *)(a2[14] + v8) = v17;
      *(float *)(a2[14] + v8 + 4) = v18;
    }
LABEL_18:
    skip_to_next_line(&v15);
    goto LABEL_19;
  }
  return result;
}

