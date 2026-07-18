/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: dispatch_cutscene_animation @ 0x444600 */

00444606        if (immediate == 0)
004446c6        snail->anim_manager.queued_animations[snail->anim_manager.queue_count] = animation_id
004446d3        int32_t eax_7 = snail->anim_manager.queue_count + 1
004446d4        snail->anim_manager.queue_count = eax_7
004446da        return eax_7
00444622        int16_t* animation = snail->cutscene_animation_slots[animation_id].body.bod.object->animation
0044462f        snail->anim_manager.active_animation = animation
00444635        if (mode_flags != 0xffffffff)
00444637        *animation = mode_flags.w
0044463a        struct ObjectAnimation* active_animation = snail->anim_manager.active_animation
00444643        if ((active_animation->flags.b & 8) == 0)
00444670        struct ObjectAnimation* active_animation_1 = snail->anim_manager.active_animation
00444676        snail->anim_manager.progress = 0f
00444680        long double x87_r7_4 = fconvert.t(active_animation_1->progress_step)
00444683        long double temp1_1 = fconvert.t(0f)
00444683        x87_r7_4 - temp1_1
00444689        long double x87_r7_5 = fconvert.t(active_animation_1->progress_step)
00444691        if ((((x87_r7_4 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp1_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp1_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
00444693        x87_r7_5 = fneg(x87_r7_5)
00444695        snail->anim_manager.progress_step = fconvert.s(x87_r7_5)
00444645        long double x87_r7 = fconvert.t(active_animation->progress_step)
00444648        long double temp2_1 = fconvert.t(0f)
00444648        x87_r7 - temp2_1
0044464e        long double x87_r7_1 = fconvert.t(active_animation->progress_step)
00444656        if ((((x87_r7 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp2_1) ? 1 : 0) << 0xa | (x87_r7 == temp2_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
00444658        x87_r7_1 = fneg(x87_r7_1)
0044465a        long double x87_r7_2 = fneg(x87_r7_1)
0044465c        snail->anim_manager.progress_step = fconvert.s(x87_r7_2)
00444668        snail->anim_manager.progress = fconvert.s(x87_r7_2 + fconvert.t(1f))
0044469d        snail->anim_manager.queue_count = 0
004446a7        snail->body.bod.object = snail->cutscene_animation_slots[animation_id].body.bod.object
004446aa        struct RenderableBod* target_model = snail->anim_manager.target_model
004446b1        uint32_t list_flags = target_model->bod.bod.list_flags
004446b4        list_flags.b |= 0x20
004446b6        target_model->bod.bod.list_flags = list_flags
004446b9        return list_flags
