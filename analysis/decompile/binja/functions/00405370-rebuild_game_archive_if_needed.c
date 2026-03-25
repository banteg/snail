/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: rebuild_game_archive_if_needed @ 0x405370 */

0040537b        char result = file_exists("SnailMail.dat")
00405385        if (result == 0)
00405390        result = file_exists("SnailMail.dam")
0040539a        if (result != 0)
004053ae        char* ebx_1 = sub_48b72d(0x2625a00)
004053be        int32_t var_20c
004053be        char* eax_1 = load_file_bytes_allocating("SnailMail.dam", &var_20c)
004053cf        toggle_archive_high_bit_in_place(eax_1, var_20c)
004053d4        int32_t ecx_2 = *(eax_1 + 8)
004053e1        int32_t esi_2
004053e1        int32_t edi_2
004053e1        edi_2, esi_2 = __builtin_memcpy(ebx_1, eax_1, ecx_2 u>> 2 << 2)
004053ed        __builtin_memcpy(edi_2, esi_2, ecx_2 & 3)
004053f3        void* ebp_1 = *(ebx_1 + 8)
004053f9        int32_t var_230 = 0
004053ff        char* ebp_2 = ebp_1 + ebx_1
00405403        int32_t i_1 = 0
00405407        if (*eax_1 s> 0)
0040540d        int32_t* var_22c_1 = &ebx_1[8]
00405418        int32_t* ebx_2 = &eax_1[0xc]
0040541b        int32_t* ecx_9 = &ebx_1[4] - &eax_1[4]
004055f9        int32_t i
0040542c        char* edi_5 = &ebx_1[ebx_2[-2]]
0040543d        void var_200
0040543d        if (classify_archive_entry_extension(edi_5, &var_200) == 1)
0040549b        save_file_bytes_with_optional_archive_scramble("0.png", &eax_1[ebx_2[-1]], *ebx_2, 0)
004054c0        uint32_t var_234
004054c0        int16_t var_224
004054c0        int32_t var_21c
004054c0        void var_204
004054c0        sub_42f0a0(ebx_1, edi_5, "0.png", &var_230, &var_224, &var_21c, &var_234, &var_204, nullptr)
004054d0        *var_22c_1 = ebp_2 - ebx_1
004054d2        ebp_2[7] = 0
004054d6        ebp_2[6] = 0
004054da        ebp_2[5] = 0
004054de        ebp_2[4] = 0
004054e2        ebp_2[3] = 0
004054e6        ebp_2[1] = 0
004054ea        *ebp_2 = 0
004054ee        int16_t eax_8 = var_21c.w
004054f3        ebp_2[0x11] = 8
004054f7        *(ebp_2 + 0xe) = eax_8
004054fb        ebp_2[2] = 2
004054ff        void* ecx_20
004054ff        ecx_20.b = var_234.b
00405505        ecx_20.b <<= 3
00405508        ebp_2[0x10] = ecx_20.b
0040550b        int32_t* edx_8
0040550b        edx_8.w = var_224
00405510        *(ebp_2 + 0xc) = edx_8.w
00405514        *(ebp_2 + 8) = 0
00405518        *(ebp_2 + 0xa) = 0
0040551c        int32_t edx_9 = var_224.d
00405520        uint32_t esi_8 = var_234
00405524        int32_t var_218_1 = 0
0040552a        int32_t eax_9 = var_21c
0040552e        if (edx_9 s> 0)
004055a5        bool cond:3_1
00405530        int32_t edi_9 = 0
00405534        if (eax_9 s> 0)
00405541        char* ecx_24 = (edi_9 * edx_9 + var_218_1) * esi_8
00405552        int32_t eax_14 = ((eax_9 - edi_9 - 1) * edx_9 + var_218_1) * esi_8
00405555        int32_t edx_11
00405555        edx_11.b = ecx_24[var_230]
00405558        ebp_2[eax_14 + 0x14] = edx_11.b
00405560        int32_t edx_12
00405560        edx_12.b = ecx_24[var_230 + 1]
00405564        ebp_2[eax_14 + 0x13] = edx_12.b
0040556c        int32_t edx_13
0040556c        edx_13.b = ecx_24[var_230 + 2]
00405570        ebp_2[eax_14 + 0x12] = edx_13.b
00405574        esi_8 = var_234
0040557b        if (esi_8 == 4)
00405581        ecx_24.b = ecx_24[var_230 + 3]
00405585        ebp_2[eax_14 + 0x15] = ecx_24.b
00405589        esi_8 = var_234
0040558d        eax_9 = var_21c
00405591        edx_9 = var_224.d
00405595        edi_9 += 1
00405598        do while (edi_9 s< eax_9)
0040559f        cond:3_1 = var_218_1 + 1 s< edx_9
004055a1        var_218_1 += 1
004055a5        do while (cond:3_1)
004055b8        void* ebp_4 = &ebp_2[edx_9 * eax_9 * esi_8 + 0x14]
004055bc        *(ecx_9 + ebx_2) = edx_9 * eax_9 * esi_8 + 0x14
004055bf        void* ecx_28 = ebp_4 & 0x80000003
004055c5        if (ecx_28 s< 0)
004055cb        ecx_28 = ((ecx_28 - 1) | 0xfffffffc) + 1
004055cc        char* var_248_2 = edi_5
004055d2        ebp_2 = ebp_4 + ecx_28
004055d4        sub_48b614("extracting %s\n")
0040543f        int32_t ecx_10 = *ebx_2
00405451        int32_t esi_7
00405451        int32_t edi_8
00405451        edi_8, esi_7 = __builtin_memcpy(ebp_2, &eax_1[ebx_2[-1]], ecx_10 u>> 2 << 2)
0040545c        __builtin_memcpy(edi_8, esi_7, ecx_10 & 3)
00405466        *var_22c_1 = ebp_2 - ebx_1
00405468        int32_t eax_6 = *ebx_2
0040546e        void* ebp_3 = &ebp_2[eax_6]
00405472        void* edx_5 = ebp_3 & 0x80000003
00405478        *(ecx_9 + ebx_2) = eax_6
0040547b        if (edx_5 s< 0)
00405481        edx_5 = ((edx_5 - 1) | 0xfffffffc) + 1
00405482        ebp_2 = ebp_3 + edx_5
004055e7        i = i_1 + 1
004055e8        var_22c_1 = &var_22c_1[3]
004055f0        ebx_2 = &ebx_2[3]
004055f3        i_1 = i
004055f9        do while (i s< *eax_1)
0040560e        save_file_bytes_with_optional_archive_scramble("SnailMail.dat", ebx_1, ebp_2 - ebx_1, 1)
00405618        delete_file_path("SnailMail.dam")
00405622        delete_file_path("0.png")
00405628        return sub_48b8d5(ebx_1)
0040563a        return result
