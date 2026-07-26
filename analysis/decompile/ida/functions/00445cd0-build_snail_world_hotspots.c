/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_snail_world_hotspots @ 0x445cd0 */
/* selector: build_snail_world_hotspots */

// Android `cRSnail::BuildHotSpots()`: transforms the exact Snail's 19 local hotspots through two live source matrices into the world-space bank consumed by cRCutScene. The historical `update_snail_skin` label remains an alias.
void __thiscall build_snail_world_hotspots(Snail *snail)
{
  int32_t hotspot_index; // ebx
  Vec3 *hotspot_world_cursor; // ebp
  TransformMatrix *hotspot_transform; // esi
  float y; // eax
  Vec3 *hotspot_world_slot; // ecx
  float z; // edx
  Snail *v7; // [esp+10h] [ebp-10h]
  Vec3 vector; // [esp+14h] [ebp-Ch] BYREF

  v7 = snail;
  hotspot_index = 0;
  hotspot_world_cursor = snail->snail_hotspots_world;
  while ( 1 )
  {
    hotspot_transform = &snail->snail_hotspot_body.transform;
    vector = hotspot_world_cursor[-19];
    if ( hotspot_index >= 11 )
      hotspot_transform = &snail->snail_hotspot_source_body.transform;
    multiply_vector_by_matrix(&vector, *hotspot_transform);
    y = vector.y;
    hotspot_world_slot = hotspot_world_cursor;
    ++hotspot_index;
    ++hotspot_world_cursor;
    hotspot_world_slot->x = vector.x;
    z = vector.z;
    hotspot_world_slot->y = y;
    hotspot_world_slot->z = z;
    if ( hotspot_index >= 19 )
      break;
    snail = v7;
  }
}
