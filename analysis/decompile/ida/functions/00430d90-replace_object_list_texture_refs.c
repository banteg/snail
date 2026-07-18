/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: replace_object_list_texture_refs @ 0x430d90 */
/* selector: replace_object_list_texture_refs */

// Void Windows cRObjects texture-replacement member: walks the owned contiguous Object list and replaces one borrowed TextureRef with another across face quads and any already-built grouped-render texture tables. Android retains the same owner and behavior as cRObjects::ReTextureObjects.
void __thiscall replace_object_list_texture_refs(
        ObjectList *object_list,
        TextureRef *new_texture,
        TextureRef *old_texture)
{
  int v4; // eax
  uint8_t *v5; // eax
  int v6; // esi
  int v7; // edx
  int v8; // ecx
  bool v9; // zf
  TextureRef **v10; // ecx
  bool v11; // cc
  int v12; // [esp+4h] [ebp-8h]
  int v13; // [esp+8h] [ebp-4h]

  v4 = 0;
  v12 = 0;
  if ( object_list->count > 0 )
  {
    v13 = 0;
    do
    {
      v5 = &object_list->objects->_pad_00[v4];
      if ( *((_DWORD *)v5 + 11) )
      {
        v6 = 0;
        if ( *((int *)v5 + 21) > 0 )
        {
          v7 = 0;
          do
          {
            v8 = *((_DWORD *)v5 + 23);
            v9 = *(_DWORD *)(v7 + v8 + 12) == (_DWORD)old_texture;
            v10 = (TextureRef **)(v7 + v8 + 12);
            if ( v9 )
              *v10 = new_texture;
            ++v6;
            v7 += 48;
          }
          while ( v6 < *((_DWORD *)v5 + 21) );
        }
        replace_object_group_texture_refs(v5, (int)new_texture, (int)old_texture);
      }
      v4 = v13 + 220;
      v11 = ++v12 < object_list->count;
      v13 += 220;
    }
    while ( v11 );
  }
}
