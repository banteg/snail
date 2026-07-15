/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_tooltip @ 0x403c20 */

00403c26        int32_t state = tooltip->state
00403c2a        if (state == 1)
00403f40        if ((tooltip->owner_widget->widget_flags & FRONTEND_WIDGET_FLAG_POINTER_INSIDE) != 0)
00403f42        tooltip->delay_progress = 0f
00403f49        tooltip->state = 2
00403c31        if (state == 2)
00403c75        struct FrontendWidget* owner_widget = tooltip->owner_widget
00403c82        if ((owner_widget->widget_flags & FRONTEND_WIDGET_FLAG_POINTER_INSIDE) == 0)
00403f27        tooltip->state = 1
00403f32        return
00403c8b        long double x87_r7_2 = fconvert.t(tooltip->delay_step) + fconvert.t(tooltip->delay_progress)
00403c8e        tooltip->delay_progress = fconvert.s(x87_r7_2)
00403c91        long double temp3_1 = fconvert.t(1f)
00403c91        x87_r7_2 - temp3_1
00403c9c        if ((((x87_r7_2 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp3_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00403caa        float anchor_x
00403caa        if (owner_widget->text_alignment == 0)
00403cd0        anchor_x = fconvert.s(fconvert.t(owner_widget->layout_width) * fconvert.t(0.5f) + fconvert.t(owner_widget->layout_anchor_x) - fconvert.t(320f))
00403cb2        anchor_x = owner_widget->anchor_x
00403cd4        struct FrontendWidget* tooltip_widget = tooltip->tooltip_widget
00403cd7        tooltip->state = 3
00403ce0        if (tooltip_widget == 0)
00403d02        tooltip->tooltip_widget = allocate_border(&g_game_base->border_manager)
00403ce7        report_errorf("Tool tip overload")
00403d05        uint32_t eax_9 = tooltip->mode_flags
00403d0b        if ((eax_9.b & 1) != 0)
00403d2c        struct tColour color_1
00403d2c        struct tColour* color_4
00403d2c        int32_t ecx_4
00403d2c        color_4, ecx_4 = set_color_rgba(&color_1, 1f, 1f, 1f, 1f)
00403d32        struct GameRoot* game_base_1 = g_game_base
00403d37        int32_t var_6c_1 = ecx_4
00403d56        initialize_frontend_widget(tooltip->tooltip_widget, 2, tooltip, 7, game_base_1->players[0].mouse_cursor.saved_x, fconvert.s(fconvert.t(game_base_1->players[0].mouse_cursor.saved_y) + fconvert.t(64f)), color_4, 1, anchor_x)
00403d62        int32_t text_alignment
00403d62        float anchor_x_1
00403d62        struct tColour* color_6
00403d62        struct FrontendWidget* owner_widget_1
00403d62        if ((eax_9.b & 4) != 0)
00403d68        owner_widget_1 = tooltip->owner_widget
00403d6b        anchor_x_1 = anchor_x
00403d7d        int32_t var_74_1
00403d7d        __builtin_memcpy(&var_74_1, "\x00\x00\x80\x3f\x00\x00\x80\x3f\x00\x00\x80\x3f\x00\x00\x80\x3f\x01\x00\x00\x00", 0x14)
00403d82        void var_40
00403d82        color_6 = &var_40
00403df9        label_403df9:
00403df9        struct tColour* color_5
00403df9        int32_t ecx_10
00403df9        color_5, ecx_10 = set_color_rgba(color_6, 1f, 1f, 1f, 1f)
00403e11        int32_t var_6c_5 = ecx_10
00403e1e        initialize_frontend_widget(tooltip->tooltip_widget, 2, tooltip, 7, owner_widget_1->layout_anchor_x, fconvert.s(fconvert.t(owner_widget_1->layout_anchor_y) - fconvert.t(owner_widget_1->current_padding)), color_5, text_alignment, anchor_x_1)
00403e23        eax_9 = tooltip->tooltip_widget
00403e9c        *(eax_9 + 0x6f8) = fconvert.s(fconvert.t(*(eax_9 + 0x6f8)) - (fconvert.t(*(eax_9 + 0x24c)) + fconvert.t(*(eax_9 + 0x220))))
00403d8a        float layout_anchor_x
00403d8a        float y
00403d8a        struct tColour* color
00403d8a        int32_t text_alignment_1
00403d8a        float anchor_x_2
00403d8a        if ((eax_9.b & 2) == 0)
00403dd8        if ((eax_9.b & 0x10) != 0)
00403dda        owner_widget_1 = tooltip->owner_widget
00403ddd        anchor_x_1 = 0f
00403ddf        text_alignment = 0
00403de1        int32_t var_68_2 = 0x3f800000
00403de6        int32_t var_6c_4 = 0x3f800000
00403deb        int32_t var_70_2 = 0x3f800000
00403df0        int32_t var_74_2 = 0x3f800000
00403df5        void var_20
00403df5        color_6 = &var_20
00403df5        goto label_403df9
00403e3c        if ((eax_9.b & 8) != 0)
00403e3e        struct FrontendWidget* owner_widget_3 = tooltip->owner_widget
00403e41        anchor_x_2 = 0f
00403e43        text_alignment_1 = 0
00403e5d        struct tColour color_3
00403e5d        struct tColour* color_8
00403e5d        int32_t ecx_13
00403e5d        color_8, ecx_13 = set_color_rgba(&color_3, 1f, 1f, 1f, 1f)
00403e6e        color = color_8
00403e75        int32_t var_6c_7 = ecx_13
00403e7c        y = fconvert.s(fconvert.t(owner_widget_3->layout_anchor_y) + fconvert.t(owner_widget_3->layout_height) + fconvert.t(owner_widget_3->current_padding))
00403e7f        layout_anchor_x = owner_widget_3->layout_anchor_x
00403e7f        goto label_403e88
00403d90        struct FrontendWidget* owner_widget_2 = tooltip->owner_widget
00403d93        anchor_x_2 = anchor_x
00403d94        text_alignment_1 = 1
00403dae        struct tColour color_2
00403dae        struct tColour* color_7
00403dae        int32_t ecx_8
00403dae        color_7, ecx_8 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
00403dbf        color = color_7
00403dc0        int32_t var_6c_3 = ecx_8
00403dcd        y = fconvert.s(fconvert.t(owner_widget_2->layout_anchor_y) + fconvert.t(owner_widget_2->layout_height) + fconvert.t(owner_widget_2->current_padding))
00403dd0        layout_anchor_x = owner_widget_2->layout_anchor_x
00403e88        label_403e88:
00403e88        initialize_frontend_widget(tooltip->tooltip_widget, 2, tooltip, 7, layout_anchor_x, y, color, text_alignment_1, anchor_x_2)
00403e8d        eax_9 = tooltip->tooltip_widget
00403e9c        *(eax_9 + 0x6f8) = fconvert.s(fconvert.t(*(eax_9 + 0x220)) + fconvert.t(*(eax_9 + 0x6f8)))
00403ea2        struct FrontendWidget* tooltip_widget_2 = tooltip->tooltip_widget
00403eb2        long double x87_r7_23 = fconvert.t(tooltip_widget_2->layout_left) - fconvert.t(tooltip_widget_2->hot_padding) - fconvert.t(tooltip_widget_2->stack_gap)
00403eb8        long double temp4 = fconvert.t(0f)
00403eb8        x87_r7_23 - temp4
00403ec3        if ((((x87_r7_23 < temp4 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_23, temp4) ? 1 : 0) << 0xa | (x87_r7_23 == temp4 ? 1 : 0) << 0xe):1.b & 1) != 0)
00403ecb        tooltip_widget_2->layout_anchor_x = tooltip_widget_2->stack_gap
00403ed1        struct FrontendWidget* tooltip_widget_3 = tooltip->tooltip_widget
00403ee6        long double x87_r7_27 = fconvert.t(tooltip_widget_3->stack_gap) + fconvert.t(tooltip_widget_3->layout_width) + fconvert.t(tooltip_widget_3->layout_left) + fconvert.t(tooltip_widget_3->hot_padding)
00403eec        long double temp5 = fconvert.t(640f)
00403eec        x87_r7_27 - temp5
00403ef7        if ((((x87_r7_27 < temp5 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_27, temp5) ? 1 : 0) << 0xa | (x87_r7_27 == temp5 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) != 0)
00403f1d        layout_frontend_widget(tooltip->tooltip_widget)
00403f26        return
00403f05        tooltip_widget_3->layout_anchor_x = fconvert.s(fconvert.t(tooltip_widget_3->layout_anchor_x) - (x87_r7_27 - fconvert.t(640f)))
00403f0e        layout_frontend_widget(tooltip->tooltip_widget)
00403c47        if (state == 3 && (tooltip->owner_widget->widget_flags & FRONTEND_WIDGET_FLAG_POINTER_INSIDE) == 0)
00403c4d        struct FrontendWidget* tooltip_widget_1 = tooltip->tooltip_widget
00403c50        tooltip->state = 1
00403c57        g_game_base
00403c64        kill_border(tooltip_widget_1)
00403c69        tooltip->tooltip_widget = nullptr
00403f54        return
