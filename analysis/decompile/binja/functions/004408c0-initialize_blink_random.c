/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_blink_random @ 0x4408c0 */

004408c0        void* var_4_1 = arg1
004408c3        *(arg1 + 0x3bb700) = 0
004408cd        void* esi = arg1 + 0x3bb704
004408d3        int32_t i_1 = 0x18
00440904        int32_t result
00440904        int32_t i
004408d8        result = next_math_random_value()
004408e1        esi += 4
004408e8        i = i_1
004408e8        i_1 -= 1
00440901        *(esi - 4) = fconvert.s(fconvert.t(1f) / ((float.t(result) * fconvert.t(3.05175781e-05f) + fconvert.t(1f)) * fconvert.t(60f)))
00440904        do while (i != 1)
00440909        return result
