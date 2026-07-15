/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_subgoldy_ghost @ 0x43d230 */
/* selector: initialize_subgoldy_ghost */

// Void `Player` member that initializes Goldy's paired ghost sprites for the active player slot. Its sole caller discards EAX and the terminal value is only the second sprite's cleared visibility flags. Cross-port iOS symbols match this helper to `cRSubGoldy::GhostInit(int)` in v1.5 and `cRSubGoldy::GhostInit(int, int)` in v1.9.
void __thiscall initialize_subgoldy_ghost(Player *player, int32_t owner)
{
  Sprite *sprite; // eax
  SpriteFlag flags; // ecx
  Sprite *v5; // eax
  SpriteFlag v6; // ecx
  Color4f color; // [esp+10h] [ebp-10h] BYREF

  sprite = (Sprite *)allocate_sprite(g_sprite_manager, owner, 159, -1, -1);
  player->ghost_sprite_a = sprite;
  flags = sprite->flags;
  BYTE1(flags) |= 8u;
  sprite->flags = flags;
  player->ghost_sprite_a->progress = 0.0;
  player->ghost_sprite_a->progress_step = 0.0;
  player->ghost_sprite_a->gravity_step = 0.0;
  player->ghost_sprite_a->color = *set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  player->ghost_sprite_a->size_start = 0.5;
  player->ghost_sprite_a->size_end = 0.5;
  player->ghost_sprite_a->position.x = 4.5;
  player->ghost_sprite_a->position.y = 1.0;
  player->ghost_sprite_a->position.z = 0.0;
  v5 = (Sprite *)allocate_sprite(g_sprite_manager, owner, 159, -1, -1);
  player->ghost_sprite_b = v5;
  v6 = v5->flags;
  BYTE1(v6) |= 8u;
  v5->flags = v6;
  player->ghost_sprite_b->progress = 0.0;
  player->ghost_sprite_b->progress_step = 0.0;
  player->ghost_sprite_b->gravity_step = 0.0;
  player->ghost_sprite_b->color = *set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  player->ghost_sprite_b->size_start = 0.5;
  player->ghost_sprite_b->size_end = 0.5;
  player->ghost_sprite_b->position.x = -4.5;
  player->ghost_sprite_b->position.y = 1.0;
  player->ghost_sprite_b->position.z = 0.0;
  player->ghost_sprite_a->flags &= ~0x40u;
  player->ghost_sprite_b->flags &= ~0x40u;
}
