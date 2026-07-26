/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_sprite_tail @ 0x44e410 */
/* selector: build_sprite_tail */

// Windows `cRSprite::BuildTail(tMatrix*)`: derives the sprite tail/facing angle at `+0x7c` from its camera-space motion delta, optionally throttled by the refresh timer at `+0x8c/+0x90`. Android and iOS independently preserve the exact authored owner, symbol, and corresponding body; the former `update_sprite_facing_angle` label remains a compatibility alias.
void __thiscall build_sprite_tail(Sprite *sprite, const struct TransformMatrix *matrix)
{
  double v3; // st7
  double v4; // st7
  Vec3 *v5; // eax
  double v6; // st7
  double v7; // st7
  double v8; // st7
  double v9; // st7
  Vec3 *v10; // eax
  float x; // [esp-8h] [ebp-24h]
  float v12; // [esp-8h] [ebp-24h]
  float y; // [esp-4h] [ebp-20h]
  float v14; // [esp-4h] [ebp-20h]
  float v15; // [esp+4h] [ebp-18h]
  float v16; // [esp+4h] [ebp-18h]
  float v17; // [esp+8h] [ebp-14h]
  float v18; // [esp+8h] [ebp-14h]
  float v19; // [esp+Ch] [ebp-10h]
  float v20; // [esp+Ch] [ebp-10h]
  Vec3 vector; // [esp+10h] [ebp-Ch] BYREF

  if ( (sprite->flags & 0x400) != 0 )
  {
    if ( sprite->facing_refresh_progress == 0.0 )
    {
      v15 = sprite->position.x - sprite->previous_position.x;
      v3 = sprite->position.y - sprite->previous_position.y;
      vector.x = v15;
      v17 = v3;
      v4 = sprite->position.z - sprite->previous_position.z;
      vector.y = v17;
      v19 = v4;
      vector.z = v19;
      v5 = rotate_vector_by_matrix(&vector, matrix);
      y = v5->y;
      x = v5->x;
      vector.z = v5->z;
      v6 = atan2_positive(x, y);
      sprite->facing_refresh_progress = 0.001;
      sprite->facing_angle = v6 + 7.0685835;
    }
    v7 = sprite->facing_refresh_step + sprite->facing_refresh_progress;
    sprite->facing_refresh_progress = v7;
    if ( v7 > 1.0 )
      sprite->facing_refresh_progress = 0.0;
  }
  else
  {
    v16 = sprite->position.x - sprite->previous_position.x;
    v8 = sprite->position.y - sprite->previous_position.y;
    vector.x = v16;
    v18 = v8;
    v9 = sprite->position.z - sprite->previous_position.z;
    vector.y = v18;
    v20 = v9;
    vector.z = v20;
    v10 = rotate_vector_by_matrix(&vector, matrix);
    v14 = v10->y;
    v12 = v10->x;
    vector.z = v10->z;
    sprite->facing_angle = atan2_positive(v12, v14) + 7.0685835;
  }
}
