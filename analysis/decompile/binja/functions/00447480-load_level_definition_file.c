/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_level_definition_file @ 0x447480 */

0044749e        g_current_level_definition_name = filename
004474a4        char level_path[0x200]
004474a4        sprintf(&level_path, "Levels/%s", filename)
004474bf        if (load_file_bytes_from_archive_or_fs(&level_path, &g_level_file_text_buffer, nullptr) == 0)
004474cb        report_errorf("Cannot find %s reverting to default.txt", &level_path)
004474da        sprintf(&level_path, "Levels/Default.txt")
004474eb        load_file_bytes_from_archive_or_fs(&level_path, &g_level_file_text_buffer, nullptr)
004474fd        char* searched = find_case_insensitive_substring("Name:'", &g_level_file_text_buffer)
00447505        char* cursor = searched
0044750b        if (searched == 0)
00447517        report_errorf("Cannot find Name:' in %s", &level_path)
0044751c        searched = cursor
00447531        char* cursor_5 = &find_case_insensitive_substring("'", searched)[1]
00447532        cursor = cursor_5
0044753c        char i = *cursor_5
0044753e        char* level_display_name_cursor = &tracks->level_display_name
00447543        if (i != 0x27)
00447548        while (i s>= 0x20)
0044754a        *level_display_name_cursor = i
0044754c        level_display_name_cursor = &level_display_name_cursor[1]
0044754d        cursor_5 = &cursor_5[1]
0044754e        cursor = cursor_5
00447552        i = *cursor_5
00447557        if (i == 0x27)
00447557        break
00447559        *level_display_name_cursor = 0
00447569        if (g_game_base->subgame.galaxy.active == 0)
00447575        char* searched_1 = find_case_insensitive_substring("Arcade", filename)
0044757d        cursor = searched_1
00447583        if (searched_1 != 0)
0044759a        cursor = &find_case_insensitive_substring("e", searched_1)[1]
004475bb        int32_t edi_2 = parse_next_signed_int(&cursor) * 0x2a0
004475c6        sprintf(&g_game_base->subgame.galaxy.route_slots[0].record.detail_text[edi_2], "%s", &tracks->level_display_name)
004475d5        char* searched_2 = find_case_insensitive_substring("GalaxyText:", &g_level_file_text_buffer)
004475dd        cursor = searched_2
004475e3        if (searched_2 != 0)
00447616        char* cursor_1 = find_case_insensitive_substring("{", searched_2)
0044761e        cursor = cursor_1
00447624        if (cursor_1 != 0)
00447651        char* searched_3 = advance_to_next_crlf_line(cursor_1)
0044765c        cursor = searched_3
00447660        char* eax_8 = find_case_insensitive_substring("}", searched_3)
0044766a        if (eax_8 != 0)
0044769d        char* edx_3 = &g_game_base->subgame.galaxy.route_slots[0].record.description_text[edi_2]
004476a4        char* i_1 = cursor
004476aa        while (i_1 u< eax_8 - 2)
004476af        if (*i_1 s< 0x20)
004476b1        *edx_3 = 0x3e
004476b4        i_1 = cursor
004476b8        edx_3 = &edx_3[1]
004476bc        while (*i_1 s< 0x20)
004476be        i_1 = &i_1[1]
004476bf        cursor = i_1
004476ca        *edx_3 = *i_1
004476d0        edx_3 = &edx_3[1]
004476d1        i_1 = &cursor[1]
004476d4        cursor = i_1
004476da        *edx_3 = 0
00447672        report_warningf("Cannot find } for GalaxyText: in %s", filename)
0044768a        rstrcpy_checked_ascii(&g_game_base->subgame.galaxy.route_slots[0].record.description_text[edi_2], "TEXT ERROR } MISSING")
0044762c        report_warningf("Cannot find { for GalaxyText: in %s", filename)
00447643        rstrcpy_checked_ascii(&g_game_base->subgame.galaxy.route_slots[0].record.description_text[edi_2], "TEXT ERROR { MISSING")
004475eb        report_warningf("Cannot find GalaxyText: in %s", filename)
00447603        rstrcpy_checked_ascii(&g_game_base->subgame.galaxy.route_slots[0].record.description_text[edi_2], "TEXT MISSING")
004476e7        char* cursor_6 = find_case_insensitive_substring("Random:yes", &g_level_file_text_buffer)
004476f3        cursor = cursor_6
004476fc        if (cursor_6 == 0)
00447794        tracks->random_enabled = 0
0044779b        tracks->random_length = 0
0044770c        tracks->random_enabled = 1
00447712        char* searched_4 = find_case_insensitive_substring("Length:", &g_level_file_text_buffer)
0044771c        cursor = searched_4
00447720        if (searched_4 == 0)
0044772c        report_errorf("Cannot Length: in %s", &level_path)
0044773e        return
0044774f        char* cursor_7 = &find_case_insensitive_substring(":", searched_4)[1]
00447750        cursor = cursor_7
00447754        tracks->random_length = 0
0044775a        char i_2 = *cursor_7
00447769        if (i_2 != 0x61 && i_2 != 0x41 && i_2 s>= 0x30)
0044776e        while (i_2 s<= 0x39)
00447770        int32_t random_length = tracks->random_length
00447776        cursor_7 = &cursor_7[1]
0044777d        cursor = cursor_7
00447785        tracks->random_length = sx.d(i_2) + random_length * 0xa - 0x30
0044778b        i_2 = *cursor_7
00447790        if (i_2 s< 0x30)
00447790        break
004477ab        char* searched_5 = find_case_insensitive_substring("Background:", &g_level_file_text_buffer)
004477b5        cursor = searched_5
004477b9        if (searched_5 == 0)
004477c5        report_errorf("No Background: in %s", &level_path)
004477d7        return
004477e8        char* cursor_8 = &find_case_insensitive_substring(":", searched_5)[1]
004477e9        cursor = cursor_8
004477ed        char script_name[0x200]
004477ed        char* script_name_cursor = &script_name
004477f4        char i_3 = *cursor_8
004477f9        while (i_3 != 0x2e)
004477fb        *script_name_cursor = i_3
004477fd        script_name_cursor = &script_name_cursor[1]
004477fe        cursor_8 = &cursor_8[1]
004477ff        cursor = cursor_8
00447803        i_3 = *cursor_8
0044780a        *script_name_cursor = 0x2e
0044780e        struct GameRoot* game_base_1 = g_game_base
00447814        script_name_cursor[1] = 0x74
00447818        script_name_cursor[2] = 0x78
0044781c        script_name_cursor[3] = 0x74
0044781f        script_name_cursor[4] = 0
00447840        tracks->landscape_script_index = load_landscape_script_by_name(&game_base_1->subgame.landscape_manager, &script_name)
00447846        char* searched_6 = find_case_insensitive_substring("Fringe:", &g_level_file_text_buffer)
00447850        cursor = searched_6
00447854        if (searched_6 != 0)
0044789a        cursor = &find_case_insensitive_substring(":", searched_6)[1]
004478b6        tracks->fringe_color.r = fconvert.s(float.t(parse_next_signed_int(&cursor)) * fconvert.t(0.00392156886f))
004478d4        tracks->fringe_color.g = fconvert.s(float.t(parse_next_signed_int(&cursor)) * fconvert.t(0.00392156886f))
004478f0        tracks->fringe_color.b = fconvert.s(float.t(parse_next_signed_int(&cursor)) * fconvert.t(0.00392156886f))
00447860        report_errorf("No Fringe: in %s using white", &level_path)
00447882        store_color4f(&tracks->fringe_color, 1f, 1f, 1f, 1f)
00447900        char* searched_7 = find_case_insensitive_substring("Track:", &g_level_file_text_buffer)
0044790a        cursor = searched_7
0044790e        if (searched_7 != 0)
00447938        char* cursor_9 = &find_case_insensitive_substring(":", searched_7)[1]
00447939        cursor = cursor_9
0044793d        char eax_20 = *cursor_9
00447941        if (eax_20 == 0x30)
00447943        tracks->track_texture_set = 0
0044794d        if (eax_20 == 0x31)
0044794f        tracks->track_texture_set = 1
00447959        if (eax_20 == 0x32)
0044795b        tracks->track_texture_set = 2
00447969        if (eax_20 == 0x33)
0044796b        tracks->track_texture_set = 3
00447979        if (eax_20 == 0x72)
0044797b        tracks->track_texture_set = 5
0044791a        report_errorf("No Track: in %s using Track0.tga", &level_path)
00447922        tracks->track_texture_set = 0
0044798f        char* searched_8 = find_case_insensitive_substring("Parcels:", &g_level_file_text_buffer)
00447999        cursor = searched_8
0044799d        if (searched_8 == 0)
004479a3        tracks->parcel_count = 0
004479af        report_errorf("No Parcel: in %s", &level_path)
004479c1        return
004479cf        cursor = find_case_insensitive_substring(":", searched_8)
004479e7        tracks->parcel_count = parse_next_signed_int(&cursor)
004479ed        char* searched_9 = find_case_insensitive_substring("Quota:", &g_level_file_text_buffer)
004479f7        cursor = searched_9
004479fb        if (searched_9 == 0)
00447a01        tracks->parcel_quota = 0
00447a0d        report_errorf("No Quota: in %s", &level_path)
00447a1f        return
00447a31        cursor = find_case_insensitive_substring(":", searched_9)
00447a45        tracks->parcel_quota = parse_next_signed_int(&cursor)
00447a4b        char* cursor_10 = find_case_insensitive_substring("Speed:select", &g_level_file_text_buffer)
00447a55        cursor = cursor_10
00447a5e        if (cursor_10 == 0)
00447a72        char* searched_10 = find_case_insensitive_substring("Speed:", &g_level_file_text_buffer)
00447a7c        cursor = searched_10
00447a80        if (searched_10 != 0)
00447ab1        cursor = &find_case_insensitive_substring(":", searched_10)[1]
00447aba        tracks->selected_speed.bits = fconvert.s(parse_next_float32(&cursor))
00447a8c        report_errorf("Cannot find Speed: in Segment %s\n", &level_path)
00447a94        tracks->selected_speed.bits = 0x42c80000
00447a60        tracks->selected_speed.bits = 0xbf800000
00447acd        char* cursor_11 = find_case_insensitive_substring("Garbage:", &g_level_file_text_buffer)
00447ad7        cursor = cursor_11
00447adb        if (cursor_11 != 0)
00447aef        tracks->garbage_frequency = fconvert.s(parse_next_float32(&cursor))
00447add        tracks->garbage_frequency = -1f
00447b02        char* cursor_12 = find_case_insensitive_substring("Salt:", &g_level_file_text_buffer)
00447b0c        cursor = cursor_12
00447b10        if (cursor_12 != 0)
00447b24        tracks->salt_frequency = fconvert.s(parse_next_float32(&cursor))
00447b12        tracks->salt_frequency = -1f
00447b37        tracks->segment_count = 0
00447b39        char* cursor_13 = find_case_insensitive_substring("Segments Begin:", &g_level_file_text_buffer)
00447b43        cursor = cursor_13
00447b47        if (cursor_13 == 0)
00447b53        report_errorf("Cannot find Segments Begin: in %s", &level_path)
00447b65        return
00447b77        char* segments_end = find_case_insensitive_substring("Segments End:", &g_level_file_text_buffer)
00447b82        if (segments_end == 0)
00447b8e        report_errorf("Cannot find Segments End: in %s", &level_path)
00447ba0        return
00447ba8        char* cursor_14 = advance_to_next_crlf_line(cursor)
00447bb2        cursor = cursor_14
00447bb6        if (cursor_14 != 0)
00447bbe        char segment_name[0x200]
00447bbe        while (cursor_14 u< segments_end)
00447bc9        char i_4 = *cursor_14
00447bcb        char* segment_name_cursor = &segment_name
00447bd5        while (i_4 != 0x2e)
00447bd7        *segment_name_cursor = i_4
00447bd9        segment_name_cursor = &segment_name_cursor[1]
00447bda        cursor_14 = &cursor_14[1]
00447bdb        cursor = cursor_14
00447bdf        i_4 = *cursor_14
00447be6        int32_t segment_count = tracks->segment_count
00447be8        *segment_name_cursor = 0x2e
00447bf1        segment_name_cursor[1] = 0x74
00447bfa        segment_name_cursor[2] = 0x78
00447c03        segment_name_cursor[3] = 0x74
00447c06        segment_name_cursor[4] = 0
00447c19        copy_segment_definition_to_level_slot(tracks, &segment_name, &tracks->segment_slots[segment_count])
00447c22        char* line_cursor_4 = &cursor[3]
00447c25        char line_options[0x80]
00447c25        char* line_options_cursor = &line_options
00447c2c        char* line_cursor = line_cursor_4
00447c30        char i_5 = *line_cursor_4
00447c34        while (i_5 s>= 0x20)
00447c36        *line_options_cursor = i_5
00447c38        line_options_cursor = &line_options_cursor[1]
00447c39        line_cursor_4 = &line_cursor_4[1]
00447c3a        line_cursor = line_cursor_4
00447c3e        i_5 = *line_cursor_4
00447c4b        *line_options_cursor = 0
00447c54        char* searched_11 = find_case_insensitive_substring("Angle=", &line_options)
00447c5e        line_cursor = searched_11
00447c62        if (searched_11 == 0)
00447cb9        tracks->segment_slots[tracks->segment_count].angle_radians.bits = 0
00447c73        line_cursor = find_case_insensitive_substring("=", searched_11)
00447c9f        tracks->segment_slots[tracks->segment_count].angle_radians.bits = fconvert.s(float.t(parse_next_signed_int(&line_cursor)) * fconvert.t(0.0174532924f))
00447cde        tracks->segment_slots[tracks->segment_count].message_text[0] = 0
00447ce6        char* searched_12 = find_case_insensitive_substring("Message=", &line_options)
00447cf0        line_cursor = searched_12
00447cf4        if (searched_12 != 0)
00447d08        char* line_cursor_1 = &find_case_insensitive_substring("=", searched_12)[1]
00447d09        line_cursor = line_cursor_1
00447d10        if (*line_cursor_1 != 0x22)
00447ef6        report_errorf("Need " after Message=")
00447f08        return
00447d16        char* line_cursor_2 = &line_cursor_1[1]
00447d17        line_cursor = line_cursor_2
00447d1b        char* line_cursor_5 = line_cursor_2
00447d20        if (*line_cursor_2 != 0x22)
00447d29        char i_6
00447d22        i_6 = line_cursor_5[1]
00447d25        line_cursor_5 = &line_cursor_5[1]
00447d29        do while (i_6 != 0x22)
00447d3e        char* ecx_26 = &tracks->segment_slots[tracks->segment_count].message_text
00447d45        while (line_cursor_2 u< line_cursor_5)
00447d49        *ecx_26 = *line_cursor_2
00447d4f        ecx_26 = &ecx_26[1]
00447d50        line_cursor_2 = &line_cursor[1]
00447d53        line_cursor = line_cursor_2
00447d59        *ecx_26 = 0
00447d6e        line_cursor = find_case_insensitive_substring("Duration=", &line_options)
00447d86        tracks->segment_slots[tracks->segment_count].message_duration.bits = 0x40800000
00447d8d        char* searched_13 = line_cursor
00447d93        if (searched_13 != 0)
00447da1        line_cursor = &find_case_insensitive_substring("=", searched_13)[1]
00447dc3        tracks->segment_slots[tracks->segment_count].message_duration.bits = fconvert.s(parse_next_float32(&line_cursor))
00447ddc        line_cursor = find_case_insensitive_substring("Sample=", &line_options)
00447df5        *((tracks->segment_count + 1) * 0x4220 + tracks) = 0xffffffff
00447dfc        char* searched_14 = line_cursor
00447e02        if (searched_14 != 0)
00447e13        char* line_cursor_3 = &find_case_insensitive_substring("=", searched_14)[2]
00447e19        line_cursor = line_cursor_3
00447e1d        char sample_name[0x80]
00447e1d        char* sample_name_cursor = &sample_name
00447e24        char i_7 = *line_cursor_3
00447e29        while (i_7 != 0x22)
00447e2b        *sample_name_cursor = i_7
00447e2d        sample_name_cursor = &sample_name_cursor[1]
00447e2e        line_cursor_3 = &line_cursor_3[1]
00447e2f        line_cursor = line_cursor_3
00447e33        i_7 = *line_cursor_3
00447e3a        *sample_name_cursor = 0
00447e5f        *((tracks->segment_count + 1) * 0x4220 + tracks) = find_registered_sound_sample_id_by_name(&sample_name)
00447e78        if (*((tracks->segment_count + 1) * 0x4220 + tracks) == 0xffffffff)
00447e8c        report_errorf("Cannot find sample %s in %s", &sample_name, &level_path)
00447e96        char* cursor_4 = cursor
00447e9c        tracks->segment_count += 1
00447e9e        cursor_14 = advance_to_next_crlf_line(cursor_4)
00447ea8        cursor = cursor_14
00447eac        if (cursor_14 == 0)
00447f18        report_errorf("Unexpected end of file in %s", filename)
00447f2a        return
00447ec2        char* cursor_2 = find_case_insensitive_substring("First:", &g_level_file_text_buffer)
00447ecc        cursor = cursor_2
00447ed0        if (cursor_2 == 0)
00447edc        report_errorf("Cannot find 'First:' in %s", &level_path)
00447eee        return
00447f2e        char* cursor_15 = advance_to_next_crlf_line(cursor_2)
00447f38        cursor = cursor_15
00447f3c        if (cursor_15 != 0)
00447f5d        char i_8 = *cursor_15
00447f5f        char* first_segment_name_cursor = &segment_name
00447f69        while (i_8 != 0x2e)
00447f6b        *first_segment_name_cursor = i_8
00447f6d        first_segment_name_cursor = &first_segment_name_cursor[1]
00447f6e        cursor_15 = &cursor_15[1]
00447f6f        cursor = cursor_15
00447f73        i_8 = *cursor_15
00447f7a        *first_segment_name_cursor = 0x2e
00447f8b        first_segment_name_cursor[1] = 0x74
00447f91        first_segment_name_cursor[2] = 0x78
00447f95        first_segment_name_cursor[3] = 0x74
00447f98        first_segment_name_cursor[4] = 0
00447f9e        copy_segment_definition_to_level_slot(tracks, &segment_name, &tracks->first_segment)
00447fad        char* cursor_3 = find_case_insensitive_substring("Last:", &g_level_file_text_buffer)
00447fb7        cursor = cursor_3
00447fbb        if (cursor_3 == 0)
00447fc7        report_errorf("Cannot find 'Last:' in %s", &level_path)
00447fd9        return
00447fdd        char* cursor_16 = advance_to_next_crlf_line(cursor_3)
00447fe7        cursor = cursor_16
00447feb        if (cursor_16 == 0)
00447ff7        report_errorf("Unexpected end of file in %s", &level_path)
00448009        return
0044800c        char i_9 = *cursor_16
0044800e        char* last_segment_name_cursor = &segment_name
00448018        while (i_9 != 0x2e)
0044801a        *last_segment_name_cursor = i_9
0044801c        last_segment_name_cursor = &last_segment_name_cursor[1]
0044801d        cursor_16 = &cursor_16[1]
0044801e        cursor = cursor_16
00448022        i_9 = *cursor_16
00448029        *last_segment_name_cursor = 0x2e
00448033        last_segment_name_cursor[1] = 0x74
00448038        last_segment_name_cursor[2] = 0x78
0044803c        last_segment_name_cursor[3] = 0x74
0044803f        last_segment_name_cursor[4] = 0
0044804d        copy_segment_definition_to_level_slot(tracks, &segment_name, &tracks->last_segment)
0044805c        return
00447f48        report_errorf("Unexpected end of file in %s", &level_path)
00447f5a        return
