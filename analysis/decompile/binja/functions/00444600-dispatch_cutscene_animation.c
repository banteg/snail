/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: dispatch_cutscene_animation @ 0x444600 */

00444606        if (immediate == 0)
004446c6        presentation->anim_manager.queued_animation_ids[presentation->anim_manager.queued_animation_count] = animation_id
004446d3        int32_t eax_8 = presentation->anim_manager.queued_animation_count + 1
004446d4        presentation->anim_manager.queued_animation_count = eax_8
004446da        return eax_8
00444611        int32_t eax_2 = animation_id << 7
00444622        int16_t* eax_3 = *(*(&presentation->_pad_14c[0x24] + eax_2) + 0xbc)
0044462f        presentation->anim_manager.active_keyframe = eax_3
00444635        if (initial_frame != 0xffffffff)
00444637        *eax_3 = initial_frame.w
0044463a        void* active_keyframe = presentation->anim_manager.active_keyframe
00444643        if ((*active_keyframe & 8) == 0)
00444670        void* active_keyframe_1 = presentation->anim_manager.active_keyframe
00444676        presentation->anim_manager.progress = 0f
00444680        long double x87_r7_4 = fconvert.t(*(active_keyframe_1 + 0x10))
00444683        long double temp1_1 = fconvert.t(0f)
00444683        x87_r7_4 - temp1_1
00444689        long double x87_r7_5 = fconvert.t(*(active_keyframe_1 + 0x10))
0044468c        eax_3.w = (x87_r7_4 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp1_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp1_1 ? 1 : 0) << 0xe | 0x3800
00444691        if ((eax_3:1.b & 1) != 0)
00444693        x87_r7_5 = fneg(x87_r7_5)
00444695        presentation->anim_manager.progress_step = fconvert.s(x87_r7_5)
00444645        long double x87_r7 = fconvert.t(*(active_keyframe + 0x10))
00444648        long double temp2_1 = fconvert.t(0f)
00444648        x87_r7 - temp2_1
0044464e        long double x87_r7_1 = fconvert.t(*(active_keyframe + 0x10))
00444651        eax_3.w = (x87_r7 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp2_1) ? 1 : 0) << 0xa | (x87_r7 == temp2_1 ? 1 : 0) << 0xe | 0x3800
00444656        if ((eax_3:1.b & 1) != 0)
00444658        x87_r7_1 = fneg(x87_r7_1)
0044465a        long double x87_r7_2 = fneg(x87_r7_1)
0044465c        presentation->anim_manager.progress_step = fconvert.s(x87_r7_2)
00444668        presentation->anim_manager.progress = fconvert.s(x87_r7_2 + fconvert.t(1f))
0044469d        presentation->anim_manager.queued_animation_count = 0
004446a7        presentation->visual_root = *(&presentation->_pad_14c[0x24] + eax_2)
004446aa        void* self_ref = presentation->anim_manager.self_ref
004446b4        int32_t eax_5
004446b4        eax_5.b = (*(self_ref + 4)).b | 0x20
004446b6        *(self_ref + 4) = eax_5
004446b9        return eax_5
