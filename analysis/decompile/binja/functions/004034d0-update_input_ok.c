/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_input_ok @ 0x4034d0 */

004034d0        void* result = *(arg1 + 0x1c)
004034d3        char edx = (*(result + 0x70c)).b
004034dc        void* edx_1
004034dc        long double x87_r7_4
004034dc        if ((edx & 4) != 0)
004034de        edx_1 = *(arg1 + 0x20)
004034f3        x87_r7_4 = fconvert.t(*(edx_1 + 0x218)) + fconvert.t(*(result + 0x248)) + fconvert.t(*(result + 0x238)) + fconvert.t(*(result + 0x218))
0040351f        label_40351f:
0040351f        *(edx_1 + 0x238) = fconvert.s(x87_r7_4)
00403531        *(*(arg1 + 0x20) + 0x23c) = *(*(arg1 + 0x1c) + 0x23c)
00403537        void* eax_2 = *(arg1 + 0x20)
00403540        *(eax_2 + 0x6f4) = *(eax_2 + 0x238)
00403546        result = *(arg1 + 0x1c)
00403552        *(*(arg1 + 0x20) + 0x6f8) = *(result + 0x6f8)
004034fe        if ((edx & 8) != 0)
00403500        edx_1 = *(arg1 + 0x20)
00403515        long double x87_r6_1 = fconvert.t(*(edx_1 + 0x218))
0040351d        x87_r7_4 = fconvert.t(*(result + 0x238)) - fconvert.t(*(edx_1 + 0x248)) - fconvert.t(*(result + 0x218)) - (x87_r6_1 + x87_r6_1)
0040351d        goto label_40351f
00403558        return result
