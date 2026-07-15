/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_anim_manager @ 0x4447d0 */

004447d0        struct AnimManager* manager_1 = manager
004447d1        int32_t state = manager->state
004447d3        int32_t i = 0
004447d9        manager->completed = 0
004447dc        if (state == 0)
004447dc        return
004447e3        if (state == 1)
004447f0        long double x87_r7_1 = fconvert.t(g_game_base->subgame.rate_or_level_arg.base_rate)
0044480a        manager_1 = fconvert.s((x87_r7_1 + x87_r7_1 - fconvert.t(0.200000003f) + fconvert.t(1f)) * fconvert.t(manager->progress_step) + fconvert.t(manager->progress))
0044480e        long double x87_r7_7 = fconvert.t(manager_1)
00444812        long double temp2_1 = fconvert.t(1f)
00444812        x87_r7_7 - temp2_1
0044481c        manager->progress = manager_1
00444823        if ((1 & ((x87_r7_7 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp2_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp2_1 ? 1 : 0) << 0xe):1.b) == 0)
00444828        uint8_t flags = (manager->active_animation->flags).b
0044482d        if ((1 & flags) != 0)
00444839        manager->completed = 1
0044483c        manager->progress = fconvert.s(fconvert.t(manager_1) - fconvert.t(1f))
00444843        if ((flags & 4) != 0)
00444845        manager->progress = 0.999000013f
0044484c        manager->progress_step = 0f
0044484f        manager->completed = 1
00444856        if ((flags & 2) != 0)
00444862        manager->progress = fconvert.s(fconvert.t(2f) - fconvert.t(manager_1))
0044486e        manager->progress_step = fconvert.s(fconvert.t(manager->progress_step) * fconvert.t(-1f))
00444871        long double x87_r7_14 = fconvert.t(manager->progress)
00444874        long double temp3_1 = fconvert.t(0f)
00444874        x87_r7_14 - temp3_1
0044487f        if ((((x87_r7_14 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp3_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp3_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00444881        struct ObjectAnimation* active_animation = manager->active_animation
00444887        if ((active_animation->flags.b & 2) != 0)
0044488e        manager->progress = fconvert.s(fneg(fconvert.t(manager->progress)))
00444894        long double x87_r7_18 = fconvert.t(manager->progress_step) * fconvert.t(-1f)
0044489a        manager->completed = 1
0044489d        manager->progress_step = fconvert.s(x87_r7_18)
004448a3        if ((active_animation->flags.b & 8) != 0)
004448a5        manager->progress = 0f
004448a8        manager->progress_step = 0f
004448ab        manager->completed = 1
004448ae        long double x87_r7_19 = fconvert.t(manager->progress)
004448b1        long double temp4_1 = fconvert.t(0f)
004448b1        x87_r7_19 - temp4_1
004448bc        long double x87_r7_20
004448bc        if ((((x87_r7_19 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_19, temp4_1) ? 1 : 0) << 0xa | (x87_r7_19 == temp4_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
004448c6        long double x87_r7_21 = fconvert.t(manager->progress)
004448c9        long double temp5_1 = fconvert.t(0.999899983f)
004448c9        x87_r7_21 - temp5_1
004448d4        if ((((x87_r7_21 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_21, temp5_1) ? 1 : 0) << 0xa | (x87_r7_21 == temp5_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
004448de        x87_r7_20 = fconvert.t(manager->progress)
004448d6        x87_r7_20 = fconvert.t(0.999899983f)
004448be        x87_r7_20 = fconvert.t(0f)
004448e1        manager->progress = fconvert.s(x87_r7_20)
004448ec        if (manager->completed == 0 || manager->queue_count s<= 0)
004448ec        return
004448f1        int32_t (* eax_7)[0xa] = &manager->queued_animations
004448f8        if (manager->queued_animations[0] != 0xffffffff)
00444909        struct RenderableBod* target_model_1 = manager->target_model
00444912        target_model_1->bod.bod.list_flags |= 0x20
0044491d        int32_t* esi_4 = &manager->animation_slots[(eax_7 - 0x14)->queued_animations[0]].body.bod.object
00444923        struct ObjectAnimation* edi_3 = *(*esi_4 + 0xbc)
00444929        manager->progress = 0f
0044492c        manager->active_animation = edi_3
00444932        manager->progress_step = edi_3->progress_step
0044493a        manager->target_model->bod.object = *esi_4
004448fa        struct RenderableBod* target_model = manager->target_model
004448fd        manager->progress = 0f
00444900        manager->progress_step = 0f
00444903        target_model->bod.bod.list_flags &= 0xffffffdf
00444941        int32_t ebx_4 = manager->queue_count - 1
00444944        manager->queue_count = ebx_4
00444949        if (ebx_4 s<= 0)
00444949        return
0044494e        i += 1
0044494f        (eax_7 - 0x14)->queued_animations[0] = (eax_7 - 0x14)->queued_animations[1]
00444954        eax_7 = &(*eax_7)[1]
00444959        do while (i s< manager->queue_count)
0044495e        return
