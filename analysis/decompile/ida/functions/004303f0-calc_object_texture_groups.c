/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: calc_object_texture_groups @ 0x4303f0 */
/* selector: calc_object_texture_groups */

// Collapses contiguous face quads by texture group for one render object; iOS RObject.o names this `cRObject::CalcTextureGroups()`.
void __thiscall calc_object_texture_groups(Object *object)
{
  int i; // ebp
  ObjectFaceQuad *facequads; // eax
  int v4; // ebx
  int32_t v5; // edi
  TextureRef *texture_ref; // edx
  int v7; // ecx
  TextureRef *v8; // eax

  for ( i = 0; i < 2; ++i )
  {
    facequads = object->facequads;
    v4 = 0;
    v5 = 0;
    texture_ref = facequads->texture_ref;
    if ( object->facequad_count > 0 )
    {
      v7 = 0;
      do
      {
        if ( (BYTE1(object->flags) & 4) != 0 )
        {
          facequads[v7].flags |= 2u;
          v8 = object->facequads[v7].texture_ref;
          v8->flags |= 0x20u;
        }
        facequads = object->facequads;
        if ( facequads[v7].texture_ref != texture_ref || (facequads[v7].flags & 0x10) != 0 )
        {
          if ( i == 1 )
            object->texture_group_ends[v4] = v5;
          facequads = object->facequads;
          ++v4;
          texture_ref = facequads[v7].texture_ref;
        }
        ++v5;
        ++v7;
      }
      while ( v5 < object->facequad_count );
    }
    if ( i == 1 )
    {
      object->texture_group_ends[v4] = v5;
    }
    else if ( !i )
    {
      request_object_texture_groups(object, v4 + 1);
    }
  }
}
