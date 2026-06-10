/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: copy_segment_definition_to_level_slot @ 0x447300 */

0044730d        int32_t* edi = data_4df904 + 0x1075ae4
00447313        int32_t i = 0
00447318        if (*edi s> 0)
0044731a        char* ebp_1 = &edi[0x11]
0044732a        if (sub_44e6c0(arg1, ebp_1) == 1)
0044732a        break
0044732e        i += 1
0044732f        ebp_1 = &ebp_1[0x4088]
00447337        do while (i s< *edi)
0044733b        if (i == *edi)
0044734a        report_errorf("Cannot find segment %s for %s", arg1, data_74ec74)
00447356        return 0
0044735b        void* ebp_2 = arg2
00447364        arg1 = 8
00447371        void* edx_5 = &edi[i * 0x1022]
00447374        char* edi_1 = ebp_2 + 0x14
00447377        char* ecx_1 = edx_5 + 0x8c
004473ae        bool cond:0_1
00447383        int32_t i_1 = 0
00447387        if (*(edx_5 + 0x88) s> 0)
00447389        char* esi_1 = ecx_1
0044738b        char* ebx
0044738b        ebx.b = *esi_1
0044738d        esi_1 = &esi_1[8]
00447390        edi_1[i_1] = ebx.b
00447399        i_1 += 1
0044739c        do while (i_1 s< *(edx_5 + 0x88))
004473a2        ecx_1 = &ecx_1[1]
004473a3        edi_1 = &edi_1[0x100]
004473a9        cond:0_1 = arg1 != 1
004473aa        arg1 -= 1
004473ae        do while (cond:0_1)
004473b9        int32_t i_2 = 0
004473bb        *(ebp_2 + 4) = *(edx_5 + 0x88)
004473be        *(ebp_2 + 0x10) = edx_5 + 0x44
004473c1        *(ebp_2 + 0x4014) = 0
004473cd        *(ebp_2 + 0xc) = *(edx_5 + 0x84)
004473d0        int32_t* result = *(edx_5 + 0x88)
004473d8        if (result s> 0)
004473da        int32_t* ecx_3 = ebp_2 + 0x828
004473e0        result = edx_5 + 0x8a0
004473ec        ecx_3[-5] = result[-5]
004473f1        *ecx_3 = *result
004473f6        i_2 += 1
004473f9        ecx_3[1] = result[1]
004473fe        ecx_3[2] = result[2]
00447404        ecx_3[3] = result[3]
0044740f        ecx_3[4] = result[4]
00447414        ecx_3[5] = result[5]
0044741a        ecx_3[6] = result[6]
00447420        ecx_3[-4] = result[-4]
00447423        int32_t* edi_9 = &result[-3]
00447426        int32_t* ebx_3 = &ecx_3[-3]
00447429        result = &result[0xe]
0044742e        ecx_3 = &ecx_3[0xe]
00447431        *ebx_3 = *edi_9
00447436        ebx_3[1] = edi_9[1]
0044743c        ebx_3[2] = edi_9[2]
00447442        ecx_3[-7] = result[-7]
00447448        ecx_3[-6] = result[-6]
00447453        do while (i_2 s< *(edx_5 + 0x88))
00447455        ebp_2 = arg2
0044745a        *(ebp_2 + 0x4018) = 0
00447461        *(ebp_2 + 0x4218) = 0
0044746b        *(ebp_2 + 0x421c) = 0xffffffff
00447478        return result
