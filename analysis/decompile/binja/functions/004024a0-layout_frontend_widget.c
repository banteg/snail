/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: layout_frontend_widget @ 0x4024a0 */

004024a6        struct FrontendWidget* widget_1 = widget
004024b6        while (true)
004024b6        float* result = widget_1->__offset(0x1a0).d
004024bf        void* __offset(FrontendWidget, 0x238) ebx_1
004024bf        void* __offset(FrontendWidget, 0x23c) edi_1
004024bf        if ((result:1.b & 8) != 0)
004024c7        int32_t edx_1 = widget_1->__offset(0x23c).d
004024cd        ebx_1 = widget_1 + 0x238
004024d3        edi_1 = widget_1 + 0x23c
004024d9        widget_1->__offset(0x6f4).d = widget_1->__offset(0x238).d
004024df        widget_1->__offset(0x6f8).d = edx_1
004024ef        if ((result & 0x10000) == 0)
00402557        edi_1 = widget_1 + 0x23c
00402564        ebx_1 = widget_1 + 0x238
00402584        result = layout_and_queue_wrapped_font_text(widget_1 + 0x2cc, widget_1->__offset(0x6ec).d, widget_1->__offset(0x6f0).d, widget_1->__offset(0x6f4).d, widget_1->__offset(0x6f8).d, ebx_1, edi_1, widget_1 + 0x248, widget_1 + 0x24c, widget_1->__offset(0x228).d, (data_4df934.d u>> 8).b & 1, widget_1->__offset(0x25c).d, widget_1->__offset(0x260).d, 0x1000000, widget_1 + 0x1ec, 1, 0)
004024f1        int32_t eax_3 = widget_1->__offset(0x4c).d
004024f4        int32_t ecx_1 = widget_1->__offset(0x50).d
004024fa        ebx_1 = widget_1 + 0x238
00402500        edi_1 = widget_1 + 0x23c
00402506        widget_1->__offset(0x248).d = widget_1->__offset(0x54).d
0040250c        (ebx_1 - 0x238)->__offset(0x238).d = eax_3
0040250e        result = widget_1->__offset(0x58).d
00402511        (edi_1 - 0x23c)->__offset(0x23c).d = ecx_1
00402513        widget_1->__offset(0x24c).d = result
0040258e        int32_t edx_7 = (edi_1 - 0x23c)->__offset(0x23c).d
00402590        widget_1->__offset(0x240).d = (ebx_1 - 0x238)->__offset(0x238).d
00402596        int32_t ecx_7 = widget_1->__offset(0x1a0).d
004025a2        widget_1->__offset(0x244).d = edx_7
004025a8        if ((ecx_7 & 0x20000000) == 0)
004025b6        long double x87_r7_3 = fconvert.t((ebx_1 - 0x238)->__offset(0x238).d) + fconvert.t(widget_1->__offset(0x218).d) + fconvert.t(widget_1->__offset(0x248).d)
004025bc        long double temp0_1 = fconvert.t(640f)
004025bc        x87_r7_3 - temp0_1
004025c2        result.w = (x87_r7_3 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp0_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp0_1 ? 1 : 0) << 0xe
004025c7        if ((result:1.b & 0x41) != 0)
004025e5        long double x87_r7_8 = fconvert.t((ebx_1 - 0x238)->__offset(0x238).d) - fconvert.t(widget_1->__offset(0x218).d)
004025eb        long double temp1_1 = fconvert.t(0f)
004025eb        x87_r7_8 - temp1_1
004025f1        result.w = (x87_r7_8 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp1_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp1_1 ? 1 : 0) << 0xe
004025f6        if ((result:1.b & 1) != 0)
004025fe        widget_1->__offset(0x240).d = widget_1->__offset(0x218).d
004025db        widget_1->__offset(0x240).d = fconvert.s(fconvert.t(640f) - fconvert.t(widget_1->__offset(0x218).d) - fconvert.t(widget_1->__offset(0x248).d))
0040260a        long double x87_r7_10 = fconvert.t(widget_1->__offset(0x218).d) + fconvert.t((edi_1 - 0x23c)->__offset(0x23c).d)
0040260c        long double temp2_1 = fconvert.t(480f)
0040260c        x87_r7_10 - temp2_1
00402612        result.w = (x87_r7_10 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp2_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp2_1 ? 1 : 0) << 0xe
00402617        if ((result:1.b & 0x41) != 0)
0040262f        long double x87_r7_14 = fconvert.t((edi_1 - 0x23c)->__offset(0x23c).d) - fconvert.t(widget_1->__offset(0x218).d)
00402635        long double temp3_1 = fconvert.t(0f)
00402635        x87_r7_14 - temp3_1
0040263b        result.w = (x87_r7_14 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp3_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp3_1 ? 1 : 0) << 0xe
00402640        if ((result:1.b & 1) != 0)
00402648        widget_1->__offset(0x244).d = widget_1->__offset(0x218).d
00402625        widget_1->__offset(0x244).d = fconvert.s(fconvert.t(480f) - fconvert.t(widget_1->__offset(0x218).d))
00402654        long double x87_r7_16 = fconvert.t(widget_1->__offset(0x240).d) - fconvert.t((ebx_1 - 0x238)->__offset(0x238).d)
00402658        result = ecx_7 & 0x100000
00402665        widget_1->__offset(0x260).d = fconvert.s(x87_r7_16 + fconvert.t(widget_1->__offset(0x260).d))
00402671        widget_1->__offset(0x6f4).d = fconvert.s(x87_r7_16 + fconvert.t(widget_1->__offset(0x6f4).d))
00402685        widget_1->__offset(0x6f8).d = fconvert.s(fconvert.t(widget_1->__offset(0x244).d) - fconvert.t((edi_1 - 0x23c)->__offset(0x23c).d) + fconvert.t(widget_1->__offset(0x6f8).d))
0040268b        long double x87_r7_21 = fconvert.t(widget_1->__offset(0x240).d)
00402691        (ebx_1 - 0x238)->__offset(0x238).d = fconvert.s(x87_r7_21)
00402693        long double x87_r6_3 = fconvert.t(widget_1->__offset(0x244).d)
0040269d        (edi_1 - 0x23c)->__offset(0x23c).d = fconvert.s(x87_r6_3)
0040269f        if (result != 0)
004026bb        widget_1->__offset(0x184).d = fconvert.s(fconvert.t(widget_1->__offset(0x248).d) * fconvert.t(0.100000001f) + x87_r7_21 + fconvert.t(4f) - fconvert.t(12f))
004026d5        widget_1->__offset(0x188).d = fconvert.s(fconvert.t(widget_1->__offset(0x248).d) * fconvert.t(0.800000012f) + x87_r7_21 - fconvert.t(4f))
004026e9        long double x87_r7_25 = fconvert.t(widget_1->__offset(0x24c).d) * fconvert.t(0.5f) + fconvert.t(fconvert.s(x87_r6_3))
004026f5        widget_1->__offset(0x18c).d = fconvert.s(x87_r7_25 - fconvert.t(6f))
00402707        widget_1->__offset(0x190).d = fconvert.s(x87_r7_25 + fconvert.t(32f) - fconvert.t(6f))
00402713        if ((ecx_7 & 0x20000000) != 0 || result == 0)
00402784        return result
00402727        *(widget_1->__offset(0x71c).d + 0x23c) = fconvert.s(fconvert.t(widget_1->__offset(0x244).d) + fconvert.t(33f))
00402733        layout_frontend_widget(widget_1->__offset(0x71c).d)
0040274a        *(widget_1->__offset(0x718).d + 0x23c) = fconvert.s(fconvert.t(widget_1->__offset(0x244).d) + fconvert.t(33f))
00402756        layout_frontend_widget(widget_1->__offset(0x718).d)
0040276d        *(widget_1->__offset(0x720).d + 0x6f8) = fconvert.s(fconvert.t(widget_1->__offset(0x244).d) + fconvert.t(49f))
00402773        widget_1 = widget_1->__offset(0x720).d
