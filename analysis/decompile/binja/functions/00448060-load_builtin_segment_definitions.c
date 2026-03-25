/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_builtin_segment_definitions @ 0x448060 */

00448061        int32_t* ebx = arg2
00448065        *arg1 = 0
0044806b        arg1[0x69631] = 0x3e8
00448075        char* result = *ebx
0044807d        if (**(result + 0x28) != 0)
00448086        int32_t edx_1 = *arg1
0044808b        char* esi_1 = *(ebx[edx_1] + 0x28)
0044808e        int32_t eax_1 = 0
00448092        if (*esi_1 != 0)
00448094        eax_1 += 1
00448099        do while (esi_1[eax_1] != 0)
0044809d        arg2 = nullptr
004480aa        int32_t i = 0x28
004480b7        arg1[edx_1 * 0x1088 + 2] = eax_1
004480c0        *ebx[*arg1] = eax_1
0044810d        int32_t eax_2
004480c2        eax_2 = *arg1
004480c4        int32_t esi_8 = 0
004480cc        char* edx_5
004480cc        edx_5.b = **(ebx[eax_2] + i)
004480e3        void* ebp_8 = &arg2[eax_2 * 0x1088] + esi_8
004480e5        esi_8 += 1
004480e6        *(arg1 + ebp_8 + 0x18) = edx_5.b
004480ea        eax_2 = *arg1
004480f2        edx_5.b = (*(ebx[eax_2] + i))[esi_8]
004480f7        do while (edx_5.b != 0)
004480fd        i += 4
00448109        arg2 = &arg2[0x40]
0044810d        do while (i s< 0x48)
00448124        arg1[eax_2 * 0x1088 + 5] = *(ebx[eax_2] + 0x20)
00448128        int32_t eax_5 = *arg1
0044813f        arg1[eax_5 * 0x1088 + 4] = *(ebx[eax_5] + 0x1c)
00448145        int32_t esi_22 = *arg1 + 1
00448148        *arg1 = esi_22
0044814d        result = *(ebx[esi_22] + 0x28)
00448153        do while (*result != 0)
0044815d        return result
