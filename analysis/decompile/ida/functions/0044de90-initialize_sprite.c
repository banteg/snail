/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_sprite @ 0x44de90 */
/* selector: initialize_sprite */

// Initializes one sprite slot in the `cRSprite` runtime family before manager allocation links it into active/free lists.
void __thiscall initialize_sprite(Sprite *sprite)
{
  sprite->flags = SPRITE_FLAG_RENDER_ENABLED|SPRITE_FLAG_SKIP_INITIAL_PROGRESS|SPRITE_FLAG_ACTIVE;
  set_color_white(&sprite->color);
  sprite->gravity_step = -0.013;
  sprite->draw_mode = 0;
  sprite->progress = 0.0;
  sprite->lifetime = 0.0;
  sprite->lifetime_step = 0.0;
  sprite->facing_angle = 0.0;
  sprite->facing_angle_step = 0.0;
  sprite->reserved_84 = 0;
  sprite->corner_scale = 1.0;
  sprite->facing_refresh_progress = 0.0;
  sprite->facing_refresh_step = 0.0;
  sprite->depth_offset = -500.0;
  sprite->texture_ref_a = nullptr;
  sprite->texture_ref_b = nullptr;
  sprite->velocity.z = 0.0;
  sprite->velocity.y = 0.0;
  sprite->velocity.x = 0.0;
  sprite->depth_bias = 0.0;
  sprite->object_ref = (void *)-1;
  sprite->texture_id = 0;
  sprite->frame_count = 0;
  sprite->frame = 0;
  sprite->frame_progress = 0.0;
  sprite->frame_progress_step = 0.0;
  sprite->frame_step = 1;
}
