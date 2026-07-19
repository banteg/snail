/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_completion_screen @ 0x404920 */

00404920        struct GameRoot* game_base_1 = g_game_base
00404932        int32_t level_mode_1 = game_base_1->subgame.level_mode
0040493c        if (level_mode_1 != 0)
00404959        if (level_mode_1 == 1)
00404967        int32_t ecx_1
00404967        int32_t esi_1
00404967        if (game_base_1->subgame.selected_level_record_active == 0)
00404995        int32_t eax_3
00404995        int32_t edx_5
00404995        edx_5:eax_3 = muls.dp.d(0x66666667, g_runtime_config.completion_bonus_y_source)
00404997        int32_t edx_6 = edx_5 s>> 3
0040499a        ecx_1 = g_runtime_config.completion_bonus_x_source
004049a7        esi_1 = edx_6 + (edx_6 u>> 0x1f)
00404969        struct SubSolution* selected_level_record = game_base_1->subgame.selected_level_record
00404977        ecx_1 = selected_level_record->challenge_speed_value
0040497a        int32_t eax
0040497a        int32_t edx_2
0040497a        edx_2:eax = muls.dp.d(0x66666667, selected_level_record->challenge_difficulty_value)
0040497c        int32_t edx_3 = edx_2 s>> 3
00404986        esi_1 = edx_3 + (edx_3 u>> 0x1f)
004049b8        int32_t edx_10 = ecx_1 s/ 0x14
004049bc        if (esi_1 s< 0)
004049be        esi_1 = 0
004049c5        if (esi_1 s> 5)
004049c7        esi_1 = 5
004049ce        if (edx_10 s< 0)
004049d0        edx_10 = 0
004049d7        if (edx_10 s> 5)
004049d9        edx_10 = 5
004049e5        if (esi_1 != 5 || edx_10 != esi_1)
00404a00        completion->bonus_score = *((edx_10 << 2) + &data_4a11ac) + *((esi_1 << 2) + &data_4a1194)
004049e7        completion->bonus_score = 0x7a120
00404940        if (perfect_delivery == 0)
0040494e        completion->bonus_score = 0
00404942        completion->bonus_score = 0xc350
00404a0d        int32_t bonus_score = completion->bonus_score
00404a10        completion->parcel_target_count = delivered_count
00404a13        completion->bonus_enabled = zx.d(perfect_delivery)
00404a2d        completion->display_token = g_game_base->subgame.player.total_score + delivered_count * 0x64 + bonus_score
00404a5c        completion->widget_a = allocate_border(&g_game_base->border_manager)
00404a5f        struct tColour color_2
00404a5f        struct tColour* color_3 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00404a7a        initialize_frontend_widget(completion->widget_a, 0x20400002, "Delivery Complete!", 0x14, 0f, 80f, color_3, 2, 0f)
00404a91        completion->delivered_count_widget = allocate_border(&g_game_base->border_manager)
00404ab0        char* text
00404ab0        struct tColour* color
00404ab0        if (completion->parcel_target_count != 1)
00404ad4        color = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00404ad5        int32_t var_30_1 = 0x43200000
00404ada        int32_t var_34_1 = 0
00404adb        int32_t var_38_1 = 0x14
00404add        text = "00 Packages Delivered"
00404abb        color = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00404abc        int32_t var_30 = 0x43200000
00404ac1        int32_t var_34 = 0
00404ac2        int32_t var_38 = 0x14
00404ac4        text = " 0 Package Delivered"
00404aea        initialize_frontend_widget(completion->delivered_count_widget, 0x20400002, text, 0x14, 0f, 160f, color, 2, 0f)
00404b1a        completion->widget_d = allocate_border(&g_game_base->border_manager)
00404b1d        struct tColour* color_4 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00404b37        initialize_frontend_sprite_button(completion->widget_d, 0x400800, 0x7a, 100f, 146f, color_4, 0f, 4)
00404b3f        *(completion->widget_d + 0x178) = 0
00404b56        completion->bonus_widget = allocate_border(&g_game_base->border_manager)
00404b5e        int32_t level_mode = g_game_base->subgame.level_mode
00404b66        if (level_mode == 0)
00404b83        struct tColour* color_5 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00404b9e        initialize_frontend_widget(completion->bonus_widget, 0x20400002, "PERFECT SCORE!>50,000 Bonus Points", 0x14, 0f, 302f, color_5, 2, 0f)
00404bab        if (level_mode == 1)
00404bc8        struct tColour* color_6 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00404be3        initialize_frontend_widget(completion->bonus_widget, 0x20400002, "LEVEL COMPLETE!>", 0x14, 0f, 302f, color_6, 2, 0f)
00404bef        border_add_text_number(completion->bonus_widget, completion->bonus_score)
00404bf7        char* edi_1 = " Bonus Points"
00404bfc        int32_t i = 0xffffffff
00404c07        while (i != 0)
00404c07        bool cond:2_1 = 0 != *edi_1
00404c07        edi_1 = &edi_1[1]
00404c07        i -= 1
00404c07        if (not(cond:2_1))
00404c07        break
00404c09        int32_t ecx_25 = not.d(i)
00404c11        void* edi_3 = completion->bonus_widget + 0x2cc
00404c13        int32_t i_1 = 0xffffffff
00404c16        while (i_1 != 0)
00404c16        bool cond:3_1 = 0 != *edi_3
00404c16        edi_3 += 1
00404c16        i_1 -= 1
00404c16        if (not(cond:3_1))
00404c16        break
00404c1e        int32_t esi_3
00404c1e        int32_t edi_5
00404c1e        edi_5, esi_3 = __builtin_memcpy(edi_3 - 1, edi_1 - ecx_25, ecx_25 & 0xfffffffc)
00404c25        __builtin_memcpy(edi_5, esi_3, ecx_25 & 3)
00404c2c        hide_border_init(completion->bonus_widget)
00404c31        completion->bonus_blink_progress = 0f
00404c34        completion->bonus_blink_step = 0.0416666679f
00404c4c        completion->continue_widget = allocate_border(&g_game_base->border_manager)
00404c6a        float y
00404c6a        struct tColour* color_1
00404c6a        if (completion->bonus_enabled == 0)
00404c86        color_1 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00404c87        y = 320f
00404c75        color_1 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00404c76        y = 400f
00404c9c        initialize_frontend_widget(completion->continue_widget, 0x20400002, "Click to Continue", 0x14, 0f, y, color_1, 2, 0f)
00404ca4        hide_border_init(completion->continue_widget)
00404ca9        int32_t parcel_target_count = completion->parcel_target_count
00404cac        completion->staged_parcel_count = 0
00404cb0        completion->delivered_parcel_count = 0
00404cb3        perfect_delivery.d = parcel_target_count + 1
00404cbc        completion->state = COMPLETION_STATE_STAGING_PARCELS
00404cc3        __builtin_strncpy(&completion->progress, "UUU?", 4)
00404cca        completion->gate_18 = 1
00404ce1        completion->progress_step = fconvert.s(fconvert.t(1f) / (fconvert.t(3.4000001f) / float.t(perfect_delivery.d) * fconvert.t(60f)))
00404ce9        return
