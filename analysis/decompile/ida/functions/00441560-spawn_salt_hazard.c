/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_salt_hazard @ 0x441560 */
/* selector: spawn_salt_hazard */

// Exact `cRSaltManager::Add(tVector&)`: allocates one manager-owned Salt from the 40 inline slots, seeds its runtime state and inherited BOD link, and returns the slot index. Android preserves the vector-only signature; iOS v1.9 adds the owning Goldy argument.
int32_t __thiscall spawn_salt_hazard(SaltManager *manager, const Vec3 *position)
{
  int32_t result; // eax
  uint32_t *i; // edx
  Salt *v4; // esi
  BodBase *p_salt_hazard_list_head; // eax
  struct BodNode *list_next; // eax
  float angle; // [esp+0h] [ebp-Ch]

  result = 0;
  for ( i = &manager->slots[0].state; *i; i += 38 )
  {
    if ( ++result >= 40 )
      return result;
  }
  v4 = &manager->slots[result];
  v4->state = 1;
  v4->fade_alpha = 0.0;
  v4->spawn_velocity_y = g_game_base->subgame.subgame_rate * 0.033333335;
  *(Vec3 *)&v4->body.transform.position.x = *position;
  set_matrix_rotation_identity(&v4->body.transform);
  angle = ((double)next_math_random_value() - 16384.0) * 0.0001917476;
  rotate_matrix_world_y(&v4->body.transform, angle);
  v4->collision_armed = 1;
  p_salt_hazard_list_head = &g_game_base->subgame.salt_hazard_list_head;
  if ( (v4->body.bod.bod.list_flags & 0x200) != 0 )
    return report_errorf(aListAddafter);
  v4->body.bod.bod.list_prev = &p_salt_hazard_list_head->bod;
  v4->body.bod.bod.list_next = p_salt_hazard_list_head->bod.list_next;
  p_salt_hazard_list_head->bod.list_next = &v4->body.bod.bod;
  list_next = v4->body.bod.bod.list_next;
  if ( list_next )
    list_next->list_prev = &v4->body.bod.bod;
  result = v4->body.bod.bod.list_flags | 0x200;
  v4->body.bod.bod.list_flags = result;
  return result;
}
