/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_anim_manager @ 0x4447d0 */
/* selector: update_anim_manager */

// Exact Windows `cRAnimManager::AI()`: advances the authored 0x48-byte queue owner, applies loop, bounce, or clamp flags, then installs the next owned RenderableBod slot's Object and ObjectAnimation on its borrowed Snail or animation-channel target. Android independently preserves the same ownership chain with port-specific slot layout.
void __thiscall update_anim_manager(AnimManager *manager)
{
  int32_t state; // eax
  int32_t v2; // edx
  bool v3; // zf
  ObjectAnimationFlags flags; // ax
  ObjectAnimation *active_animation; // eax
  double v6; // st7
  double progress; // st7
  int32_t *queued_animations; // eax
  RenderableBod *target_model; // esi
  Object **p_object; // esi
  ObjectAnimation *animation; // edi
  int32_t v12; // esi
  float v13; // [esp+8h] [ebp-4h]

  state = manager->state;
  v2 = 0;
  v3 = manager->state == 0;
  manager->completed = 0;
  if ( !v3 )
  {
    if ( state == 1 )
    {
      v13 = (g_game_base->subgame.rate_or_level_arg.base_rate
           + g_game_base->subgame.rate_or_level_arg.base_rate
           - 0.2
           + 1.0)
          * manager->progress_step
          + manager->progress;
      manager->progress = v13;
      if ( v13 >= 1.0 )
      {
        flags = manager->active_animation->flags;
        if ( (flags & 1) != 0 )
        {
          manager->completed = 1;
          manager->progress = v13 - 1.0;
        }
        else if ( (flags & 4) != 0 )
        {
          manager->progress = 0.99900001;
          manager->progress_step = 0.0;
          manager->completed = 1;
        }
        else if ( (flags & 2) != 0 )
        {
          manager->progress = 2.0 - v13;
          manager->progress_step = manager->progress_step * -1.0;
        }
      }
      if ( manager->progress < 0.0 )
      {
        active_animation = manager->active_animation;
        if ( (active_animation->flags & 2) != 0 )
        {
          manager->progress = -manager->progress;
          v6 = manager->progress_step * -1.0;
          manager->completed = 1;
          manager->progress_step = v6;
        }
        if ( (active_animation->flags & 8) != 0 )
        {
          manager->progress = 0.0;
          manager->progress_step = 0.0;
          manager->completed = 1;
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
    if ( manager->completed && manager->queue_count > 0 )
    {
      queued_animations = manager->queued_animations;
      if ( manager->queued_animations[0] == -1 )
      {
        target_model = manager->target_model;
        manager->progress = 0.0;
        manager->progress_step = 0.0;
        target_model->bod.bod.list_flags &= ~0x20u;
      }
      else
      {
        manager->target_model->bod.bod.list_flags |= 0x20u;
        p_object = &manager->animation_slots[*queued_animations].body.bod.object;
        animation = (*p_object)->animation;
        manager->progress = 0.0;
        manager->active_animation = animation;
        manager->progress_step = animation->progress_step;
        manager->target_model->bod.object = *p_object;
      }
      v12 = manager->queue_count - 1;
      manager->queue_count = v12;
      if ( v12 > 0 )
      {
        do
        {
          ++v2;
          *queued_animations = queued_animations[1];
          ++queued_animations;
        }
        while ( v2 < manager->queue_count );
      }
    }
  }
}
