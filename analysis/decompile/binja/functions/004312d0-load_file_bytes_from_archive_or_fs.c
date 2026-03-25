/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_file_bytes_from_archive_or_fs @ 0x4312d0 */

004312df        update_loading_screen(0x503290)
004312e4        int32_t* ebx = data_53c7f8
004312f3        if (ebx != 0)
004312f5        int32_t eax_1 = *ebx
004312f7        int32_t edi_1 = 0
004312fb        int32_t var_204_1 = eax_1
004312ff        if (eax_1 s> 0)
00431301        int32_t* ebx_1 = &ebx[1]
00431304        char* edx_1 = *ebx_1
00431306        char* esi_1 = arg1
00431308        char i = *edx_1
0043130c        if (i != 0)
0043130e        eax_1.b = *esi_1
00431312        if (eax_1.b == 0)
00431312        break
0043131a        if (eax_1.b s>= 0x61 && eax_1.b s<= 0x7a)
0043131c        eax_1.b -= 0x20
00431320        if (i != eax_1.b)
00431320        break
00431322        i = edx_1[1]
00431325        esi_1 = &esi_1[1]
00431326        edx_1 = &edx_1[1]
00431329        do while (i != 0)
0043132b        eax_1 = var_204_1
00431337        if (*edx_1 == 0 && *esi_1 == 0)
00431391        if (arg3 != 0)
004313a0        *arg3 = *(data_53c7f8 + ((edi_1 * 3 + 3) << 2))
004313ac        if (arg2 == 0xffffffff)
004313c4        return *(data_53c7f8 + edi_1 * 0xc + 8)
004313c7        if (arg2 != 0)
00431454        void* eax_15 = sub_48b4bc(data_53c7f0)
00431462        int32_t esi_6 = edi_1 * 0xc
00431474        sub_48b430(data_53c7f0, *(esi_6 + data_53c7f8 + 8) - eax_15, FILE_CURRENT)
0043148a        uint32_t* edi_5 = (edi_1 * 3 + 3) << 2
00431494        sub_48b645(arg2, 1, *(edi_5 + data_53c7f8), data_53c7f0)
00431499        int32_t eax_18 = data_53c7f8
004314a8        xor_archive_bytes_in_place(*(esi_6 + eax_18 + 8), arg2, *(edi_5 + eax_18))
004314bc        return arg2
004313d7        uint32_t* esi_4 = (edi_1 * 3 + 3) << 2
004313df        char* eax_7 = allocate_tracked_memory(*(esi_4 + data_53c7f8), arg1)
004313ec        void* eax_9 = sub_48b4bc(data_53c7f0)
004313fa        int32_t edi_3 = edi_1 * 0xc
0043140c        sub_48b430(data_53c7f0, *(edi_3 + data_53c7f8 + 8) - eax_9, FILE_CURRENT)
00431425        sub_48b645(eax_7, 1, *(esi_4 + data_53c7f8), data_53c7f0)
0043142a        int32_t eax_12 = data_53c7f8
00431439        xor_archive_bytes_in_place(*(edi_3 + eax_12 + 8), eax_7, *(esi_4 + eax_12))
0043144d        return eax_7
00431339        edi_1 += 1
0043133a        ebx_1 = &ebx_1[3]
0043133f        do while (edi_1 s< eax_1)
00431347        int32_t* eax_2 = sub_48b41d(arg1, "rb")
00431353        if (eax_2 == 0)
00431363        char var_200[0x200]
00431363        sub_496946(&var_200, 0x200)
0043136c        char (* var_220)[0x200] = &var_200
0043136d        char* var_224 = arg1
00431373        report_messagef("WARNING:Cannot find file : %s (from %s)\n")
00431387        return 0
004314be        void* eax_20 = get_stream_length_preserve_position(eax_2)
004314c3        char* ebx_4 = arg2
004314d6        if (ebx_4 == 0 || ebx_4 == 0xffffffff)
004314e2        ebx_4 = allocate_tracked_memory(eax_20, arg1)
004314e9        sub_48b645(ebx_4, 1, eax_20, eax_2)
004314ef        sub_48b3a7(eax_2)
00431500        if (arg3 != 0)
00431502        *arg3 = eax_20
00431510        return ebx_4
