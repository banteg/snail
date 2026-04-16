/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_frontend_sprite_button @ 0x401a70 */

00401a78        void* eax = data_4df904 + 0xb4c
00401a8b        if ((arg1->__offset(0x4).d & 0x200) == 0)
00401a9c        arg1->__offset(0x8).d = eax
00401aa2        arg1->__offset(0xc).d = *(eax + 0xc)
00401aa5        *(eax + 0xc) = arg1
00401aa8        void* eax_1 = arg1->__offset(0xc).d
00401aad        if (eax_1 != 0)
00401aaf        *(eax_1 + 8) = arg1
00401ab2        arg1->__offset(0x4).d |= 0x200
00401a92        report_errorf("List ADDafter")
00401ab5        arg1->__offset(0x48).d = 5
00401abc        arg1->__offset(0x5c).b = 0
00401abf        arg1->__offset(0x290).d = 0
00401ac5        arg1->__offset(0x298).d = arg1
00401acb        arg1->__offset(0x2a4).d = 0
00401ad1        arg1->__offset(0x2c4).d = arg1
00401adc        arg1->__offset(0x22c).d = 0
00401ae2        arg1->__offset(0x230).d = 0x41a00000
00401ae8        arg1->__offset(0x234).b = 0
00401aee        arg1->__offset(0x178).d = 0x40800000
00401af8        arg1->__offset(0x6ec).d = 0
00401aff        arg1->__offset(0x6f0).d = 0x3f800000
00401b0b        arg1->__offset(0x214).d = 0x41200000
00401b15        arg1->__offset(0x218).d = 0x41700000
00401b1f        arg1->__offset(0x26c).d = 0x41a00000
00401b25        arg1->__offset(0x258).d = 0
00401b2b        arg1->__offset(0x38).d = 1
00401b32        unhide_border_init(arg1)
00401b3f        int32_t eax_3 = arg2 | 0x40801
00401b44        arg1->__offset(0x6f8).d = arg5
00401b4a        arg1->__offset(0x1a0).d = eax_3
00401b50        arg1->__offset(0x1a4).d = eax_3
00401b5a        arg1->__offset(0x2cc).b = 0
00401b60        arg1->__offset(0x6f4).d = arg4
00401b83        arg1->__offset(0x1bc).d = *arg6
00401b8d        arg1->__offset(0x1c0).d = arg6[1]
00401b93        arg1->__offset(0x1c4).d = arg6[2]
00401b99        arg1->__offset(0x1c8).d = arg6[3]
00401ba4        arg1->__offset(0x1cc).d = *arg6
00401bad        arg1->__offset(0x1d0).d = arg6[1]
00401bb3        arg1->__offset(0x1d4).d = arg6[2]
00401bbd        arg1->__offset(0x1d8).d = arg6[3]
00401bc0        struct Color4f color
00401bc0        struct Color4f* eax_7 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00401bd7        *(arg1 + 0x1ec) = eax_7->r
00401be6        *(arg1 + 0x1f0) = eax_7->g
00401bec        *(arg1 + 0x1f4) = eax_7->b
00401bf2        *(arg1 + 0x1f8) = eax_7->a
00401bf9        struct Color4f* eax_9 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00401c06        arg1->__offset(0x1fc).d = eax_9->r
00401c0f        arg1->__offset(0x200).d = eax_9->g
00401c15        arg1->__offset(0x204).d = eax_9->b
00401c1b        arg1->__offset(0x208).d = eax_9->a
00401c1e        float eax_10
00401c1e        eax_10.b = arg1->__offset(0x1a0).b
00401c27        if ((eax_10.b & 2) == 0)
00401c41        int32_t edx_10 = arg1->__offset(0x214).d
00401c47        arg1->__offset(0x20c).d = 0
00401c4d        arg1->__offset(0x21c).d = edx_10
00401c29        int32_t ecx_11 = arg1->__offset(0x218).d
00401c2f        arg1->__offset(0x20c).d = 0x3f800000
00401c39        arg1->__offset(0x21c).d = ecx_11
00401c59        int32_t ecx_12 = arg1->__offset(0x21c).d
00401c63        arg1->__offset(0x210).d = arg1->__offset(0x20c).d
00401c6d        arg1->__offset(0x220).d = ecx_12
00401c77        arg1->__offset(0x224).d = 0
00401c7d        arg1->__offset(0x228).d = 0
00401c83        arg1->__offset(0x25c).d = 0
00401c89        arg1->__offset(0x260).d = arg7
00401c98        long double x87_r7_1 = fconvert.t(arg7) + fconvert.t(*(data_4df904 + 0x440fc))
00401ca2        arg1->__offset(0x238).d = arg4
00401ca8        arg1->__offset(0x23c).d = arg5
00401cae        arg1->__offset(0x260).d = fconvert.s(x87_r7_1)
00401cbe        arg1->__offset(0x248).d = fconvert.s(float.t(*(*((arg3 << 2) + &data_78ff90) + 4)))
00401cd1        long double x87_r7_3 = float.t(*(*((arg3 << 2) + &data_78ff90) + 8))
00401cd4        arg1->__offset(0x250).d = arg1->__offset(0x248).d
00401cde        arg1->__offset(0x270).d = arg3
00401ce8        arg1->__offset(0x24c).d = fconvert.s(x87_r7_3)
00401cee        int32_t edx_14 = arg1->__offset(0x24c).d
00401cf4        arg1->__offset(0x6f4).d = arg4
00401cfa        arg1->__offset(0x254).d = edx_14
00401d06        arg1->__offset(0x6f8).d = arg5
00401d0c        arg1->__offset(0x274).d = arg8
00401d12        arg1->__offset(0x264).d = 0
00401d18        arg1->__offset(0x268).d = 0
00401d28        return layout_frontend_widget(arg1)
