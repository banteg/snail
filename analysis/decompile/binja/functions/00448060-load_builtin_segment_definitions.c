/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_builtin_segment_definitions @ 0x448060 */

00448065        tracks->segment_count = 0
0044806b        tracks->random_length = 0x3e8
0044807d        if (*(*raw_segments)->glyph_rows[0] == 0)
0044807d        return
00448153        int32_t esi_22
00448086        int32_t segment_count_2 = tracks->segment_count
0044808b        char* esi_1 = raw_segments[segment_count_2]->glyph_rows[0]
0044808e        int32_t eax_2 = 0
00448092        if (*esi_1 != 0)
00448094        eax_2 += 1
00448099        do while (esi_1[eax_2] != 0)
0044809d        int32_t grid_offset = 0
004480aa        int32_t i = 0x28
004480b7        tracks->segment_slots[segment_count_2].row_count = eax_2
004480c0        raw_segments[tracks->segment_count]->row_count = eax_2
0044810d        int32_t segment_count
004480c2        segment_count = tracks->segment_count
004480c4        int32_t esi_8 = 0
004480cc        char j = **(raw_segments[segment_count] + i)
004480e3        int32_t ebp_8 = segment_count * 0x4220 + grid_offset + esi_8
004480e5        esi_8 += 1
004480e6        tracks->segment_slots[0].glyph_rows[0][ebp_8] = j
004480ea        segment_count = tracks->segment_count
004480f2        j = (*(raw_segments[segment_count] + i))[esi_8]
004480f7        do while (j != 0)
004480fd        i += 4
00448109        grid_offset += 0x100
0044810d        do while (i s< 0x48)
00448124        tracks->segment_slots[segment_count].source_name = raw_segments[segment_count]->source_name
00448128        int32_t segment_count_1 = tracks->segment_count
0044813f        tracks->segment_slots[segment_count_1].path_index = raw_segments[segment_count_1]->path_index
00448145        esi_22 = tracks->segment_count + 1
00448148        tracks->segment_count = esi_22
00448153        do while (*raw_segments[esi_22]->glyph_rows[0] != 0)
0044815d        return
