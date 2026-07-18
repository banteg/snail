/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: sort_object_faces_by_texture_group @ 0x419fd0 */
/* selector: sort_object_faces_by_texture_group */

// Sorts one Object's 0x30-byte face records into contiguous texture runs using independent scan and insertion cursors, swapping whole ObjectFaceQuad records so calc_object_texture_groups can retain cumulative run ends.
void __cdecl sort_object_faces_by_texture_group(Object *object)
{
  Object *v1; // esi
  int32_t v2; // ebp
  int32_t facequad_count; // eax
  ObjectFaceQuad *facequads; // ecx
  int32_t v5; // ebx
  ObjectFaceQuad *v6; // edx
  ObjectFaceQuad *v7; // eax
  ObjectFaceQuad *v8; // edi
  int v9; // [esp+8h] [ebp-40h]
  int v10; // [esp+Ch] [ebp-3Ch]
  TextureRef *texture_ref; // [esp+10h] [ebp-38h]
  ObjectFaceQuad *v12; // [esp+14h] [ebp-34h]
  _BYTE v13[48]; // [esp+18h] [ebp-30h] BYREF

  v1 = object;
  v2 = 0;
  v10 = 0;
  facequad_count = object->facequad_count;
  facequads = object->facequads;
  v12 = facequads;
  if ( facequad_count > 0 )
  {
    do
    {
      v5 = v2 + 1;
      texture_ref = facequads[v2].texture_ref;
      if ( v2 + 1 < facequad_count )
      {
        v6 = &facequads[v5];
        v9 = v2 + 1;
        v7 = v6;
        do
        {
          if ( v6->texture_ref == texture_ref )
          {
            ++v2;
            if ( v5 == v9 )
            {
              ++v7;
              ++v9;
            }
            else
            {
              qmemcpy(v13, v7, sizeof(v13));
              v8 = v7++;
              qmemcpy(v8, v6, sizeof(ObjectFaceQuad));
              qmemcpy(v6, v13, sizeof(ObjectFaceQuad));
              ++v9;
              v1 = object;
              ++v10;
              facequads = v12;
            }
          }
          ++v5;
          ++v6;
        }
        while ( v5 < v1->facequad_count );
      }
      facequad_count = v1->facequad_count;
      ++v2;
    }
    while ( v2 < facequad_count );
  }
}
