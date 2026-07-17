/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_slug_hazard_ai @ 0x43f930 */
/* selector: update_slug_hazard_ai */

// Void slot-zero callback running one owned `SlugPool` record through inactive, active, lateral-active, death-toss-pending, and teardown-pending states. Each record borrows its containing SubgameRuntime, embedded owner Player, source cell, and SpriteManager handle. The exact Windows constructor table at 0x497324 points directly here, while Android and iOS retain `cRSlug::AI()`.
void __thiscall update_slug_hazard_ai(Slug *slug)
{
  float hit_flash_progress_step; // ecx
  double v3; // st7
  Sprite *sprite; // edx
  __int64 v5; // rax
  Player *owner_player; // ecx
  Vec3 *p_position; // eax
  Player *v8; // ecx
  uint32_t list_flags; // eax
  BodList *p_active_bod_list; // ecx
  struct BodNode *list_next; // eax
  struct BodNode *list_prev; // eax
  Player *v13; // ecx
  double v14; // st7
  unsigned __int8 v16; // c0
  unsigned __int8 v17; // c3
  double v18; // st7
  Player *v19; // ecx
  Vec3 *v20; // edx
  Player *v21; // ecx
  uint32_t v22; // eax
  struct BodNode *v23; // eax
  struct BodNode *v24; // eax
  double v25; // st7
  Vec3 *p_velocity; // ecx
  int32_t death_toss_direction; // eax
  double x; // st7
  char v30; // c0
  double v32; // st7
  char v33; // c0
  SubgameRuntime *owner_game; // eax
  double v35; // st7
  uint32_t v36; // eax
  struct BodNode *v37; // eax
  struct BodNode *v38; // eax
  uint32_t v39; // eax
  Sprite *v40; // ecx
  float v41; // [esp+Ch] [ebp-14h]
  int v42; // [esp+Ch] [ebp-14h]
  float v43; // [esp+10h] [ebp-10h]
  float v44; // [esp+14h] [ebp-Ch]

  if ( !slug->owner_game->subgame_pause_gate )
  {
    switch ( slug->state )
    {
      case 0:
        return;
      case 1:
        if ( slug->hit_flash_pending && g_render_queue_active )
        {
          hit_flash_progress_step = slug->hit_flash_progress_step;
          slug->hit_flash_pending = 0;
          slug->hit_flash_progress = hit_flash_progress_step;
        }
        if ( slug->hit_flash_progress == 0.0 )
        {
          slug->blink_progress = slug->blink_step + slug->blink_progress;
          if ( slug->blink_step <= 0.0 )
            set_sprite_texture_ref(&slug->sprite->object_ref, 119, 0);
          else
            set_sprite_texture_ref(&slug->sprite->object_ref, 118, 0);
          slug->sprite->draw_mode = 0;
          store_color4f(&slug->sprite->color, 1.0, 1.0, 1.0, 1.0);
          if ( slug->blink_progress >= 0.0 )
          {
            if ( slug->blink_progress > 1.0 )
            {
              slug->blink_progress = 1.0;
              slug->blink_step = -0.16666667;
            }
          }
          else
          {
            slug->blink_progress = 0.0;
            slug->blink_step = advance_blink_random((float *)&g_game_base->subgame.scan_reset);
          }
        }
        else
        {
          v3 = slug->hit_flash_progress_step + slug->hit_flash_progress;
          slug->hit_flash_progress = v3;
          if ( v3 <= 1.0 )
          {
            slug->sprite->draw_mode = 5;
            set_sprite_texture_ref(&slug->sprite->object_ref, 120, 0);
            store_color4f(&slug->sprite->color, 1.0, 0.0, 0.0, 0.99000001);
          }
          else
          {
            sprite = slug->sprite;
            slug->hit_flash_progress = 0.0;
            slug->blink_progress = 1.0;
            slug->blink_step = -0.16666667;
            sprite->draw_mode = 0;
            store_color4f(&slug->sprite->color, 1.0, 1.0, 1.0, 1.0);
            set_sprite_texture_ref(&slug->sprite->object_ref, 119, 0);
          }
        }
        if ( slug->owner_player->body.transform.position.z + 1.0 > slug->body.transform.position.z
          && !slug->player_encounter_latched )
        {
          slug->player_encounter_latched = 1;
          if ( (double)next_math_random_value() * 0.000030517578 > 0.60000002 )
          {
            v5 = (__int64)((double)next_math_random_value() * -0.00012207031);
            play_slug_voice(slug, 30 - v5);
          }
        }
        owner_player = slug->owner_player;
        if ( slug->body.transform.position.z < (double)owner_player->body.transform.position.z && !slug->passed_player )
          slug->passed_player = 1;
        if ( slug->engagement_voice_gate == 1
          && owner_player->body.transform.position.z + 16.0 > slug->body.transform.position.z )
        {
          slug->engagement_voice_gate = 0;
          play_voice_manager((int)g_voice_manager, 2, 1u, -1);
        }
        p_position = &slug->sprite->position;
        p_position->x = slug->body.transform.position.x;
        p_position->y = slug->body.transform.position.y;
        p_position->z = slug->body.transform.position.z;
        v8 = slug->owner_player;
        if ( slug->body.transform.position.z >= (double)v8->interaction_max_z )
        {
          if ( v8->nuke_effect_progress > 0.0 )
            kill_slug_hazard(slug);
          append_subgame_contact_target(
            &slug->owner_game->enemy_manager,
            (const Vec3 *)&slug->body.transform.position,
            2.0,
            1,
            (ContactTargetObject *)slug);
          goto LABEL_39;
        }
        list_flags = slug->body.bod.bod.list_flags;
        slug->state = 0;
        p_active_bod_list = &g_game_base->active_bod_list;
        if ( (list_flags & 0x200) == 0 )
          goto LABEL_70;
        if ( (list_flags & 0x40) != 0 )
          goto LABEL_72;
        list_next = slug->body.bod.bod.list_next;
        if ( list_next )
          list_next->list_prev = slug->body.bod.bod.list_prev;
        list_prev = slug->body.bod.bod.list_prev;
        if ( list_prev )
        {
          list_prev->list_next = slug->body.bod.bod.list_next;
          goto LABEL_78;
        }
        goto LABEL_77;
      case 2:
        slug->state = 3;
        v43 = random_float_below(0.30000001);
        v41 = random_float_below(0.2) + 0.1;
        v25 = random_signed_float_below(0.1);
        p_velocity = &slug->velocity;
        v44 = v25;
        slug->velocity.x = v44;
        slug->velocity.y = v41;
        slug->velocity.z = v43;
        death_toss_direction = slug->death_toss_direction;
        if ( death_toss_direction == 1 )
        {
          x = p_velocity->x;
          if ( v30 )
            x = -x;
        }
        else
        {
          if ( death_toss_direction != 2 )
            goto LABEL_65;
          v32 = p_velocity->x;
          if ( v33 )
            v32 = -v32;
          x = -v32;
        }
        p_velocity->x = x;
LABEL_65:
        if ( p_velocity->x >= 0.0 )
          v42 = p_velocity->x != 0.0;
        else
          v42 = -1;
        owner_game = slug->owner_game;
        *(_DWORD *)slug->unknown_9c = 0;
        p_velocity->x = (double)v42 * 0.2 + p_velocity->x;
        v35 = owner_game->subgame_rate * 0.0083333338;
        *(_DWORD *)&slug->unknown_9c[8] = 0;
        *(float *)&slug->unknown_9c[4] = v35;
        *(float *)&slug->unknown_9c[12] = owner_game->subgame_rate * 0.16666667;
LABEL_69:
        v36 = slug->body.bod.bod.list_flags;
        slug->state = 0;
        p_active_bod_list = &g_game_base->active_bod_list;
        if ( (v36 & 0x200) == 0 )
          goto LABEL_70;
        if ( (v36 & 0x40) != 0 )
          goto LABEL_72;
        v37 = slug->body.bod.bod.list_next;
        if ( v37 )
          v37->list_prev = slug->body.bod.bod.list_prev;
        v38 = slug->body.bod.bod.list_prev;
        if ( !v38 )
          goto LABEL_77;
        v38->list_next = slug->body.bod.bod.list_next;
        goto LABEL_78;
      case 3:
        goto LABEL_69;
      case 4:
        v14 = slug->lateral_phase_step + slug->lateral_phase;
        slug->lateral_phase = v14;
        if ( !(v16 | v17) )
          slug->lateral_phase = v14 - 6.2831855;
        v18 = sine(slug->lateral_phase);
        v19 = slug->owner_player;
        slug->body.transform.position.x = v18 * 3.0;
        if ( slug->body.transform.position.z < (double)v19->body.transform.position.z && !slug->passed_player )
          slug->passed_player = 1;
        v20 = &slug->sprite->position;
        v20->x = slug->body.transform.position.x;
        v20->y = slug->body.transform.position.y;
        v20->z = slug->body.transform.position.z;
        v21 = slug->owner_player;
        if ( slug->body.transform.position.z >= (double)v21->interaction_max_z )
        {
          if ( v21->nuke_effect_progress > 0.0 )
            kill_slug_hazard(slug);
LABEL_39:
          slug->sprite->facing_angle = slug->owner_player->heading_roll + slug->attachment_facing_angle;
          v13 = slug->owner_player;
          if ( v13->follow_state.active == 1 )
            slug->sprite->facing_angle = v13->follow_state.orientation_b + slug->sprite->facing_angle;
          update_slug_voice_ai(slug);
        }
        else
        {
          v22 = slug->body.bod.bod.list_flags;
          slug->state = 0;
          p_active_bod_list = &g_game_base->active_bod_list;
          if ( (v22 & 0x200) != 0 )
          {
            if ( (v22 & 0x40) != 0 )
            {
LABEL_72:
              report_errorf(aListRemoveNext);
              kill_sprite((int)slug->sprite);
            }
            else
            {
              v23 = slug->body.bod.bod.list_next;
              if ( v23 )
                v23->list_prev = slug->body.bod.bod.list_prev;
              v24 = slug->body.bod.bod.list_prev;
              if ( v24 )
                v24->list_next = slug->body.bod.bod.list_next;
              else
LABEL_77:
                p_active_bod_list->first = slug->body.bod.bod.list_next;
LABEL_78:
              slug->body.bod.bod.list_next = p_active_bod_list->free_top;
              p_active_bod_list->free_top = &slug->body.bod.bod;
              v39 = slug->body.bod.bod.list_flags;
              v40 = slug->sprite;
              BYTE1(v39) &= ~2u;
              slug->body.bod.bod.list_flags = v39;
              kill_sprite((int)v40);
            }
          }
          else
          {
LABEL_70:
            report_errorf(aListRemove);
            kill_sprite((int)slug->sprite);
          }
        }
        break;
      default:
        goto LABEL_39;
    }
  }
}
