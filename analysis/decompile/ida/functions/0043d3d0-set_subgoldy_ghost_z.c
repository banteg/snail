/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_subgoldy_ghost_z @ 0x43d3d0 */
/* selector: set_subgoldy_ghost_z */

// Exact void Windows `cRSubGoldy::GhostDraw(float)`: marks the two cached Goldy ghost sprites visible with flag 0x40 and writes the supplied z into each `Sprite::position.z` lane. Android preserves the same two borrowed sprite slots, flag updates, and z stores.
void __thiscall set_subgoldy_ghost_z(Player *player, float ghost_z)
{
  player->ghost_sprite_a->flags |= 0x40u;
  player->ghost_sprite_b->flags |= 0x40u;
  player->ghost_sprite_a->position.z = ghost_z;
  player->ghost_sprite_b->position.z = ghost_z;
}
