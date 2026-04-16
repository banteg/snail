/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: recycle_bod_to_free_list @ 0x447290 */

00447294        int16_t edx = (*(arg2 + 4)).w
0044729a        if ((edx:1.b & 2) == 0)
004472a1        report_errorf("List remove")
004472a9        return 0
004472af        if ((edx.b & 0x40) != 0)
004472b6        report_errorf("List remove NEXTBOD")
004472be        return 0
004472c1        void* edx_1 = *(arg2 + 0xc)
004472c7        if (edx_1 != 0)
004472cc        *(edx_1 + 8) = *(arg2 + 8)
004472cf        void* edx_2 = *(arg2 + 8)
004472d4        if (edx_2 == 0)
004472e1        *(arg1 + 4) = *(arg2 + 0xc)
004472d9        *(edx_2 + 0xc) = *(arg2 + 0xc)
004472e8        *(arg2 + 0xc) = *(arg1 + 8)
004472eb        *(arg1 + 8) = arg2
004472f1        int32_t ecx
004472f1        ecx:1.b = (*(arg2 + 4)):1.b & 0xfd
004472f4        *(arg2 + 4) = ecx
004472f7        return arg2
