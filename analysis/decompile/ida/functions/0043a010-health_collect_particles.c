/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: health_collect_particles @ 0x43a010 */
/* selector: health_collect_particles */

// Exact `Player` collection burst for one `SubHealth`, emitting eight particles from the pickup sprite. Android and iOS retain the authored member as `cRSubGoldy::HealthCollect(cRSubHealth*)`.
void __thiscall health_collect_particles(Player *player, SubHealth *pickup)
{
  Sprite *sprite; // esi
  tColour *v4; // eax
  float *p_x; // edi
  float a; // eax
  float v7; // ebp
  bool v8; // cc
  int v9; // [esp+4h] [ebp-34h]
  float v10; // [esp+8h] [ebp-30h]
  SpriteFlag v11; // [esp+8h] [ebp-30h]
  int32_t v12; // [esp+Ch] [ebp-2Ch]
  float v13; // [esp+10h] [ebp-28h]
  float v14; // [esp+20h] [ebp-18h]
  float v15; // [esp+24h] [ebp-14h]
  Color4f color; // [esp+28h] [ebp-10h] BYREF

  if ( (g_runtime_config.render_flags & 0x10) != 0 )
  {
    v9 = 0;
    do
    {
      sprite = allocate_sprite((SpriteManager *)g_sprite_manager, player->player_slot, 128, -1, -1);
      sprite->flags |= 0x800u;
      sprite->progress = 0.0;
      sprite->progress_step = 0.041666668;
      sprite->gravity_step = -0.00019999999;
      v4 = set_color_rgba((tColour *)&color, 1.0, 0.75, 0.75, 1.0);
      sprite->color.r = v4->r;
      p_x = &sprite->position.x;
      sprite->color.g = v4->g;
      sprite->color.b = v4->b;
      a = v4->a;
      sprite->size_start = 0.1;
      sprite->size_end = 0.5;
      sprite->color.a = a;
      v10 = (double)v9 * 0.78539819;
      v7 = v10;
      sprite->position = pickup->sprite->position;
      *(float *)&v12 = player->velocity.z * 0.40000001;
      *(float *)&v11 = cosine(v10) * 0.015;
      sprite = (Sprite *)((char *)sprite + 84);
      v13 = sine(v7) * 0.015;
      *(float *)&sprite->object_ref = v13;
      sprite->flags = v11;
      sprite->owner = v12;
      v14 = player->velocity.y * 3.0;
      v15 = player->velocity.z * 3.0;
      *p_x = player->velocity.x * 3.0 + *p_x;
      p_x[1] = v14 + p_x[1];
      v8 = ++v9 < 8;
      p_x[2] = v15 + p_x[2];
    }
    while ( v8 );
  }
}
