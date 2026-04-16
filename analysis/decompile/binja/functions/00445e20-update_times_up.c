/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_times_up @ 0x445e20 */

00445e21        int32_t* esi = arg1
00445e23        int32_t result_1 = *esi
00445e25        int32_t result = result_1
00445e28        if (result_1 != 0)
00445e2b        if (result == 1)
00445e50        long double x87_r7_2 = fconvert.t(esi[3]) + fconvert.t(esi[2])
00445e53        esi[2] = fconvert.s(x87_r7_2)
00445e56        long double temp2_1 = fconvert.t(1f)
00445e56        x87_r7_2 - temp2_1
00445e5c        result.w = (x87_r7_2 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp2_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp2_1 ? 1 : 0) << 0xe
00445e61        if ((result:1.b & 0x41) == 0)
00445e63        *esi = 2
00445e2d        int32_t temp3_1 = result - 1
00445e2d        result -= 2
00445e2e        if (temp3_1 == 1)
00445e30        uninit_times_up(arg1)
00445e40        kill_subgoldy(data_4df904 + 0x42fd7c)
00445e45        *esi = 0
00445e4c        return 0
00445e6a        return result
