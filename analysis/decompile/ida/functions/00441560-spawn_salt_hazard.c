/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_salt_hazard @ 0x441560 */
/* selector: spawn_salt_hazard */

// Authored void `cRSaltManager::Add(tVector&)`: allocates one manager-owned Salt from the 40 inline slots, seeds its active state, independent fade/spawn-y/collision-latch fields, and inherited BOD link. Android's full-pool and successful exits leave a slot state and list-insertion residue in R0; iOS independently leaves this, a matrix-call residue, or an error-call residue, proving those incompatible values are incidental rather than a result. Android preserves the vector-only signature; iOS v1.9 adds the owning Goldy argument.
void __thiscall spawn_salt_hazard(SaltManager *manager, const Vec3 *position)
{
  int v2; // eax
  SaltStateStrideCursor *salt_state_cursor; // edx
  Salt *v4; // esi
  BodBase *p_salt_hazard_list_head; // eax
  struct BodNode *list_next; // eax
  float angle; // [esp+0h] [ebp-Ch]

  v2 = 0;
  for ( salt_state_cursor = (SaltStateStrideCursor *)&manager->slots[0].state; salt_state_cursor->state; ++salt_state_cursor )
  {
    if ( ++v2 >= 40 )
      return;
  }
  v4 = &manager->slots[v2];
  v4->state = SALT_STATE_ACTIVE;
  v4->fade_alpha = 0.0;
  v4->spawn_velocity_y = g_game_base->subgame.subgame_rate * 0.033333335;
  v4->body.transform.position = *position;
  set_matrix_rotation_identity(&v4->body.transform);
  angle = ((double)next_math_random_value() - 16384.0) * 0.0001917476;
  rotate_matrix_local_y(&v4->body.transform, angle);
  v4->collision_armed = 1;
  p_salt_hazard_list_head = &g_game_base->subgame.salt_hazard_list_head;
  if ( (v4->body.bod.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    v4->body.bod.bod.list_prev = &p_salt_hazard_list_head->bod;
    v4->body.bod.bod.list_next = p_salt_hazard_list_head->bod.list_next;
    p_salt_hazard_list_head->bod.list_next = &v4->body.bod.bod;
    list_next = v4->body.bod.bod.list_next;
    if ( list_next )
      list_next->list_prev = &v4->body.bod.bod;
    v4->body.bod.bod.list_flags |= 0x200u;
  }
}
