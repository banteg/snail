/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: deserialize_compact_high_score_record @ 0x440020 */

00440028        int32_t eax = *(arg2 + 4)
0044003b        if (*(arg2 + 0x28) != ((eax * eax) ^ 0xdeadbabe))
0044003d        *arg1 = 0
00440044        int32_t eax_1
00440044        eax_1.b = 0
00440047        return eax_1
0044004e        arg1[0x1b] = *(arg2 + 0x74)
00440054        arg1[0xa] = *(arg2 + 0x2c)
0044005a        arg1[0xb] = *(arg2 + 0x30)
00440060        arg1[0x12] = *(arg2 + 0x48)
0044006f        arg1[0xd] = *(arg2 + 0x54)
00440072        sub_44e5b0(&arg1[0x15], arg2 + 0x5c)
00440085        arg1[1] = *(arg2 + 4)
0044008b        __builtin_memcpy(&arg1[2], arg2 + 8, 0x18)
00440090        arg1[8] = *(arg2 + 0x20)
00440096        arg1[0x13] = *(arg2 + 0x4c)
0044009c        arg1[0x14] = *(arg2 + 0x50)
004400a2        arg1[0x7eac] = *(arg2 + 0x78)
004400ab        arg1[0x7ead] = *(arg2 + 0x7c)
004400b4        arg1[9] = *(arg2 + 0x24)
004400ba        arg1[0x1a] = *(arg2 + 0x70)
004400c3        arg1[0x7eae] = *(arg2 + 0x80)
004400cf        arg1[0x7eaf] = *(arg2 + 0x84)
004400d8        arg1[0xe] = *(arg2 + 0x38)
004400de        arg1[0xf] = *(arg2 + 0x3c)
004400e4        int32_t edx_7 = arg1[0x1b]
004400e7        arg1[0x10] = *(arg2 + 0x40)
004400ed        int32_t i = 0
004400ef        arg1[0x11] = *(arg2 + 0x44)
004400f2        int16_t* ecx_10 = arg2 + 0x88
004400fa        int32_t esi_1
004400fa        if (edx_7 s> 0)
004400fc        int16_t* edx_8 = &arg1[0x1c]
004400ff        esi_1.w = *ecx_10
00440102        i += 1
00440103        *edx_8 = esi_1.w
00440109        ecx_10 = &ecx_10[1]
0044010c        edx_8 = &edx_8[3]
00440111        do while (i s< arg1[0x1b])
00440113        int32_t ecx_11 = arg1[0x1b]
00440116        int32_t i_1 = 0
0044011a        int16_t* edx_9 = arg2 + (ecx_11 << 1) + 0x88
00440121        if (ecx_11 s> 0)
00440123        int16_t* ecx_12 = arg1 + 0x72
00440126        esi_1.w = *edx_9
00440129        i_1 += 1
0044012a        *ecx_12 = esi_1.w
00440130        ecx_12 = &ecx_12[3]
00440133        edx_9 = &edx_9[1]
00440138        do while (i_1 s< arg1[0x1b])
0044013a        int32_t ecx_13 = arg1[0x1b]
0044013d        char* i_2 = nullptr
0044014a        if (ecx_13 s> 0)
0044014c        int16_t* ecx_14 = &arg1[0x1d]
0044014f        edx_9.w = zx.w(*(i_2 + arg2 + (ecx_13 << 2) + 0x88))
00440154        *ecx_14 = edx_9.w
0044015a        i_2 = &i_2[1]
0044015b        ecx_14 = &ecx_14[3]
00440160        do while (i_2 s< arg1[0x1b])
00440162        *arg1 = 1
00440169        i_2.b = 1
0044016c        return i_2
