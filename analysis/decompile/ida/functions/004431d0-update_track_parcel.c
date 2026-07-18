/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_track_parcel @ 0x4431d0 */
/* selector: update_track_parcel */

// Runs one live `Parcel` through bobbing, homing, and final delivery-arc states, consuming the owned `Completion::widget_world` vector before registering delivery and tearing down its sprite. The exact Windows constructor table at 0x497364 points directly here, while Android and iOS retain `cRParcel::AI()`.
void __thiscall update_track_parcel(Parcel *parcel)
{
  SubgameRuntime *owner_subgame; // ecx
  double v3; // st7
  unsigned __int8 v5; // c0
  unsigned __int8 v6; // c3
  Vec3 *p_position; // ecx
  Sprite *sprite; // edi
  Player *owner_player; // eax
  double v10; // st7
  float *p_scan_reset; // eax
  double v12; // st7
  float *v13; // eax
  double v14; // st7
  double v15; // st7
  double v16; // st7
  Vec3 *v17; // eax
  double v18; // st6
  double v19; // st6
  double v20; // st6
  float y; // eax
  Sprite *v22; // eax
  double v23; // st7
  Vec4 *p_basis_up; // eax
  Vec3 *v25; // edx
  double v26; // st7
  float v27; // ecx
  double v28; // st7
  double v29; // st7
  Sprite *v30; // ecx
  int math_random_value; // eax
  SubgameRuntime *v32; // eax
  double v33; // st7
  Sprite *v34; // ecx
  double v35; // st7
  double progress; // st7
  Vec3 *v37; // eax
  float v38; // edx
  double v39; // st7
  Vec3 *v40; // eax
  float z; // ecx
  double v42; // st7
  Vec3 *v43; // eax
  double v44; // st7
  double v45; // st7
  Sprite *v46; // ecx
  float v47; // [esp+0h] [ebp-38h]
  float v48; // [esp+0h] [ebp-38h]
  float v49; // [esp+0h] [ebp-38h]
  float v50; // [esp+0h] [ebp-38h]
  Vec3 vector; // [esp+14h] [ebp-24h] BYREF
  Vec3 v52; // [esp+20h] [ebp-18h]
  float v53; // [esp+2Ch] [ebp-Ch]
  float v54; // [esp+30h] [ebp-8h]

  owner_subgame = parcel->owner_subgame;
  if ( !owner_subgame->subgame_pause_gate )
  {
    switch ( parcel->state )
    {
      case PARCEL_STATE_TRACK_ACTIVE:
        if ( owner_subgame->player.interaction_max_z - 10.0 > parcel->bod.position.z )
        {
          kill_sprite(parcel->sprite);
          parcel->state = PARCEL_STATE_INACTIVE;
        }
        v3 = parcel->bob_phase_step + parcel->bob_phase;
        parcel->bob_phase = v3;
        if ( !(v5 | v6) )
          parcel->bob_phase = v3 - 1.0;
        p_position = &parcel->sprite->position;
        p_position->x = parcel->bod.position.x;
        p_position->y = parcel->bod.position.y;
        p_position->z = parcel->bod.position.z;
        sprite = parcel->sprite;
        v47 = parcel->bob_phase * 6.2831855;
        sprite->position.y = sine(v47) * 0.30000001 + sprite->position.y;
        parcel->sprite->facing_angle = parcel->owner_player->heading_roll;
        owner_player = parcel->owner_player;
        if ( owner_player->follow_state.active == 1 )
          parcel->sprite->facing_angle = owner_player->follow_state.orientation_b + parcel->sprite->facing_angle;
        return;
      case PARCEL_STATE_COLLECT_PENDING:
        v48 = parcel->bob_phase * 6.2831855;
        v10 = sine(v48);
        p_scan_reset = (float *)&parcel->owner_subgame->scan_reset;
        parcel->progress = 0.0;
        p_scan_reset += 982599;
        parcel->progress_step = 0.041666668;
        parcel->bod.position.y = v10 * 0.30000001 + parcel->bod.position.y;
        v52.x = *p_scan_reset - parcel->bod.position.x;
        v52.y = p_scan_reset[1] - parcel->bod.position.y;
        v52.z = p_scan_reset[2] - parcel->bod.position.z;
        vector = v52;
        v12 = vector_magnitude(&vector);
        v13 = (float *)&parcel->owner_subgame->scan_reset;
        parcel->state = PARCEL_STATE_COLLECTING;
        parcel->target_distance = v12;
        v14 = parcel->bod.position.x - v13[982599];
        v13 += 982599;
        v52.x = v14;
        v52.y = parcel->bod.position.y - v13[1];
        v15 = parcel->bod.position.z - v13[2];
        parcel->travel_dir.x = v52.x;
        v52.z = v15;
        parcel->travel_dir.y = v52.y;
        parcel->travel_dir.z = v52.z;
        normalize_vector(&parcel->travel_dir);
        goto LABEL_10;
      case PARCEL_STATE_COLLECTING:
LABEL_10:
        v16 = 1.0 - parcel->progress;
        v17 = &parcel->owner_subgame->player.presentation.snail_hotspots_world[11];
        v18 = v16 * parcel->target_distance;
        v53 = v18 * parcel->travel_dir.x;
        v54 = v18 * parcel->travel_dir.y;
        v19 = v18 * parcel->travel_dir.z;
        v52.x = v53 + v17->x;
        v52.y = v54 + v17->y;
        v20 = v19 + v17->z;
        y = v52.y;
        parcel->bod.position.x = v52.x;
        parcel->bod.position.y = y;
        v22 = parcel->sprite;
        v52.z = v20;
        parcel->bod.position.z = v52.z;
        v22->size_end = v16 * 0.60000002 + 0.40000001;
        parcel->sprite->size_start = parcel->sprite->size_end;
        v49 = parcel->progress * 3.1415927;
        v23 = sine(v49) * 0.5;
        p_basis_up = &parcel->owner_subgame->player.presentation.body.transform.basis_up;
        v25 = &parcel->sprite->position;
        v53 = v23 * p_basis_up->x;
        v54 = v23 * p_basis_up->y;
        v26 = v23 * p_basis_up->z;
        v52.x = v53 + parcel->bod.position.x;
        v52.y = v54 + parcel->bod.position.y;
        v27 = v52.y;
        v28 = v26 + parcel->bod.position.z;
        v25->x = v52.x;
        v25->y = v27;
        v52.z = v28;
        v25->z = v52.z;
        v29 = parcel->progress_step + parcel->progress;
        parcel->progress = v29;
        if ( v29 > 1.0 )
        {
          v30 = parcel->sprite;
          parcel->state = PARCEL_STATE_INACTIVE;
          kill_sprite(v30);
        }
        return;
      case PARCEL_STATE_DELIVERY_PENDING:
        parcel->progress = 0.0;
        parcel->progress_step = 0.016666668;
        parcel->state = PARCEL_STATE_DELIVERING;
        parcel->delivery_offset.x = ((double)next_math_random_value() - 16384.0) * 0.000061035156;
        math_random_value = next_math_random_value();
        parcel->delivery_offset.z = 0.0;
        parcel->delivery_offset.y = ((double)math_random_value - 16384.0) * 0.000091552734 + 1.0;
        goto LABEL_13;
      case PARCEL_STATE_DELIVERING:
LABEL_13:
        v32 = parcel->owner_subgame;
        v52.x = v32->completion.widget_world.x - v32->player.presentation.snail_hotspots_world[11].x;
        v52.y = v32->completion.widget_world.y - v32->player.presentation.snail_hotspots_world[11].y;
        v33 = v32->completion.widget_world.z - v32->player.presentation.snail_hotspots_world[11].z;
        vector.x = v52.x;
        v34 = parcel->sprite;
        vector.y = v52.y;
        v52.z = v33;
        v35 = parcel->progress * 0.60000002;
        vector.z = v52.z;
        v34->size_end = v35 + 0.40000001;
        parcel->sprite->size_start = parcel->sprite->size_end;
        progress = parcel->progress;
        v37 = &parcel->owner_subgame->player.presentation.snail_hotspots_world[11];
        v53 = vector.x * progress;
        v54 = vector.y * progress;
        v52.x = v53 + v37->x;
        v52.y = v54 + v37->y;
        v38 = v52.y;
        v39 = progress * vector.z + v37->z;
        v40 = &parcel->sprite->position;
        v52.z = v39;
        v40->x = v52.x;
        z = v52.z;
        v40->y = v38;
        v40->z = z;
        v50 = parcel->progress * 3.1415927;
        v42 = sine(v50);
        v43 = &parcel->sprite->position;
        v53 = v42 * parcel->delivery_offset.x;
        v54 = v42 * parcel->delivery_offset.y;
        v44 = v42 * parcel->delivery_offset.z;
        v43->x = v53 + v43->x;
        v43->y = v54 + v43->y;
        v43->z = v44 + v43->z;
        v45 = parcel->progress_step + parcel->progress;
        parcel->progress = v45;
        if ( v45 > 1.0 )
        {
          register_parcel_delivery(&parcel->owner_subgame->completion);
          v46 = parcel->sprite;
          parcel->state = PARCEL_STATE_INACTIVE;
          kill_sprite(v46);
        }
        break;
      default:
        return;
    }
  }
}
