/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: kill_golb @ 0x414670 */

00414678        void* ecx = data_4df904 + 0x5a8
0041467e        int16_t eax = (*(arg1 + 4)).w
00414684        if ((eax:1.b & 2) == 0)
0041468b        report_errorf("List remove")
00414697        if ((eax.b & 0x40) == 0)
004146a8        void* eax_1 = *(arg1 + 0xc)
004146ad        if (eax_1 != 0)
004146b2        *(eax_1 + 8) = *(arg1 + 8)
004146b5        void* eax_2 = *(arg1 + 8)
004146ba        if (eax_2 == 0)
004146c7        *(ecx + 4) = *(arg1 + 0xc)
004146bf        *(eax_2 + 0xc) = *(arg1 + 0xc)
004146cd        *(arg1 + 0xc) = *(ecx + 8)
004146d0        *(ecx + 8) = arg1
004146d6        int32_t eax_4
004146d6        eax_4:1.b = (*(arg1 + 4)):1.b & 0xfd
004146d9        *(arg1 + 4) = eax_4
0041469e        report_errorf("List remove NEXTBOD")
004146dc        int32_t eax_5 = *(arg1 + 0x1c0)
004146e2        *(arg1 + 0x244) = 0
004146ef        if (eax_5 == 0)
0041480b        return kill_sprite(*(arg1 + 0x248))
004146f6        if (eax_5 == 1)
00414795        int16_t ecx_8 = (*(arg1 + 0x84)).w
004147a1        void* edx_6 = data_4df904 + 0x5a8
004147aa        if ((ecx_8:1.b & 2) == 0)
004147b1        report_errorf("List remove")
004147ba        return 0
004147be        if ((ecx_8.b & 0x40) != 0)
004147c5        report_errorf("List remove NEXTBOD")
004147ce        return 0
004147cf        void* ecx_9 = *(arg1 + 0x8c)
004147d4        if (ecx_9 != 0)
004147d9        *(ecx_9 + 8) = *(arg1 + 0x88)
004147dc        void* ecx_10 = *(arg1 + 0x88)
004147e1        if (ecx_10 == 0)
004147ee        *(edx_6 + 4) = *(arg1 + 0x8c)
004147e6        *(ecx_10 + 0xc) = *(arg1 + 0x8c)
004147f5        *(arg1 + 0x8c) = *(edx_6 + 8)
004147f8        *(edx_6 + 8) = arg1 + 0x80
004147fe        int32_t ecx_13
004147fe        ecx_13:1.b = (*(arg1 + 0x84)):1.b & 0xfd
00414801        *(arg1 + 0x84) = ecx_13
00414804        return arg1 + 0x80
004146fc        void* eax_8 = eax_5 - 2
004146fd        if (eax_5 == 2)
00414709        eax_8 = arg1 + 0x118
0041470f        void* edx_4 = data_4df904 + 0x5a8
00414715        int16_t ecx_2 = (*(eax_8 + 4)).w
0041471b        if ((ecx_2:1.b & 2) == 0)
00414722        eax_8 = report_errorf("List remove")
0041472f        if ((ecx_2.b & 0x40) == 0)
00414740        void* ecx_3 = *(eax_8 + 0xc)
00414746        if (ecx_3 != 0)
0041474b        *(ecx_3 + 8) = *(eax_8 + 8)
0041474e        void* ecx_4 = *(eax_8 + 8)
00414753        if (ecx_4 == 0)
00414760        *(edx_4 + 4) = *(eax_8 + 0xc)
00414758        *(ecx_4 + 0xc) = *(eax_8 + 0xc)
00414767        *(eax_8 + 0xc) = *(edx_4 + 8)
0041476a        *(edx_4 + 8) = eax_8
00414770        int32_t ecx_7
00414770        ecx_7:1.b = (*(eax_8 + 4)):1.b & 0xfd
00414773        *(eax_8 + 4) = ecx_7
00414736        eax_8 = report_errorf("List remove NEXTBOD")
00414776        void* esi_1 = *(arg1 + 0x198)
0041477e        if (esi_1 != 0)
00414787        int32_t eax_9
00414787        eax_9:1.b = (*(esi_1 + 4)):1.b & 0xef
0041478a        *(esi_1 + 4) = eax_9
0041478e        return eax_9
00414811        return eax_8
