/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_or_create_texture_ref @ 0x44e810 */
/* selector: get_or_create_texture_ref */

TextureRef *__thiscall get_or_create_texture_ref(
        TextureRefList *texture_list,
        char *texture_path,
        int32_t arg3,
        int16_t arg4)
{
  int32_t v5; // edi
  char *v6; // ebx
  int32_t v7; // edx

  v5 = 0;
  if ( texture_list->count == texture_list->capacity )
    report_errorf(aTooManyTexture);
  if ( (arg4 & 0x800) != 0 || texture_list->count <= 0 )
  {
LABEL_8:
    copy_c_string(texture_list->entries[texture_list->count].texture_path, texture_path);
    texture_list->entries[texture_list->count].slot_index = texture_list->count;
    texture_list->entries[texture_list->count].flags = 0;
    texture_list->entries[texture_list->count].flags = 1024;
    texture_list->entries[texture_list->count].arg3_98 = arg3;
    texture_list->entries[texture_list->count].one_a0 = 1;
    v7 = texture_list->count++;
    return &texture_list->entries[v7];
  }
  else
  {
    v6 = texture_list->entries[0].texture_path;
    while ( !strings_equal_case_insensitive(v6, texture_path) )
    {
      ++v5;
      v6 += 164;
      if ( v5 >= texture_list->count )
        goto LABEL_8;
    }
    return &texture_list->entries[v5];
  }
}

