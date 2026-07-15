/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_golb_ai @ 0x414820 */
/* selector: update_golb_ai */

// Advances one live Golb shot actor, borrowing the authored `SubLoc`/`Path` follow owners and the shared `SubGarbagePool` collision chain for straight-flight or path-follow motion, impact transitions, trail effects, and final cleanup.
void __thiscall update_golb_ai(GolbShot *shot)
{
  GolbPathFollowState *p_path_follow; // ecx
  float y; // edx
  float z; // ecx
  Vec3 *p_velocity; // edi
  Vec4 *p_position; // esi
  int32_t kind; // eax
  double v8; // st7
  double v9; // st7
  double v10; // st7
  double homing_blend; // st7
  double v12; // st7
  double v13; // st6
  double v14; // st6
  double v15; // st5
  double path_entry_z_latch; // st7
  float v17; // eax
  TrackRowCell *track_grid_cell_at_world_position; // eax
  TrackRowCell *v19; // edi
  int32_t v20; // eax
  int v21; // eax
  double v22; // st7
  unsigned __int8 v24; // c0
  unsigned __int8 v25; // c3
  double v26; // st7
  double v27; // st7
  double v28; // st7
  float *v29; // ecx
  double v30; // st7
  double v31; // st7
  double v32; // st7
  double v33; // st7
  double v34; // st7
  double v35; // st7
  Vec4 *v36; // edi
  double v37; // st7
  double v38; // st7
  float x; // ecx
  float v40; // edx
  float v41; // eax
  Player *owner_player; // ecx
  SubGarbage *active_head; // esi
  double v44; // st7
  char v46; // c0
  int v47; // esi
  int j; // ebx
  uint8_t *v49; // eax
  int v50; // ecx
  double v51; // st7
  char v53; // c0
  double v54; // st7
  float v55; // ecx
  int32_t v56; // eax
  SubGarbage *i; // esi
  double v58; // st7
  float v59; // edx
  float v60; // [esp+10h] [ebp-70h]
  float v61; // [esp+10h] [ebp-70h]
  Vec3 v62; // [esp+14h] [ebp-6Ch] BYREF
  Vec3 vector; // [esp+20h] [ebp-60h] BYREF
  Vec3 v64; // [esp+2Ch] [ebp-54h]
  float v65; // [esp+38h] [ebp-48h]
  float v66; // [esp+3Ch] [ebp-44h]
  float v67; // [esp+44h] [ebp-3Ch]
  float v68; // [esp+48h] [ebp-38h]
  float v69; // [esp+4Ch] [ebp-34h]
  Vec3 v70; // [esp+50h] [ebp-30h] BYREF
  Vec3 v71; // [esp+5Ch] [ebp-24h] BYREF
  Vec3 v72; // [esp+68h] [ebp-18h] BYREF
  Vec3 v73; // [esp+74h] [ebp-Ch] BYREF

  if ( !shot->game->subgame_pause_gate )
  {
    if ( shot->skip_one_tick == 1 )
    {
      shot->skip_one_tick = 0;
      return;
    }
    if ( shot->state == 1 )
    {
      p_path_follow = &shot->path_follow;
      if ( shot->path_follow.active == 1 )
      {
        switch ( calc_path_length_z(
                   (char *)p_path_follow,
                   shot->path_factor,
                   &shot->flight_transform.position.x,
                   &shot->velocity.x) )
        {
          case 0:
          case 2:
            shot->source_matrix.position.x = shot->path_follow.output_position.x;
            shot->source_matrix.position.y = shot->path_follow.output_position.y;
            shot->source_matrix.position.z = shot->path_follow.output_position.z;
            break;
          case 1:
          case 3:
            y = shot->flight_transform.position.y;
            shot->source_matrix.position.x = shot->flight_transform.position.x;
            z = shot->flight_transform.position.z;
            shot->source_matrix.position.y = y;
            shot->source_matrix.position.z = z;
            break;
          default:
            break;
        }
      }
      else
      {
        p_velocity = &shot->velocity;
        p_position = &shot->flight_transform.position;
        shot->flight_transform.position.x = shot->velocity.x + shot->flight_transform.position.x;
        shot->flight_transform.position.y = shot->velocity.y + shot->flight_transform.position.y;
        shot->flight_transform.position.z = shot->velocity.z + shot->flight_transform.position.z;
        kind = shot->kind;
        if ( kind )
        {
          if ( kind == 2 && shot->homing_target_object )
          {
            v8 = shot->homing_blend_step + shot->homing_blend;
            shot->homing_blend = v8;
            if ( v8 > 1.0 )
              shot->homing_blend = 1.0;
            v60 = normalize_vector(p_velocity);
            v64.x = shot->homing_target.x - p_position->x;
            v9 = shot->homing_target.y - shot->flight_transform.position.y;
            vector.x = v64.x;
            v64.y = v9;
            v10 = shot->homing_target.z - shot->flight_transform.position.z;
            vector.y = v64.y;
            v64.z = v10;
            vector.z = v64.z;
            if ( normalize_vector(&vector) < 0.40000001 )
            {
              spawn_golb_impact_sprite(shot, (Vec3 *)&shot->flight_transform.position);
              goto LABEL_82;
            }
            homing_blend = shot->homing_blend;
            v67 = vector.x * homing_blend;
            v68 = vector.y * homing_blend;
            v12 = homing_blend * vector.z;
            v13 = 1.0 - shot->homing_blend * 1.5;
            v65 = v13 * p_velocity->x;
            v66 = v13 * shot->velocity.y;
            v14 = v13 * shot->velocity.z;
            v64.x = v65 + v67;
            v15 = v66 + v68;
            p_velocity->x = v64.x;
            v64.y = v15;
            shot->velocity.y = v64.y;
            v64.z = v14 + v12;
            shot->velocity.z = v64.z;
            normalize_vector(p_velocity);
            p_velocity->x = v60 * p_velocity->x;
            shot->velocity.y = v60 * shot->velocity.y;
            shot->velocity.z = v60 * shot->velocity.z;
            if ( v60 < 0.1 )
              goto LABEL_82;
          }
        }
        else if ( shot->flight_transform.position.y > 0.49000001 || shot->flight_transform.position.y < 0.0 )
        {
          shot->velocity.y = shot->velocity.y - shot->game->subgame_rate * 0.017000001;
        }
        else
        {
          shot->velocity.y = 0.0;
        }
        path_entry_z_latch = shot->path_entry_z_latch;
        shot->source_matrix.position.x = p_position->x;
        v17 = shot->flight_transform.position.z;
        shot->source_matrix.position.y = shot->flight_transform.position.y;
        shot->source_matrix.position.z = v17;
        if ( path_entry_z_latch < shot->source_matrix.position.z
          && shot->flight_transform.position.y < 1.0
          && shot->flight_transform.position.y > 0.0 )
        {
          track_grid_cell_at_world_position = get_track_grid_cell_at_world_position(
                                                shot->game,
                                                (Vec3 *)&shot->source_matrix.position);
          v19 = track_grid_cell_at_world_position;
          if ( track_grid_cell_at_world_position->tile_id == 30 )
          {
            shot->path_entry_z_latch = shot->source_matrix.position.z;
            initialize_path_follow_golb(
              (float *)&shot->path_follow.active,
              (int)track_grid_cell_at_world_position,
              (int)&shot->flight_transform.position,
              (int)shot);
          }
          if ( shot->velocity.z > 1.0 && v19[-8].tile_id == 30 )
          {
            shot->path_entry_z_latch = shot->source_matrix.position.z + 1.0;
            initialize_path_follow_golb(
              (float *)&shot->path_follow.active,
              (int)&v19[-8],
              (int)&shot->flight_transform.position,
              (int)shot);
          }
        }
      }
      v20 = shot->kind;
      if ( v20 )
      {
        v21 = v20 - 1;
        if ( v21 )
        {
          if ( v21 == 1 )
          {
            v22 = shot->spin_step + shot->spin;
            shot->spin = v22;
            qmemcpy(&shot->live_matrix, &shot->source_matrix, sizeof(shot->live_matrix));
            if ( !(v24 | v25) )
              shot->spin = v22 - 6.2831855;
            spawn_golb_smoke(shot, (Vec3 *)&shot->source_matrix.position);
            v26 = shot->direction.x * 0.5;
            v68 = shot->direction.y * 0.5;
            v69 = shot->direction.z * 0.5;
            v64.x = shot->source_matrix.position.x - v26;
            v27 = shot->source_matrix.position.y - v68;
            v70.x = v64.x;
            v64.y = v27;
            v28 = shot->source_matrix.position.z - v69;
            v70.y = v64.y;
            v64.z = v28;
            v70.z = v64.z;
            spawn_golb_smoke(shot, &v70);
          }
        }
        else
        {
          add_vapour_point(&shot->vapour, &shot->source_matrix);
        }
      }
      else
      {
        v29 = (float *)((char *)shot->render_body_owner + 72);
        *v29 = shot->source_matrix.position.x;
        v29[1] = shot->source_matrix.position.y;
        v29[2] = shot->source_matrix.position.z;
        spawn_golb_trail_sprite(shot, (Vec3 *)&shot->source_matrix.position);
        v30 = shot->direction.x * 0.30000001;
        v68 = shot->direction.y * 0.30000001;
        v69 = shot->direction.z * 0.30000001;
        v64.x = shot->source_matrix.position.x - v30;
        v31 = shot->source_matrix.position.y - v68;
        v71.x = v64.x;
        v64.y = v31;
        v32 = shot->source_matrix.position.z - v69;
        v71.y = v64.y;
        v64.z = v32;
        v71.z = v64.z;
        spawn_golb_trail_sprite(shot, &v71);
        v33 = shot->direction.x * 0.60000002;
        v68 = shot->direction.y * 0.60000002;
        v69 = shot->direction.z * 0.60000002;
        v64.x = shot->source_matrix.position.x - v33;
        v34 = shot->source_matrix.position.y - v68;
        v72.x = v64.x;
        v64.y = v34;
        v35 = shot->source_matrix.position.z - v69;
        v72.y = v64.y;
        v64.z = v35;
        v72.z = v64.z;
        spawn_golb_trail_sprite(shot, &v72);
      }
      v36 = &shot->source_matrix.position;
      v64.x = shot->source_matrix.position.x - shot->previous_flight_transform.position.x;
      v64.y = shot->source_matrix.position.y - shot->previous_flight_transform.position.y;
      v37 = shot->source_matrix.position.z - shot->previous_flight_transform.position.z;
      shot->direction.x = v64.x;
      shot->direction.y = v64.y;
      v64.z = v37;
      shot->direction.z = v64.z;
      if ( shot->kind == 2 )
      {
        set_matrix_z_direction(&shot->tertiary_body.transform, &shot->direction);
        rotate_matrix_local_z(&shot->tertiary_body.transform, shot->spin);
      }
      v38 = shot->lifetime_step + shot->lifetime;
      x = v36->x;
      shot->lifetime = v38;
      v40 = shot->source_matrix.position.y;
      shot->previous_flight_transform.position.x = x;
      v41 = shot->source_matrix.position.z;
      shot->previous_flight_transform.position.y = v40;
      shot->previous_flight_transform.position.z = v41;
      if ( v38 <= 1.0 )
      {
        owner_player = shot->owner_player;
        if ( shot->flight_transform.position.z >= (double)owner_player->interaction_max_z
          && owner_player->body.transform.position.z + 46.0 >= shot->flight_transform.position.z )
        {
          active_head = shot->game->garbage_hazards.active_head;
          if ( active_head )
          {
            while ( 1 )
            {
              if ( active_head->state == 1 )
              {
                v64.x = active_head->body.transform.position.x - v36->x;
                v64.y = active_head->body.transform.position.y - shot->source_matrix.position.y;
                v44 = active_head->body.transform.position.z - shot->source_matrix.position.z;
                v64.z = v44;
                v62 = v64;
                if ( v46 )
                  v44 = -v44;
                if ( v44 < 3.0 && normalize_vector(&v62) < active_head->radius + 0.49000001 )
                {
                  active_head->state = 2;
                  active_head->collision_side = v62.x >= 0.0 ? 1 : 2;
                  add_subgoldy_score(shot->owner_player, 0, 0);
                  if ( shot->kind != 1 )
                    break;
                }
              }
              active_head = active_head->next_active;
              if ( !active_head )
                goto LABEL_53;
            }
            kill_golb(shot);
            spawn_golb_impact_sprite(shot, (Vec3 *)&shot->source_matrix.position);
            if ( shot->kind == 2 )
            {
              for ( i = shot->game->garbage_hazards.active_head; i; i = i->next_active )
              {
                if ( i->state == 1 )
                {
                  v64.x = i->body.transform.position.x - v36->x;
                  v64.y = i->body.transform.position.y - shot->source_matrix.position.y;
                  v64.z = i->body.transform.position.z - shot->source_matrix.position.z;
                  v62 = v64;
                  if ( normalize_vector(&v62) < 3.0 )
                  {
                    i->state = 2;
                    if ( v62.x >= 0.0 )
                      i->collision_side = 1;
                    else
                      i->collision_side = 2;
                    add_subgoldy_score(shot->owner_player, 0, 0);
                  }
                }
              }
            }
            return;
          }
LABEL_53:
          v47 = 0;
          for ( j = 0; j < 1888; j += 236 )
          {
            v49 = &shot->game->scan_reset + j;
            v50 = *((_DWORD *)v49 + 874760);
            if ( v50 == 1 || v50 == 4 )
            {
              v64.x = *((float *)v49 + 874754) - v36->x;
              v64.y = *((float *)v49 + 874755) - shot->source_matrix.position.y;
              v51 = *((float *)v49 + 874756) - shot->source_matrix.position.z;
              v64.z = v51;
              v62 = v64;
              if ( v53 )
                v51 = -v51;
              if ( v51 < 2.5 && normalize_vector(&v62) < 2.5 )
              {
                shot->path_follow.active = 0;
                v61 = normalize_vector(&shot->velocity);
                v62.y = 0.0;
                normalize_vector(&v62);
                vector.y = 0.0;
                vector.x = -(v61 * v62.x);
                v54 = v61 * v62.z;
                shot->velocity.x = vector.x;
                vector.z = -v54;
                v55 = vector.z;
                shot->velocity.y = 0.0;
                shot->velocity.z = v55;
                v56 = shot->kind;
                switch ( v56 )
                {
                  case 1:
                    kill_golb(shot);
                    spawn_golb_impact_sprite(shot, (Vec3 *)&shot->source_matrix.position);
                    hit_slug_hazard(&shot->game->slug_hazards.slots[v47], 2);
                    return;
                  case 2:
                    kill_golb(shot);
                    spawn_golb_impact_sprite(shot, (Vec3 *)&shot->source_matrix.position);
                    hit_slug_hazard(&shot->game->slug_hazards.slots[v47], 4);
                    return;
                  case 0:
                    if ( shot->slug_bounce_armed )
                    {
                      kill_golb(shot);
                      spawn_golb_impact_sprite(shot, (Vec3 *)&shot->source_matrix.position);
                    }
                    else
                    {
                      shot->slug_bounce_armed = 1;
                    }
                    return;
                }
              }
            }
            ++v47;
          }
          if ( get_track_grid_cell_at_world_position(shot->game, (Vec3 *)&shot->source_matrix.position)->tile_id != 14 )
            return;
          v58 = shot->source_matrix.position.z - 1.0;
          v59 = shot->source_matrix.position.y;
          v64.x = v36->x;
          v64.y = v59;
          v73.x = v64.x;
          v64.z = v58;
          v73.y = v59;
          v73.z = v64.z;
          spawn_golb_impact_sprite(shot, &v73);
        }
      }
LABEL_82:
      kill_golb(shot);
    }
  }
}
