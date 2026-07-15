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
  float *sprite; // esi
  int v6; // eax
  double v7; // st7
  tColour *v8; // eax
  float a; // eax
  float *v10; // ecx
  double v11; // st7
  float g; // eax
  Color4f color; // [esp+4h] [ebp-10h] BYREF

  if ( (g_runtime_config.render_flags & 0x10) != 0 )
  {
    sprite = (float *)allocate_sprite(g_sprite_manager, owner_player->player_slot, 33, -1, -1);
    v6 = *((_DWORD *)sprite + 1);
    sprite[26] = 0.0;
    BYTE1(v6) |= 8u;
    *((_DWORD *)sprite + 1) = v6;
    v7 = sub_garbage->owner_game->subgame_rate * 0.033333335;
    sprite[28] = 0.0;
    sprite[27] = v7;
    sprite[29] = sub_garbage->owner_game->subgame_rate * 0.41666669;
    v8 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
    sprite[11] = v8->r;
    sprite[12] = v8->g;
    sprite[13] = v8->b;
    a = v8->a;
    sprite[24] = 0.30000001;
    sprite[25] = 1.3;
    sprite[14] = a;
    v10 = sprite + 21;
    sprite += 18;
    color.r = velocity->x * 0.2;
    color.g = velocity->y * 0.2;
    v11 = velocity->z * 0.2;
    g = color.g;
    *v10 = color.r;
    sprite[12] = 0.0;
    v10[1] = g;
    color.b = v11;
    v10[2] = color.b;
    *(Vec3 *)sprite = *position;
  }
}
