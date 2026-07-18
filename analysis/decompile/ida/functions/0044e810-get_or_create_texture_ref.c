/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_or_create_texture_ref @ 0x44e810 */
/* selector: get_or_create_texture_ref */

// Looks up or allocates one TextureRefList entry, using the 0xa4-byte TextureRef stride, 0x80-byte inline path, no-reuse flag, and slot-index/count bookkeeping behind sprite texture registration.
TextureRef *__thiscall get_or_create_texture_ref(
        TextureRefList *texture_list,
        char *texture_path,
        void *payload,
        int32_t flags)
{
  int32_t v5; // edi
  char *name; // ebx
  int32_t v7; // edx

  v5 = 0;
  if ( texture_list->count == texture_list->capacity )
    report_errorf(aTooManyTexture);
  if ( (flags & 0x800) != 0 || texture_list->count <= 0 )
  {
LABEL_8:
    copy_c_string(texture_list->entries[texture_list->count].name, texture_path);
    texture_list->entries[texture_list->count].slot_index = texture_list->count;
    texture_list->entries[texture_list->count].flags = 0;
    texture_list->entries[texture_list->count].flags = TEXTURE_REF_REGISTERED;
    texture_list->entries[texture_list->count].texture_ref = payload;
    texture_list->entries[texture_list->count].mip_levels = 1;
    v7 = texture_list->count++;
    return &texture_list->entries[v7];
  }
  else
  {
    name = texture_list->entries[0].name;
    while ( !strings_equal_case_insensitive(name, texture_path) )
    {
      ++v5;
      name += 164;
      if ( v5 >= texture_list->count )
        goto LABEL_8;
    }
    return &texture_list->entries[v5];
  }
}
