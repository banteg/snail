/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_file_bytes_fixed_size_from_archive_or_fs @ 0x431030 */

0043103f        update_loading_screen(0x503290)
00431044        int32_t* eax = data_53c7f8
0043104b        int32_t* var_204_1
0043104b        int32_t* ecx_1
0043104b        int32_t ebp_1
0043104b        if (eax != 0)
00431051        ecx_1 = *eax
00431053        ebp_1 = 0
00431057        var_204_1 = ecx_1
0043105b        char* ebx_1
0043105b        if (eax == 0 || ecx_1 s<= 0)
004311ab        ebx_1 = arg1
00431061        int32_t* edi_1 = &eax[1]
00431064        char* edx_1 = *edi_1
00431066        ebx_1 = arg1
0043106d        char* esi_1 = ebx_1
0043106f        ecx_1.b = *edx_1
00431073        while (ecx_1.b != 0)
00431075        eax.b = *esi_1
00431079        if (eax.b == 0)
00431079        break
00431081        if (eax.b s>= 0x61 && eax.b s<= 0x7a)
00431083        eax.b -= 0x20
00431087        if (ecx_1.b != eax.b)
00431087        break
00431089        ecx_1.b = edx_1[1]
0043108c        esi_1 = &esi_1[1]
0043108d        edx_1 = &edx_1[1]
0043109a        if (*edx_1 == 0 && *esi_1 == 0)
004310b7        if (arg2 == 0xffffffff)
004310d1        return *(data_53c7f8 + ebp_1 * 0xc + 8)
004310d4        if (arg2 != 0)
0043114c        void* eax_8 = sub_48b4bc(data_53c7f0)
0043115b        int32_t esi_5 = ebp_1 * 0xc
0043116e        sub_48b430(data_53c7f0, *(esi_5 + data_53c7f8 + 8) - eax_8, FILE_CURRENT)
00431184        sub_48b645(arg2, 1, arg3, data_53c7f0)
00431196        xor_archive_bytes_in_place(*(esi_5 + data_53c7f8 + 8), arg2, arg3)
004311aa        return arg2
004310df        char* eax_3 = allocate_tracked_memory(arg3, ebx_1)
004310ed        void* eax_4 = sub_48b4bc(data_53c7f0)
004310fc        int32_t esi_3 = ebp_1 * 0xc
0043110e        sub_48b430(data_53c7f0, *(esi_3 + data_53c7f8 + 8) - eax_4, FILE_CURRENT)
0043111e        sub_48b645(eax_3, 1, arg3, data_53c7f0)
00431130        xor_archive_bytes_in_place(*(esi_3 + data_53c7f8 + 8), eax_3, arg3)
00431144        return eax_3
004310a0        ebp_1 += 1
004310a1        edi_1 = &edi_1[3]
004310a6        do while (ebp_1 s< var_204_1)
004311b8        int32_t* eax_11 = sub_48b41d(ebx_1, "rb")
004311c4        if (eax_11 == 0)
004311d0        char var_200[0x200]
004311d0        sub_496946(&var_200, 0x200)
004311d9        char (* var_220_2)[0x200] = &var_200
004311da        char* var_224_1 = ebx_1
004311e0        report_messagef("WARNING:Cannot find file : %s (from %s)\n")
004311f4        return 0
004311f6        get_stream_length_preserve_position(eax_11)
004311fb        char* edi_4 = arg2
00431213        if (edi_4 == 0 || edi_4 == 0xffffffff)
00431226        edi_4 = allocate_tracked_memory(arg3, arg1)
0043122d        sub_48b645(edi_4, 1, arg3, eax_11)
00431233        sub_48b3a7(eax_11)
00431247        return edi_4
