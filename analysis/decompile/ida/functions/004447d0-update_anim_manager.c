/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_anim_manager @ 0x4447d0 */
/* selector: update_anim_manager */

// Advances one queued presentation animation channel, applying loop, bounce, or clamp flags and starting the next queued entry when the current one finishes.
void __thiscall update_anim_manager(AnimationDispatchState *manager)
{
  int32_t active; // eax
  int32_t v2; // edx
  bool v3; // zf
  __int16 v4; // ax
  _BYTE *active_keyframe; // eax
  double v6; // st7
  double progress; // st7
  int32_t *queued_animation_ids; // eax
  _DWORD *self_ref; // esi
  char *v10; // esi
  float *v11; // edi
  int32_t v12; // esi
  float v13; // [esp+8h] [ebp-4h]

  active = manager->active;
  v2 = 0;
  v3 = manager->active == 0;
  manager->edge_latched = 0;
  if ( !v3 )
  {
    if ( active == 1 )
    {
      v13 = (*((float *)MEMORY[0x4DF904] + 119186) + *((float *)MEMORY[0x4DF904] + 119186) - 0.2 + 1.0)
          * manager->progress_step
          + manager->progress;
      manager->progress = v13;
      if ( v13 >= 1.0 )
      {
        v4 = *(_WORD *)manager->active_keyframe;
        if ( (v4 & 1) != 0 )
        {
          manager->edge_latched = 1;
          manager->progress = v13 - 1.0;
        }
        else if ( (v4 & 4) != 0 )
        {
          manager->progress = 0.99900001;
          manager->progress_step = 0.0;
          manager->edge_latched = 1;
        }
        else if ( (v4 & 2) != 0 )
        {
          manager->progress = 2.0 - v13;
          manager->progress_step = manager->progress_step * -1.0;
        }
      }
      if ( manager->progress < 0.0 )
      {
        active_keyframe = manager->active_keyframe;
        if ( (*active_keyframe & 2) != 0 )
        {
          manager->progress = -manager->progress;
          v6 = manager->progress_step * -1.0;
          manager->edge_latched = 1;
          manager->progress_step = v6;
        }
        if ( (*active_keyframe & 8) != 0 )
        {
          manager->progress = 0.0;
          manager->progress_step = 0.0;
          manager->edge_latched = 1;
        }
      }
      if ( manager->progress >= 0.0 )
      {
        if ( manager->progress <= 0.99989998 )
          progress = manager->progress;
        else
          progress = 0.99989998;
      }
      else
      {
        progress = 0.0;
      }
      manager->progress = progress;
    }
    if ( manager->edge_latched && manager->queued_animation_count > 0 )
    {
      queued_animation_ids = manager->queued_animation_ids;
      if ( manager->queued_animation_ids[0] == -1 )
      {
        self_ref = manager->self_ref;
        manager->progress = 0.0;
        manager->progress_step = 0.0;
        self_ref[1] &= ~0x20u;
      }
      else
      {
        *((_DWORD *)manager->self_ref + 1) |= 0x20u;
        v10 = (char *)manager->queue_sentinel + 128 * *queued_animation_ids + 36;
        v11 = *(float **)(*(_DWORD *)v10 + 188);
        manager->progress = 0.0;
        manager->active_keyframe = v11;
        manager->progress_step = v11[4];
        *((_DWORD *)manager->self_ref + 9) = *(_DWORD *)v10;
      }
      v12 = manager->queued_animation_count - 1;
      manager->queued_animation_count = v12;
      if ( v12 > 0 )
      {
        do
        {
          ++v2;
          *queued_animation_ids = queued_animation_ids[1];
          ++queued_animation_ids;
        }
        while ( v2 < manager->queued_animation_count );
      }
    }
  }
}

