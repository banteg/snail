/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: open_logo @ 0x419110 */
/* selector: open_logo */

// Implements `cRLogo::Open()`: initializes the 32-image-donor tail of the root-owned cRLogo and preloads every Intro/*.tga texture. The donor bank starts at cRLogo +0x24018 after the 1024-entry cRLogoLetter crawl bank.
void __thiscall open_logo(cRLogo *logo)
{
  Object **p_object; // esi
  int i; // edi
  Object *v3; // eax
  Object *v4; // eax
  int v5; // esi
  char *v6; // edi
  TextureRef *texture_ref; // eax
  TextureRefFlags flags; // ecx
  int out_count; // [esp+8h] [ebp-4084h] BYREF
  char Buffer[128]; // [esp+Ch] [ebp-4080h] BYREF
  EnumeratedEntryName names; // [esp+8Ch] [ebp-4000h] BYREF

  p_object = &logo->image_donors[0].renderable.bod.object;
  for ( i = 32; i != 0; --i )
  {
    v3 = add_object_to_list(&g_object_list);
    set_bod_object((BodBase *)(p_object - 9), v3);
    load_object_definition(aObjectsFont3d, *p_object);
    v4 = *p_object;
    p_object += 36;
    v4->flags |= 4u;
  }
  enumerate_matching_archive_or_fs_entries(aIntro, (char *)pattern, &out_count, (EnumeratedEntryName *)names);
  v5 = 0;
  if ( out_count > 0 )
  {
    v6 = names;
    do
    {
      sprintf(Buffer, "Intro/%s", v6);
      texture_ref = get_or_create_texture_ref(&g_texture_refs, Buffer, nullptr, 0);
      flags = texture_ref->flags;
      v6 += 128;
      BYTE1(flags) = ((unsigned __int16)texture_ref->flags >> 8) | 4;
      ++v5;
      texture_ref->flags = flags;
    }
    while ( v5 < out_count );
  }
}
