/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_voice_set @ 0x449360 */

00449360        long double x87_r7 = fconvert.t(*(arg1 + 0x10))
00449363        long double temp0 = fconvert.t(0f)
00449363        x87_r7 - temp0
00449369        int16_t result = (x87_r7 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp0) ? 1 : 0) << 0xa | (x87_r7 == temp0 ? 1 : 0) << 0xe
0044936e        if ((result:1.b & 0x41) == 0)
00449373        long double x87_r7_2 = fconvert.t(*(arg1 + 0x14)) + fconvert.t(*(arg1 + 0x10))
00449376        *(arg1 + 0x10) = fconvert.s(x87_r7_2)
00449379        long double temp1_1 = fconvert.t(1f)
00449379        x87_r7_2 - temp1_1
0044937f        result = (x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe
00449384        if ((result:1.b & 0x41) == 0)
00449386        *(arg1 + 0x10) = 0
0044938d        return result
