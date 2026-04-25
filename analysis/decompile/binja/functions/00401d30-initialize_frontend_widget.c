/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_frontend_widget @ 0x401d30 */

00401d42        widget->widget_type = widget_type
00401d45        widget->_pad_10[0x38] = 5
00401d45        widget->_pad_10[0x39] = 0
00401d45        widget->_pad_10[0x3a] = 0
00401d45        widget->_pad_10[0x3b] = 0
00401d4c        widget->state_5c = 0
00401d4f        widget->render_inset_delta = 0f
00401d55        widget->render_inset_base = 20f
00401d5f        widget->render_inset_dynamic = 0
00401d6e        struct FrontendWidget* eax = data_4df904 + 0xb4c
00401d7b        if ((0x200 & widget->list_flags) == 0)
00401d8c        widget->list_prev = eax
00401d92        widget->list_next = eax->list_next
00401d95        eax->list_next = widget
00401d98        struct FrontendWidget* list_next = widget->list_next
00401d9d        if (list_next != 0)
00401d9f        list_next->list_prev = widget
00401da2        widget->list_flags |= 0x200
00401d82        report_errorf("List ADDafter")
00401db9        widget->tooltip.state = 0
00401dbf        widget->tooltip.owner_widget = widget
00401dc5        widget->tooltip.tooltip_widget = nullptr
00401dcb        widget->tooltip.owner_widget_38 = widget
00401dd1        widget->widget_flags = widget_flags | 0x40001
00401dd7        set_color_white()
00401de4        set_color_white()
00401df6        struct Color4f color_1
00401df6        if (widget_type - 0x14 u> 3)
0040220a        report_errorf("Unknown Border Style Requested")
00401dfc        struct Color4f* color_15
00401dfc        switch (widget_type)
00401e1a        case 0x14
00401e1a        widget->font_id = 0
00401e20        widget->font_scale = 1.29999995f
00401e2a        widget->idle_padding = 9f
00401e34        widget->hot_padding = 13f
00401e3e        widget->stack_gap = 26f
00401e48        struct Color4f color_6
00401e48        struct Color4f* eax_4 = set_color_rgba(&color_6, 1f, 0.521568656f, 0f, 0.699999988f)
00401e5f        widget->idle_text_color.r = eax_4->r
00401e6e        widget->idle_text_color.g = eax_4->g
00401e74        widget->idle_text_color.b = eax_4->b
00401e81        widget->idle_text_color.a = eax_4->a
00401e84        struct Color4f color_13
00401e84        struct Color4f* eax_6 = set_color_rgba(&color_13, 1f, 1f, 1f, 1f)
00401e90        widget->hot_text_color.r = eax_6->r
00401e9f        widget->hot_text_color.g = eax_6->g
00401eaa        widget->hot_text_color.b = eax_6->b
00401eb7        widget->hot_text_color.a = eax_6->a
00401eba        struct Color4f color_10
00401eba        struct Color4f* eax_7 = set_color_rgba(&color_10, 0.329411775f, 0.223529413f, 0.501960814f, 0.699999988f)
00401ebf        float r = eax_7->r
00401ec7        int32_t var_118_1 = 0x3f800000
00401ecc        int32_t var_11c_1 = 0x3f31b1b2
00401ed1        widget->idle_fill_color.r.b = r.b
00401ed1        widget->idle_fill_color.r:1.b = r:1.b
00401ed1        widget->idle_fill_color.r:2.b = r:2.b
00401ed1        widget->idle_fill_color.r:3.b = r:3.b
00401ed6        int32_t var_120_1 = 0x3e9e9e9f
00401edb        int32_t var_124_1 = 0x3f1b9b9c
00401ee0        widget->idle_fill_color.g = eax_7->g
00401ee6        widget->idle_fill_color.b = eax_7->b
00401eec        widget->idle_fill_color.a = eax_7->a
00401eef        void var_c0
00401eef        color_15 = &var_c0
0040210e        case 0x15
0040210e        widget->font_id = 0
00402114        widget->font_scale = 1f
0040211e        widget->idle_padding = 9f
00402128        widget->hot_padding = 13f
00402132        widget->stack_gap = 26f
0040213c        struct Color4f color_7
0040213c        struct Color4f* eax_19 = set_color_rgba(&color_7, 1f, 0.521568656f, 0f, 0.699999988f)
00402141        float r_5 = eax_19->r
00402153        widget->idle_text_color.r.b = r_5.b
00402153        widget->idle_text_color.r:1.b = r_5:1.b
00402153        widget->idle_text_color.r:2.b = r_5:2.b
00402153        widget->idle_text_color.r:3.b = r_5:3.b
00402162        widget->idle_text_color.g = eax_19->g
00402168        widget->idle_text_color.b = eax_19->b
0040216e        widget->idle_text_color.a = eax_19->a
00402178        struct Color4f color_9
00402178        struct Color4f* eax_21 = set_color_rgba(&color_9, 1f, 1f, 1f, 1f)
00402184        widget->hot_text_color.r = eax_21->r
00402193        widget->hot_text_color.g = eax_21->g
0040219e        widget->hot_text_color.b = eax_21->b
004021ab        widget->hot_text_color.a = eax_21->a
004021ae        struct Color4f color_11
004021ae        struct Color4f* eax_22 = set_color_rgba(&color_11, 0.329411775f, 0.223529413f, 0.501960814f, 0.699999988f)
004021b3        float r_6 = eax_22->r
004021bb        int32_t var_118_4 = 0x3f800000
004021c0        int32_t var_11c_4 = 0x3f31b1b2
004021c5        widget->idle_fill_color.r.b = r_6.b
004021c5        widget->idle_fill_color.r:1.b = r_6:1.b
004021c5        widget->idle_fill_color.r:2.b = r_6:2.b
004021c5        widget->idle_fill_color.r:3.b = r_6:3.b
004021ca        int32_t var_120_4 = 0x3e9e9e9f
004021cf        int32_t var_124_4 = 0x3f1b9b9c
004021d4        widget->idle_fill_color.g = eax_22->g
004021da        widget->idle_fill_color.b = eax_22->b
004021e0        widget->idle_fill_color.a = eax_22->a
004021e3        color_15 = &color_1
00401f03        case 0x16
00401f03        widget->render_inset_base = 20f
00401f19        widget->font_id = 0
00401f1f        __builtin_strncpy(&widget->font_scale, "ff&?", 4)
00401f29        widget->idle_padding = 1f
00401f33        widget->hot_padding = 3f
00401f3d        widget->stack_gap = 2f
00401f47        widget->render_inset_dynamic = 1
00401f4e        struct Color4f color_8
00401f4e        struct Color4f* eax_9 = set_color_rgba(&color_8, 1f, 0.521568656f, 0f, 0.699999988f)
00401f53        float r_1 = eax_9->r
00401f65        widget->idle_text_color.r.b = r_1.b
00401f65        widget->idle_text_color.r:1.b = r_1:1.b
00401f65        widget->idle_text_color.r:2.b = r_1:2.b
00401f65        widget->idle_text_color.r:3.b = r_1:3.b
00401f74        widget->idle_text_color.g = eax_9->g
00401f7a        widget->idle_text_color.b = eax_9->b
00401f80        widget->idle_text_color.a = eax_9->a
00401f8a        struct Color4f color_5
00401f8a        struct Color4f* eax_11 = set_color_rgba(&color_5, 1f, 1f, 1f, 1f)
00401f96        widget->hot_text_color.r = eax_11->r
00401fa5        widget->hot_text_color.g = eax_11->g
00401fb0        widget->hot_text_color.b = eax_11->b
00401fbd        widget->hot_text_color.a = eax_11->a
00401fc0        struct Color4f color_12
00401fc0        struct Color4f* eax_12 = set_color_rgba(&color_12, 0.329411775f, 0.223529413f, 0.501960814f, 0.699999988f)
00401fc5        float r_2 = eax_12->r
00401fcd        int32_t var_118_2 = 0x3f800000
00401fd2        int32_t var_11c_2 = 0x3f31b1b2
00401fd7        widget->idle_fill_color.r.b = r_2.b
00401fd7        widget->idle_fill_color.r:1.b = r_2:1.b
00401fd7        widget->idle_fill_color.r:2.b = r_2:2.b
00401fd7        widget->idle_fill_color.r:3.b = r_2:3.b
00401fdc        int32_t var_120_2 = 0x3e9e9e9f
00401fe1        int32_t var_124_2 = 0x3f1b9b9c
00401fe6        widget->idle_fill_color.g = eax_12->g
00401fec        widget->idle_fill_color.b = eax_12->b
00401ff2        widget->idle_fill_color.a = eax_12->a
00401ff5        void var_f0
00401ff5        color_15 = &var_f0
00402012        case 0x17
00402012        widget->font_id = 0
00402018        widget->font_scale = 1.13999999f
00402022        widget->idle_padding = 6f
0040202c        widget->hot_padding = 7f
00402036        widget->stack_gap = 2f
00402040        widget->render_inset_base = 20f
0040204a        struct Color4f color_2
0040204a        struct Color4f* eax_14 = set_color_rgba(&color_2, 1f, 0.521568656f, 0f, 0.699999988f)
0040204f        float r_3 = eax_14->r
00402061        widget->idle_text_color.r.b = r_3.b
00402061        widget->idle_text_color.r:1.b = r_3:1.b
00402061        widget->idle_text_color.r:2.b = r_3:2.b
00402061        widget->idle_text_color.r:3.b = r_3:3.b
00402070        widget->idle_text_color.g = eax_14->g
00402076        widget->idle_text_color.b = eax_14->b
0040207c        widget->idle_text_color.a = eax_14->a
00402083        struct Color4f color_3
00402083        struct Color4f* eax_16 = set_color_rgba(&color_3, 1f, 1f, 1f, 1f)
0040208f        widget->hot_text_color.r = eax_16->r
0040209e        widget->hot_text_color.g = eax_16->g
004020a9        widget->hot_text_color.b = eax_16->b
004020b3        widget->hot_text_color.a = eax_16->a
004020b6        struct Color4f color_4
004020b6        struct Color4f* eax_17 = set_color_rgba(&color_4, 0.329411775f, 0.223529413f, 0.501960814f, 0.699999988f)
004020bb        float r_4 = eax_17->r
004020c3        int32_t var_118_3 = 0x3f800000
004020c8        int32_t var_11c_3 = 0x3f31b1b2
004020cd        widget->idle_fill_color.r.b = r_4.b
004020cd        widget->idle_fill_color.r:1.b = r_4:1.b
004020cd        widget->idle_fill_color.r:2.b = r_4:2.b
004020cd        widget->idle_fill_color.r:3.b = r_4:3.b
004020d2        int32_t var_120_3 = 0x3e9e9e9f
004020d7        int32_t var_124_3 = 0x3f1b9b9c
004020dc        widget->idle_fill_color.g = eax_17->g
004020e2        widget->idle_fill_color.b = eax_17->b
004020e8        widget->idle_fill_color.a = eax_17->a
004020eb        void var_90
004020eb        color_15 = &var_90
004021e7        int32_t* eax_24 = set_color_rgba(color_15, 0.607843161f, 0.309803933f, 0.694117665f, 1f)
004021ee        widget->hot_fill_color.r = *eax_24
004021f4        widget->hot_fill_color.g = eax_24[1]
004021fa        widget->hot_fill_color.b = eax_24[2]
00402200        widget->hot_fill_color.a = eax_24[3]
0040221e        widget->slider_position_target = 0.5f
00402224        widget->slider_position_current = 0.5f
0040222a        widget->_pad_10[0x28] = 1
0040222a        widget->_pad_10[0x29] = 0
0040222a        widget->_pad_10[0x2a] = 0
0040222a        widget->_pad_10[0x2b] = 0
0040222d        unhide_border_init(widget)
00402241        rstrcpy_checked_ascii(&widget->text_buffer, text)
00402254        widget->layout_anchor_y = y
0040225a        float eax_26
0040225a        eax_26.b = widget->widget_flags.b
00402263        widget->layout_anchor_x = x
0040226b        widget->hover_blend_target = 1f
00402277        if ((eax_26.b & 2) == 0)
00402280        unhighlight_border(widget)
00402279        highlight_border(widget)
00402285        long double x87_r5 = fconvert.t(widget->idle_padding)
0040229f        widget->hover_blend_current = widget->hover_blend_target
004022a5        widget->target_padding = fconvert.s(x87_r5)
004022ab        widget->current_padding = fconvert.s(x87_r5)
004022b8        widget->text_effect_target = 0f
004022be        widget->text_effect_current = 0f
004022c4        widget->text_alignment = text_alignment
004022ca        widget->anchor_x = anchor_x
004022dc        bool cond:0 = (widget->widget_flags & 0x100000) == 0
004022e1        long double x87_r5_2 = fconvert.t(anchor_x) + fconvert.t(*(data_4df904 + 0x440fc))
004022e7        widget->mouse_settle_frames = 1
004022ed        widget->anchor_x = fconvert.s(x87_r5_2)
004022f3        if (not(cond:0))
0040232e        float var_104_1 = fconvert.s(fconvert.t(y) + fconvert.t(40f))
00402336        widget->slider_more_widget = allocate_border(data_4df904 + 0xb4c)
0040233c        struct Color4f* eax_30
0040233c        int32_t ecx_43
0040233c        eax_30, ecx_43 = set_color_rgba(&color_1, 1f, 1f, 1f, 1f)
0040234c        int32_t var_128_1 = ecx_43
00402377        initialize_frontend_sprite_button(widget->slider_more_widget, (widget->widget_flags & 0x800000) | 0x20400814, 0x2a, fconvert.s(fconvert.t(*(data_4df904 + 0x440fc)) + fconvert.t(458f)), var_104_1, eax_30, 0f, 4)
00402389        border_sprite_extend(widget->slider_more_widget, 0x2c, 0x2b, 0x2d, 1)
004023ba        widget->slider_less_widget = allocate_border(data_4df904 + 0xb4c)
004023c0        int32_t* eax_33
004023c0        int32_t ecx_51
004023c0        eax_33, ecx_51 = set_color_rgba(&color_1, 1f, 1f, 1f, 1f)
004023cc        int32_t var_128_3 = ecx_51
004023f7        initialize_frontend_sprite_button(widget->slider_less_widget, (widget->widget_flags & 0x800000) | 0x20400814, 0x26, fconvert.s(fconvert.t(*(data_4df904 + 0x440fc)) + fconvert.t(118f)), var_104_1, eax_33, 0f, 4)
00402409        border_sprite_extend(widget->slider_less_widget, 0x28, 0x27, 0x29, 0)
0040243a        widget->slider_value_widget = allocate_border(data_4df904 + 0xb4c)
00402440        struct Color4f* color_14
00402440        int32_t ecx_59
00402440        color_14, ecx_59 = set_color_rgba(&color_1, 1f, 1f, 1f, 1f)
00402452        int32_t var_124_7 = ecx_59
00402469        initialize_frontend_widget(widget->slider_value_widget, &__dos_header, "00%", 0x15, 0f, fconvert.s(fconvert.t(widget->layout_anchor_y) + fconvert.t(40f)), color_14, 2, 0f)
0040247f        return layout_frontend_widget(widget)
