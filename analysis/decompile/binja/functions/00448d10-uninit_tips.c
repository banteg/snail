/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: uninit_tips @ 0x448d10 */

00448d12        int32_t* esi = arg1 + 0x38
00448d15        int32_t i_1 = 3
00448d2a        int32_t i
00448d1d        if (*esi == 1)
00448d21        kill_tip_widgets(esi)
00448d26        esi = &esi[8]
00448d29        i = i_1
00448d29        i_1 -= 1
00448d2a        do while (i != 1)
00448d2e        return
