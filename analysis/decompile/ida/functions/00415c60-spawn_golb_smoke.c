/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_golb_smoke @ 0x415c60 */
/* selector: spawn_golb_smoke */

// Side-effect-only `cRSubGolb::Smoke(tVector)`/`GolbShot` member that borrows the owning subgame rate and projectile velocity to seed one sprite at the supplied world position. Android preserves the owner and all Sprite initialization lanes.
void __thiscall spawn_golb_smoke(GolbShot *shot, Vec3 *position)
{
  Sprite *sprite; // esi
  SpriteFlag flags; // ecx
  double v5; // st7
  tColour *v6; // eax
  float a; // eax
  Vec3 *p_velocity; // ecx
  double v9; // st7
  float g; // eax
  Color4f color; // [esp+8h] [ebp-10h] BYREF

  sprite = allocate_sprite(&g_sprite_manager, shot->owner_player->player_slot, 128, -1, -1);
  flags = sprite->flags;
  sprite->progress = 0.0;
  BYTE1(flags) |= 8u;
  sprite->flags = flags;
  v5 = shot->game->subgame_rate * 0.16666667;
  sprite->lifetime = 0.0;
  sprite->progress_step = v5;
  sprite->lifetime_step = shot->game->subgame_rate * 0.41666669;
  v6 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  sprite->color.r = v6->r;
  sprite->color.g = v6->g;
  sprite->color.b = v6->b;
  a = v6->a;
  sprite->size_start = 0.1;
  sprite->size_end = 0.5;
  sprite->color.a = a;
  p_velocity = &sprite->velocity;
  sprite = (Sprite *)((char *)sprite + 72);
  color.r = shot->velocity.x * 0.40000001;
  color.g = shot->velocity.y * 0.40000001;
  v9 = shot->velocity.z * 0.40000001;
  g = color.g;
  p_velocity->x = color.r;
  sprite->color.g = 0.0;
  p_velocity->y = g;
  color.b = v9;
  p_velocity->z = color.b;
  *(Vec3 *)&sprite->object_ref = *position;
}
