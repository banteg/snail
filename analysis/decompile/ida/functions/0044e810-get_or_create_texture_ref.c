/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_or_create_texture_ref @ 0x44e810 */
/* selector: get_or_create_texture_ref */

TextureRef *__thiscall get_or_create_texture_ref(int32_t *texture_list, char *texture_path, int32_t arg3, int16_t arg4)
{
  int32_t v5; // edi
  char *v6; // ebx
  int v7; // edx

  v5 = 0;
  if ( *texture_list == *(texture_list + 1) )
    report_errorf(aTooManyTexture);
  if ( (arg4 & 0x800) != 0 || *texture_list <= 0 )
  {
LABEL_8:
    copy_c_string((_BYTE *)texture_list + 164 * *texture_list + 20, texture_path);
    *(texture_list + 41 * *texture_list + 37) = *texture_list;
    *(texture_list + 41 * *texture_list + 2) = 0;
    *(texture_list + 41 * *texture_list + 2) = 1024;
    *(texture_list + 41 * *texture_list + 40) = arg3;
    *(texture_list + 41 * *texture_list + 42) = 1;
    v7 = 41 * (*texture_list)++;
    return (TextureRef *)(texture_list + v7 + 2);
  }
  else
  {
    v6 = (char *)(texture_list + 5);
    while ( !strings_equal_case_insensitive(v6, texture_path) )
    {
      ++v5;
      v6 += 164;
      if ( v5 >= *texture_list )
        goto LABEL_8;
    }
    return (TextureRef *)(texture_list + 41 * v5 + 2);
  }
}

