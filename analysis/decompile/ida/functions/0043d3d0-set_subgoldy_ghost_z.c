/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_subgoldy_ghost_z @ 0x43d3d0 */
/* selector: set_subgoldy_ghost_z */

// Marks the two cached SubGoldy ghost sprites visible with flag 0x40 and writes the supplied ghost z into each Sprite::position.z lane.
Sprite *__thiscall set_subgoldy_ghost_z(Player *player, float ghost_z)
{
  Sprite *result; // eax

  player->ghost_sprite_a->flags |= 0x40u;
  player->ghost_sprite_b->flags |= 0x40u;
  player->ghost_sprite_a->position.z = ghost_z;
  result = player->ghost_sprite_b;
  result->position.z = ghost_z;
  return result;
}
