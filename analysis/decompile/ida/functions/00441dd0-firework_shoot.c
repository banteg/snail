/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: firework_shoot @ 0x441dd0 */
/* selector: firework_shoot */

// Windows `FireWork::firework_shoot`, authored as `cRFireWork::Shoot`: spawns a randomized sprite burst through the exact empty one-byte child at `Player +0x1d0`. The receiver is unused by the body but is passed by the native thiscall; Android and iOS retain the owner with a by-value vector signature.
void __thiscall firework_shoot(FireWork *firework, Vec3 *position, int32_t owner, int32_t texture_id, int32_t count)
{
  Sprite *sprite; // esi
  SpriteFlag flags; // ecx
  double duration_random; // st7
  float green; // [esp+0h] [ebp-28h]
  int32_t remaining; // [esp+18h] [ebp-10h]
  float velocity_x; // [esp+1Ch] [ebp-Ch]
  float velocity_z; // [esp+30h] [ebp+8h]
  float velocity_y; // [esp+34h] [ebp+Ch]
  float red; // [esp+38h] [ebp+10h]
  int32_t velocity_x_random; // [esp+38h] [ebp+10h]

  if ( (g_runtime_config.render_flags & 0x10) != 0 && count > 0 )
  {
    remaining = count;
    do
    {
      sprite = allocate_sprite(&g_sprite_manager, owner, texture_id, -1, -1);
      flags = sprite->flags;
      sprite->draw_mode = 10;
      sprite->corner_scale = 4.0;
      sprite->flags = flags | 0x802;
      sprite->progress = 0.0;
      duration_random = random_float_below(0.5);
      sprite->lifetime = 0.0;
      sprite->lifetime_step = 0.27777779;
      sprite->progress_step = 1.0 / ((duration_random + 0.80000001) * 60.0);
      red = random_float_below(0.30000001) + 0.69999999;
      green = red * 0.5;
      set_color_rgb(&sprite->color, red, green, 0.0);
      sprite->size_start = 0.5;
      sprite->size_end = 0.1;
      velocity_z = ((double)next_math_random_value() - 16384.0) * 0.000012207031;
      velocity_y = ((double)next_math_random_value() - 16384.0) * 0.000018310548 + 0.1;
      velocity_x_random = next_math_random_value();
      sprite->depth_offset = 0.0;
      velocity_x = ((double)velocity_x_random - 16384.0) * 0.000012207031;
      sprite->velocity.x = velocity_x;
      sprite->velocity.y = velocity_y;
      sprite->velocity.z = velocity_z;
      sprite->position = *position;
      --remaining;
    }
    while ( remaining );
  }
}
