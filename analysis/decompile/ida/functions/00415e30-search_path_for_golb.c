/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: search_path_for_golb @ 0x415e30 */
/* selector: search_path_for_golb */

ContactTargetEntry *__thiscall search_path_for_golb(ContactTargetRegistry *registry, const Vec3 *position)
{
  ContactTargetEntry *result; // eax
  int32_t v4; // ebx
  float *p_z; // esi
  double v6; // st7
  double v7; // st7
  float v8; // [esp+8h] [ebp-20h]
  ContactTargetEntry *v9; // [esp+Ch] [ebp-1Ch]
  float v10; // [esp+10h] [ebp-18h]
  float v11; // [esp+14h] [ebp-14h]
  float v12; // [esp+18h] [ebp-10h]
  float v13[3]; // [esp+1Ch] [ebp-Ch] BYREF

  result = nullptr;
  v4 = 0;
  v9 = nullptr;
  v8 = 1000000000.0;
  if ( registry->count > 0 )
  {
    p_z = &registry->entries[0].position.z;
    do
    {
      v10 = *(p_z - 2) - position->x;
      v6 = *(p_z - 1) - position->y;
      v13[0] = v10;
      v11 = v6;
      v7 = *p_z - position->z;
      v13[1] = v11;
      v12 = v7;
      v13[2] = v12;
      if ( v12 > 0.0 && v12 < 30.0 )
      {
        vector_magnitude(v13);
        if ( v12 < (double)v8 )
        {
          v8 = v7;
          v9 = (ContactTargetEntry *)(p_z - 3);
        }
      }
      ++v4;
      p_z += 6;
    }
    while ( v4 < registry->count );
    return v9;
  }
  return result;
}

