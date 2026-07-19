/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_sub_lazer_projectile @ 0x441670 */
/* selector: spawn_sub_lazer_projectile */

// Exact Windows `cRSubLazer::Shoot` implementation: sets one manager-owned actor to SUB_LAZER_STATE_ACTIVE, stores body position at +0x68 and velocity at +0x8c, resets its bob phase, links the inherited BOD node, and refreshes the forward basis. Android preserves the two-vector signature; iOS v1.9 adds the owning Goldy argument.
void __thiscall spawn_sub_lazer_projectile(SubLazer *sub_lazer, const Vec3 *origin, const Vec3 *direction)
{
  TransformMatrix *p_transform; // edi
  float z; // edx
  SubgameRuntime *owner_game; // eax
  uint32_t list_flags; // edx
  double v8; // st7
  struct BodNode *p_bod; // eax
  struct BodNode *list_next; // eax

  p_transform = &sub_lazer->body.transform;
  sub_lazer->state = SUB_LAZER_STATE_ACTIVE;
  set_matrix_identity(&sub_lazer->body.transform);
  sub_lazer->body.transform.position.x = origin->x;
  sub_lazer->body.transform.position.y = origin->y;
  sub_lazer->body.transform.position.z = origin->z;
  sub_lazer->velocity.x = direction->x;
  sub_lazer->velocity.y = direction->y;
  z = direction->z;
  sub_lazer->sprite_bob_phase = 0.0;
  sub_lazer->velocity.z = z;
  owner_game = sub_lazer->owner_game;
  list_flags = sub_lazer->body.bod.bod.list_flags;
  v8 = owner_game->subgame_rate * 0.0055555557;
  p_bod = &owner_game->barrier_sub_lazer_list_head.bod;
  sub_lazer->sprite_bob_phase_step = v8;
  if ( (list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
    set_matrix_z_direction(p_transform, &sub_lazer->velocity);
  }
  else
  {
    sub_lazer->body.bod.bod.list_prev = p_bod;
    sub_lazer->body.bod.bod.list_next = p_bod->list_next;
    p_bod->list_next = &sub_lazer->body.bod.bod;
    list_next = sub_lazer->body.bod.bod.list_next;
    if ( list_next )
      list_next->list_prev = &sub_lazer->body.bod.bod;
    sub_lazer->body.bod.bod.list_flags |= 0x200u;
    set_matrix_z_direction(p_transform, &sub_lazer->velocity);
  }
}
