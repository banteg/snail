/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: copy_segment_definition_to_level_slot @ 0x447300 */

0044730d        struct SMTracks* edi = &g_game_base->subgame.sm_tracks
00447313        int32_t i = 0
00447318        if (edi->count s> 0)
0044731a        char (* ebp_1)[0x40] = &edi->entries[0].filename
0044732a        if (strings_equal_case_insensitive_path(segment_name, ebp_1) == 1)
0044732a        break
0044732e        i += 1
0044732f        ebp_1 = &(*ebp_1)[0x4088]
00447337        do while (i s< edi->count)
0044733b        if (i == edi->count)
0044734a        report_errorf("Cannot find segment %s for %s", segment_name, g_current_level_definition_name)
00447356        return
0044735b        struct SubSegment* segment_1 = segment
00447364        segment_name = 8
00447371        void* edx_5 = edi + i * 0x4088
00447374        char (* edi_1)[0x8][0x100] = &segment_1->glyph_rows
00447377        char* ecx_1 = edx_5 + 0x8c
004473ae        bool cond:0_1
00447383        int32_t i_1 = 0
00447387        if (*(edx_5 + 0x88) s> 0)
00447389        char* esi_1 = ecx_1
0044738b        char ebx_1 = *esi_1
0044738d        esi_1 = &esi_1[8]
00447390        (*edi_1)[0][i_1] = ebx_1
00447399        i_1 += 1
0044739c        do while (i_1 s< *(edx_5 + 0x88))
004473a2        ecx_1 = &ecx_1[1]
004473a3        edi_1 = &(*edi_1)[1]
004473a9        cond:0_1 = segment_name != 1
004473aa        segment_name -= 1
004473ae        do while (cond:0_1)
004473b9        int32_t i_2 = 0
004473bb        segment_1->row_count = *(edx_5 + 0x88)
004473be        segment_1->source_name = edx_5 + 0x44
004473c1        segment_1->angle_radians.bits = 0
004473cd        segment_1->path_index = *(edx_5 + 0x84)
004473d8        if (*(edx_5 + 0x88) s> 0)
004473da        int32_t* ecx_3 = &segment_1->rows[0].object_id
004473e0        int32_t* eax_7 = edx_5 + 0x8a0
004473ec        (ecx_3 - 0x828)->rows[0].flags = eax_7[-5]
004473f1        (ecx_3 - 0x828)->rows[0].object_id = *eax_7
004473f6        i_2 += 1
004473f9        ecx_3[1].d = eax_7[1]
004473fe        ecx_3[1]:4.d = eax_7[2]
00447404        ecx_3[1]:8.d = eax_7[3]
0044740f        ecx_3[4].d = eax_7[4]
00447414        ecx_3[4]:4.d = eax_7[5]
0044741a        ecx_3[4]:8.d = eax_7[6]
00447420        (ecx_3 - 0x828)->rows[0].parcel_set_id = eax_7[-4]
00447423        int32_t* edi_9 = &eax_7[-3]
00447426        struct Vec3* ebx_4 = &ecx_3[-3]
00447429        eax_7 = &eax_7[0xe]
0044742e        ecx_3 = &ecx_3[0xe]
00447431        ebx_4->x = *edi_9
00447436        ebx_4->y = edi_9[1]
0044743c        ebx_4->z = edi_9[2]
0044743f        int32_t edi_11 = eax_7[-7]
00447442        (ecx_3 - 0x828)->glyph_rows[7][0xf8] = edi_11.b
00447442        (ecx_3 - 0x828)->glyph_rows[7][0xf9] = edi_11:1.b
00447442        (ecx_3 - 0x828)->glyph_rows[7][0xfa] = edi_11:2.b
00447442        (ecx_3 - 0x828)->glyph_rows[7][0xfb] = edi_11:3.b
00447445        int32_t edi_12 = eax_7[-6]
00447448        (ecx_3 - 0x828)->glyph_rows[7][0xfc] = edi_12.b
00447448        (ecx_3 - 0x828)->glyph_rows[7][0xfd] = edi_12:1.b
00447448        (ecx_3 - 0x828)->glyph_rows[7][0xfe] = edi_12:2.b
00447448        (ecx_3 - 0x828)->glyph_rows[7][0xff] = edi_12:3.b
00447453        do while (i_2 s< *(edx_5 + 0x88))
00447455        segment_1 = segment
0044745a        segment_1->message_text[0] = 0
00447461        segment_1->message_duration.bits = 0
0044746b        segment_1->message_sample_id = 0xffffffff
00447478        return
