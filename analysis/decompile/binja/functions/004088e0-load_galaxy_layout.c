/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_galaxy_layout @ 0x4088e0 */

004088e6        float* route_point_y_cursor = &g_galaxy_route_points[0].y
004088f1        galaxy->active = 0
004088f4        galaxy->record_count = 1
004088fe        long double x87_r7_2 = fconvert.t(route_point_y_cursor[-1]) * fconvert.t(0.800000012f)
00408904        route_point_y_cursor = &route_point_y_cursor[2]
0040890c        route_point_y_cursor[-3] = fconvert.s(x87_r7_2)
0040892a        route_point_y_cursor[-2] = fconvert.s((fconvert.t(route_point_y_cursor[-2]) * fconvert.t(0.800000012f) - fconvert.t(240f)) * fconvert.t(0.930000007f) + fconvert.t(250f))
0040892d        do while (route_point_y_cursor s< "ing " in _Galaxy.txt")
0040892f        float* group_point_rescale_y_cursor = &g_galaxy_group_points[0].y
00408937        long double x87_r7_9 = fconvert.t(group_point_rescale_y_cursor[-1]) * fconvert.t(0.800000012f)
0040893d        group_point_rescale_y_cursor = &group_point_rescale_y_cursor[2]
00408945        group_point_rescale_y_cursor[-3] = fconvert.s(x87_r7_9)
00408963        group_point_rescale_y_cursor[-2] = fconvert.s((fconvert.t(group_point_rescale_y_cursor[-2]) * fconvert.t(0.800000012f) - fconvert.t(240f)) * fconvert.t(0.930000007f) + fconvert.t(250f))
00408966        do while (group_point_rescale_y_cursor s< 0x4a1ca0)
0040896d        int32_t j_1 = 0
00408975        galaxy->level_progress_base = &g_game_base->subgame
00408986        char* file_text = load_file_bytes_from_archive_or_fs("Galaxy/_Galaxy.txt", get_archive_data_base(), nullptr)
0040898b        float* current_group_point_y_cursor = &g_galaxy_group_points[0].y
00408997        int32_t var_d0 = 0
0040899b        int32_t var_cc = 0
0040899f        float* current_group_point_y_cursor_1 = &g_galaxy_group_points[0].y
004089a3        struct tColour* edi = &galaxy->route_names[0].color
004089b8        void buffer
004089b8        sprintf(&buffer, "Galaxy%i:", var_d0)
004089c7        char* eax_4 = find_case_insensitive_substring(&buffer, file_text)
004089d1        char* var_d4 = eax_4
004089d5        if (eax_4 == 0)
00408bd8        report_errorf("Cannot find Galaxy %i in _Galaxy.txt")
00408bea        return
004089e9        char* eax_6 = &find_case_insensitive_substring(":", eax_4)[1]
004089ea        var_d4 = eax_6
004089f1        if (*eax_6 != 0x22)
00408bf0        report_errorf("missing " in _Galaxy.txt")
00408c02        return
004089f7        char* eax_7 = &eax_6[1]
004089f8        char* route_name_character_cursor = edi - 0x84
004089fe        var_d4 = eax_7
00408a02        char j = *eax_7
00408a07        while (j != 0x22)
00408a09        *route_name_character_cursor = j
00408a0b        route_name_character_cursor = &route_name_character_cursor[1]
00408a0c        eax_7 = &eax_7[1]
00408a0d        var_d4 = eax_7
00408a11        j = *eax_7
00408a1e        *route_name_character_cursor = 0
00408a21        char* eax_8 = find_case_insensitive_substring("StarNumber=", eax_7)
00408a2c        var_d4 = eax_8
00408a3b        var_d4 = &find_case_insensitive_substring("=", eax_8)[1]
00408a44        (edi - 0x109b4)->route_names[0].star_count = parse_next_signed_int(&var_d4)
00408a4c        edi->r = 0x3f800000
00408a4e        edi->g = 1f
00408a51        edi->b = 1f
00408a54        edi->a = 0.800000012f
00408a61        edi->__offset(0x10).d = current_group_point_y_cursor[-1]
00408a67        edi->__offset(0x14).d = *current_group_point_y_cursor
00408a6a        edi->__offset(0x18).d = 0f
00408a70        if ((edi - 0x109b4)->route_names[0].star_count s> 0)
00408a76        int32_t ebp = 0
00408a8e        galaxy->route_slots[galaxy->record_count].record.route_name_index = var_d0
00408ab9        (&galaxy->route_slots[0].record.map_x)[galaxy->record_count * 0xa8] = g_galaxy_route_points[1 + divs.dp.d(sx.q(ebp), (edi - 0x109b4)->route_names[0].star_count) + var_cc].x
00408ae4        (&galaxy->route_slots[0].record.map_y)[galaxy->record_count * 0xa8] = g_galaxy_route_points[1 + divs.dp.d(sx.q(ebp), (edi - 0x109b4)->route_names[0].star_count) + var_cc].y
00408afe        (&galaxy->route_slots[0].record.map_z)[galaxy->record_count * 0xa8] = 0
00408b10        void buffer_1
00408b10        sprintf(&buffer_1, "LEVEL %i MISSING", galaxy->record_count)
00408b31        rstrcpy_checked_ascii(&galaxy->route_slots[0].record.detail_text[galaxy->record_count * 0x2a0], &buffer_1)
00408b55        rstrcpy_checked_ascii(&galaxy->route_slots[0].record.description_text[galaxy->record_count * 0x2a0], &buffer_1)
00408b61        j_1 += 1
00408b62        galaxy->record_count += 1
00408b68        ebp += 0xa
00408b6d        do while (j_1 s< (edi - 0x109b4)->route_names[0].star_count)
00408b73        current_group_point_y_cursor = current_group_point_y_cursor_1
00408b77        j_1 = 0
00408b81        current_group_point_y_cursor = &current_group_point_y_cursor[2]
00408b88        edi = &edi[0xa]
00408b94        var_d0 += 1
00408b98        current_group_point_y_cursor_1 = current_group_point_y_cursor
00408b9c        var_cc += 0xa
00408ba0        do while (current_group_point_y_cursor s< 0x4a1ca0)
00408ba6        galaxy->route_slots[0].record.route_name_index = 0
00408baf        galaxy->route_slots[0].record.map_x = g_galaxy_route_points[0].x
00408bb7        galaxy->route_slots[0].record.map_y = g_galaxy_route_points[0].y
00408bba        galaxy->route_slots[0].record.map_z = 0f
00408bbd        galaxy->route_slots[0].record.detail_text[0] = 0
00408bc1        galaxy->route_slots[0].record.description_text[0] = 0
00408bd2        return
