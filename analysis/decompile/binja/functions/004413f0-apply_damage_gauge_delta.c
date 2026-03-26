/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: apply_damage_gauge_delta @ 0x4413f0 */

004413f0        void* edx_1 = data_4df904
00441400        void* result
00441400        if ((*(edx_1 + 0x4300b4) & 0x80) != 0)
00441402        result.b = force
00441408        if ((*(edx_1 + 0x4300b4) & 0x80) == 0 || result.b != 0)
0044140e        int32_t state = controller->state
00441413        if (state != 2)
0044144c        label_44144c:
0044144c        long double x87_r7_3 = fconvert.t(controller->hit_flash_progress)
0044144f        long double temp1_1 = fconvert.t(0f)
0044144f        x87_r7_3 - temp1_1
00441455        result.w = (x87_r7_3 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp1_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp1_1 ? 1 : 0) << 0xe
0044145a        if ((result:1.b & 0x40) != 0)
00441460        long double x87_r7_4 = fconvert.t(delta)
00441464        long double temp4_1 = fconvert.t(0f)
00441464        x87_r7_4 - temp4_1
0044146a        result.w = (x87_r7_4 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp4_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp4_1 ? 1 : 0) << 0xe
0044146f        if ((result:1.b & 0x41) == 0)
0044147e        change_snail_skin(edx_1 + 0x434038, 1, 0.200000003f)
00441495        if (play_voice_manager(0x751498, 0, 1, 0xffffffff).b != 0)
004414ed        controller->hit_flash_progress = controller->hit_flash_step
004414a9        if (play_voice_manager(0x751498, 9, 0, 0xffffffff) != 0)
004414ae        controller->hit_flash_progress = controller->hit_flash_step
004414b1        result = data_4df904
004414be        if (*(result + 0x430054) == 0)
004414cc        dispatch_cutscene_animation(result + 0x432700, 6, 1, 0xffffffff)
004414e3        dispatch_cutscene_animation(data_4df904 + 0x432700, 1, 0, 0xffffffff)
004414f4        long double x87_r7_6 = fconvert.t(delta) + fconvert.t(controller->fill)
004414f7        long double temp3_1 = fconvert.t(0f)
004414f7        x87_r7_6 - temp3_1
004414fd        controller->fill = fconvert.s(x87_r7_6)
004414fd        bool c1_1 = unimplemented  {fst dword [esi+0x1c], st0}
00441500        result.w = (x87_r7_6 < temp3_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_6, temp3_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp3_1 ? 1 : 0) << 0xe | 0x3800
00441505        if ((result:1.b & 1) != 0)
0044150f        controller->fill = fconvert.s(fconvert.t(0f))
00441513        return result
00441516        long double temp5_1 = fconvert.t(1f)
00441516        x87_r7_6 - temp5_1
0044151c        result.w = (x87_r7_6 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp5_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp5_1 ? 1 : 0) << 0xe | 0x3800
00441521        if ((result:1.b & 0x41) == 0)
00441525        x87_r7_6 = fconvert.t(1f)
0044152b        controller->fill = fconvert.s(x87_r7_6)
00441415        long double x87_r7_1 = fconvert.t(delta)
00441419        long double temp2_1 = fconvert.t(0f)
00441419        x87_r7_1 - temp2_1
0044141f        result.w = (x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe
00441424        if ((result:1.b & 0x41) != 0)
0044142c        if (state != state)
0044142c        goto label_44144c
0044142e        long double x87_r7_2 = fconvert.t(delta)
00441432        long double temp6_1 = fconvert.t(0f)
00441432        x87_r7_2 - temp6_1
00441438        result.w = (x87_r7_2 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp6_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp6_1 ? 1 : 0) << 0xe
00441446        if ((result:1.b & 1) == 0 || *(edx_1 + 0x42ff60) != 1)
0044143d        goto label_44144c
0044152f        return result
