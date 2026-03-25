/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: layout_frontend_widget @ 0x4024a0 */

004024a6        void* esi = arg1
004024b6        while (true)
004024b6        float* result = *(esi + 0x1a0)
004024bf        float* ebx_1
004024bf        float* edi_1
004024bf        if ((result:1.b & 8) != 0)
004024c7        int32_t edx_1 = *(esi + 0x23c)
004024cd        ebx_1 = esi + 0x238
004024d3        edi_1 = esi + 0x23c
004024d9        *(esi + 0x6f4) = *(esi + 0x238)
004024df        *(esi + 0x6f8) = edx_1
004024ef        if ((result & 0x10000) == 0)
00402557        edi_1 = esi + 0x23c
00402564        ebx_1 = esi + 0x238
00402584        result = layout_and_queue_wrapped_font_text(esi + 0x2cc, *(esi + 0x6ec), *(esi + 0x6f0), *(esi + 0x6f4), *(esi + 0x6f8), ebx_1, edi_1, esi + 0x248, esi + 0x24c, *(esi + 0x228), (data_4df934.d u>> 8).b & 1, *(esi + 0x25c), *(esi + 0x260), 0x1000000, esi + 0x1ec, 1, 0)
004024f1        float eax_3 = *(esi + 0x4c)
004024f4        float ecx_1 = *(esi + 0x50)
004024fa        ebx_1 = esi + 0x238
00402500        edi_1 = esi + 0x23c
00402506        *(esi + 0x248) = *(esi + 0x54)
0040250c        *ebx_1 = eax_3
0040250e        result = *(esi + 0x58)
00402511        *edi_1 = ecx_1
00402513        *(esi + 0x24c) = result
0040258e        float edx_7 = *edi_1
00402590        *(esi + 0x240) = *ebx_1
00402596        int32_t ecx_7 = *(esi + 0x1a0)
004025a2        *(esi + 0x244) = edx_7
004025a8        if ((ecx_7 & 0x20000000) == 0)
004025b6        long double x87_r7_3 = fconvert.t(*ebx_1) + fconvert.t(*(esi + 0x218)) + fconvert.t(*(esi + 0x248))
004025bc        long double temp0_1 = fconvert.t(640f)
004025bc        x87_r7_3 - temp0_1
004025c2        result.w = (x87_r7_3 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp0_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp0_1 ? 1 : 0) << 0xe
004025c7        if ((result:1.b & 0x41) != 0)
004025e5        long double x87_r7_8 = fconvert.t(*ebx_1) - fconvert.t(*(esi + 0x218))
004025eb        long double temp1_1 = fconvert.t(0f)
004025eb        x87_r7_8 - temp1_1
004025f1        result.w = (x87_r7_8 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp1_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp1_1 ? 1 : 0) << 0xe
004025f6        if ((result:1.b & 1) != 0)
004025fe        *(esi + 0x240) = *(esi + 0x218)
004025db        *(esi + 0x240) = fconvert.s(fconvert.t(640f) - fconvert.t(*(esi + 0x218)) - fconvert.t(*(esi + 0x248)))
0040260a        long double x87_r7_10 = fconvert.t(*(esi + 0x218)) + fconvert.t(*edi_1)
0040260c        long double temp2_1 = fconvert.t(480f)
0040260c        x87_r7_10 - temp2_1
00402612        result.w = (x87_r7_10 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp2_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp2_1 ? 1 : 0) << 0xe
00402617        if ((result:1.b & 0x41) != 0)
0040262f        long double x87_r7_14 = fconvert.t(*edi_1) - fconvert.t(*(esi + 0x218))
00402635        long double temp3_1 = fconvert.t(0f)
00402635        x87_r7_14 - temp3_1
0040263b        result.w = (x87_r7_14 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp3_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp3_1 ? 1 : 0) << 0xe
00402640        if ((result:1.b & 1) != 0)
00402648        *(esi + 0x244) = *(esi + 0x218)
00402625        *(esi + 0x244) = fconvert.s(fconvert.t(480f) - fconvert.t(*(esi + 0x218)))
00402654        long double x87_r7_16 = fconvert.t(*(esi + 0x240)) - fconvert.t(*ebx_1)
00402658        result = ecx_7 & 0x100000
00402665        *(esi + 0x260) = fconvert.s(x87_r7_16 + fconvert.t(*(esi + 0x260)))
00402671        *(esi + 0x6f4) = fconvert.s(x87_r7_16 + fconvert.t(*(esi + 0x6f4)))
00402685        *(esi + 0x6f8) = fconvert.s(fconvert.t(*(esi + 0x244)) - fconvert.t(*edi_1) + fconvert.t(*(esi + 0x6f8)))
0040268b        long double x87_r7_21 = fconvert.t(*(esi + 0x240))
00402691        *ebx_1 = fconvert.s(x87_r7_21)
00402693        long double x87_r6_3 = fconvert.t(*(esi + 0x244))
0040269d        *edi_1 = fconvert.s(x87_r6_3)
0040269f        if (result != 0)
004026bb        *(esi + 0x184) = fconvert.s(fconvert.t(*(esi + 0x248)) * fconvert.t(0.100000001f) + x87_r7_21 + fconvert.t(4f) - fconvert.t(12f))
004026d5        *(esi + 0x188) = fconvert.s(fconvert.t(*(esi + 0x248)) * fconvert.t(0.800000012f) + x87_r7_21 - fconvert.t(4f))
004026e9        long double x87_r7_25 = fconvert.t(*(esi + 0x24c)) * fconvert.t(0.5f) + fconvert.t(fconvert.s(x87_r6_3))
004026f5        *(esi + 0x18c) = fconvert.s(x87_r7_25 - fconvert.t(6f))
00402707        *(esi + 0x190) = fconvert.s(x87_r7_25 + fconvert.t(32f) - fconvert.t(6f))
00402713        if ((ecx_7 & 0x20000000) != 0 || result == 0)
00402784        return result
00402727        *(*(esi + 0x71c) + 0x23c) = fconvert.s(fconvert.t(*(esi + 0x244)) + fconvert.t(33f))
0040272d        *(esi + 0x71c)
00402733        layout_frontend_widget()
0040274a        *(*(esi + 0x718) + 0x23c) = fconvert.s(fconvert.t(*(esi + 0x244)) + fconvert.t(33f))
00402750        *(esi + 0x718)
00402756        layout_frontend_widget()
0040276d        *(*(esi + 0x720) + 0x6f8) = fconvert.s(fconvert.t(*(esi + 0x244)) + fconvert.t(49f))
00402773        esi = *(esi + 0x720)
