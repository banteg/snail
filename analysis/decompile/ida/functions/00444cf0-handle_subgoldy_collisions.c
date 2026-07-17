/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: handle_subgoldy_collisions @ 0x444cf0 */
/* selector: handle_subgoldy_collisions */

// Void `Player` member that processes Goldy's live collision sweep against rings, parcels, health pickups, garbage, salt, slugs, and related runtime object pools, updating score and contact damage. Its sole `update_subgoldy` caller discards EAX, and the terminal register value is only the last incidental score-helper result. The first slug hit scales `(0, 0.2, -0.2)` by the subgame rate and emits a burst through the Player-owned Firework controller. Cross-port Android and iOS symbols identify `cRSubGoldy::Collision()`.
void __thiscall handle_subgoldy_collisions(Player *player)
{
  int i; // edi
  SaltSlotCursor *salt_cursor; // eax
  double v4; // st7
  int j; // edi
  SubLazerSlotCursor *sub_lazer_cursor; // eax
  double v7; // st7
  SubGarbage *k; // edi
  double v9; // st7
  __int64 v10; // rax
  int m; // edi
  SubgameRuntime *game; // edx
  int32_t state; // ecx
  SlugSlotCursor *slug_cursor; // eax
  double v15; // st7
  double v16; // st7
  SubgameRuntime *v17; // eax
  double v18; // st7
  SubgameRuntime *v19; // eax
  __int64 v20; // rax
  double v21; // st7
  double v22; // st6
  double v23; // st7
  double subgame_rate; // st7
  int n; // edi
  ParcelSlotCursor *parcel_cursor; // eax
  double v27; // st7
  SubgameRuntime *v28; // eax
  int32_t v29; // ebx
  int ii; // edi
  SubHealthSlotCursor *health_cursor; // eax
  double v32; // st7
  double y; // st7
  double v35; // st7
  char v36; // c0
  SubgameRuntime *v37; // eax
  double v38; // st7
  double v39; // st7
  double v41; // st7
  char v42; // c0
  SubgameRuntime *v43; // eax
  double v44; // st7
  double v45; // st7
  int jj; // edi
  SubRingSlotCursor *ring_cursor; // eax
  double v48; // st7
  SubgameRuntime *v49; // ecx
  SubRingKind kind; // eax
  SubgameRuntime *v51; // ecx
  SubRingKind v52; // eax
  int32_t v53; // eax
  int v54; // eax
  int32_t lives; // eax
  int32_t movement_flag_selector; // eax
  int32_t player_slot; // [esp-Ch] [ebp-90h]
  float v58; // [esp+10h] [ebp-74h]
  Vec3 v59; // [esp+18h] [ebp-6Ch] BYREF
  Vec3 v60; // [esp+24h] [ebp-60h] BYREF
  Vec3 v61; // [esp+30h] [ebp-54h]
  int v62; // [esp+3Ch] [ebp-48h]
  float v63; // [esp+40h] [ebp-44h]
  float v64; // [esp+44h] [ebp-40h]
  Vec3 vector; // [esp+48h] [ebp-3Ch] BYREF
  float v66; // [esp+54h] [ebp-30h]
  float v67; // [esp+58h] [ebp-2Ch]
  Vec3 position; // [esp+60h] [ebp-24h] BYREF
  Vec3 v69; // [esp+6Ch] [ebp-18h] BYREF
  Vec3 v70; // [esp+78h] [ebp-Ch] BYREF

  if ( !player->attachment_exit_pending && !player->boost_one_tick && !player->control_override_active )
  {
    if ( SLOBYTE(player->movement_flags) >= 0 )
    {
      for ( i = 0; i < 40; ++i )
      {
        salt_cursor = (SaltSlotCursor *)(&player->game->scan_reset + i * 152);
        if ( salt_cursor->salt.state == 1 && salt_cursor->salt.collision_armed == 1 )
        {
          v61.x = salt_cursor->salt.body.transform.position.x - player->cached_camera_target_world.x;
          v61.y = salt_cursor->salt.body.transform.position.y - player->cached_camera_target_world.y;
          v4 = salt_cursor->salt.body.transform.position.z - player->cached_camera_target_world.z;
          v61.z = v4;
          vector = v61;
          if ( v4 < 1.0 && normalize_vector(&vector) < 0.98000002 )
          {
            if ( player->damage_retrigger_timer == 0.0 )
              player->damage_retrigger_timer = player->damage_retrigger_step;
            player->game->salt_hazards.slots[i].collision_armed = 0;
            apply_damage_gauge_delta(&player->damage_gauge, 0.15000001, 0);
          }
        }
      }
    }
    for ( j = 0; j < 20; ++j )
    {
      sub_lazer_cursor = (SubLazerSlotCursor *)(&player->game->scan_reset + j * 176);
      if ( sub_lazer_cursor->sub_lazer.state == 1 )
      {
        v61.x = sub_lazer_cursor->sub_lazer.body.transform.position.x - player->cached_camera_target_world.x;
        v61.y = sub_lazer_cursor->sub_lazer.body.transform.position.y - player->cached_camera_target_world.y;
        v7 = sub_lazer_cursor->sub_lazer.body.transform.position.z - player->cached_camera_target_world.z;
        v61.z = v7;
        v59 = v61;
        if ( v7 < 1.0 && normalize_vector(&v59) < 0.49000001 )
        {
          player->game->sub_lazers.slots[j].state = 2;
          apply_damage_gauge_delta(&player->damage_gauge, 0.02, 0);
        }
      }
    }
    for ( k = player->game->garbage_hazards.active_head; k; k = k->next_active )
    {
      if ( k->state == 1 )
      {
        v61.x = k->body.transform.position.x - player->cached_camera_target_world.x;
        v61.y = k->body.transform.position.y - player->cached_camera_target_world.y;
        v9 = k->body.transform.position.z - player->cached_camera_target_world.z;
        v61.z = v9;
        v59 = v61;
        if ( v9 < 1.0 && normalize_vector(&v59) < 0.98000002 )
        {
          if ( (player->movement_flags & 0x80) == 0 )
          {
            player->velocity.x = player->velocity.x - v59.x * player->velocity.z * 0.18000001;
            player->velocity.z = player->velocity.z - v59.z * player->velocity.z * 0.1;
          }
          k->state = 2;
          if ( v59.x >= 0.0 )
            k->collision_side = 1;
          else
            k->collision_side = 2;
          add_subgoldy_score(player, 0, 0);
          apply_damage_gauge_delta(&player->damage_gauge, 0.039999999, 0);
          v10 = (__int64)((double)next_math_random_value() * -0.000061035156);
          play_sound_effect(39 - v10);
        }
      }
    }
    for ( m = 0; m < 8; ++m )
    {
      game = player->game;
      state = game->slug_hazards.slots[m].state;
      slug_cursor = (SlugSlotCursor *)(&game->scan_reset + m * 236);
      if ( state == 1 || state == 4 )
      {
        v61.x = slug_cursor->slug.body.transform.position.x - player->cached_camera_target_world.x;
        v61.y = slug_cursor->slug.body.transform.position.y - player->cached_camera_target_world.y;
        v15 = slug_cursor->slug.body.transform.position.z - player->cached_camera_target_world.z;
        v61.z = v15;
        v59 = v61;
        if ( v15 < 2.0 )
        {
          v16 = normalize_vector(&v59);
          v58 = v16;
          if ( v16 < 1.5675001 )
          {
            if ( (player->movement_flags & 0x80) != 0 )
            {
              kill_slug_hazard(&player->game->slug_hazards.slots[m]);
            }
            else if ( player->control_override_active )
            {
              subgame_rate = player->game->subgame_rate;
              player->velocity.z = subgame_rate * subgame_rate * 0.0040000002 * -8.0;
              apply_damage_gauge_delta(&player->damage_gauge, 1.0, 0);
            }
            else
            {
              v17 = player->game;
              player->control_override_active = 1;
              player->follow_state.active = 0;
              v62 = 0;
              v18 = v17->subgame_rate;
              player->velocity.x = 0.0;
              v63 = v18 * 0.2;
              player->velocity.y = v63;
              v64 = v18 * -0.2;
              player->velocity.z = v64;
              begin_post_follow_carryover((int)player);
              v19 = player->game;
              player->presentation.cutscene.state = CUT_SCENE_STATE_DEATH_PENDING;
              v19->slug_hazards.slots[m].player_encounter_latched = 1;
              v20 = (__int64)((double)next_math_random_value() * -0.000061035156);
              play_slug_voice(&player->game->slug_hazards.slots[m], 34 - v20);
              v21 = v58 * 0.5;
              player->presentation.wobble.lift_phase_step = 0.0;
              v66 = v21 * v59.x;
              v67 = v59.y * v21;
              vector.x = v66 + player->cached_camera_target_world.x;
              v22 = v67 + player->cached_camera_target_world.y;
              position.x = vector.x;
              player_slot = player->player_slot;
              vector.y = v22;
              v23 = v21 * v59.z + player->cached_camera_target_world.z;
              position.y = vector.y;
              vector.z = v23;
              position.z = vector.z;
              firework_shoot(&player->firework, &position, player_slot, 92, 80);
            }
          }
        }
      }
    }
    for ( n = 0; n < 50; ++n )
    {
      parcel_cursor = (ParcelSlotCursor *)(&player->game->scan_reset + n * 140);
      if ( parcel_cursor->parcel.state == PARCEL_STATE_TRACK_ACTIVE )
      {
        vector.x = parcel_cursor->parcel.bod.position.x - player->cached_camera_target_world.x;
        vector.y = parcel_cursor->parcel.bod.position.y - player->cached_camera_target_world.y;
        v27 = parcel_cursor->parcel.bod.position.z - player->cached_camera_target_world.z;
        vector.z = v27;
        v69 = vector;
        if ( v27 < 1.0 && normalize_vector(&v69) < 1.24 )
        {
          add_subgoldy_score(player, 3, 0);
          play_voice_manager((int)g_voice_manager, 10, 1u, -1);
          play_sound_effect(27);
          player->game->parcel_manager.slots[n].state = PARCEL_STATE_COLLECT_PENDING;
          v28 = player->game;
          v29 = player->parcels_collected + 1;
          player->parcels_collected = v29;
          if ( !v28->level_mode )
            sprintf((char *const)&v28->lives_text_widget->text_buffer, "%i/%i", v29, v28->level_definition.parcel_count);
        }
      }
    }
  }
  for ( ii = 0; ii < 8; ++ii )
  {
    health_cursor = (SubHealthSlotCursor *)(&player->game->scan_reset + ii * 116);
    if ( health_cursor->health.state == TRACK_PICKUP_STATE_ACTIVE )
    {
      v59.x = health_cursor->health.world_position.x - player->cached_camera_target_world.x;
      v59.y = health_cursor->health.world_position.y - player->cached_camera_target_world.y;
      v32 = health_cursor->health.world_position.z - player->cached_camera_target_world.z;
      v60.x = v59.x;
      v60.y = v59.y;
      v59.z = v32;
      y = player->body.transform.position.y;
      v60.z = v59.z;
      if ( y >= 0.49000001 && v59.z < 1.0 )
      {
        v35 = v59.y;
        if ( v36 )
          v35 = -v35;
        if ( v35 < 0.40000001 && normalize_vector(&v60) < 0.98000002 )
        {
          play_sound_effect(14);
          player->game->health_pickups[ii].state = TRACK_PICKUP_STATE_TEARDOWN_PENDING;
          health_collect_particles((int)player, (int)&player->game->health_pickups[ii]);
          apply_damage_gauge_delta(&player->damage_gauge, -0.5, 0);
        }
      }
    }
  }
  v37 = player->game;
  if ( v37->speedup_pickup.state == TRACK_PICKUP_STATE_ACTIVE )
  {
    v59.x = v37->speedup_pickup.body.transform.position.x - player->cached_camera_target_world.x;
    v59.y = v37->speedup_pickup.body.transform.position.y - player->cached_camera_target_world.y;
    v38 = v37->speedup_pickup.body.transform.position.z - player->cached_camera_target_world.z;
    v60.x = v59.x;
    v60.y = v59.y;
    v59.z = v38;
    v39 = player->body.transform.position.y;
    v60.z = v59.z;
    if ( v39 >= 0.49000001 && v59.z < 1.0 )
    {
      v41 = v59.y;
      if ( v42 )
        v41 = -v41;
      if ( v41 < 0.40000001 && normalize_vector(&v60) < 0.98000002 )
      {
        player->game->speedup_pickup.state = TRACK_PICKUP_STATE_TEARDOWN_PENDING;
        noop_runtime_ai();
        player->velocity.z = player->game->subgame_rate * 0.5;
      }
    }
  }
  v43 = player->game;
  if ( v43->jetpack_pickup.state == TRACK_PICKUP_STATE_ACTIVE )
  {
    v59.x = v43->jetpack_pickup.world_position.x - player->cached_camera_target_world.x;
    v59.y = v43->jetpack_pickup.world_position.y - player->cached_camera_target_world.y;
    v44 = v43->jetpack_pickup.world_position.z - player->cached_camera_target_world.z;
    v60.x = v59.x;
    v60.y = v59.y;
    v59.z = v44;
    v45 = player->body.transform.position.y;
    v60.z = v59.z;
    if ( v45 >= 0.49000001 && v59.z < 1.0 && normalize_vector(&v60) < 3.0 )
    {
      player->game->jetpack_pickup.state = TRACK_PICKUP_STATE_TEARDOWN_PENDING;
      arm_jetpack_gauge(&player->sub_hover);
    }
  }
  for ( jj = 0; jj < 2; ++jj )
  {
    ring_cursor = (SubRingSlotCursor *)(&player->game->scan_reset + jj * 504);
    if ( ring_cursor->ring.state == SUB_RING_STATE_ACTIVE )
    {
      vector.x = ring_cursor->ring.body.transform.position.x - player->cached_camera_target_world.x;
      vector.y = ring_cursor->ring.body.transform.position.y - player->cached_camera_target_world.y;
      v48 = ring_cursor->ring.body.transform.position.z - player->cached_camera_target_world.z;
      vector.z = v48;
      v70 = vector;
      if ( v48 < 1.0 && normalize_vector(&v70) < 0.98000002 )
      {
        player->game->ring_effects.slots[jj].state = SUB_RING_STATE_COLLECT_PENDING;
        if ( !player->completion_handoff_active )
        {
          v49 = player->game;
          kind = v49->ring_effects.slots[jj].kind;
          if ( kind == SUB_RING_KIND_SLOW_DEFAULT || kind == SUB_RING_KIND_SLOW_AUTHORED )
          {
            player->velocity.z = -0.1;
            play_sound_effect(43);
          }
          else
          {
            player->velocity.z = v49->subgame_rate * 0.5;
          }
        }
        v51 = player->game;
        v52 = v51->ring_effects.slots[jj].kind;
        switch ( v52 )
        {
          case SUB_RING_KIND_NORMAL_DEFAULT:
          case SUB_RING_KIND_NORMAL_AUTHORED:
            lives = player->lives;
            if ( lives < 10 )
            {
              if ( (v51->runtime_flags & 0x10) != 0 && v51->level_mode != 3 )
                player->lives = lives + 1;
              play_voice_manager((int)g_voice_manager, 5, 1u, -1);
            }
            movement_flag_selector = player->movement_flag_selector;
            if ( movement_flag_selector >= 8 )
            {
              if ( movement_flag_selector == 8 )
                player->movement_flag_selector = 7;
            }
            else
            {
              player->movement_flag_selector = movement_flag_selector + 1;
            }
            v54 = player->movement_flag_selector - 1;
            if ( v54 > 6 )
LABEL_105:
              v54 = 6;
LABEL_106:
            play_sound_effect(v54 + 1);
            add_subgoldy_score(player, 2, 0);
            continue;
          case SUB_RING_KIND_POWER_UP_AUTHORED:
            v53 = player->movement_flag_selector;
            if ( v53 >= 8 )
            {
              if ( v53 == 8 )
                player->movement_flag_selector = 7;
            }
            else
            {
              player->movement_flag_selector = v53 + 1;
            }
            v54 = player->movement_flag_selector - 1;
            if ( v54 > 6 )
              goto LABEL_105;
            goto LABEL_106;
          case SUB_RING_KIND_UNKNOWN_1:
            add_subgoldy_score(player, 2, 0);
            play_sound_effect(1);
            break;
          case SUB_RING_KIND_EXPLODE_RAMP:
          case SUB_RING_KIND_EXPLODE_AUTHORED:
            add_subgoldy_score(player, 2, 0);
            play_sound_effect(42);
            player->nuke_effect_progress = player->nuke_effect_progress_step;
            initialize_nuke(&player->nuke);
            break;
        }
      }
    }
  }
}
