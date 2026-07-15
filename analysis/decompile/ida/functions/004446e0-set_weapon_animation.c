/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_weapon_animation @ 0x4446e0 */
/* selector: set_weapon_animation */

// Authored void `cRWeapon::SetAnimation(int, bool, int)` over one exact 0x3dc-byte Weapon owner: queues an id or immediately selects one of five owned 0x80-byte RenderableBod slots, follows its Object::animation link, and installs the borrowed Object on the channel. Android independently preserves the void mutator contract.
void __thiscall set_weapon_animation(Weapon *weapon, int32_t animation_id, uint8_t immediate, int32_t mode_flags)
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
  uint32_t list_flags; // eax

  if ( immediate )
  {
    animation = weapon->animation_slots[animation_id].body.bod.object->animation;
    weapon->anim_manager.active_animation = animation;
    if ( mode_flags != -1 )
      animation->flags = mode_flags;
    active_animation = weapon->anim_manager.active_animation;
    if ( (active_animation->flags & 8) != 0 )
    {
      progress_step = active_animation->progress_step;
      if ( v8 )
        progress_step = -progress_step;
      v9 = -progress_step;
      weapon->anim_manager.progress_step = v9;
      weapon->anim_manager.progress = v9 + 1.0;
    }
    else
    {
      v10 = weapon->anim_manager.active_animation;
      weapon->anim_manager.progress = 0.0;
      v12 = v10->progress_step;
      if ( v13 )
        v12 = -v12;
      weapon->anim_manager.progress_step = v12;
    }
    object = weapon->animation_slots[animation_id].body.bod.object;
    weapon->anim_manager.queue_count = 0;
    weapon->body.bod.object = object;
    target_model = weapon->anim_manager.target_model;
    list_flags = target_model->bod.bod.list_flags;
    LOBYTE(list_flags) = list_flags | 0x20;
    target_model->bod.bod.list_flags = list_flags;
  }
  else
  {
    weapon->anim_manager.queued_animations[weapon->anim_manager.queue_count++] = animation_id;
  }
}
