/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_row_event_display @ 0x404cf0 */

00404cf4        int32_t __saved_esi
00404cf4        int32_t* esp = &__saved_esi
00404cf5        struct RowEventDisplayController* controller_1 = controller
00404cfc        if (controller_1->state != 0)
00404d07        controller.b = *(data_4df904 + 0x74621)
00404d0f        void* widget_b = controller_1->widget_b
00404d12        if (controller.b != 0)
00404d14        hide_border_init(widget_b)
00404d1b        hide_border_init(controller_1->widget_a)
00404d23        hide_border_init(controller_1->widget_d)
00404d2b        hide_border_init(controller_1->widget_c)
00404d33        hide_border_init(controller_1->widget_e)
00404d3d        return 
00404d3e        unhide_border_init(widget_b)
00404d45        unhide_border_init(controller_1->widget_a)
00404d4d        unhide_border_init(controller_1->widget_d)
00404d55        unhide_border_init(controller_1->widget_e)
00404d5a        int32_t state = controller_1->state
00404d60        if (state u> 6)
00404d60        goto label_404ed7
00404d66        int32_t bonus_score
00404d66        switch (state)
00404d70        case 1
00404d70        long double x87_r7_2 = fconvert.t(controller_1->progress_step) + fconvert.t(controller_1->progress)
00404d73        controller_1->progress = fconvert.s(x87_r7_2)
00404d76        long double temp2_1 = fconvert.t(1f)
00404d76        x87_r7_2 - temp2_1
00404d7c        state.w = (x87_r7_2 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp2_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp2_1 ? 1 : 0) << 0xe
00404d81        if ((state:1.b & 0x41) == 0)
00404d87        int32_t staged_parcel_count = controller_1->staged_parcel_count
00404d8f        if (staged_parcel_count s< controller_1->parcel_target_count)
00404d92        controller_1->staged_parcel_count = staged_parcel_count + 1
00404d95        void* eax_3 = data_4df904
00404da6        bonus_score = eax_3 + 0x42fd7c
00404dae        struct TrackParcelRuntime* eax_4 = spawn_track_parcel(eax_3 + 0x74618, eax_3 + 0x433f34)
00404dae        esp = &bonus_score
00404db3        void* sprite = eax_4->sprite
00404db6        eax_4->state = 6
00404dbd        *(sprite + 0x64) = 0
00404dc3        *(eax_4->sprite + 0x60) = 0
00404dc6        int32_t parcel_target_count = controller_1->parcel_target_count
00404dcc        bool cond:2_1 = controller_1->staged_parcel_count != parcel_target_count
00404dce        controller_1->progress = 0f
00404dd1        if (not(cond:2_1))
00404dd9        if (parcel_target_count != 0)
00404df1        controller_1->state = 2
00404ddb        controller_1->state = 6
00404de2        controller_1->progress = 0f
00404de5        controller_1->progress_step = 0.00833333377f
00404d81        goto label_404ed7
00404d66        case 2, 5
00404d66        goto label_404ed7
00404e26        case 3
00404e26        unhide_border_init(controller_1->widget_e)
00404e2b        int32_t bonus_enabled = controller_1->bonus_enabled
00404e2e        controller_1->completion_fast_forward_gate = 0
00404e33        controller_1->state = 4
00404e3a        if (bonus_enabled == 0)
00404e3a        goto label_404e74
00404e3f        unhide_border_init(controller_1->widget_c)
00404e47        if (controller_1->parcel_target_count != 0)
00404e47        goto label_404e74
00404e49        void* eax_5 = data_4df904
00404e55        if (*(eax_5 + 0x74658) == 1)
00404e5a        bonus_score = controller_1->bonus_score
00404e63        add_subgoldy_score(eax_5 + 0x42fd7c, SUBGOLDY_SCORE_BONUS, bonus_score)
00404e68        bonus_score = 0x31
00404e6f        play_sound_effect(bonus_score)
00404e6f        esp = &__saved_esi
00404e74        label_404e74:
00404e74        eax_5 = data_4df904
00404e7c        if (controller_1->bonus_enabled != 0)
00404e81        long double x87_r7_6 = fconvert.t(controller_1->bonus_blink_step) + fconvert.t(controller_1->bonus_blink_progress)
00404e84        controller_1->bonus_blink_progress = fconvert.s(x87_r7_6)
00404e87        long double temp4_1 = fconvert.t(1f)
00404e87        x87_r7_6 - temp4_1
00404e8d        eax_5.w = (x87_r7_6 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp4_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp4_1 ? 1 : 0) << 0xe
00404e92        if ((eax_5:1.b & 0x41) == 0)
00404e94        void* widget_c = controller_1->widget_c
00404e97        controller_1->bonus_blink_progress = 0f
00404ea3        if (((*(widget_c + 0x1a0)).w:1.b & 0x10) == 0)
00404eac        hide_border_init(widget_c)
00404ea5        unhide_border_init(widget_c)
00404eb1        eax_5 = data_4df904
00404ec2        if (((*(*(eax_5 + 0x28c) + 0x3c)).w:1.b & 0x40) != 0)
00404ec4        bonus_score = 8
00404ecb        controller_1->state = 5
00404ed2        play_sound_effect(bonus_score)
00404ed2        esp = &__saved_esi
00404ed7        label_404ed7:
00404ed7        eax_5 = data_4df904
00404ee2        long double x87_r7_8 = fconvert.t(*(eax_5 + 0x17c)) * fconvert.t(6f)
00404ef4        esp[0xf] = fconvert.s(fconvert.t(*(eax_5 + 0x180)) * fconvert.t(6f))
00404f04        esp[0x10] = fconvert.s(fconvert.t(*(eax_5 + 0x184)) * fconvert.t(6f))
00404f08        long double x87_r6_5 = fconvert.t(*(eax_5 + 0x16c))
00404f10        long double x87_r5_1 = fconvert.t(*(eax_5 + 0x170))
00404f18        esp[9] = fconvert.s(x87_r5_1 + x87_r5_1)
00404f1c        long double x87_r5_3 = fconvert.t(*(eax_5 + 0x174))
00404f24        esp[0xa] = fconvert.s(x87_r5_3 + x87_r5_3)
00404f2e        long double x87_r5_6 = fconvert.t(*(eax_5 + 0x15c)) * fconvert.t(7.30000019f)
00404f40        esp[3] = fconvert.s(fconvert.t(*(eax_5 + 0x160)) * fconvert.t(7.30000019f))
00404f50        esp[4] = fconvert.s(fconvert.t(*(eax_5 + 0x164)) * fconvert.t(7.30000019f))
00404f54        long double x87_r5_7 = x87_r5_6 + fconvert.t(*(eax_5 + 0x18c))
00404f64        esp[6] = fconvert.s(fconvert.t(esp[3]) + fconvert.t(*(eax_5 + 0x190)))
00404f75        esp[7] = fconvert.s(fconvert.t(esp[4]) + fconvert.t(*(eax_5 + 0x194)))
00404f83        esp[0xc] = fconvert.s(fconvert.t(esp[6]) + fconvert.t(esp[9]))
00404f8f        esp[0xd] = fconvert.s(fconvert.t(esp[7]) + fconvert.t(esp[0xa]))
00404f95        esp[2] = fconvert.s(x87_r6_5 + x87_r6_5 + x87_r5_7 + x87_r7_8)
00404fa3        long double x87_r7_11 = fconvert.t(esp[0xc]) + fconvert.t(esp[0xf])
00404fa7        controller_1->widget_world_x = esp[2]
00404fa9        esp[3] = fconvert.s(x87_r7_11)
00404fb1        long double x87_r7_13 = fconvert.t(esp[0xd]) + fconvert.t(esp[0x10])
00404fb9        controller_1->widget_world_y = esp[3]
00404fbc        esp[4] = fconvert.s(x87_r7_13)
00404fc4        controller_1->widget_world_z = esp[4]
00404fc7        int32_t delivered_parcel_count = controller_1->delivered_parcel_count
00404fcd        if (delivered_parcel_count s>= 0xa)
00404ff2        *(controller_1->widget_b + 0x2cc) = (delivered_parcel_count s/ 0xa).b + 0x30
00404fd2        *(controller_1->widget_b + 0x2cc) = 0x20
00405009        *(controller_1->widget_b + 0x2cd) = (mods.dp.d(sx.q(controller_1->delivered_parcel_count), 0xa)).b + 0x30
00404d66        case 4
00404d66        goto label_404e74
00404e00        case 6
00404e00        long double x87_r7_4 = fconvert.t(controller_1->progress_step) + fconvert.t(controller_1->progress)
00404e03        controller_1->progress = fconvert.s(x87_r7_4)
00404e06        long double temp3_1 = fconvert.t(1f)
00404e06        x87_r7_4 - temp3_1
00404e0c        state.w = (x87_r7_4 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp3_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp3_1 ? 1 : 0) << 0xe
00404e11        if ((state:1.b & 0x41) == 0)
00404e17        controller_1->state = 3
00404e11        goto label_404ed7
0040500f        *esp
0040500f        esp[1]
00405014        return
