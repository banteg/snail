/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_weapon_animation @ 0x4446e0 */

004446e6        if (immediate == 0)
004447a6        channel->anim_manager.queued_animation_ids[channel->anim_manager.queued_animation_count] = animation_id
004447b3        int32_t eax_8 = channel->anim_manager.queued_animation_count + 1
004447b4        channel->anim_manager.queued_animation_count = eax_8
004447ba        return eax_8
004446f1        int32_t eax_2 = animation_id << 7
00444702        int16_t* eax_3 = *(*(&channel->animation_slot_table + eax_2) + 0xbc)
0044470f        channel->anim_manager.active_keyframe = eax_3
00444715        if (initial_frame != 0xffffffff)
00444717        *eax_3 = initial_frame.w
0044471a        void* active_keyframe = channel->anim_manager.active_keyframe
00444723        if ((*active_keyframe & 8) == 0)
00444750        void* active_keyframe_1 = channel->anim_manager.active_keyframe
00444756        channel->anim_manager.progress = 0f
00444760        long double x87_r7_4 = fconvert.t(*(active_keyframe_1 + 0x10))
00444763        long double temp1_1 = fconvert.t(0f)
00444763        x87_r7_4 - temp1_1
00444769        long double x87_r7_5 = fconvert.t(*(active_keyframe_1 + 0x10))
0044476c        eax_3.w = (x87_r7_4 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp1_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp1_1 ? 1 : 0) << 0xe | 0x3800
00444771        if ((eax_3:1.b & 1) != 0)
00444773        x87_r7_5 = fneg(x87_r7_5)
00444775        channel->anim_manager.progress_step = fconvert.s(x87_r7_5)
00444725        long double x87_r7 = fconvert.t(*(active_keyframe + 0x10))
00444728        long double temp2_1 = fconvert.t(0f)
00444728        x87_r7 - temp2_1
0044472e        long double x87_r7_1 = fconvert.t(*(active_keyframe + 0x10))
00444731        eax_3.w = (x87_r7 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp2_1) ? 1 : 0) << 0xa | (x87_r7 == temp2_1 ? 1 : 0) << 0xe | 0x3800
00444736        if ((eax_3:1.b & 1) != 0)
00444738        x87_r7_1 = fneg(x87_r7_1)
0044473a        long double x87_r7_2 = fneg(x87_r7_1)
0044473c        channel->anim_manager.progress_step = fconvert.s(x87_r7_2)
00444748        channel->anim_manager.progress = fconvert.s(x87_r7_2 + fconvert.t(1f))
0044477d        channel->anim_manager.queued_animation_count = 0
00444787        channel->visual_root = *(&channel->animation_slot_table + eax_2)
0044478a        void* self_ref = channel->anim_manager.self_ref
00444794        int32_t eax_5
00444794        eax_5.b = (*(self_ref + 4)).b | 0x20
00444796        *(self_ref + 4) = eax_5
00444799        return eax_5
