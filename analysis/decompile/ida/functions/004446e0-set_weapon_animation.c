/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_weapon_animation @ 0x4446e0 */
/* selector: set_weapon_animation */

int32_t __thiscall set_weapon_animation(
        PresentationAnimationChannel *channel,
        int32_t animation_id,
        uint8_t immediate,
        int32_t initial_frame)
{
  _WORD *v4; // eax
  float *active_keyframe; // edx
  double v7; // st7
  char v8; // c0
  double v9; // st7
  float *v10; // edx
  double v12; // st7
  char v13; // c0
  SnailVisual *v14; // eax
  _DWORD *self_ref; // ecx
  int32_t result; // eax

  if ( immediate )
  {
    v4 = *(_WORD **)(*(_DWORD *)&channel->animation_slot_table[128 * animation_id] + 188);
    channel->anim_manager.active_keyframe = v4;
    if ( initial_frame != -1 )
      *v4 = initial_frame;
    active_keyframe = (float *)channel->anim_manager.active_keyframe;
    if ( (*(_BYTE *)active_keyframe & 8) != 0 )
    {
      v7 = active_keyframe[4];
      if ( v8 )
        v7 = -v7;
      v9 = -v7;
      channel->anim_manager.progress_step = v9;
      channel->anim_manager.progress = v9 + 1.0;
    }
    else
    {
      v10 = (float *)channel->anim_manager.active_keyframe;
      channel->anim_manager.progress = 0.0;
      v12 = v10[4];
      if ( v13 )
        v12 = -v12;
      channel->anim_manager.progress_step = v12;
    }
    v14 = *(SnailVisual **)&channel->animation_slot_table[128 * animation_id];
    channel->anim_manager.queued_animation_count = 0;
    channel->visual_root = v14;
    self_ref = channel->anim_manager.self_ref;
    result = self_ref[1];
    LOBYTE(result) = result | 0x20;
    self_ref[1] = result;
  }
  else
  {
    channel->anim_manager.queued_animation_ids[channel->anim_manager.queued_animation_count] = animation_id;
    result = channel->anim_manager.queued_animation_count + 1;
    channel->anim_manager.queued_animation_count = result;
  }
  return result;
}

