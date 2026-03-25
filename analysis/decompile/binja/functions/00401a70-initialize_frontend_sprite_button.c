/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_frontend_sprite_button @ 0x401a70 */

00401a78        void* eax = data_4df904 + 0xb4c
00401a8b        if ((*(arg1 + 4) & 0x200) == 0)
00401a9c        *(arg1 + 8) = eax
00401aa2        *(arg1 + 0xc) = *(eax + 0xc)
00401aa5        *(eax + 0xc) = arg1
00401aa8        void* eax_1 = *(arg1 + 0xc)
00401aad        if (eax_1 != 0)
00401aaf        *(eax_1 + 8) = arg1
00401ab2        *(arg1 + 4) |= 0x200
00401a92        report_errorf("List ADDafter")
00401ab5        *(arg1 + 0x48) = 5
00401abc        *(arg1 + 0x5c) = 0
00401abf        *(arg1 + 0x290) = 0
00401ac5        *(arg1 + 0x298) = arg1
00401acb        *(arg1 + 0x2a4) = 0
00401ad1        *(arg1 + 0x2c4) = arg1
00401adc        *(arg1 + 0x22c) = 0
00401ae2        *(arg1 + 0x230) = 0x41a00000
00401ae8        *(arg1 + 0x234) = 0
00401aee        *(arg1 + 0x178) = 0x40800000
00401af8        *(arg1 + 0x6ec) = 0
00401aff        *(arg1 + 0x6f0) = 0x3f800000
00401b0b        *(arg1 + 0x214) = 0x41200000
00401b15        *(arg1 + 0x218) = 0x41700000
00401b1f        *(arg1 + 0x26c) = 0x41a00000
00401b25        *(arg1 + 0x258) = 0
00401b2b        *(arg1 + 0x38) = 1
00401b32        unhide_border_init(arg1)
00401b3f        int32_t eax_3 = arg2 | 0x40801
00401b44        *(arg1 + 0x6f8) = arg5
00401b4a        *(arg1 + 0x1a0) = eax_3
00401b50        *(arg1 + 0x1a4) = eax_3
00401b5a        *(arg1 + 0x2cc) = 0
00401b60        *(arg1 + 0x6f4) = arg4
00401b83        *(arg1 + 0x1bc) = *arg6
00401b8d        *(arg1 + 0x1c0) = arg6[1]
00401b93        *(arg1 + 0x1c4) = arg6[2]
00401b99        *(arg1 + 0x1c8) = arg6[3]
00401ba4        *(arg1 + 0x1cc) = *arg6
00401bad        *(arg1 + 0x1d0) = arg6[1]
00401bb3        *(arg1 + 0x1d4) = arg6[2]
00401bbd        *(arg1 + 0x1d8) = arg6[3]
00401bc0        struct Color4f color
00401bc0        struct Color4f* eax_7 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00401bd7        *(arg1 + 0x1ec) = eax_7->r
00401be6        *(arg1 + 0x1f0) = eax_7->g
00401bec        *(arg1 + 0x1f4) = eax_7->b
00401bf2        *(arg1 + 0x1f8) = eax_7->a
00401bf9        struct Color4f* eax_9 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00401c06        *(arg1 + 0x1fc) = eax_9->r
00401c0f        *(arg1 + 0x200) = eax_9->g
00401c15        *(arg1 + 0x204) = eax_9->b
00401c1b        *(arg1 + 0x208) = eax_9->a
00401c1e        float eax_10
00401c1e        eax_10.b = *(arg1 + 0x1a0)
00401c27        if ((eax_10.b & 2) == 0)
00401c41        int32_t edx_10 = *(arg1 + 0x214)
00401c47        *(arg1 + 0x20c) = 0
00401c4d        *(arg1 + 0x21c) = edx_10
00401c29        int32_t ecx_11 = *(arg1 + 0x218)
00401c2f        *(arg1 + 0x20c) = 0x3f800000
00401c39        *(arg1 + 0x21c) = ecx_11
00401c59        int32_t ecx_12 = *(arg1 + 0x21c)
00401c63        *(arg1 + 0x210) = *(arg1 + 0x20c)
00401c6d        *(arg1 + 0x220) = ecx_12
00401c77        *(arg1 + 0x224) = 0
00401c7d        *(arg1 + 0x228) = 0
00401c83        *(arg1 + 0x25c) = 0
00401c89        *(arg1 + 0x260) = arg7
00401c98        long double x87_r7_1 = fconvert.t(arg7) + fconvert.t(*(data_4df904 + 0x440fc))
00401ca2        *(arg1 + 0x238) = arg4
00401ca8        *(arg1 + 0x23c) = arg5
00401cae        *(arg1 + 0x260) = fconvert.s(x87_r7_1)
00401cbe        *(arg1 + 0x248) = fconvert.s(float.t(*(*((arg3 << 2) + &data_78ff90) + 4)))
00401cd1        long double x87_r7_3 = float.t(*(*((arg3 << 2) + &data_78ff90) + 8))
00401cd4        *(arg1 + 0x250) = *(arg1 + 0x248)
00401cde        *(arg1 + 0x270) = arg3
00401ce8        *(arg1 + 0x24c) = fconvert.s(x87_r7_3)
00401cee        int32_t edx_14 = *(arg1 + 0x24c)
00401cf4        *(arg1 + 0x6f4) = arg4
00401cfa        *(arg1 + 0x254) = edx_14
00401d06        *(arg1 + 0x6f8) = arg5
00401d0c        *(arg1 + 0x274) = arg8
00401d12        *(arg1 + 0x264) = 0
00401d18        *(arg1 + 0x268) = 0
00401d28        return layout_frontend_widget(arg1)
