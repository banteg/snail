/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_weapon_animation @ 0x4446e0 */

004446e6        if (immediate == 0)
004447a6        weapon->anim_manager.queued_animations[weapon->anim_manager.queue_count] = animation_id
004447b4        weapon->anim_manager.queue_count += 1
004447ba        return
00444702        int16_t* animation = weapon->animation_slots[animation_id].body.bod.object->animation
0044470f        weapon->anim_manager.active_animation = animation
00444715        if (mode_flags != 0xffffffff)
00444717        *animation = mode_flags.w
0044471a        struct ObjectAnimation* active_animation = weapon->anim_manager.active_animation
00444723        if ((active_animation->flags.b & 8) == 0)
00444750        struct ObjectAnimation* active_animation_1 = weapon->anim_manager.active_animation
00444756        weapon->anim_manager.progress = 0f
00444760        long double x87_r7_4 = fconvert.t(active_animation_1->progress_step)
00444763        long double temp1_1 = fconvert.t(0f)
00444763        x87_r7_4 - temp1_1
00444769        long double x87_r7_5 = fconvert.t(active_animation_1->progress_step)
00444771        if ((((x87_r7_4 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp1_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp1_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
00444773        x87_r7_5 = fneg(x87_r7_5)
00444775        weapon->anim_manager.progress_step = fconvert.s(x87_r7_5)
00444725        long double x87_r7 = fconvert.t(active_animation->progress_step)
00444728        long double temp2_1 = fconvert.t(0f)
00444728        x87_r7 - temp2_1
0044472e        long double x87_r7_1 = fconvert.t(active_animation->progress_step)
00444736        if ((((x87_r7 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp2_1) ? 1 : 0) << 0xa | (x87_r7 == temp2_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
00444738        x87_r7_1 = fneg(x87_r7_1)
0044473a        long double x87_r7_2 = fneg(x87_r7_1)
0044473c        weapon->anim_manager.progress_step = fconvert.s(x87_r7_2)
00444748        weapon->anim_manager.progress = fconvert.s(x87_r7_2 + fconvert.t(1f))
0044477d        weapon->anim_manager.queue_count = 0
00444787        weapon->body.bod.object = weapon->animation_slots[animation_id].body.bod.object
0044478a        struct RenderableBod* target_model = weapon->anim_manager.target_model
00444791        uint32_t list_flags = target_model->bod.bod.list_flags
00444794        list_flags.b |= 0x20
00444796        target_model->bod.bod.list_flags = list_flags
00444799        return
