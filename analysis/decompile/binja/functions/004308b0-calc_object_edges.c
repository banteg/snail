/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: calc_object_edges @ 0x4308b0 */

004308b0        char* var_4 = arg1
004308b8        if ((arg1[0x10] & 1) == 0)
004308b8        return 
004308c0        char* esi_1 = *(arg1 + 0x5c)
004308c9        void* edi_1 = get_archive_data_base()
004308cb        int32_t ecx = 0
004308cd        data_503300 = edi_1
004308d3        data_503318 = 0
004308dc        var_4 = nullptr
004308e2        if (*(arg1 + 0x54) s> 0)
004308e8        int32_t edi_2 = 0
004308ee        float* eax_3
004308ee        eax_3.w = *(esi_1 + 4)
004308f2        int32_t ecx_1
004308f2        ecx_1.w = *(esi_1 + 2)
004308fb        add_object_edge(arg1, ecx_1, eax_3, edi_2)
00430904        float* edx_1
00430904        edx_1.w = *(esi_1 + 2)
00430908        int32_t eax_4
00430908        eax_4.w = *(esi_1 + 6)
00430911        add_object_edge(arg1, eax_4, edx_1, edi_2)
0043091a        float* ecx_4
0043091a        ecx_4.w = *(esi_1 + 6)
0043091e        int32_t edx_2
0043091e        edx_2.w = *(esi_1 + 4)
00430927        add_object_edge(arg1, edx_2, ecx_4, edi_2)
0043092f        if ((*esi_1 & 0x80) == 0)
00430936        float* eax_5
00430936        eax_5.w = *(esi_1 + 6)
0043093c        int32_t ecx_6
0043093c        ecx_6.w = *(esi_1 + 2)
00430945        add_object_edge(arg1, ecx_6, eax_5, edi_2 + 1)
0043094e        float* edx_3
0043094e        edx_3.w = *(esi_1 + 2)
00430952        int32_t eax_6
00430952        eax_6.w = *(esi_1 + 8)
0043095b        add_object_edge(arg1, eax_6, edx_3, edi_2 + 1)
00430964        float* ecx_9
00430964        ecx_9.w = *(esi_1 + 8)
00430968        int32_t edx_4
00430968        edx_4.w = *(esi_1 + 6)
00430971        add_object_edge(arg1, edx_4, ecx_9, edi_2 + 1)
0043097d        esi_1 = &esi_1[0x30]
00430981        edi_2 += 2
00430986        var_4 = &var_4[1]
0043098a        do while (&var_4[1] s< *(arg1 + 0x54))
00430990        edi_1 = data_503300
00430996        ecx = data_503318
004309a2        if (((*(arg1 + 0x10)).w:1.b & 0x80) != 0)
004309a4        int32_t i_1 = 0
004309a8        if (ecx s> 0)
004309aa        char* edx_5 = nullptr
004309ac        var_4 = nullptr
004309b4        if ((*(edx_5 + edi_1) & 1) != 0)
004309b9        int32_t i = i_1
004309bd        if (i_1 s< ecx - 1)
004309ca        i += 1
004309cb        __builtin_memcpy(edi_1 + edx_5, edx_5 + edi_1 + 0x24, 0x24)
004309cd        ecx = data_503318
004309d3        edi_1 = data_503300
004309d9        edx_5 = &edx_5[0x24]
004309e1        do while (i s< ecx - 1)
004309e3        edx_5 = var_4
004309e7        ecx -= 1
004309e8        i_1 -= 1
004309e9        data_503318 = ecx
004309ef        edx_5 -= 0x24
004309f2        i_1 += 1
004309f3        edx_5 = &edx_5[0x24]
004309f8        var_4 = edx_5
004309fc        do while (i_1 s< ecx)
00430a01        request_object_edges(arg1, ecx)
00430a17        int32_t ecx_14 = data_503318 * 0x24
00430a1f        int32_t esi_6
00430a1f        int32_t edi_5
00430a1f        edi_5, esi_6 = __builtin_memcpy(*(arg1 + 0x74), data_503300, ecx_14 & 0xfffffffc)
00430a26        __builtin_memcpy(edi_5, esi_6, ecx_14 & 3)
00430a2d        return
