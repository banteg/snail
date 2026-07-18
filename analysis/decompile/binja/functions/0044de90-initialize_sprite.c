/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_sprite @ 0x44de90 */

0044de96        sprite->flags = SPRITE_FLAG_ACTIVE | SPRITE_FLAG_SKIP_INITIAL_PROGRESS | SPRITE_FLAG_RENDER_ENABLED
0044de9d        set_color_white(&sprite->color)
0044dea4        sprite->gravity_step = -0.0130000003f
0044deab        sprite->draw_mode = 0
0044deae        sprite->progress = 0f
0044deb1        sprite->lifetime = 0f
0044deb4        sprite->lifetime_step = 0f
0044deb7        sprite->facing_angle = 0f
0044deba        sprite->facing_angle_step = 0f
0044dec0        sprite->reserved_84 = 0
0044dec6        sprite->corner_scale = 1f
0044ded0        sprite->facing_refresh_progress = 0f
0044ded6        sprite->facing_refresh_step = 0f
0044dedc        sprite->depth_offset = -500f
0044dee6        sprite->texture_ref_a = nullptr
0044dee9        sprite->texture_ref_b = nullptr
0044deec        sprite->velocity.z = 0f
0044deef        sprite->velocity.y = 0f
0044def2        sprite->velocity.x = 0
0044def5        sprite->depth_bias = 0f
0044defb        sprite->object_ref = 0xffffffff
0044df01        sprite->texture_id = 0
0044df07        sprite->frame_count = 0
0044df0d        sprite->frame = 0
0044df13        sprite->frame_progress = 0f
0044df19        sprite->frame_progress_step = 0f
0044df1f        sprite->frame_step = 1
0044df2a        return
