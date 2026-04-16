/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: add_subgoldy_score @ 0x4402c0 */

004402cb        int32_t eax
004402cb        if (arg2 u> 5)
004402f4        report_errorf("Unknown Score Type")
004402fc        eax = 0
004402cb        switch (arg2)
004402d4        case 0
004402d4        eax = 0xa
004402db        case 1
004402db        eax = 0x1f4
004402e2        case 2, 3, 4
004402e2        eax = 0x64
004402e9        case 5
004402e9        eax = arg3
00440307        *(arg1 + (arg2 << 2) + 0x310) += eax
0044030e        int32_t edi_1 = *(arg1 + 0x2e4)
00440314        int32_t ecx_2 = edi_1 + eax
0044031e        *(arg1 + 0x2e4) = ecx_2
00440335        int32_t eax_4
00440335        int32_t edx_1
00440335        edx_1:eax_4 = muls.dp.d(0x14f8b589, edi_1)
0044033c        uint32_t result = edx_1 s>> 0xc u>> 0x1f
00440343        if (edi_1 s/ 0xc350 != ecx_2 s/ 0xc350)
00440345        result = *(arg1 + 0x4340)
0044034e        if (result s< 9)
00440351        *(arg1 + 0x4340) = result + 1
00440357        result = data_4df904
0044036b        if (*(result + 0x74658) == 0 && *(result + 0x24) == 0)
00440374        return play_sound_effect(0x2c)
0044037b        return result
