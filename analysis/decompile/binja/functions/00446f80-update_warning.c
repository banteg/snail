/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_warning @ 0x446f80 */

00446f80        void* result = data_4df904
00446f88        int32_t ebx
00446f88        ebx.b = *(result + 0x74621)
00446f91        if (ebx.b == 0)
00446f97        int32_t result_1 = *arg1
00446f99        result = result_1
00446f9b        if (result_1 != 0)
00446fa1        void* eax = result - 1
00446fa2        if (result == 1)
00447009        *(arg1[3] + 0x208) = 0x3f7fbe77
00447016        long double x87_r7_8 = fconvert.t(arg1[2]) + fconvert.t(arg1[1])
00447019        arg1[1] = fconvert.s(x87_r7_8)
0044701c        long double temp2_1 = fconvert.t(1f)
0044701c        x87_r7_8 - temp2_1
00447022        result.w = (x87_r7_8 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp2_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp2_1 ? 1 : 0) << 0xe
00447027        if ((result:1.b & 0x41) == 0)
00447029        arg1[1] = 0
0044702c        *arg1 = 2
00446fa4        result = eax - 1
00446fa5        if (eax == 1)
00446fab        long double x87_r7_1 = fconvert.t(arg1[1])
00446fae        long double temp4_1 = fconvert.t(0.5f)
00446fae        x87_r7_1 - temp4_1
00446fb4        result.w = (x87_r7_1 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp4_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp4_1 ? 1 : 0) << 0xe
00446fb9        if ((result:1.b & 1) == 0)
00446fd4        *(arg1[3] + 0x208) = 0
00446fbb        long double x87_r7_2 = fconvert.t(arg1[1])
00446fc9        *(arg1[3] + 0x208) = fconvert.s(fconvert.t(1f) - (x87_r7_2 + x87_r7_2))
00446fdd        long double x87_r7_6 = fconvert.t(arg1[2]) + fconvert.t(arg1[1])
00446fe0        arg1[1] = fconvert.s(x87_r7_6)
00446fe3        long double temp5_1 = fconvert.t(1f)
00446fe3        x87_r7_6 - temp5_1
00446fe9        result.w = (x87_r7_6 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp5_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp5_1 ? 1 : 0) << 0xe
00446fee        if ((result:1.b & 0x41) == 0)
00446ff0        arg1[1] = 0
00446ff3        *arg1 = 1
00447005        return play_sound_effect(0x32)
00447032        return result
