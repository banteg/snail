/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: calc_object_texture_groups @ 0x4303f0 */

00430468        void* result
004303f6        int32_t i = 0
00430468        while (i s< 2)
004303f8        result = *(arg1 + 0x5c)
004303fe        int32_t ebx_1 = 0
00430400        int32_t j = 0
00430402        int32_t edx_1 = *(result + 0xc)
00430407        if (*(arg1 + 0x54) s> 0)
00430409        char* ecx_1 = nullptr
0043040f        if ((*(arg1 + 0x11) & 4) != 0)
00430411        *(ecx_1 + result) |= 2
00430418        int32_t* eax_2 = *(*(arg1 + 0x5c) + ecx_1 + 0xc)
0043041c        *eax_2 |= 0x20
0043041f        result = *(arg1 + 0x5c)
0043042c        if (*(ecx_1 + result + 0xc) != edx_1 || (*(ecx_1 + result) & 0x10) != 0)
00430431        if (i == 1)
00430436        *(*(arg1 + 0x6c) + (ebx_1 << 2)) = j
00430439        result = *(arg1 + 0x5c)
0043043c        ebx_1 += 1
0043043d        edx_1 = *(ecx_1 + result + 0xc)
00430441        j += 1
00430442        ecx_1 = &ecx_1[0x30]
00430448        do while (j s< *(arg1 + 0x54))
0043044d        if (i == 1)
0043044f        result = *(arg1 + 0x6c)
00430452        *(result + (ebx_1 << 2)) = j
00430459        if (i == 0)
0043045f        result = request_object_texture_groups(arg1, ebx_1 + 1)
00430464        i += 1
0043046e        return result
