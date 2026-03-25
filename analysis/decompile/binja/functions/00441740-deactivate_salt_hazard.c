/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: deactivate_salt_hazard @ 0x441740 */

00441748        void* ecx = data_4df904 + 0x5a8
0044174e        int16_t eax = (*(arg1 + 4)).w
00441754        if ((eax:1.b & 2) == 0)
0044175b        report_errorf("List remove")
00441763        *(arg1 + 0x80) = 0
0044176e        return 0
00441771        if ((eax.b & 0x40) != 0)
00441778        report_errorf("List remove NEXTBOD")
00441780        *(arg1 + 0x80) = 0
0044178b        return 0
0044178c        void* eax_1 = *(arg1 + 0xc)
00441791        if (eax_1 != 0)
00441796        *(eax_1 + 8) = *(arg1 + 8)
00441799        void* eax_2 = *(arg1 + 8)
0044179e        if (eax_2 == 0)
004417ab        *(ecx + 4) = *(arg1 + 0xc)
004417a3        *(eax_2 + 0xc) = *(arg1 + 0xc)
004417b1        *(arg1 + 0xc) = *(ecx + 8)
004417b4        *(ecx + 8) = arg1
004417b7        int32_t result = *(arg1 + 4)
004417ba        *(arg1 + 0x80) = 0
004417c4        result:1.b &= 0xfd
004417c7        *(arg1 + 4) = result
004417cb        return result
