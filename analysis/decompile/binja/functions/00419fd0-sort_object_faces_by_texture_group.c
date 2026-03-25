/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: sort_object_faces_by_texture_group @ 0x419fd0 */

00419fd5        void* esi = arg1
00419fd9        int32_t ebp = 0
00419fdb        int32_t var_3c = 0
00419fdf        int32_t result = *(esi + 0x54)
00419fe2        int32_t ecx = *(esi + 0x5c)
00419fe7        int32_t var_34 = ecx
00419feb        if (result s> 0)
00419ff7        int32_t i = ebp + 1
00419fff        int32_t edx_3 = *(ebp * 0x30 + ecx + 0xc)
0041a007        if (i s< result)
0041a015        void* edx_6 = i * 0x30 + ecx
0041a017        int32_t i_1 = i
0041a01b        int32_t eax_2 = i * 0x30 + ecx
0041a024        if (*(edx_6 + 0xc) == edx_3)
0041a02c        if (i != i_1)
0041a044        ebp += 1
0041a045        void var_30
0041a045        __builtin_memcpy(&var_30, eax_2, 0x30)
0041a04e        int32_t edi_4 = eax_2
0041a050        eax_2 += 0x30
0041a053        __builtin_memcpy(edi_4, edx_6, 0x30)
0041a060        __builtin_memcpy(edx_6, &var_30, 0x30)
0041a06c        i_1 += 1
0041a070        esi = arg1
0041a074        var_3c += 1
0041a078        ecx = var_34
0041a02e        ebp += 1
0041a02f        eax_2 += 0x30
0041a033        i_1 += 1
0041a07f        i += 1
0041a080        edx_6 += 0x30
0041a085        do while (i s< *(esi + 0x54))
0041a087        result = *(esi + 0x54)
0041a08a        ebp += 1
0041a08d        do while (ebp s< result)
0041a09a        return result
