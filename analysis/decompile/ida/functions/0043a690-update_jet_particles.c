/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_jet_particles @ 0x43a690 */
/* selector: update_jet_particles */

// Windows `SubHover::update_jet_particles`, authored as `cRSubHover::Jets`: projects the owner's 15-by-2 jet exhaust grid backward from the authored snail hotspots and occasionally emits a detached puff with 85% of Player velocity.
void __thiscall update_jet_particles(SubHover *sub_hover)
{
  int v2; // esi
  int v3; // ecx
  double v4; // st7
  double v5; // st7
  JetParticleSlot *v6; // eax
  float *p_x; // eax
  Sprite *sprite; // esi
  SpriteFlag flags; // eax
  tColour *v10; // eax
  float a; // eax
  float *v12; // ecx
  double v13; // st7
  int v14; // [esp+4h] [ebp-50h]
  int v15; // [esp+8h] [ebp-4Ch]
  float v16; // [esp+Ch] [ebp-48h]
  float v17; // [esp+10h] [ebp-44h]
  float v18; // [esp+14h] [ebp-40h]
  float v19; // [esp+18h] [ebp-3Ch]
  float x; // [esp+20h] [ebp-34h]
  float v21; // [esp+20h] [ebp-34h]
  float y; // [esp+24h] [ebp-30h]
  float v23; // [esp+24h] [ebp-30h]
  float z; // [esp+28h] [ebp-2Ch]
  float v25; // [esp+28h] [ebp-2Ch]
  float v26; // [esp+2Ch] [ebp-28h]
  float v27; // [esp+30h] [ebp-24h]
  float v28; // [esp+34h] [ebp-20h]
  float v29; // [esp+38h] [ebp-1Ch]
  float v30; // [esp+3Ch] [ebp-18h]
  Color4f color; // [esp+44h] [ebp-10h] BYREF

  if ( sub_hover->state == SUB_HOVER_STATE_ACTIVE
    && sub_hover->game->player.presentation.jetpack_channel.anim_manager.active_animation == sub_hover->game->player.presentation.jetpack_channel.animation_slots[0].body.bod.object->animation )
  {
    v19 = (double)next_math_random_value() * 0.0000015258789 + 0.40000001;
    v2 = 0;
    v14 = 0;
    v18 = (double)next_math_random_value() * 0.0000015258789 + 0.12;
    while ( 1 )
    {
      v3 = 0;
      v15 = 0;
      v16 = (double)v14 * 0.071428575;
      v17 = (1.0 - v16) * v18 * sub_hover->warning_intensity;
      do
      {
        if ( v3 )
        {
          x = sub_hover->game->player.presentation.snail_hotspots_world[14].x;
          y = sub_hover->game->player.presentation.snail_hotspots_world[14].y;
          z = sub_hover->game->player.presentation.snail_hotspots_world[14].z;
        }
        else
        {
          x = sub_hover->game->player.presentation.snail_hotspots_world[13].x;
          y = sub_hover->game->player.presentation.snail_hotspots_world[13].y;
          z = sub_hover->game->player.presentation.snail_hotspots_world[13].z;
        }
        v4 = -(v16 * v19 * sub_hover->warning_intensity);
        v29 = v4 * sub_hover->player->presentation.body.transform.basis_forward.x;
        v30 = v4 * sub_hover->player->presentation.body.transform.basis_forward.y;
        v5 = v4 * sub_hover->player->presentation.body.transform.basis_forward.z;
        v6 = &sub_hover->particle_slots[2 * v2 + v3];
        v21 = x + v29;
        v6->sprite->size_end = v17;
        v6->sprite->size_start = v17;
        v23 = y + v30;
        p_x = &v6->sprite->position.x;
        *p_x = v21;
        p_x[1] = v23;
        v25 = z + v5;
        p_x[2] = v25;
        if ( v2 == 14 )
        {
          if ( (double)next_math_random_value() * 0.000030517578 > 0.89999998 )
          {
            sprite = allocate_sprite((SpriteManager *)g_sprite_manager, sub_hover->game->player.player_slot, 33, -1, -1);
            flags = sprite->flags;
            BYTE1(flags) |= 8u;
            sprite->flags = flags;
            sprite->progress = 0.0;
            sprite->progress_step = 0.1388889;
            sprite->lifetime = 0.0;
            sprite->lifetime_step = 0.0;
            v10 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
            sprite->color.r = v10->r;
            sprite->color.g = v10->g;
            sprite->color.b = v10->b;
            a = v10->a;
            sprite->size_start = 0.1;
            sprite->size_end = 0.30000001;
            sprite->color.a = a;
            v12 = &sprite->velocity.x;
            sprite = (Sprite *)((char *)sprite + 72);
            v26 = sub_hover->game->player.velocity.x * 0.85000002;
            v27 = sub_hover->game->player.velocity.y * 0.85000002;
            v13 = sub_hover->game->player.velocity.z * 0.85000002;
            sprite->color.g = 0.001;
            *v12 = v26;
            *(float *)&sprite->object_ref = v21;
            v28 = v13;
            v12[1] = v27;
            *(float *)&sprite->flags = v23;
            v12[2] = v28;
            *(float *)&sprite->owner = v25;
            v2 = v14;
          }
          v3 = v15;
        }
        v15 = ++v3;
      }
      while ( v3 < 2 );
      v14 = v2 + 1;
      if ( v2 + 1 >= 15 )
        break;
      ++v2;
    }
  }
}
