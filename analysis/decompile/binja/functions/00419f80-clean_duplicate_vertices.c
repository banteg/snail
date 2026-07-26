/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: clean_duplicate_vertices @ 0x419f80 */

00419f80        int32_t active_count = duplicate_vertices->active_count
00419f83        int32_t i_1 = 0
00419f87        if (active_count s<= 0)
00419f87        return
00419f89        int32_t ebp
00419f89        int32_t var_8_1 = ebp
00419f8c        int16_t* edi_1 = nullptr
00419f90        int32_t i = i_1
00419f92        if (i_1 s< active_count)
00419f94        int16_t* edx_1 = edi_1
00419f96        struct DuplicateVertexRecord* records = duplicate_vertices->records
00419fa2        if (*(edx_1 + records) == *(&records->compare_vertex + edi_1))
00419fa4        *(&records->live_flag + edx_1) = 0
00419fad        i += 1
00419fae        edx_1 = &edx_1[5]
00419fb3        do while (i s< duplicate_vertices->active_count)
00419fb5        active_count = duplicate_vertices->active_count
00419fb7        i_1 += 1
00419fb8        edi_1 = &edi_1[5]
00419fbd        do while (i_1 s< active_count)
00419fc3        return
