/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_frontend_widget @ 0x401d30 */

00401d42        *(arg1 + 0x7c) = arg4
00401d45        *(arg1 + 0x48) = 5
00401d4c        *(arg1 + 0x5c) = 0
00401d4f        *(arg1 + 0x22c) = 0
00401d55        *(arg1 + 0x230) = 0x41a00000
00401d5f        *(arg1 + 0x234) = 0
00401d6e        void* eax = data_4df904 + 0xb4c
00401d7b        if ((0x200 & *(arg1 + 4)) == 0)
00401d8c        *(arg1 + 8) = eax
00401d92        *(arg1 + 0xc) = *(eax + 0xc)
00401d95        *(eax + 0xc) = arg1
00401d98        void* eax_1 = *(arg1 + 0xc)
00401d9d        if (eax_1 != 0)
00401d9f        *(eax_1 + 8) = arg1
00401da2        *(arg1 + 4) |= 0x200
00401d82        report_errorf("List ADDafter")
00401db9        *(arg1 + 0x290) = 0
00401dbf        *(arg1 + 0x298) = arg1
00401dc5        *(arg1 + 0x2a4) = 0
00401dcb        *(arg1 + 0x2c4) = arg1
00401dd1        *(arg1 + 0x1a0) = arg2 | 0x40001
00401dd7        set_color_white()
00401de4        set_color_white()
00401df6        struct Color4f color
00401df6        if (arg4 - 0x14 u> 3)
0040220a        report_errorf("Unknown Border Style Requested")
00401dfc        struct Color4f* color_13
00401dfc        switch (arg4)
00401e1a        case 0x14
00401e1a        *(arg1 + 0x6ec) = 0
00401e20        *(arg1 + 0x6f0) = 0x3fa66666
00401e2a        *(arg1 + 0x214) = 0x41100000
00401e34        *(arg1 + 0x218) = 0x41500000
00401e3e        *(arg1 + 0x26c) = 0x41d00000
00401e48        struct Color4f color_5
00401e48        struct Color4f* eax_5 = set_color_rgba(&color_5, 1f, 0.521568656f, 0f, 0.699999988f)
00401e5f        *(arg1 + 0x1ec) = eax_5->r
00401e6e        *(arg1 + 0x1f0) = eax_5->g
00401e74        *(arg1 + 0x1f4) = eax_5->b
00401e81        *(arg1 + 0x1f8) = eax_5->a
00401e84        struct Color4f color_12
00401e84        struct Color4f* eax_7 = set_color_rgba(&color_12, 1f, 1f, 1f, 1f)
00401e90        *(arg1 + 0x1fc) = eax_7->r
00401e9f        *(arg1 + 0x200) = eax_7->g
00401eaa        *(arg1 + 0x204) = eax_7->b
00401eb7        *(arg1 + 0x208) = eax_7->a
00401eba        struct Color4f color_9
00401eba        struct Color4f* eax_8 = set_color_rgba(&color_9, 0.329411775f, 0.223529413f, 0.501960814f, 0.699999988f)
00401ec7        int32_t var_118_1 = 0x3f800000
00401ecc        int32_t var_11c_1 = 0x3f31b1b2
00401ed1        *(arg1 + 0x1bc) = eax_8->r
00401ed6        int32_t var_120_1 = 0x3e9e9e9f
00401edb        int32_t var_124_1 = 0x3f1b9b9c
00401ee0        *(arg1 + 0x1c0) = eax_8->g
00401ee6        *(arg1 + 0x1c4) = eax_8->b
00401eec        *(arg1 + 0x1c8) = eax_8->a
00401eef        void var_c0
00401eef        color_13 = &var_c0
0040210e        case 0x15
0040210e        *(arg1 + 0x6ec) = 0
00402114        *(arg1 + 0x6f0) = 0x3f800000
0040211e        *(arg1 + 0x214) = 0x41100000
00402128        *(arg1 + 0x218) = 0x41500000
00402132        *(arg1 + 0x26c) = 0x41d00000
0040213c        struct Color4f color_6
0040213c        struct Color4f* eax_20 = set_color_rgba(&color_6, 1f, 0.521568656f, 0f, 0.699999988f)
00402153        *(arg1 + 0x1ec) = eax_20->r
00402162        *(arg1 + 0x1f0) = eax_20->g
00402168        *(arg1 + 0x1f4) = eax_20->b
0040216e        *(arg1 + 0x1f8) = eax_20->a
00402178        struct Color4f color_8
00402178        struct Color4f* eax_22 = set_color_rgba(&color_8, 1f, 1f, 1f, 1f)
00402184        *(arg1 + 0x1fc) = eax_22->r
00402193        *(arg1 + 0x200) = eax_22->g
0040219e        *(arg1 + 0x204) = eax_22->b
004021ab        *(arg1 + 0x208) = eax_22->a
004021ae        struct Color4f color_10
004021ae        struct Color4f* eax_23 = set_color_rgba(&color_10, 0.329411775f, 0.223529413f, 0.501960814f, 0.699999988f)
004021bb        int32_t var_118_4 = 0x3f800000
004021c0        int32_t var_11c_4 = 0x3f31b1b2
004021c5        *(arg1 + 0x1bc) = eax_23->r
004021ca        int32_t var_120_4 = 0x3e9e9e9f
004021cf        int32_t var_124_4 = 0x3f1b9b9c
004021d4        *(arg1 + 0x1c0) = eax_23->g
004021da        *(arg1 + 0x1c4) = eax_23->b
004021e0        *(arg1 + 0x1c8) = eax_23->a
004021e3        color_13 = &color
00401f03        case 0x16
00401f03        *(arg1 + 0x230) = 0x41a00000
00401f19        *(arg1 + 0x6ec) = 0
00401f1f        __builtin_strncpy(arg1 + 0x6f0, "ff&?", 4)
00401f29        *(arg1 + 0x214) = 0x3f800000
00401f33        *(arg1 + 0x218) = 0x40400000
00401f3d        *(arg1 + 0x26c) = 0x40000000
00401f47        *(arg1 + 0x234) = 1
00401f4e        struct Color4f color_7
00401f4e        struct Color4f* eax_10 = set_color_rgba(&color_7, 1f, 0.521568656f, 0f, 0.699999988f)
00401f65        *(arg1 + 0x1ec) = eax_10->r
00401f74        *(arg1 + 0x1f0) = eax_10->g
00401f7a        *(arg1 + 0x1f4) = eax_10->b
00401f80        *(arg1 + 0x1f8) = eax_10->a
00401f8a        struct Color4f color_4
00401f8a        struct Color4f* eax_12 = set_color_rgba(&color_4, 1f, 1f, 1f, 1f)
00401f96        *(arg1 + 0x1fc) = eax_12->r
00401fa5        *(arg1 + 0x200) = eax_12->g
00401fb0        *(arg1 + 0x204) = eax_12->b
00401fbd        *(arg1 + 0x208) = eax_12->a
00401fc0        struct Color4f color_11
00401fc0        struct Color4f* eax_13 = set_color_rgba(&color_11, 0.329411775f, 0.223529413f, 0.501960814f, 0.699999988f)
00401fcd        int32_t var_118_2 = 0x3f800000
00401fd2        int32_t var_11c_2 = 0x3f31b1b2
00401fd7        *(arg1 + 0x1bc) = eax_13->r
00401fdc        int32_t var_120_2 = 0x3e9e9e9f
00401fe1        int32_t var_124_2 = 0x3f1b9b9c
00401fe6        *(arg1 + 0x1c0) = eax_13->g
00401fec        *(arg1 + 0x1c4) = eax_13->b
00401ff2        *(arg1 + 0x1c8) = eax_13->a
00401ff5        void var_f0
00401ff5        color_13 = &var_f0
00402012        case 0x17
00402012        *(arg1 + 0x6ec) = 0
00402018        *(arg1 + 0x6f0) = 0x3f91eb85
00402022        *(arg1 + 0x214) = 0x40c00000
0040202c        *(arg1 + 0x218) = 0x40e00000
00402036        *(arg1 + 0x26c) = 0x40000000
00402040        *(arg1 + 0x230) = 0x41a00000
0040204a        struct Color4f color_1
0040204a        struct Color4f* eax_15 = set_color_rgba(&color_1, 1f, 0.521568656f, 0f, 0.699999988f)
00402061        *(arg1 + 0x1ec) = eax_15->r
00402070        *(arg1 + 0x1f0) = eax_15->g
00402076        *(arg1 + 0x1f4) = eax_15->b
0040207c        *(arg1 + 0x1f8) = eax_15->a
00402083        struct Color4f color_2
00402083        struct Color4f* eax_17 = set_color_rgba(&color_2, 1f, 1f, 1f, 1f)
0040208f        *(arg1 + 0x1fc) = eax_17->r
0040209e        *(arg1 + 0x200) = eax_17->g
004020a9        *(arg1 + 0x204) = eax_17->b
004020b3        *(arg1 + 0x208) = eax_17->a
004020b6        struct Color4f color_3
004020b6        struct Color4f* eax_18 = set_color_rgba(&color_3, 0.329411775f, 0.223529413f, 0.501960814f, 0.699999988f)
004020c3        int32_t var_118_3 = 0x3f800000
004020c8        int32_t var_11c_3 = 0x3f31b1b2
004020cd        *(arg1 + 0x1bc) = eax_18->r
004020d2        int32_t var_120_3 = 0x3e9e9e9f
004020d7        int32_t var_124_3 = 0x3f1b9b9c
004020dc        *(arg1 + 0x1c0) = eax_18->g
004020e2        *(arg1 + 0x1c4) = eax_18->b
004020e8        *(arg1 + 0x1c8) = eax_18->a
004020eb        void var_90
004020eb        color_13 = &var_90
004021e7        struct Color4f* eax_25 = set_color_rgba(color_13, 0.607843161f, 0.309803933f, 0.694117665f, 1f)
004021ee        *(arg1 + 0x1cc) = eax_25->r
004021f4        *(arg1 + 0x1d0) = eax_25->g
004021fa        *(arg1 + 0x1d4) = eax_25->b
00402200        *(arg1 + 0x1d8) = eax_25->a
0040221e        *(arg1 + 0x17c) = 0x3f000000
00402224        *(arg1 + 0x180) = 0x3f000000
0040222a        *(arg1 + 0x38) = 1
0040222d        unhide_border_init(arg1)
00402241        sub_44e5b0(arg1 + 0x2cc, arg3)
00402254        *(arg1 + 0x6f8) = arg6
0040225a        float eax_27
0040225a        eax_27.b = *(arg1 + 0x1a0)
00402263        *(arg1 + 0x6f4) = arg5
0040226b        *(arg1 + 0x20c) = 0x3f800000
00402277        if ((eax_27.b & 2) == 0)
00402280        unhighlight_border(arg1)
00402279        highlight_border(arg1)
00402285        long double x87_r5 = fconvert.t(*(arg1 + 0x214))
0040229f        *(arg1 + 0x210) = *(arg1 + 0x20c)
004022a5        *(arg1 + 0x21c) = fconvert.s(x87_r5)
004022ab        *(arg1 + 0x220) = fconvert.s(x87_r5)
004022b8        *(arg1 + 0x224) = 0
004022be        *(arg1 + 0x228) = 0
004022c4        *(arg1 + 0x25c) = arg7
004022ca        *(arg1 + 0x260) = arg8
004022dc        bool cond:0 = (*(arg1 + 0x1a0) & 0x100000) == 0
004022e1        long double x87_r5_2 = fconvert.t(arg8) + fconvert.t(*(data_4df904 + 0x440fc))
004022e7        *(arg1 + 0x278) = 1
004022ed        *(arg1 + 0x260) = fconvert.s(x87_r5_2)
004022f3        if (not(cond:0))
0040232e        float var_104_1 = fconvert.s(fconvert.t(arg6) + fconvert.t(40f))
00402336        *(arg1 + 0x71c) = allocate_border(data_4df904 + 0xb4c)
0040233c        struct Color4f* eax_31
0040233c        int32_t ecx_43
0040233c        eax_31, ecx_43 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0040234c        int32_t var_128_1 = ecx_43
00402377        initialize_frontend_sprite_button(*(arg1 + 0x71c), (*(arg1 + 0x1a0) & 0x800000) | 0x20400814, 0x2a, fconvert.s(fconvert.t(*(data_4df904 + 0x440fc)) + fconvert.t(458f)), var_104_1, eax_31, 0f, 4)
00402389        border_sprite_extend(*(arg1 + 0x71c), 0x2c, 0x2b, 0x2d, 1)
004023ba        *(arg1 + 0x718) = allocate_border(data_4df904 + 0xb4c)
004023c0        int32_t* eax_34
004023c0        int32_t ecx_51
004023c0        eax_34, ecx_51 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
004023cc        int32_t var_128_3 = ecx_51
004023f7        initialize_frontend_sprite_button(*(arg1 + 0x718), (*(arg1 + 0x1a0) & 0x800000) | 0x20400814, 0x26, fconvert.s(fconvert.t(*(data_4df904 + 0x440fc)) + fconvert.t(118f)), var_104_1, eax_34, 0f, 4)
00402409        border_sprite_extend(*(arg1 + 0x718), 0x28, 0x27, 0x29, 0)
0040243a        *(arg1 + 0x720) = allocate_border(data_4df904 + 0xb4c)
00402440        struct Color4f* eax_37
00402440        int32_t ecx_59
00402440        eax_37, ecx_59 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00402452        int32_t var_124_7 = ecx_59
00402453        *(arg1 + 0x720)
00402469        initialize_frontend_widget(&__dos_header, 0x4a10d0, 0x15, 0, fconvert.s(fconvert.t(*(arg1 + 0x6f8)) + fconvert.t(40f)), eax_37, 2, 0)
0040247f        return layout_frontend_widget(arg1)
