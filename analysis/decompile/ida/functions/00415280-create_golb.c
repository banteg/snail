/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: create_golb @ 0x415280 */
/* selector: create_golb */

// Void Windows `cRSubGolb::Create(cRSubGoldy*, int, int)`: initializes one Golb shot actor from the player's current movement_flags family and emitter slot, choosing the matching spawn anchor, velocity lane, render owner, and any path-follow state before dispatching the actor's slot-zero AI callback. The sole Windows caller and the independent iOS body establish no result contract.
void __thiscall create_golb(GolbShot *shot, Player *player, int32_t spawn_selector, int32_t emitter_index)
{
  BodNode **p_first; // eax
  BodNode *first; // ecx
  struct BodNode *list_prev; // ecx
  uint32_t movement_flags; // eax
  Player *owner_player; // eax
  Vec4 *p_position; // edi
  double v11; // st7
  Player *v12; // ecx
  uint32_t v13; // eax
  double v14; // st7
  double v15; // st7
  float v16; // eax
  double v17; // st7
  float v18; // edx
  double x; // st7
  double v20; // st7
  float g; // eax
  float v22; // edx
  double v23; // st7
  float v24; // ecx
  Vec3 *snail_hotspots_world; // edx
  double v26; // st7
  double v27; // st7
  float b; // ecx
  double v29; // st7
  float v30; // eax
  double v31; // st7
  float v32; // edx
  double v33; // st7
  float v34; // ecx
  int32_t kind; // eax
  int v36; // eax
  SubgameRuntime *game; // ecx
  double v38; // st7
  RenderableBod *p_tertiary_body; // ecx
  BodNode **v40; // eax
  BodNode *v41; // edx
  struct BodNode *v42; // edx
  uint32_t list_flags; // eax
  EnemyManager *p_enemy_manager; // ecx
  ContactTargetEntry *v45; // eax
  ContactTargetObject *object; // ecx
  int32_t v47; // edx
  Vec3 *v48; // eax
  float z; // eax
  SubgameRuntime *v50; // ecx
  Vapour *p_vapour; // ebp
  double v52; // st7
  BodBase *p_golb_vapour_list_head; // eax
  struct BodNode *list_next; // eax
  SubgameRuntime *v55; // ecx
  Player *v56; // edx
  _DWORD *sprite; // eax
  char *v58; // eax
  Player *v59; // ecx
  float v60; // eax
  double v61; // st7
  float v62; // eax
  float y; // ecx
  float v64; // eax
  Color4f color; // [esp+Ch] [ebp-10h] BYREF

  shot->skip_one_tick = 0;
  shot->slug_bounce_armed = 0;
  if ( (shot->primary_body.bod.bod.list_flags & 0x200) != 0 )
  {
    report_errorf(aListAdd);
  }
  else
  {
    p_first = &g_game_base->active_bod_list.first;
    first = g_game_base->active_bod_list.first;
    if ( first )
    {
      first->list_prev = &shot->primary_body.bod.bod;
      (*p_first)->list_prev->list_next = *p_first;
      list_prev = (*p_first)->list_prev;
      *p_first = list_prev;
      list_prev->list_prev = nullptr;
    }
    else
    {
      *p_first = &shot->primary_body.bod.bod;
      shot->primary_body.bod.bod.list_prev = nullptr;
      (*p_first)->list_next = nullptr;
    }
    shot->primary_body.bod.bod.list_flags |= 0x200u;
  }
  shot->owner_player = player;
  movement_flags = player->movement_flags;
  if ( (movement_flags & 7) != 0 )
  {
    shot->kind = 0;
  }
  else if ( (movement_flags & 0x18) != 0 )
  {
    shot->kind = 1;
  }
  else if ( (movement_flags & 0x60) != 0 )
  {
    shot->kind = 2;
  }
  set_matrix_identity(&shot->source_matrix);
  owner_player = shot->owner_player;
  p_position = &shot->flight_transform.position;
  shot->state = 1;
  shot->flight_transform.position.x = owner_player->body.transform.position.x;
  shot->flight_transform.position.y = owner_player->body.transform.position.y;
  shot->flight_transform.position.z = owner_player->body.transform.position.z;
  v11 = owner_player->body.transform.basis_forward.x * 0.5;
  color.g = owner_player->body.transform.basis_forward.y * 0.5;
  color.b = owner_player->body.transform.basis_forward.z * 0.5;
  shot->flight_transform.position.x = v11 + shot->flight_transform.position.x;
  shot->flight_transform.position.y = color.g + shot->flight_transform.position.y;
  shot->flight_transform.position.z = color.b + shot->flight_transform.position.z;
  v12 = shot->owner_player;
  v13 = v12->movement_flags;
  if ( (v13 & 5) != 0 )
  {
    switch ( spawn_selector )
    {
      case 3:
        snail_hotspots_world = v12->presentation.snail_hotspots_world;
        break;
      case 2:
        snail_hotspots_world = &v12->presentation.snail_hotspots_world[2];
        break;
      case 1:
        snail_hotspots_world = &v12->presentation.snail_hotspots_world[4];
        break;
      default:
LABEL_43:
        if ( (v12->movement_flags & 4) == 0 )
          goto LABEL_50;
        if ( spawn_selector == 3 )
        {
          v26 = v12->velocity.z + 1.0;
          color.r = 0.1;
          color.g = 0.0;
          color.b = v26;
          v27 = p_position->x + 0.5;
          shot->velocity.x = 0.1;
          b = color.b;
          shot->velocity.y = 0.0;
          p_position->x = v27;
          shot->velocity.z = b;
          goto LABEL_51;
        }
        if ( spawn_selector != 2 )
        {
          v31 = v12->velocity.z + 1.0;
          color.r = 0.0;
          color.g = 0.0;
          shot->velocity.x = 0.0;
          color.b = v31;
          v32 = color.b;
          shot->velocity.y = 0.0;
          shot->velocity.z = v32;
          goto LABEL_51;
        }
        v29 = v12->velocity.z + 1.0;
        color.r = -0.1;
        color.g = 0.0;
        shot->velocity.x = -0.1;
        color.b = v29;
        v30 = color.b;
        shot->velocity.y = 0.0;
        x = p_position->x;
        shot->velocity.z = v30;
LABEL_48:
        p_position->x = x - 0.5;
        goto LABEL_51;
    }
    p_position->x = snail_hotspots_world->x;
    shot->flight_transform.position.y = snail_hotspots_world->y;
    shot->flight_transform.position.z = snail_hotspots_world->z;
    goto LABEL_43;
  }
  if ( (v13 & 2) != 0 )
  {
    if ( spawn_selector == 2 )
    {
      p_position->x = v12->presentation.snail_hotspots_world[0].x;
      shot->flight_transform.position.y = v12->presentation.snail_hotspots_world[0].y;
      shot->flight_transform.position.z = v12->presentation.snail_hotspots_world[0].z;
      v14 = p_position->x + 0.5;
LABEL_19:
      p_position->x = v14;
      goto LABEL_50;
    }
    if ( spawn_selector == 1 )
    {
      p_position->x = v12->presentation.snail_hotspots_world[2].x;
      shot->flight_transform.position.y = v12->presentation.snail_hotspots_world[2].y;
      shot->flight_transform.position.z = v12->presentation.snail_hotspots_world[2].z;
      v14 = p_position->x - 0.5;
      goto LABEL_19;
    }
LABEL_50:
    v33 = v12->velocity.z + 1.0;
    color.r = 0.0;
    color.g = 0.0;
    shot->velocity.x = 0.0;
    color.b = v33;
    v34 = color.b;
    shot->velocity.y = 0.0;
    shot->velocity.z = v34;
    goto LABEL_51;
  }
  if ( (v13 & 0x18) != 0 )
  {
    if ( spawn_selector == 2 )
    {
      p_position->x = v12->presentation.snail_hotspots_world[6].x;
      shot->flight_transform.position.y = v12->presentation.snail_hotspots_world[6].y;
      shot->flight_transform.position.z = v12->presentation.snail_hotspots_world[6].z;
      if ( v12->body.transform.basis_forward.z > 0.0 )
      {
        spawn_selector = (int32_t)&v12->presentation.snail_hotspots_world[6].z;
LABEL_35:
        v23 = v12->velocity.z + 1.0;
        color.r = 0.0;
        color.g = 0.0;
        shot->skip_one_tick = 1;
        shot->velocity.x = 0.0;
        color.b = v23;
        v24 = color.b;
        shot->velocity.y = 0.0;
        shot->velocity.z = v24;
        goto LABEL_51;
      }
    }
    else
    {
      p_position->x = v12->presentation.snail_hotspots_world[7].x;
      shot->flight_transform.position.y = v12->presentation.snail_hotspots_world[7].y;
      shot->flight_transform.position.z = v12->presentation.snail_hotspots_world[7].z;
      if ( v12->body.transform.basis_forward.z > 0.0 )
      {
        spawn_selector = (int32_t)&v12->presentation.snail_hotspots_world[6].z;
        goto LABEL_35;
      }
    }
    spawn_selector = 0;
    goto LABEL_35;
  }
  if ( (v13 & 0x60) != 0 )
  {
    color.r = 0.0;
    color.g = 0.0;
    p_position->x = v12->presentation.snail_hotspots_world[10].x;
    shot->flight_transform.position.y = v12->presentation.snail_hotspots_world[10].y;
    shot->flight_transform.position.z = v12->presentation.snail_hotspots_world[10].z;
    v20 = v12->velocity.z + 0.60000002;
    g = color.g;
    shot->velocity.x = color.r;
    color.b = v20;
    v22 = color.b;
    shot->velocity.y = g;
    shot->velocity.z = v22;
    goto LABEL_51;
  }
  if ( (v13 & 0x29) != 0 )
  {
    v15 = v12->velocity.z + 1.0;
    color.r = 0.0;
    color.g = 0.0;
    shot->velocity.x = 0.0;
    color.b = v15;
    v16 = color.b;
    shot->velocity.y = 0.0;
    shot->velocity.z = v16;
    goto LABEL_51;
  }
  if ( (v13 & 0x52) != 0 )
  {
    v17 = v12->velocity.z + 1.0;
    color.r = 0.0;
    color.g = 0.0;
    shot->velocity.x = 0.0;
    color.b = v17;
    v18 = color.b;
    shot->velocity.y = 0.0;
    x = p_position->x;
    shot->velocity.z = v18;
    if ( spawn_selector == 2 )
    {
      p_position->x = x + 0.5;
      goto LABEL_51;
    }
    goto LABEL_48;
  }
LABEL_51:
  if ( shot->kind == 1 )
  {
    shot->velocity.x = shot->velocity.x + shot->velocity.x;
    shot->velocity.y = shot->velocity.y + shot->velocity.y;
    shot->velocity.z = shot->velocity.z + shot->velocity.z;
  }
  if ( shot->kind == 2 )
  {
    shot->velocity.x = shot->velocity.x * 0.80000001;
    shot->velocity.y = shot->velocity.y * 0.80000001;
    shot->velocity.z = shot->velocity.z * 0.80000001;
  }
  shot->direction.x = shot->velocity.x;
  shot->direction.y = shot->velocity.y;
  shot->direction.z = shot->velocity.z;
  kind = shot->kind;
  if ( kind )
  {
    v36 = kind - 1;
    if ( v36 )
    {
      if ( v36 == 1 )
      {
        game = shot->game;
        shot->lifetime = 0.0;
        v38 = game->subgame_rate * 0.027777776;
        p_tertiary_body = &shot->tertiary_body;
        shot->rocket_owner_shot = shot;
        shot->spin = 0.0;
        shot->spin_step = 0.20943952;
        shot->homing_target_object = nullptr;
        shot->lifetime_step = v38;
        if ( (shot->tertiary_body.bod.bod.list_flags & 0x200) != 0 )
        {
          report_errorf(aListAdd);
        }
        else
        {
          v40 = &g_game_base->active_bod_list.first;
          v41 = g_game_base->active_bod_list.first;
          if ( v41 )
          {
            v41->list_prev = &p_tertiary_body->bod.bod;
            (*v40)->list_prev->list_next = *v40;
            v42 = (*v40)->list_prev;
            *v40 = v42;
            v42->list_prev = nullptr;
          }
          else
          {
            *v40 = &p_tertiary_body->bod.bod;
            shot->tertiary_body.bod.bod.list_prev = nullptr;
            (*v40)->list_next = nullptr;
          }
          list_flags = shot->tertiary_body.bod.bod.list_flags;
          BYTE1(list_flags) |= 2u;
          shot->tertiary_body.bod.bod.list_flags = list_flags;
        }
        p_enemy_manager = &shot->game->enemy_manager;
        shot->object_ref = (void *)emitter_index;
        v45 = search_path_for_golb(p_enemy_manager, (const Vec3 *)&shot->flight_transform.position);
        if ( v45 )
        {
          object = v45->object;
          shot->homing_target_object = object;
          if ( !v45->kind )
          {
            v47 = object->list_flags;
            BYTE1(v47) |= 0x10u;
            object->list_flags = v47;
          }
          v48 = &v45->position;
          shot->homing_target.x = v48->x;
          shot->homing_target.y = v48->y;
          z = v48->z;
          shot->homing_blend = 0.0;
          shot->homing_target.z = z;
          shot->homing_blend_step = 0.033333335;
        }
      }
    }
    else
    {
      v50 = shot->game;
      shot->lifetime = 0.0;
      p_vapour = &shot->vapour;
      v52 = v50->subgame_rate * 0.041666668;
      shot->vapour_owner_shot = shot;
      shot->lifetime_step = v52;
      p_golb_vapour_list_head = &g_game_base->subgame.golb_vapour_list_head;
      if ( (shot->vapour.body.bod.bod.list_flags & 0x200) != 0 )
      {
        report_errorf(aListAddafter);
      }
      else
      {
        shot->vapour.body.bod.bod.list_prev = &p_golb_vapour_list_head->bod;
        shot->vapour.body.bod.bod.list_next = p_golb_vapour_list_head->bod.list_next;
        p_golb_vapour_list_head->bod.list_next = &p_vapour->body.bod.bod;
        list_next = shot->vapour.body.bod.bod.list_next;
        if ( list_next )
          list_next->list_prev = &p_vapour->body.bod.bod;
        shot->vapour.body.bod.bod.list_flags |= 0x200u;
      }
      reset_vapour(&shot->vapour, (float *)spawn_selector);
      store_color4f(&shot->vapour.body.bod.color, 1.0, 1.0, 1.0, 0.99000001);
      shot->object_ref = (void *)emitter_index;
      add_vapour_point(&shot->vapour, &shot->flight_transform);
      (*(void (__thiscall **)(Vapour *))p_vapour->body.bod.bod.vtable)(&shot->vapour);
    }
  }
  else
  {
    v55 = shot->game;
    v56 = shot->owner_player;
    shot->lifetime = 0.0;
    shot->lifetime_step = v55->subgame_rate * 0.041666668;
    sprite = allocate_sprite(g_sprite_manager, v56->player_slot, 130, -1, -1);
    shot->render_body_owner = sprite;
    sprite[1] |= 0x800u;
    *((_DWORD *)shot->render_body_owner + 26) = 0;
    *((_DWORD *)shot->render_body_owner + 27) = 0;
    *((_DWORD *)shot->render_body_owner + 30) = 0;
    *(tColour *)((char *)shot->render_body_owner + 44) = *set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
    *((_DWORD *)shot->render_body_owner + 24) = 1056629064;
    *((_DWORD *)shot->render_body_owner + 25) = 1056629064;
    v58 = (char *)shot->render_body_owner + 72;
    *(float *)v58 = p_position->x;
    *((_DWORD *)v58 + 1) = LODWORD(shot->flight_transform.position.y);
    *((_DWORD *)v58 + 2) = LODWORD(shot->flight_transform.position.z);
    *((float *)shot->render_body_owner + 31) = ((double)next_math_random_value() - 16384.0) * 0.0001917476;
    *((float *)shot->render_body_owner + 32) = shot->game->subgame_rate * 0.58177644;
    shot->object_ref = (void *)emitter_index;
  }
  v59 = shot->owner_player;
  if ( v59->follow_state.active == 1 && v59->follow_state.vertical_offset < 0.5 )
  {
    shot->path_follow.active = 1;
    shot->path_follow.template_record = v59->follow_state.template_record;
    shot->path_follow.source_cell = v59->follow_state.source_cell;
    shot->path_follow.sample_index = v59->follow_state.sample_index;
    shot->path_follow.progress = v59->follow_state.progress;
    shot->path_follow.vertical_offset = 0.0;
    shot->path_follow.output_position.x = v59->follow_state.output_position.x;
    shot->path_follow.output_position.y = v59->follow_state.output_position.y;
    v60 = v59->follow_state.output_position.z;
    shot->path_follow.shot = shot;
    shot->path_follow.output_position.z = v60;
    shot->path_entry_z_latch = v59->follow_state.output_position.z;
  }
  else
  {
    shot->path_follow.active = 0;
    shot->path_entry_z_latch = -1.0;
  }
  v61 = vector_magnitude(&shot->velocity);
  v62 = p_position->x;
  y = shot->flight_transform.position.y;
  shot->path_factor = v61;
  shot->previous_flight_transform.position.x = v62;
  v64 = shot->flight_transform.position.z;
  shot->previous_flight_transform.position.y = y;
  shot->previous_flight_transform.position.z = v64;
  (*(void (__thiscall **)(GolbShot *))shot->primary_body.bod.bod.vtable)(shot);
}
