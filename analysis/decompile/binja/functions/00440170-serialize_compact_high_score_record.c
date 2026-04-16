/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: serialize_compact_high_score_record @ 0x440170 */

00440178        int32_t eax = arg1[0x1b]
0044017b        *arg1 = 1
00440181        arg2[0x1d] = eax
00440187        arg2[0xb] = arg1[0xa]
0044018d        arg2[0xc] = arg1[0xb]
00440194        arg2[0x12] = arg1[0x12]
004401a3        arg2[0x15] = arg1[0xd]
004401a6        sub_44e5b0(&arg2[0x17], &arg1[0x15])
004401b9        __builtin_memcpy(&arg2[2], &arg1[2], 0x18)
004401be        arg2[8] = arg1[8]
004401c4        arg2[0x13] = arg1[0x13]
004401ca        arg2[0x14] = arg1[0x14]
004401d3        arg2[0x1e] = arg1[0x7eac]
004401dc        arg2[0x1f] = arg1[0x7ead]
004401e2        arg2[9] = arg1[9]
004401e8        arg2[1] = arg1[1]
004401eb        int32_t eax_5 = arg1[1]
004401f9        arg2[0xa] = (eax_5 * eax_5) ^ 0xdeadbabe
004401ff        arg2[0x1c] = arg1[0x1a]
00440208        arg2[0x20] = arg1[0x7eae]
00440214        arg2[0x21] = arg1[0x7eaf]
0044021d        arg2[0xe] = arg1[0xe]
00440223        arg2[0xf] = arg1[0xf]
00440229        arg2[0x10] = arg1[0x10]
0044022f        arg2[0x11] = arg1[0x11]
00440235        int32_t i = 0
00440237        int16_t* edx_9 = &arg2[0x22]
0044023f        int32_t esi_1
0044023f        if (arg1[0x1b] s> 0)
00440241        int16_t* ecx_8 = &arg1[0x1c]
00440244        esi_1.w = *ecx_8
00440247        i += 1
00440248        *edx_9 = esi_1.w
0044024e        ecx_8 = &ecx_8[3]
00440251        edx_9 = &edx_9[1]
00440256        do while (i s< arg1[0x1b])
00440258        int32_t ecx_9 = arg1[0x1b]
0044025b        int32_t i_1 = 0
0044025f        int16_t* edx_10 = arg2 + (ecx_9 << 1) + 0x88
00440266        if (ecx_9 s> 0)
00440268        int16_t* ecx_10 = arg1 + 0x72
0044026b        esi_1.w = *ecx_10
0044026e        i_1 += 1
0044026f        *edx_10 = esi_1.w
00440275        ecx_10 = &ecx_10[3]
00440278        edx_10 = &edx_10[1]
0044027d        do while (i_1 s< arg1[0x1b])
0044027f        int32_t ecx_11 = arg1[0x1b]
00440282        int32_t i_2 = 0
00440286        char* edi_1 = &arg2[ecx_11 + 0x22]
0044028d        if (ecx_11 s> 0)
0044028f        char* esi_2 = &arg1[0x1d]
00440292        ecx_11.b = *esi_2
00440294        esi_2 = &esi_2[6]
00440297        edi_1[i_2] = ecx_11.b
0044029d        i_2 += 1
004402a0        do while (i_2 s< arg1[0x1b])
004402a2        int32_t ebx_1 = arg1[0x1b]
004402ae        *arg2 = ebx_1 * 5 + 0x88
004402b3        return ebx_1 * 5 + 0x88
