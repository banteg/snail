/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_sprite @ 0x44df30 */
/* selector: update_sprite */

// Runs one live sprite's per-frame state update; iOS RSprite.o names this `cRSprite::AI()`.
void __thiscall update_sprite(Sprite *sprite)
{
  SpriteFlag flags; // edx
  double v2; // st7
  unsigned __int8 v4; // c0
  unsigned __int8 v5; // c3
  double v6; // st7
  SpriteFlag v7; // eax
  SpriteFlag v8; // eax
  __int16 v9; // si
  double v10; // st7
  unsigned __int8 v12; // c0
  unsigned __int8 v13; // c3
  int32_t v14; // edx
  int32_t frame_count; // eax

  flags = sprite->flags;
  if ( (BYTE1(flags) & 8) != 0 && g_sprite_manager[0] )
    return;
  if ( (flags & 8) != 0 )
  {
    sprite->flags = flags & 0xFFFFFFF7;
LABEL_12:
    v7 = sprite->flags;
    LOBYTE(v7) = v7 & 0xF7;
    sprite->flags = v7;
    sprite->previous_position = sprite->position;
    sprite->position.x = sprite->velocity.x + sprite->position.x;
    sprite->position.y = sprite->velocity.y + sprite->position.y;
    sprite->position.z = sprite->velocity.z + sprite->position.z;
    sprite->velocity.y = sprite->gravity_step + sprite->velocity.y;
    sprite->facing_angle = sprite->facing_angle_step + sprite->facing_angle;
    v8 = sprite->flags;
    if ( sprite->lifetime_step <= 0.0 )
      BYTE1(v8) &= ~2u;
    else
      BYTE1(v8) |= 2u;
    v9 = v8;
    sprite->flags = v8;
    if ( (v8 & 0x2000) != 0 )
    {
      v10 = sprite->frame_progress_step + sprite->frame_progress;
      sprite->frame_progress = v10;
      if ( !(v12 | v13) )
      {
        v14 = sprite->frame_step + sprite->frame;
        frame_count = sprite->frame_count;
        sprite->frame_progress = v10 - 1.0;
        sprite->frame = v14;
        if ( (v9 & 0x4000) != 0 )
        {
          if ( v14 == frame_count )
          {
            sprite->frame_step = -1;
            sprite->frame = frame_count - 1;
          }
          if ( sprite->frame == -1 )
          {
            sprite->frame = 0;
            sprite->frame_step = 1;
          }
        }
        else if ( v14 == frame_count )
        {
          sprite->frame = 0;
        }
        set_sprite_texture_ref(sprite, sprite->texture_id, sprite->frame);
      }
    }
    return;
  }
  v2 = sprite->progress_step + sprite->progress;
  sprite->progress = v2;
  if ( v4 | v5 && v2 >= 0.0 )
  {
    if ( sprite->lifetime_step != 0.0 )
    {
      v6 = sprite->lifetime_step + sprite->lifetime;
      sprite->lifetime = v6;
      if ( v6 > 1.0 )
        sprite->lifetime_step = 0.0;
    }
    goto LABEL_12;
  }
  sprite->progress = 1.0;
  if ( (BYTE1(flags) & 1) == 0 )
    kill_sprite(sprite);
}
