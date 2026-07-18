/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_snail_skin @ 0x445cd0 */
/* selector: update_snail_skin */

// Stable Windows name for Android `cRSnail::BuildHotSpots()`: transforms the exact Snail's 19 local hotspots through two live source matrices into the world-space bank consumed by cRCutScene.
void __thiscall update_snail_skin(Snail *snail)
{
  int v1; // ebx
  Vec3 *snail_hotspots_world; // ebp
  TransformMatrix *p_transform; // esi
  float y; // eax
  Vec3 *v5; // ecx
  float z; // edx
  TransformMatrix v7; // [esp-40h] [ebp-60h] BYREF
  Snail *v8; // [esp+10h] [ebp-10h]
  Vec3 vector; // [esp+14h] [ebp-Ch] BYREF

  v8 = snail;
  v1 = 0;
  snail_hotspots_world = snail->snail_hotspots_world;
  while ( 1 )
  {
    p_transform = &snail->snail_hotspot_body.transform;
    vector = snail_hotspots_world[-19];
    if ( v1 >= 11 )
      p_transform = &snail->snail_hotspot_source_body.transform;
    qmemcpy(&v7, p_transform, sizeof(v7));
    multiply_vector_by_matrix(&vector, v7);
    y = vector.y;
    v5 = snail_hotspots_world;
    ++v1;
    ++snail_hotspots_world;
    v5->x = vector.x;
    z = vector.z;
    v5->y = y;
    v5->z = z;
    if ( v1 >= 19 )
      break;
    snail = v8;
  }
}
