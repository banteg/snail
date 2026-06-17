/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_completion_screen @ 0x404920 */

00404920        void* eax_29 = data_4df904
00404932        int32_t ecx = *(eax_29 + 0x74658)
0040493c        if (ecx != 0)
00404959        if (ecx == 1)
00404967        int32_t ecx_3
00404967        int32_t esi_1
00404967        if (*(eax_29 + 0x1066be8) == 0)
00404995        int32_t eax_3
00404995        int32_t edx_5
00404995        edx_5:eax_3 = muls.dp.d(0x66666667, data_4df960)
00404997        int32_t edx_6 = edx_5 s>> 3
0040499a        ecx_3 = data_4df958
004049a7        esi_1 = edx_6 + (edx_6 u>> 0x1f)
00404969        void* ecx_2 = *(eax_29 + 0x1066bec)
00404977        ecx_3 = *(ecx_2 + 0x4c)
0040497a        int32_t eax
0040497a        int32_t edx_2
0040497a        edx_2:eax = muls.dp.d(0x66666667, *(ecx_2 + 0x50))
0040497c        int32_t edx_3 = edx_2 s>> 3
00404986        esi_1 = edx_3 + (edx_3 u>> 0x1f)
004049b8        int32_t edx_10 = ecx_3 s/ 0x14
004049bc        if (esi_1 s< 0)
004049be        esi_1 = 0
004049c5        if (esi_1 s> 5)
004049c7        esi_1 = 5
004049ce        if (edx_10 s< 0)
004049d0        edx_10 = 0
004049d7        if (edx_10 s> 5)
004049d9        edx_10 = 5
004049e5        if (esi_1 != 5 || edx_10 != esi_1)
00404a00        screen->bonus_score = *((edx_10 << 2) + &data_4a11ac) + *((esi_1 << 2) + &data_4a1194)
004049e7        screen->bonus_score = 0x7a120
00404940        if (perfect_delivery == 0)
0040494e        screen->bonus_score = 0
00404942        screen->bonus_score = 0xc350
00404a0d        int32_t bonus_score = screen->bonus_score
00404a10        screen->delivered_count = delivered_count
00404a13        screen->perfect_delivery = zx.d(perfect_delivery)
00404a2d        screen->total_score = *(data_4df904 + 0x430060) + delivered_count * 0x64 + bonus_score
00404a5c        screen->title_widget = allocate_border(data_4df904 + 0xb4c)
00404a5f        struct Color4f color_2
00404a5f        struct Color4f* color_3 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00404a7a        initialize_frontend_widget(screen->title_widget, 0x20400002, "Delivery Complete!", 0x14, 0f, 80f, color_3, 2, 0f)
00404a91        screen->delivered_count_widget = allocate_border(data_4df904 + 0xb4c)
00404ab0        char* text
00404ab0        struct Color4f* color
00404ab0        if (screen->delivered_count != 1)
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
00404aea        initialize_frontend_widget(screen->delivered_count_widget, 0x20400002, text, 0x14, 0f, 160f, color, 2, 0f)
00404b1a        screen->bonus_icon_widget = allocate_border(data_4df904 + 0xb4c)
00404b1d        struct Color4f* eax_20 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00404b37        initialize_frontend_sprite_button(screen->bonus_icon_widget, 0x400800, 0x7a, 100f, 146f, eax_20, 0f, 4)
00404b3c        struct FrontendWidget* bonus_icon_widget = screen->bonus_icon_widget
00404b3f        bonus_icon_widget->_pad_80[0xf8] = 0
00404b3f        bonus_icon_widget->_pad_80[0xf9] = 0
00404b3f        bonus_icon_widget->_pad_80[0xfa] = 0
00404b3f        bonus_icon_widget->_pad_80[0xfb] = 0
00404b56        screen->bonus_summary_widget = allocate_border(data_4df904 + 0xb4c)
00404b5e        int32_t eax_23 = *(data_4df904 + 0x74658)
00404b66        if (eax_23 == 0)
00404b83        struct Color4f* color_4 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00404b9e        initialize_frontend_widget(screen->bonus_summary_widget, 0x20400002, "PERFECT SCORE!>50,000 Bonus Points", 0x14, 0f, 302f, color_4, 2, 0f)
00404bab        if (eax_23 == 1)
00404bc8        struct Color4f* color_5 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00404be3        initialize_frontend_widget(screen->bonus_summary_widget, 0x20400002, "LEVEL COMPLETE!>", 0x14, 0f, 302f, color_5, 2, 0f)
00404bef        border_add_text_number(screen->bonus_summary_widget, screen->bonus_score)
00404bf7        char* edi_1 = " Bonus Points"
00404bfc        int32_t i = 0xffffffff
00404c07        while (i != 0)
00404c07        bool cond:2_1 = 0 != *edi_1
00404c07        edi_1 = &edi_1[1]
00404c07        i -= 1
00404c07        if (not(cond:2_1))
00404c07        break
00404c09        int32_t ecx_26 = not.d(i)
00404c11        struct FrontendWidgetTextBuffer* edi_3 = &screen->bonus_summary_widget->text_buffer
00404c13        int32_t i_1 = 0xffffffff
00404c16        while (i_1 != 0)
00404c16        bool cond:3_1 = 0 != edi_3->raw[0]
00404c16        edi_3 = &edi_3->raw[1]
00404c16        i_1 -= 1
00404c16        if (not(cond:3_1))
00404c16        break
00404c1e        int32_t esi_3
00404c1e        int32_t edi_5
00404c1e        edi_5, esi_3 = __builtin_memcpy(edi_3 - 1, edi_1 - ecx_26, ecx_26 & 0xfffffffc)
00404c25        __builtin_memcpy(edi_5, esi_3, ecx_26 & 3)
00404c2c        hide_border_init(screen->bonus_summary_widget)
00404c31        screen->bonus_progress = 0f
00404c34        screen->bonus_progress_step = 0.0416666679f
00404c4c        screen->continue_widget = allocate_border(data_4df904 + 0xb4c)
00404c6a        float y
00404c6a        struct Color4f* color_1
00404c6a        if (screen->perfect_delivery == 0)
00404c86        color_1 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00404c87        y = 320f
00404c75        color_1 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00404c76        y = 400f
00404c9c        initialize_frontend_widget(screen->continue_widget, 0x20400002, "Click to Continue", 0x14, 0f, y, color_1, 2, 0f)
00404ca4        hide_border_init(screen->continue_widget)
00404ca9        int32_t delivered_count_1 = screen->delivered_count
00404cac        screen->delivered_count_progress = 0
00404cb0        screen->delivered_count_display = 0
00404cb3        perfect_delivery.d = delivered_count_1 + 1
00404cbc        screen->continue_state = 1
00404cc3        __builtin_strncpy(&screen->delivered_count_progress_limit, "UUU?", 4)
00404cca        screen->continue_visible = 1
00404ce1        screen->delivered_count_progress_step = fconvert.s(fconvert.t(1f) / (fconvert.t(3.4000001f) / float.t(perfect_delivery.d) * fconvert.t(60f)))
00404ce9        return
