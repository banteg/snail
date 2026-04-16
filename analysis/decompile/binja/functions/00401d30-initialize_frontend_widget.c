/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_frontend_widget @ 0x401d30 */

00401d42        widget->__offset(0x7c).d = widget_type
00401d45        widget->__offset(0x48).d = 5
00401d4c        widget->__offset(0x5c).b = 0
00401d4f        widget->__offset(0x22c).d = 0
00401d55        widget->__offset(0x230).d = 0x41a00000
00401d5f        widget->__offset(0x234).b = 0
00401d6e        void* eax = data_4df904 + 0xb4c
00401d7b        if ((0x200 & widget->__offset(0x4).d) == 0)
00401d8c        widget->__offset(0x8).d = eax
00401d92        widget->__offset(0xc).d = *(eax + 0xc)
00401d95        *(eax + 0xc) = widget
00401d98        void* eax_1 = widget->__offset(0xc).d
00401d9d        if (eax_1 != 0)
00401d9f        *(eax_1 + 8) = widget
00401da2        widget->__offset(0x4).d |= 0x200
00401d82        report_errorf("List ADDafter")
00401db9        widget->__offset(0x290).d = 0
00401dbf        widget->__offset(0x298).d = widget
00401dc5        widget->__offset(0x2a4).d = 0
00401dcb        widget->__offset(0x2c4).d = widget
00401dd1        widget->__offset(0x1a0).d = widget_flags | 0x40001
00401dd7        set_color_white()
00401de4        set_color_white()
00401df6        struct Color4f color_1
00401df6        if (widget_type - 0x14 u> 3)
0040220a        report_errorf("Unknown Border Style Requested")
00401dfc        struct Color4f* color_15
00401dfc        switch (widget_type)
00401e1a        case 0x14
00401e1a        widget->__offset(0x6ec).d = 0
00401e20        widget->__offset(0x6f0).d = 0x3fa66666
00401e2a        widget->__offset(0x214).d = 0x41100000
00401e34        widget->__offset(0x218).d = 0x41500000
00401e3e        widget->__offset(0x26c).d = 0x41d00000
00401e48        struct Color4f color_6
00401e48        struct Color4f* eax_5 = set_color_rgba(&color_6, 1f, 0.521568656f, 0f, 0.699999988f)
00401e5f        *(widget + 0x1ec) = eax_5->r
00401e6e        *(widget + 0x1f0) = eax_5->g
00401e74        *(widget + 0x1f4) = eax_5->b
00401e81        *(widget + 0x1f8) = eax_5->a
00401e84        struct Color4f color_13
00401e84        struct Color4f* eax_7 = set_color_rgba(&color_13, 1f, 1f, 1f, 1f)
00401e90        widget->__offset(0x1fc).d = eax_7->r
00401e9f        widget->__offset(0x200).d = eax_7->g
00401eaa        widget->__offset(0x204).d = eax_7->b
00401eb7        widget->__offset(0x208).d = eax_7->a
00401eba        struct Color4f color_10
00401eba        struct Color4f* eax_8 = set_color_rgba(&color_10, 0.329411775f, 0.223529413f, 0.501960814f, 0.699999988f)
00401ec7        int32_t var_118_1 = 0x3f800000
00401ecc        int32_t var_11c_1 = 0x3f31b1b2
00401ed1        *(widget + 0x1bc) = eax_8->r
00401ed6        int32_t var_120_1 = 0x3e9e9e9f
00401edb        int32_t var_124_1 = 0x3f1b9b9c
00401ee0        *(widget + 0x1c0) = eax_8->g
00401ee6        *(widget + 0x1c4) = eax_8->b
00401eec        *(widget + 0x1c8) = eax_8->a
00401eef        void var_c0
00401eef        color_15 = &var_c0
0040210e        case 0x15
0040210e        widget->__offset(0x6ec).d = 0
00402114        widget->__offset(0x6f0).d = 0x3f800000
0040211e        widget->__offset(0x214).d = 0x41100000
00402128        widget->__offset(0x218).d = 0x41500000
00402132        widget->__offset(0x26c).d = 0x41d00000
0040213c        struct Color4f color_7
0040213c        struct Color4f* eax_20 = set_color_rgba(&color_7, 1f, 0.521568656f, 0f, 0.699999988f)
00402153        *(widget + 0x1ec) = eax_20->r
00402162        *(widget + 0x1f0) = eax_20->g
00402168        *(widget + 0x1f4) = eax_20->b
0040216e        *(widget + 0x1f8) = eax_20->a
00402178        struct Color4f color_9
00402178        struct Color4f* eax_22 = set_color_rgba(&color_9, 1f, 1f, 1f, 1f)
00402184        widget->__offset(0x1fc).d = eax_22->r
00402193        widget->__offset(0x200).d = eax_22->g
0040219e        widget->__offset(0x204).d = eax_22->b
004021ab        widget->__offset(0x208).d = eax_22->a
004021ae        struct Color4f color_11
004021ae        struct Color4f* eax_23 = set_color_rgba(&color_11, 0.329411775f, 0.223529413f, 0.501960814f, 0.699999988f)
004021bb        int32_t var_118_4 = 0x3f800000
004021c0        int32_t var_11c_4 = 0x3f31b1b2
004021c5        *(widget + 0x1bc) = eax_23->r
004021ca        int32_t var_120_4 = 0x3e9e9e9f
004021cf        int32_t var_124_4 = 0x3f1b9b9c
004021d4        *(widget + 0x1c0) = eax_23->g
004021da        *(widget + 0x1c4) = eax_23->b
004021e0        *(widget + 0x1c8) = eax_23->a
004021e3        color_15 = &color_1
00401f03        case 0x16
00401f03        widget->__offset(0x230).d = 0x41a00000
00401f19        widget->__offset(0x6ec).d = 0
00401f1f        __builtin_strncpy(widget + 0x6f0, "ff&?", 4)
00401f29        widget->__offset(0x214).d = 0x3f800000
00401f33        widget->__offset(0x218).d = 0x40400000
00401f3d        widget->__offset(0x26c).d = 0x40000000
00401f47        widget->__offset(0x234).b = 1
00401f4e        struct Color4f color_8
00401f4e        struct Color4f* eax_10 = set_color_rgba(&color_8, 1f, 0.521568656f, 0f, 0.699999988f)
00401f65        *(widget + 0x1ec) = eax_10->r
00401f74        *(widget + 0x1f0) = eax_10->g
00401f7a        *(widget + 0x1f4) = eax_10->b
00401f80        *(widget + 0x1f8) = eax_10->a
00401f8a        struct Color4f color_5
00401f8a        struct Color4f* eax_12 = set_color_rgba(&color_5, 1f, 1f, 1f, 1f)
00401f96        widget->__offset(0x1fc).d = eax_12->r
00401fa5        widget->__offset(0x200).d = eax_12->g
00401fb0        widget->__offset(0x204).d = eax_12->b
00401fbd        widget->__offset(0x208).d = eax_12->a
00401fc0        struct Color4f color_12
00401fc0        struct Color4f* eax_13 = set_color_rgba(&color_12, 0.329411775f, 0.223529413f, 0.501960814f, 0.699999988f)
00401fcd        int32_t var_118_2 = 0x3f800000
00401fd2        int32_t var_11c_2 = 0x3f31b1b2
00401fd7        *(widget + 0x1bc) = eax_13->r
00401fdc        int32_t var_120_2 = 0x3e9e9e9f
00401fe1        int32_t var_124_2 = 0x3f1b9b9c
00401fe6        *(widget + 0x1c0) = eax_13->g
00401fec        *(widget + 0x1c4) = eax_13->b
00401ff2        *(widget + 0x1c8) = eax_13->a
00401ff5        void var_f0
00401ff5        color_15 = &var_f0
00402012        case 0x17
00402012        widget->__offset(0x6ec).d = 0
00402018        widget->__offset(0x6f0).d = 0x3f91eb85
00402022        widget->__offset(0x214).d = 0x40c00000
0040202c        widget->__offset(0x218).d = 0x40e00000
00402036        widget->__offset(0x26c).d = 0x40000000
00402040        widget->__offset(0x230).d = 0x41a00000
0040204a        struct Color4f color_2
0040204a        struct Color4f* eax_15 = set_color_rgba(&color_2, 1f, 0.521568656f, 0f, 0.699999988f)
00402061        *(widget + 0x1ec) = eax_15->r
00402070        *(widget + 0x1f0) = eax_15->g
00402076        *(widget + 0x1f4) = eax_15->b
0040207c        *(widget + 0x1f8) = eax_15->a
00402083        struct Color4f color_3
00402083        struct Color4f* eax_17 = set_color_rgba(&color_3, 1f, 1f, 1f, 1f)
0040208f        widget->__offset(0x1fc).d = eax_17->r
0040209e        widget->__offset(0x200).d = eax_17->g
004020a9        widget->__offset(0x204).d = eax_17->b
004020b3        widget->__offset(0x208).d = eax_17->a
004020b6        struct Color4f color_4
004020b6        struct Color4f* eax_18 = set_color_rgba(&color_4, 0.329411775f, 0.223529413f, 0.501960814f, 0.699999988f)
004020c3        int32_t var_118_3 = 0x3f800000
004020c8        int32_t var_11c_3 = 0x3f31b1b2
004020cd        *(widget + 0x1bc) = eax_18->r
004020d2        int32_t var_120_3 = 0x3e9e9e9f
004020d7        int32_t var_124_3 = 0x3f1b9b9c
004020dc        *(widget + 0x1c0) = eax_18->g
004020e2        *(widget + 0x1c4) = eax_18->b
004020e8        *(widget + 0x1c8) = eax_18->a
004020eb        void var_90
004020eb        color_15 = &var_90
004021e7        struct Color4f* eax_25 = set_color_rgba(color_15, 0.607843161f, 0.309803933f, 0.694117665f, 1f)
004021ee        widget->__offset(0x1cc).d = eax_25->r
004021f4        widget->__offset(0x1d0).d = eax_25->g
004021fa        widget->__offset(0x1d4).d = eax_25->b
00402200        widget->__offset(0x1d8).d = eax_25->a
0040221e        widget->__offset(0x17c).d = 0x3f000000
00402224        widget->__offset(0x180).d = 0x3f000000
0040222a        widget->__offset(0x38).d = 1
0040222d        unhide_border_init(widget)
00402241        sub_44e5b0(widget + 0x2cc, text)
00402254        widget->__offset(0x6f8).d = y
0040225a        float eax_27
0040225a        eax_27.b = widget->__offset(0x1a0).b
00402263        widget->__offset(0x6f4).d = x
0040226b        widget->__offset(0x20c).d = 0x3f800000
00402277        if ((eax_27.b & 2) == 0)
00402280        unhighlight_border(widget)
00402279        highlight_border(widget)
00402285        long double x87_r5 = fconvert.t(widget->__offset(0x214).d)
0040229f        widget->__offset(0x210).d = widget->__offset(0x20c).d
004022a5        widget->__offset(0x21c).d = fconvert.s(x87_r5)
004022ab        widget->__offset(0x220).d = fconvert.s(x87_r5)
004022b8        widget->__offset(0x224).d = 0
004022be        widget->__offset(0x228).d = 0
004022c4        widget->__offset(0x25c).d = text_alignment
004022ca        widget->__offset(0x260).d = anchor_x
004022dc        bool cond:0 = (widget->__offset(0x1a0).d & 0x100000) == 0
004022e1        long double x87_r5_2 = fconvert.t(anchor_x) + fconvert.t(*(data_4df904 + 0x440fc))
004022e7        widget->__offset(0x278).d = 1
004022ed        widget->__offset(0x260).d = fconvert.s(x87_r5_2)
004022f3        if (not(cond:0))
0040232e        float var_104_1 = fconvert.s(fconvert.t(y) + fconvert.t(40f))
00402336        widget->__offset(0x71c).d = allocate_border(data_4df904 + 0xb4c)
0040233c        struct Color4f* eax_31
0040233c        int32_t ecx_43
0040233c        eax_31, ecx_43 = set_color_rgba(&color_1, 1f, 1f, 1f, 1f)
0040234c        int32_t var_128_1 = ecx_43
00402377        initialize_frontend_sprite_button(widget->__offset(0x71c).d, (widget->__offset(0x1a0).d & 0x800000) | 0x20400814, 0x2a, fconvert.s(fconvert.t(*(data_4df904 + 0x440fc)) + fconvert.t(458f)), var_104_1, eax_31, 0f, 4)
00402389        border_sprite_extend(widget->__offset(0x71c).d, 0x2c, 0x2b, 0x2d, 1)
004023ba        widget->__offset(0x718).d = allocate_border(data_4df904 + 0xb4c)
004023c0        int32_t* eax_34
004023c0        int32_t ecx_51
004023c0        eax_34, ecx_51 = set_color_rgba(&color_1, 1f, 1f, 1f, 1f)
004023cc        int32_t var_128_3 = ecx_51
004023f7        initialize_frontend_sprite_button(widget->__offset(0x718).d, (widget->__offset(0x1a0).d & 0x800000) | 0x20400814, 0x26, fconvert.s(fconvert.t(*(data_4df904 + 0x440fc)) + fconvert.t(118f)), var_104_1, eax_34, 0f, 4)
00402409        border_sprite_extend(widget->__offset(0x718).d, 0x28, 0x27, 0x29, 0)
0040243a        widget->__offset(0x720).d = allocate_border(data_4df904 + 0xb4c)
00402440        struct Color4f* color_14
00402440        int32_t ecx_59
00402440        color_14, ecx_59 = set_color_rgba(&color_1, 1f, 1f, 1f, 1f)
00402452        int32_t var_124_7 = ecx_59
00402469        initialize_frontend_widget(widget->__offset(0x720).d, &__dos_header, "00%", 0x15, 0f, fconvert.s(fconvert.t(widget->__offset(0x6f8).d) + fconvert.t(40f)), color_14, 2, 0f)
0040247f        return layout_frontend_widget(widget)
