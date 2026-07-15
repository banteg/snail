/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_golb_smoke @ 0x415c60 */
/* selector: spawn_golb_smoke */

// Side-effect-only `GolbShot` smoke emitter that borrows the owning subgame rate and projectile velocity to seed one sprite at the supplied world position.
void __thiscall spawn_golb_smoke(GolbShot *shot, Vec3 *position)
{
  float *sprite; // esi
  int v4; // ecx
  double v5; // st7
  tColour *v6; // eax
  float a; // eax
  float *v8; // ecx
  double v9; // st7
  float g; // eax
  Color4f color; // [esp+8h] [ebp-10h] BYREF

  sprite = (float *)allocate_sprite(g_sprite_manager, shot->owner_player->player_slot, 128, -1, -1);
  v4 = *((_DWORD *)sprite + 1);
  sprite[26] = 0.0;
  BYTE1(v4) |= 8u;
  *((_DWORD *)sprite + 1) = v4;
  v5 = shot->game->subgame_rate * 0.16666667;
  sprite[28] = 0.0;
  sprite[27] = v5;
  sprite[29] = shot->game->subgame_rate * 0.41666669;
  v6 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  sprite[11] = v6->r;
  sprite[12] = v6->g;
  sprite[13] = v6->b;
  a = v6->a;
  sprite[24] = 0.1;
  sprite[25] = 0.5;
  sprite[14] = a;
  v8 = sprite + 21;
  sprite += 18;
  color.r = shot->velocity.x * 0.40000001;
  color.g = shot->velocity.y * 0.40000001;
  v9 = shot->velocity.z * 0.40000001;
  g = color.g;
  *v8 = color.r;
  sprite[12] = 0.0;
  v8[1] = g;
  color.b = v9;
  v8[2] = color.b;
  *(Vec3 *)sprite = *position;
}
