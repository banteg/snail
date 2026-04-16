/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: save_high_scores_and_config @ 0x417940 */

00417940        void* var_4 = arg1
00417956        int32_t* esi = allocate_tracked_memory(0x4c4b40, "High Score Table")
00417958        int32_t* eax
00417958        eax.b = arg2
00417961        if ((eax.b & 1) != 0)
00417963        int32_t* eax_1 = esi
00417965        uint32_t ebp_1 = 0
00417967        int32_t* edi_1 = arg1 + 8
0041796a        var_4 = 0xb
00417993        bool cond:0_1
00417975        if (*edi_1 == 1)
0041797f        ebp_1 += serialize_compact_high_score_record(edi_1, eax_1)
00417981        eax_1 = esi + ebp_1
00417988        edi_1 = &edi_1[0x7eb0]
0041798e        cond:0_1 = var_4 != 1
0041798f        var_4 -= 1
00417993        do while (cond:0_1)
00417997        xor_decode_buffer_with_index(esi, ebp_1)
004179a3        write_file_bytes("ScoreA.dat", esi, ebp_1)
004179b0        if ((arg2 & 2) != 0)
004179b2        int32_t* eax_3 = esi
004179b4        uint32_t ebp_2 = 0
004179b6        int32_t* edi_2 = arg1 + 0x15c648
004179bc        var_4 = 0xb
004179e5        bool cond:1_1
004179c7        if (*edi_2 == 1)
004179d1        ebp_2 += serialize_compact_high_score_record(edi_2, eax_3)
004179d3        eax_3 = esi + ebp_2
004179da        edi_2 = &edi_2[0x7eb0]
004179e0        cond:1_1 = var_4 != 1
004179e1        var_4 -= 1
004179e5        do while (cond:1_1)
004179e9        xor_decode_buffer_with_index(esi, ebp_2)
004179f5        write_file_bytes("ScoreB.dat", esi, ebp_2)
00417a02        if ((arg2 & 8) != 0)
00417a04        int32_t* edi_3 = arg1 + 0x2b8c88
00417a0a        int32_t* eax_5 = esi
00417a0c        uint32_t ebp_3 = 0
00417a0e        int32_t i_1 = 0x33
00417a2c        int32_t i
00417a16        if (*edi_3 == 1)
00417a20        ebp_3 += serialize_compact_high_score_record(edi_3, eax_5)
00417a22        eax_5 = esi + ebp_3
00417a25        edi_3 = &edi_3[0x7eb0]
00417a2b        i = i_1
00417a2b        i_1 -= 1
00417a2c        do while (i != 1)
00417a30        xor_decode_buffer_with_index(esi, ebp_3)
00417a3c        write_file_bytes("ScoreC.dat", esi, ebp_3)
00417a45        free_tracked_memory(esi)
00417a66        return save_config_file("SnailMail.cfg", &data_4df918, 0xc4)
