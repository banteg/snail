/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_segment_definitions @ 0x448160 */

00448165        struct SMTracks* tracks_after_stack_probe = chkstk(0x114e0)
00448189        tracks_after_stack_probe->count = 0
0044818b        EnumeratedEntryName segment_files[0x200]
0044818b        enumerate_matching_archive_or_fs_entries("Segments", "*.txt", tracks_after_stack_probe, &segment_files)
00448190        int32_t count = tracks_after_stack_probe->count
0044819a        if (count s>= 0x96)
004481a1        report_errorf("Too many Segments increase RSMTRACK_SEGMENT_MAX")
004481b3        return
004481b4        int32_t segment_index = 0
004481b8        int32_t segment_index_spill = 0
004481bc        if (count s<= 0)
004481bc        return
004481c2        EnumeratedEntryName* segment_file_name_cursor = &segment_files
004481cf        int32_t segment_row_base = 0
004481d3        int32_t glyph_row_base = 0
004481d7        EnumeratedEntryName* segment_file_name_saved = &segment_files
004481db        int32_t* row_count_cursor = &tracks_after_stack_probe->entries[0].row_count
004481fb        while (true)
004481fb        char file_path[0x200]
004481fb        char file_buffer[0x1000]
004481fb        sprintf(&file_path, "Segments/%s", segment_file_name_cursor, &file_buffer)
00448211        load_file_bytes_from_archive_or_fs(&file_path, &file_buffer, nullptr)
00448223        char* eax = find_case_insensitive_substring("ID:", &file_buffer)
0044822d        int32_t __saved_edi
0044822d        if (eax == 0)
0044880e        report_errorf("Cannot find ID: in Segment %s\n", &(&__saved_edi)[segment_index * 0x20 + 0x53c])
00448820        return
00448233        char i = eax[3]
00448236        char* eax_1 = &eax[3]
00448239        int32_t edx_1 = 0
0044823e        if (i s>= 0x30)
00448243        while (i s<= 0x39)
0044824b        eax_1 = &eax_1[1]
0044824c        edx_1 = sx.d(i) + edx_1 * 0xa - 0x30
00448250        i = *eax_1
00448255        if (i s< 0x30)
00448255        break
00448265        row_count_cursor[-1] = edx_1
00448268        sprintf(&row_count_cursor[-0x11], "%s", segment_file_name_cursor)
0044827a        char* searched = find_case_insensitive_substring("Name:'", &file_buffer)
00448284        if (searched == 0)
00448831        report_errorf("Cannot find Name: in Segment %s\n", &(&__saved_edi)[segment_index * 0x20 + 0x53c])
00448843        return
00448290        char* eax_3 = find_case_insensitive_substring("'", searched)
00448295        char i_1 = eax_3[1]
0044829b        void* eax_4 = &eax_3[1]
0044829f        if (i_1 != 0x27)
004482a3        char* edx_3 = &row_count_cursor[-0x11] - eax_4 - 0x40
004482a6        *(edx_3 + eax_4) = i_1
004482a9        i_1 = *(eax_4 + 1)
004482ac        eax_4 += 1
004482b0        do while (i_1 != 0x27)
004482bf        char* cursor = find_case_insensitive_substring("Data:", &file_buffer)
004482c9        if (cursor == 0)
00448854        report_errorf("Cannot find Data: in Segment %s\n", &(&__saved_edi)[segment_index * 0x20 + 0x53c])
00448866        return
004482d0        char* cursor_1 = advance_to_next_crlf_line(cursor)
004482da        void* var_14_31
004482da        if (cursor_1 == 0)
00448871        var_14_31 = &(&__saved_edi)[segment_index * 0x20 + 0x53c]
004482e6        char* data_line_cursor = advance_to_next_crlf_line(cursor_1)
004482ed        void* eax_32
004482ed        if (data_line_cursor == 0)
00448877        eax_32 = &(&__saved_edi)[segment_index * 0x20 + 0x53c]
004488d8        label_4488d8:
004488d8        var_14_31 = eax_32
004482f6        if (*data_line_cursor != 0x40)
00448890        report_errorf("Data line must start with '@' in Segment %s\n", &(&__saved_edi)[segment_index * 0x20 + 0x53c])
004488a2        return
00448300        int32_t row_index = 0
00448304        *row_count_cursor = 0
00448315        while (true)
00448315        if (*data_line_cursor == 0x40 && data_line_cursor[1] == 0x40 && data_line_cursor[2] == 0x40)
004487be        segment_index += 1
004487bf        segment_row_base += 0x127
004487dd        segment_index_spill = segment_index
004487e1        glyph_row_base += 0x811
004487e5        row_count_cursor = &row_count_cursor[0x1022]
004487e9        segment_file_name_saved = &segment_file_name_saved[1]
004487ed        if (segment_index s>= tracks_after_stack_probe->count)
004487fd        return
004481e1        segment_file_name_cursor = segment_file_name_saved
004481e1        break
00448324        int32_t flattened_row_index = sx.d(row_index.w) + segment_row_base
00448334        char* glyph_cursor = &data_line_cursor[1]
00448335        struct SegmentCatalogRowStrideAnchor* row_stride_anchor = tracks_after_stack_probe + flattened_row_index * 0x38
00448338        int32_t lane_index = 0
0044833a        row_stride_anchor->row.flags = 0
0044834c        char glyph = *glyph_cursor
0044834e        glyph_cursor = &glyph_cursor[1]
0044834f        int32_t edx_8 = lane_index + ((*row_count_cursor + glyph_row_base) << 3)
00448352        lane_index += 1
00448356        tracks_after_stack_probe->entries[0].glyph_columns[0][edx_8] = glyph
0044835d        do while (lane_index s< 8)
00448362        if (*glyph_cursor != 0x40)
004488b7        report_errorf("Data line must end with '@' in Segment %s\n", &(&__saved_edi)[segment_index_spill * 0x20 + 0x53c])
004488c9        return
0044836f        char* option_cursor = &glyph_cursor[1]
00448370        *row_count_cursor += 1
00448375        if (*option_cursor == 0x2a)
00448377        int32_t* flags = row_stride_anchor->row.flags
0044837d        flags.b |= 4
0044837f        row_stride_anchor->row.flags = flags
00448385        char option_char = *option_cursor
00448387        char option_text[0x200]
00448387        char* option_out_cursor = &option_text
0044838d        while (option_char != 0xd)
0044838f        *option_out_cursor = option_char
00448391        option_char = option_cursor[1]
00448394        option_out_cursor = &option_out_cursor[1]
00448395        option_cursor = &option_cursor[1]
004483a6        *option_out_cursor = 0
004483a8        char* searched_1 = find_case_insensitive_substring("3DModel=", &option_text)
004483b2        parse_cursor = searched_1
004483b6        if (searched_1 != 0)
004483ca        char* parse_cursor_1 = &find_case_insensitive_substring("=", searched_1)[1]
004483cb        parse_cursor = parse_cursor_1
004483cf        char mesh_name[0x80]
004483cf        char* mesh_name_cursor = &mesh_name
004483d6        char mesh_char = *parse_cursor_1
004483db        while (mesh_char != 0x2e)
004483dd        *mesh_name_cursor = mesh_char
004483df        mesh_name_cursor = &mesh_name_cursor[1]
004483e0        parse_cursor_1 = &parse_cursor_1[1]
004483e1        parse_cursor = parse_cursor_1
004483e5        mesh_char = *parse_cursor_1
004483ec        int32_t flags_1 = row_stride_anchor->row.flags
004483f2        *mesh_name_cursor = 0x2e
004483f6        flags_1.b |= 2
004483f8        row_stride_anchor->row.flags = flags_1
004483fe        struct GameRoot* game_base_1 = g_game_base
00448404        mesh_name_cursor[1] = 0x78
00448407        mesh_name_cursor[2] = 0
0044841d        row_stride_anchor->row.object_id = load_or_reuse_cached_x_mesh(&game_base_1->directx_loader, &mesh_name)
00448436        parse_cursor = find_case_insensitive_substring("(", parse_cursor)
00448440        row_stride_anchor->row.object_position.x = fconvert.s(parse_next_float32(&parse_cursor))
00448450        row_stride_anchor->row.object_position.y = fconvert.s(parse_next_float32(&parse_cursor))
00448460        row_stride_anchor->row.object_position.z = fconvert.s(parse_next_float32(&parse_cursor))
00448473        char* searched_2 = find_case_insensitive_substring("Velocity=", &option_text)
0044847d        parse_cursor = searched_2
00448481        if (searched_2 != 0)
00448489        char* eax_13 = find_case_insensitive_substring("=", searched_2)
00448495        int32_t edx_13 = row_stride_anchor->row.flags | 8
0044849e        parse_cursor = &eax_13[1]
004484a2        row_stride_anchor->row.flags = edx_13
004484b1        parse_cursor = find_case_insensitive_substring("(", &eax_13[1])
004484bb        row_stride_anchor->row.object_velocity.x = fconvert.s(parse_next_float32(&parse_cursor))
004484cb        row_stride_anchor->row.object_velocity.y = fconvert.s(parse_next_float32(&parse_cursor))
004484db        row_stride_anchor->row.object_velocity.z = fconvert.s(parse_next_float32(&parse_cursor))
004484ee        char* searched_3 = find_case_insensitive_substring("Parcel=", &option_text)
004484f8        parse_cursor = searched_3
004484fc        if (searched_3 != 0)
0044850d        row_stride_anchor->row.flags |= 1
00448519        parse_cursor = &find_case_insensitive_substring("=", searched_3)[1]
00448522        int32_t eax_18 = parse_next_signed_int(&parse_cursor)
00448527        char* searched_6 = parse_cursor
0044852b        row_stride_anchor->row.parcel_set_id = eax_18
00448542        parse_cursor = &find_case_insensitive_substring("(", searched_6)[1]
0044854b        row_stride_anchor->row.local_position.x = fconvert.s(parse_next_float32(&parse_cursor))
0044855b        row_stride_anchor->row.local_position.y = fconvert.s(parse_next_float32(&parse_cursor))
0044856b        row_stride_anchor->row.local_position.z = fconvert.s(parse_next_float32(&parse_cursor))
0044857e        char* searched_4 = find_case_insensitive_substring("Path=", &option_text)
00448588        parse_cursor = searched_4
0044858c        if (searched_4 != 0)
0044859c        char* parse_cursor_2 = &find_case_insensitive_substring("=", searched_4)[1]
0044859d        parse_cursor = parse_cursor_2
004485a1        char path_name[0x40]
004485a1        char* path_name_cursor = &path_name
004485a5        char path_char = *parse_cursor_2
004485aa        while (path_char s>= 0x20)
004485ac        *path_name_cursor = path_char
004485ae        path_name_cursor = &path_name_cursor[1]
004485af        parse_cursor_2 = &parse_cursor_2[1]
004485b0        parse_cursor = parse_cursor_2
004485b4        path_char = *parse_cursor_2
004485cc        *path_name_cursor = 0
004485ce        int32_t eax_22 = find_segment_path_index_by_name(&g_game_base->subgame.path_manager, &path_name)
004485d6        row_stride_anchor->row.path_template_index = eax_22
004485dc        if (eax_22 != 0xffffffff)
004485f7        int32_t flags_2 = row_stride_anchor->row.flags
004485fd        flags_2.b |= 8
004485ff        row_stride_anchor->row.flags = flags_2
004485ed        report_errorf("Unknown path %s in %s", &path_name, segment_file_name_saved)
0044860f        char* parse_cursor_3 = find_case_insensitive_substring("NoFall", &option_text)
00448619        parse_cursor = parse_cursor_3
0044861d        if (parse_cursor_3 != 0)
0044861f        int32_t flags_3 = row_stride_anchor->row.flags
00448625        flags_3:1.b |= 1
00448628        row_stride_anchor->row.flags = flags_3
00448638        char* parse_cursor_4 = find_case_insensitive_substring("Ring=None", &option_text)
00448642        parse_cursor = parse_cursor_4
00448646        if (parse_cursor_4 != 0)
00448648        int32_t flags_4 = row_stride_anchor->row.flags
0044864e        flags_4:1.b |= 2
00448651        row_stride_anchor->row.flags = flags_4
00448661        char* parse_cursor_5 = find_case_insensitive_substring("Ring=Normal", &option_text)
0044866b        parse_cursor = parse_cursor_5
0044866f        if (parse_cursor_5 != 0)
00448671        int32_t flags_5 = row_stride_anchor->row.flags
00448677        flags_5:1.b |= 4
0044867a        row_stride_anchor->row.flags = flags_5
0044868a        char* parse_cursor_6 = find_case_insensitive_substring("Ring=PowerUp", &option_text)
00448694        parse_cursor = parse_cursor_6
00448698        if (parse_cursor_6 != 0)
0044869a        int32_t flags_6 = row_stride_anchor->row.flags
004486a0        flags_6:1.b |= 0x20
004486a3        row_stride_anchor->row.flags = flags_6
004486b3        char* parse_cursor_7 = find_case_insensitive_substring("Ring=Explode", &option_text)
004486bd        parse_cursor = parse_cursor_7
004486c1        if (parse_cursor_7 != 0)
004486c3        int32_t flags_7 = row_stride_anchor->row.flags
004486c9        flags_7:1.b |= 8
004486cc        row_stride_anchor->row.flags = flags_7
004486dc        char* parse_cursor_8 = find_case_insensitive_substring("Ring=Slow", &option_text)
004486e6        parse_cursor = parse_cursor_8
004486ea        if (parse_cursor_8 != 0)
004486ec        int32_t flags_8 = row_stride_anchor->row.flags
004486f2        flags_8:1.b |= 0x10
004486f5        row_stride_anchor->row.flags = flags_8
00448705        char* searched_5 = find_case_insensitive_substring("RingSpeed=", &option_text)
0044870f        parse_cursor = searched_5
00448713        if (searched_5 == 0)
00448757        *(tracks_after_stack_probe + (flattened_row_index + 0x28) * 0x38) = 0
00448726        parse_cursor = &find_case_insensitive_substring("=", searched_5)[1]
00448742        *(tracks_after_stack_probe + (flattened_row_index + 0x28) * 0x38) = fconvert.s(parse_next_float32(&parse_cursor))
00448764        char* parse_cursor_9 = find_case_insensitive_substring("JetPack=Off", &option_text)
0044876e        parse_cursor = parse_cursor_9
00448772        if (parse_cursor_9 != 0)
00448774        int32_t flags_9 = row_stride_anchor->row.flags
0044877a        flags_9:1.b |= 0x80
0044877d        row_stride_anchor->row.flags = flags_9
00448789        data_line_cursor = advance_to_next_crlf_line(option_cursor)
00448790        if (data_line_cursor == 0)
004488d1        eax_32 = &(&__saved_edi)[segment_index_spill * 0x20 + 0x53c]
004488d1        goto label_4488d8
0044879a        segment_index = segment_index_spill
0044879f        row_index += 1
0044833a        continue
004488de        report_errorf("Unexpected end of file in Segment %s\n", var_14_31)
004488e3        break
004488f0        return
