/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_garbage_hazard @ 0x43f200 */
/* selector: update_garbage_hazard */

// Void `cRSubGarbage::AI()` callback advancing one owned pool slot through inactive, active, burst-pending, and burst states before teardown. The exact Windows constructor table at 0x497328 points directly here, and the active-BOD dispatcher invokes slot zero through a virtual void method; Android and iOS retain the same authored member.
void __thiscall update_garbage_hazard(SubGarbage *sub_garbage)
{
  Vec4 *p_position; // edi
  Player *owner_player; // ecx
  double x; // st7
  double v5; // st7
  SubgameRuntime *owner_game; // edx
  Vec3 *p_velocity; // ecx
  double subgame_rate; // st6
  int32_t collision_side; // eax
  double v11; // st7
  char v12; // c0
  double v14; // st7
  char v15; // c0
  double v16; // st7
  double v17; // st7
  Vec3 *v18; // eax
  Player *v19; // edi
  double v20; // st7
  Player *v21; // eax
  int v22; // [esp+Ch] [ebp-1Ch]
  float v23; // [esp+10h] [ebp-18h]
  float v24; // [esp+14h] [ebp-14h]
  float v25; // [esp+18h] [ebp-10h]
  float v26; // [esp+1Ch] [ebp-Ch]
  float v27; // [esp+20h] [ebp-8h]

  if ( !sub_garbage->owner_game->subgame_pause_gate )
  {
    switch ( sub_garbage->state )
    {
      case 0:
        return;
      case 1:
        p_position = &sub_garbage->body.transform.position;
        sub_garbage->sprite->position = *(Vec3 *)&sub_garbage->body.transform.position.x;
        owner_player = sub_garbage->owner_player;
        if ( sub_garbage->body.transform.position.z < (double)owner_player->interaction_max_z )
          goto LABEL_4;
        if ( owner_player->nuke_effect_progress > 0.0 )
        {
          x = p_position->x;
          sub_garbage->state = 2;
          if ( x <= 0.0 )
            sub_garbage->collision_side = 2;
          else
            sub_garbage->collision_side = 1;
          add_subgoldy_score(owner_player, 0, 0);
        }
        append_subgame_contact_target(
          &sub_garbage->owner_game->enemy_manager,
          (const Vec3 *)&sub_garbage->body.transform.position,
          sub_garbage->radius,
          0,
          (ContactTargetObject *)sub_garbage);
        goto LABEL_27;
      case 2:
        sub_garbage->state = 3;
        v26 = random_signed_float_below(0.1);
        v27 = random_float_below(0.2) + 0.1;
        v5 = random_float_below(0.30000001);
        owner_game = sub_garbage->owner_game;
        p_velocity = &sub_garbage->velocity;
        subgame_rate = owner_game->subgame_rate;
        v23 = subgame_rate * v26;
        sub_garbage->velocity.x = v23;
        v24 = v27 * subgame_rate;
        sub_garbage->velocity.y = v24;
        v25 = v5 * subgame_rate;
        sub_garbage->velocity.z = v25;
        collision_side = sub_garbage->collision_side;
        if ( collision_side == 1 )
        {
          v11 = p_velocity->x;
          if ( v12 )
            v11 = -v11;
        }
        else
        {
          if ( collision_side != 2 )
            goto LABEL_19;
          v14 = p_velocity->x;
          if ( v15 )
            v14 = -v14;
          v11 = -v14;
        }
        p_velocity->x = v11;
LABEL_19:
        if ( p_velocity->x >= 0.0 )
          v22 = p_velocity->x != 0.0;
        else
          v22 = -1;
        v16 = (double)v22 * 0.2 * owner_game->subgame_rate;
        sub_garbage->unknown_a4 = 0;
        p_velocity->x = v16 + p_velocity->x;
        v17 = owner_game->subgame_rate * 0.0083333338;
        sub_garbage->smoke_timer = 0.0;
        sub_garbage->burst_rate_step = v17;
        sub_garbage->smoke_timer_step = owner_game->subgame_rate * 0.27777779;
LABEL_23:
        sub_garbage->body.transform.position.x = sub_garbage->velocity.x + sub_garbage->body.transform.position.x;
        sub_garbage->body.transform.position.y = sub_garbage->velocity.y + sub_garbage->body.transform.position.y;
        sub_garbage->body.transform.position.z = sub_garbage->velocity.z + sub_garbage->body.transform.position.z;
        v18 = &sub_garbage->sprite->position;
        v18->x = sub_garbage->body.transform.position.x;
        v18->y = sub_garbage->body.transform.position.y;
        v18->z = sub_garbage->body.transform.position.z;
        sub_garbage->velocity.y = sub_garbage->owner_game->subgame_rate
                                * sub_garbage->owner_game->subgame_rate
                                * -0.0099999998
                                + sub_garbage->velocity.y;
        if ( sub_garbage->body.transform.position.y < -10.0
          || (v19 = sub_garbage->owner_player, sub_garbage->body.transform.position.z < (double)v19->interaction_max_z) )
        {
LABEL_4:
          destroy_garbage_hazard(sub_garbage);
        }
        else
        {
          v20 = sub_garbage->smoke_timer_step + sub_garbage->smoke_timer;
          sub_garbage->smoke_timer = v20;
          if ( v20 > 1.0 )
          {
            sub_garbage->smoke_timer = 0.0;
            spawn_garbage_smoke_particle(
              sub_garbage,
              (Vec3 *)&sub_garbage->body.transform.position,
              &sub_garbage->velocity,
              v19);
          }
LABEL_27:
          sub_garbage->sprite->facing_angle = sub_garbage->owner_player->heading_roll
                                            + sub_garbage->attachment_facing_angle;
          v21 = sub_garbage->owner_player;
          if ( v21->follow_state.active == 1 )
            sub_garbage->sprite->facing_angle = v21->follow_state.orientation_b + sub_garbage->sprite->facing_angle;
        }
        break;
      case 3:
        goto LABEL_23;
      default:
        goto LABEL_27;
    }
  }
}
