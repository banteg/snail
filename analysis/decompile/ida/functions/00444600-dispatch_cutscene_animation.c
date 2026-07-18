/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: dispatch_cutscene_animation @ 0x444600 */
/* selector: dispatch_cutscene_animation */

// Stable Windows name for `cRSnail::SetAnimation(int, bool, int)`: queues an animation on the exact embedded Snail or begins it immediately through the root AnimManager and one of ten owned 0x80-byte RenderableBod slots, following the slot Object link to Object::animation.
int32_t __thiscall dispatch_cutscene_animation(
        Snail *snail,
        int32_t animation_id,
        uint8_t immediate,
        int32_t mode_flags)
{
  ObjectAnimation *animation; // eax
  ObjectAnimation *active_animation; // edx
  double progress_step; // st7
  char v8; // c0
  double v9; // st7
  ObjectAnimation *v10; // edx
  double v12; // st7
  char v13; // c0
  Object *object; // eax
  RenderableBod *target_model; // ecx
  int32_t result; // eax

  if ( immediate )
  {
    animation = snail->cutscene_animation_slots[animation_id].body.bod.object->animation;
    snail->anim_manager.active_animation = animation;
    if ( mode_flags != -1 )
      animation->flags = mode_flags;
    active_animation = snail->anim_manager.active_animation;
    if ( (active_animation->flags & 8) != 0 )
    {
      progress_step = active_animation->progress_step;
      if ( v8 )
        progress_step = -progress_step;
      v9 = -progress_step;
      snail->anim_manager.progress_step = v9;
      snail->anim_manager.progress = v9 + 1.0;
    }
    else
    {
      v10 = snail->anim_manager.active_animation;
      snail->anim_manager.progress = 0.0;
      v12 = v10->progress_step;
      if ( v13 )
        v12 = -v12;
      snail->anim_manager.progress_step = v12;
    }
    object = snail->cutscene_animation_slots[animation_id].body.bod.object;
    snail->anim_manager.queue_count = 0;
    snail->body.bod.object = object;
    target_model = snail->anim_manager.target_model;
    result = target_model->bod.bod.list_flags;
    LOBYTE(result) = result | 0x20;
    target_model->bod.bod.list_flags = result;
  }
  else
  {
    snail->anim_manager.queued_animations[snail->anim_manager.queue_count] = animation_id;
    result = snail->anim_manager.queue_count + 1;
    snail->anim_manager.queue_count = result;
  }
  return result;
}
