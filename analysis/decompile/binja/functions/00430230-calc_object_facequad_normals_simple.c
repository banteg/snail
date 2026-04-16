/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: calc_object_facequad_normals_simple @ 0x430230 */

00430237        request_object_facequad_normals(arg1)
0043023c        int32_t i = *(arg1 + 0x54)
0043023f        int32_t ebp = 0
00430243        int32_t i_1 = 0
00430247        if (i s> 0)
0043024f        char* ebx_1 = nullptr
00430254        int32_t ecx = *(arg1 + 0x38)
00430257        void* eax_1 = *(arg1 + 0x5c) + ebx_1
0043025b        int32_t edx_1
0043025b        edx_1.w = *(eax_1 + 2)
00430262        float* edi_1 = ecx + edx_1 * 0xc
00430267        int32_t edx_3
00430267        edx_3.w = *(eax_1 + 4)
0043026b        int32_t edx_4 = edx_3 * 3
00430273        void* edx_5 = ecx + (edx_4 << 2)
0043028e        struct Vec3 lhs
0043028e        lhs.x = fconvert.s(fconvert.t(*(ecx + (edx_4 << 2))) - fconvert.t(*edi_1))
00430296        lhs.y = fconvert.s(fconvert.t(*(edx_5 + 4)) - fconvert.t(edi_1[1]))
004302a2        lhs.z = fconvert.s(fconvert.t(*(edx_5 + 8)) - fconvert.t(edi_1[2]))
004302a8        int32_t edx_9
004302a8        edx_9.w = *(eax_1 + 2)
004302af        float* edi_2 = ecx + edx_9 * 0xc
004302b4        int32_t edx_11
004302b4        edx_11.w = *(eax_1 + 6)
004302b8        int32_t eax_2 = edx_11 * 3
004302c0        void* eax_3 = ecx + (eax_2 << 2)
004302df        struct Vec3 rhs
004302df        rhs.x = fconvert.s(fconvert.t(*(ecx + (eax_2 << 2))) - fconvert.t(*edi_2))
004302e3        rhs.y = fconvert.s(fconvert.t(*(eax_3 + 4)) - fconvert.t(edi_2[1]))
004302fd        rhs.z = fconvert.s(fconvert.t(*(eax_3 + 8)) - fconvert.t(edi_2[2]))
00430301        struct Vec3 var_24
00430301        cross_vectors(&var_24, &lhs, &rhs)
0043030a        normalize_vector(&var_24)
00430316        float* eax_6 = *(arg1 + 0x60) + ebp
0043031a        *eax_6 = var_24.x
00430320        eax_6[1] = var_24.y
00430327        eax_6[2] = var_24.z
0043032a        int32_t edx_14 = *(arg1 + 0x5c)
0043032d        float ecx_5
0043032d        ecx_5.b = ebx_1[edx_14]
00430330        void* eax_7 = &ebx_1[edx_14]
00430336        if ((ecx_5.b & 0x80) == 0)
0043033c        int32_t edi_3 = *(arg1 + 0x38)
00430341        int32_t ecx_6
00430341        ecx_6.w = *(eax_7 + 2)
00430348        float* edx_15 = edi_3 + ecx_6 * 0xc
0043034d        int32_t ecx_8
0043034d        ecx_8.w = *(eax_7 + 8)
00430351        int32_t eax_8 = ecx_8 * 3
00430359        void* eax_9 = edi_3 + (eax_8 << 2)
00430378        rhs.x = fconvert.s(fconvert.t(*(edi_3 + (eax_8 << 2))) - fconvert.t(*edx_15))
0043037c        rhs.y = fconvert.s(fconvert.t(*(eax_9 + 4)) - fconvert.t(edx_15[1]))
00430396        rhs.z = fconvert.s(fconvert.t(*(eax_9 + 8)) - fconvert.t(edx_15[2]))
0043039a        struct Vec3 var_c
0043039a        cross_vectors(&var_c, &lhs, &rhs)
004303a3        normalize_vector(&var_c)
004303a8        int32_t eax_11 = *(arg1 + 0x60)
004303b5        *(eax_11 + ebp + 0xc) = var_c.x
004303bd        *(eax_11 + ebp + 0x10) = var_c.y
004303c4        *(eax_11 + ebp + 0x14) = var_c.z
004303ce        i = i_1 + 1
004303cf        ebx_1 = &ebx_1[0x30]
004303d2        ebp += 0x18
004303d7        i_1 = i
004303db        do while (i s< *(arg1 + 0x54))
004303e8        return i
