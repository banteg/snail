/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_garbage_smoke_particle @ 0x43d5a0 */
/* selector: spawn_garbage_smoke_particle */

// Emits the garbage impact smoke owned by `SubGarbage`; Android retains the corresponding authored member as `cRSubGarbage::Smoke(tVector&, tVector&, cRSubGoldy*)`. The source-shaped Windows reconstruction is 85.14% with nine clean masked operands.
void __thiscall spawn_garbage_smoke_particle(
        SubGarbage *sub_garbage,
        Vec3 *position,
        Vec3 *velocity,
        Player *owner_player)
{
  Sprite *sprite; // esi
  SpriteFlag flags; // eax
  double v7; // st7
  tColour *v8; // eax
  float a; // eax
  Vec3 *p_velocity; // ecx
  double v11; // st7
  float g; // eax
  Color4f color; // [esp+4h] [ebp-10h] BYREF

  if ( (g_runtime_config.render_flags & 0x10) != 0 )
  {
    sprite = allocate_sprite(&g_sprite_manager, owner_player->player_slot, 33, -1, -1);
    flags = sprite->flags;
    sprite->progress = 0.0;
    BYTE1(flags) |= 8u;
    sprite->flags = flags;
    v7 = sub_garbage->owner_game->subgame_rate * 0.033333335;
    sprite->lifetime = 0.0;
    sprite->progress_step = v7;
    sprite->lifetime_step = sub_garbage->owner_game->subgame_rate * 0.41666669;
    v8 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
    sprite->color.r = v8->r;
    sprite->color.g = v8->g;
    sprite->color.b = v8->b;
    a = v8->a;
    sprite->size_start = 0.30000001;
    sprite->size_end = 1.3;
    sprite->color.a = a;
    p_velocity = &sprite->velocity;
    sprite = (Sprite *)((char *)sprite + 72);
    color.r = velocity->x * 0.2;
    color.g = velocity->y * 0.2;
    v11 = velocity->z * 0.2;
    g = color.g;
    p_velocity->x = color.r;
    sprite->color.g = 0.0;
    p_velocity->y = g;
    color.b = v11;
    p_velocity->z = color.b;
    *(Vec3 *)&sprite->object_ref = *position;
  }
}
