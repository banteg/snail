/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: switch_track_mirror @ 0x435e60 */

00435e61        char* var_8 = "Mirror"
00435e6d        long double st0 = random_float_below(1f)
00435e72        long double temp0 = fconvert.t(0.5f)
00435e72        st0 - temp0
00435e82        int16_t result
00435e82        if ((((st0 < temp0 ? 1 : 0) << 8 | (is_unordered.t(st0, temp0) ? 1 : 0) << 0xa | (st0 == temp0 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
00435e88        result.b = 0
00435e84        result.b = 1
00435e8d        if (result.b != *(arg1 + 2))
00435e94        *(arg1 + 4) = 0
00435e8f        *(arg1 + 4) += 1
00435e9b        if (*(arg1 + 4) s< 4)
00435e9d        *(arg1 + 2) = result.b
00435ea1        return result
00435ea4        *(arg1 + 4) = 0
00435ea7        result.b = result.b == 0
00435eaa        *(arg1 + 2) = result.b
00435eae        return result
