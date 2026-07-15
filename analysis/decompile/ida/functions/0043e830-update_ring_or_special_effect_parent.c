/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_ring_or_special_effect_parent @ 0x43e830 */
/* selector: update_ring_or_special_effect_parent */

// Windows `cRSubRing::AI()`: advances a SubgameRuntime-owned SubRing and its ten inline SubRingStar children, handles collect/miss transitions, unlinks inactive parents from GameRoot's active BOD list, and returns child sprites to the sprite manager. The constructor table at 0x49732c points directly here.
void __thiscall update_ring_or_special_effect_parent(SubRing *ring)
{
  SubgameRuntime *rate_source; // eax
  int32_t v3; // ecx
  double v4; // st7
  unsigned __int8 v6; // c0
  unsigned __int8 v7; // c3
  int v8; // ebp
  SubRingStar *particles; // edi
  Player *owner_player; // ecx
  uint32_t list_flags; // eax
  FrameBodList *p_active_bod_list; // ecx
  struct BodNode *list_next; // eax
  struct BodNode *list_prev; // eax
  uint32_t v15; // eax
  int *v16; // esi
  int v17; // edi
  int v18; // ebp
  SubRingStar *v19; // edi
  double v20; // st7
  uint32_t v21; // eax
  FrameBodList *v22; // ecx
  struct BodNode *v23; // eax
  struct BodNode *v24; // eax
  uint32_t v25; // eax
  int *v26; // esi
  int v27; // edi
  int v28; // edx
  Vec4 *p_position; // eax
  float *p_radius; // ecx
  double v31; // st7
  float *v32; // esi
  int v33; // ebp
  SubRingStar *v34; // edi
  double v35; // st7
  uint32_t v36; // eax
  FrameBodList *v37; // ecx
  struct BodNode *v38; // eax
  struct BodNode *v39; // eax
  uint32_t v40; // eax
  int *v41; // esi
  int v42; // edi
  Vec4 *v43; // edx
  float *v44; // eax
  int v45; // ecx
  double v46; // st7
  float *v47; // esi
  float v48; // [esp+14h] [ebp-14h]
  float v49; // [esp+18h] [ebp-10h]
  float v50; // [esp+18h] [ebp-10h]
  float v51; // [esp+20h] [ebp-8h]
  float v52; // [esp+24h] [ebp-4h]

  rate_source = ring->rate_source;
  if ( !rate_source->subgame_pause_gate )
  {
    v3 = ring->star_shower_counter + 1;
    ring->star_shower_counter = v3;
    if ( v3 == 3 )
      ring->star_shower_counter = 0;
    switch ( ring->state )
    {
      case SUB_RING_STATE_ACTIVE:
        if ( ring->oscillate_x )
        {
          v4 = ring->active_phase_step + ring->active_phase;
          ring->active_phase = v4;
          if ( v6 | v7 )
          {
            if ( v4 < 0.0 )
              ring->active_phase = v4 + 6.2831855;
          }
          else
          {
            ring->active_phase = v4 - 6.2831855;
          }
          ring->body.transform.position.x = sine(ring->active_phase) * 3.0;
        }
        v8 = 10;
        particles = ring->particles;
        do
        {
          update_ring_or_special_effect_particle(particles++);
          --v8;
        }
        while ( v8 );
        owner_player = ring->owner_player;
        if ( ring->body.transform.position.z >= (double)owner_player->interaction_max_z )
        {
          if ( owner_player->lives < ring->owner_lives_snapshot )
            ring->state = SUB_RING_STATE_EXPAND_PENDING;
        }
        else
        {
          list_flags = ring->body.bod.bod.list_flags;
          ring->state = SUB_RING_STATE_INACTIVE;
          p_active_bod_list = &g_game_base->active_bod_list;
          if ( (list_flags & 0x200) != 0 )
          {
            if ( (list_flags & 0x40) != 0 )
            {
              report_errorf(aListRemoveNext);
            }
            else
            {
              list_next = ring->body.bod.bod.list_next;
              if ( list_next )
                list_next->list_prev = ring->body.bod.bod.list_prev;
              list_prev = ring->body.bod.bod.list_prev;
              if ( list_prev )
                list_prev->list_next = ring->body.bod.bod.list_next;
              else
                p_active_bod_list->first = (FrameBodBase *)ring->body.bod.bod.list_next;
              ring->body.bod.bod.list_next = (struct BodNode *)p_active_bod_list->free_top;
              p_active_bod_list->free_top = (FrameBodBase *)ring;
              v15 = ring->body.bod.bod.list_flags;
              BYTE1(v15) &= ~2u;
              ring->body.bod.bod.list_flags = v15;
            }
          }
          else
          {
            report_errorf(aListRemove);
          }
          v16 = (int *)ring->particles;
          v17 = 10;
          do
          {
            kill_sprite(*v16);
            v16 += 8;
            --v17;
          }
          while ( v17 );
        }
        return;
      case SUB_RING_STATE_COLLECT_PENDING:
        ring->state = SUB_RING_STATE_COLLECTING;
        ring->transition_progress = 0.0;
        ring->transition_step = rate_source->subgame_rate * 0.069444448;
        goto LABEL_30;
      case SUB_RING_STATE_COLLECTING:
LABEL_30:
        v18 = 10;
        v19 = ring->particles;
        do
        {
          update_ring_or_special_effect_particle(v19++);
          --v18;
        }
        while ( v18 );
        v20 = ring->transition_step + ring->transition_progress;
        ring->transition_progress = v20;
        if ( v20 <= 1.0 )
        {
          v28 = 10;
          p_position = &ring->body.transform.position;
          p_radius = &ring->particles[0].radius;
          v49 = ring->owner_player->cached_camera_target_world.z + 0.2;
          v51 = ring->owner_player->cached_camera_target_world.y - ring->body.transform.position.y;
          v52 = v49 - ring->body.transform.position.z;
          v48 = v51 * 0.94;
          v50 = v52 * 0.94;
          ring->body.transform.position.x = (ring->owner_player->cached_camera_target_world.x
                                           - ring->body.transform.position.x)
                                          * 0.94
                                          + ring->body.transform.position.x;
          ring->body.transform.position.y = v48 + ring->body.transform.position.y;
          ring->body.transform.position.z = v50 + ring->body.transform.position.z;
          do
          {
            v31 = *p_radius * 0.94;
            v32 = p_radius - 5;
            p_radius += 8;
            --v28;
            *(p_radius - 8) = v31;
            *v32 = p_position->x;
            v32[1] = p_position->y;
            v32[2] = p_position->z;
          }
          while ( v28 );
        }
        else
        {
          v21 = ring->body.bod.bod.list_flags;
          ring->state = SUB_RING_STATE_INACTIVE;
          v22 = &g_game_base->active_bod_list;
          if ( (v21 & 0x200) != 0 )
          {
            if ( (v21 & 0x40) != 0 )
            {
              report_errorf(aListRemoveNext);
            }
            else
            {
              v23 = ring->body.bod.bod.list_next;
              if ( v23 )
                v23->list_prev = ring->body.bod.bod.list_prev;
              v24 = ring->body.bod.bod.list_prev;
              if ( v24 )
                v24->list_next = ring->body.bod.bod.list_next;
              else
                v22->first = (FrameBodBase *)ring->body.bod.bod.list_next;
              ring->body.bod.bod.list_next = (struct BodNode *)v22->free_top;
              v22->free_top = (FrameBodBase *)ring;
              v25 = ring->body.bod.bod.list_flags;
              BYTE1(v25) &= ~2u;
              ring->body.bod.bod.list_flags = v25;
            }
          }
          else
          {
            report_errorf(aListRemove);
          }
          v26 = (int *)ring->particles;
          v27 = 10;
          do
          {
            kill_sprite(*v26);
            v26 += 8;
            --v27;
          }
          while ( v27 );
        }
        return;
      case SUB_RING_STATE_EXPAND_PENDING:
        ring->state = SUB_RING_STATE_EXPANDING;
        ring->transition_progress = 0.0;
        ring->transition_step = rate_source->subgame_rate * 0.069444448;
        goto LABEL_50;
      case SUB_RING_STATE_EXPANDING:
LABEL_50:
        v33 = 10;
        v34 = ring->particles;
        do
        {
          update_ring_or_special_effect_particle(v34++);
          --v33;
        }
        while ( v33 );
        v35 = ring->transition_step + ring->transition_progress;
        ring->transition_progress = v35;
        if ( v35 <= 1.0 )
        {
          v43 = &ring->body.transform.position;
          v44 = &ring->particles[0].radius;
          v45 = 10;
          do
          {
            v46 = *v44 * 1.1;
            v47 = v44 - 5;
            v44 += 8;
            --v45;
            *(v44 - 8) = v46;
            *v47 = v43->x;
            v47[1] = v43->y;
            v47[2] = v43->z;
          }
          while ( v45 );
        }
        else
        {
          v36 = ring->body.bod.bod.list_flags;
          ring->state = SUB_RING_STATE_INACTIVE;
          v37 = &g_game_base->active_bod_list;
          if ( (v36 & 0x200) != 0 )
          {
            if ( (v36 & 0x40) != 0 )
            {
              report_errorf(aListRemoveNext);
            }
            else
            {
              v38 = ring->body.bod.bod.list_next;
              if ( v38 )
                v38->list_prev = ring->body.bod.bod.list_prev;
              v39 = ring->body.bod.bod.list_prev;
              if ( v39 )
                v39->list_next = ring->body.bod.bod.list_next;
              else
                v37->first = (FrameBodBase *)ring->body.bod.bod.list_next;
              ring->body.bod.bod.list_next = (struct BodNode *)v37->free_top;
              v37->free_top = (FrameBodBase *)ring;
              v40 = ring->body.bod.bod.list_flags;
              BYTE1(v40) &= ~2u;
              ring->body.bod.bod.list_flags = v40;
            }
          }
          else
          {
            report_errorf(aListRemove);
          }
          v41 = (int *)ring->particles;
          v42 = 10;
          do
          {
            kill_sprite(*v41);
            v41 += 8;
            --v42;
          }
          while ( v42 );
        }
        break;
      default:
        return;
    }
  }
}
