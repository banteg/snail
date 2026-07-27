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
004089b8        char var_c0[0x40]
004089b8        sprintf(&var_c0, "Galaxy%i:", var_d0)
004089c7        char* searched = find_case_insensitive_substring(&var_c0, file_text)
004089d1        char* cursor = searched
004089d5        if (searched == 0)
00408bd8        report_errorf("Cannot find Galaxy %i in _Galaxy.txt")
00408bea        return
004089e9        char* cursor_1 = &find_case_insensitive_substring(":", searched)[1]
004089ea        cursor = cursor_1
004089f1        if (*cursor_1 != 0x22)
00408bf0        report_errorf("missing " in _Galaxy.txt")
00408c02        return
004089f7        char* searched_1 = &cursor_1[1]
004089f8        char* route_name_character_cursor = edi - 0x84
004089fe        cursor = searched_1
00408a02        char j = *searched_1
00408a07        while (j != 0x22)
00408a09        *route_name_character_cursor = j
00408a0b        route_name_character_cursor = &route_name_character_cursor[1]
00408a0c        searched_1 = &searched_1[1]
00408a0d        cursor = searched_1
00408a11        j = *searched_1
00408a1e        *route_name_character_cursor = 0
00408a21        char* searched_2 = find_case_insensitive_substring("StarNumber=", searched_1)
00408a2c        cursor = searched_2
00408a3b        cursor = &find_case_insensitive_substring("=", searched_2)[1]
00408a44        edi->r:-4.d = parse_next_signed_int(&cursor)
00408a4c        edi->r = 0x3f800000
00408a4e        edi->g = 1f
00408a51        edi->b = 1f
00408a54        edi->a = 0.800000012f
00408a61        edi->__offset(0x10).d = current_group_point_y_cursor[-1]
00408a67        edi->__offset(0x14).d = *current_group_point_y_cursor
00408a6a        edi->__offset(0x18).d = 0
00408a70        if (edi->r:-4.d s> 0)
00408a76        int32_t ebp = 0
00408a8e        galaxy->route_slots[galaxy->record_count].record.route_name_index = var_d0
00408ab9        (&galaxy->route_slots[0].record.map_x)[galaxy->record_count * 0xa8] = g_galaxy_route_points[1 + divs.dp.d(sx.q(ebp), edi->r:-4.d) + var_cc].x
00408ae4        (&galaxy->route_slots[0].record.map_y)[galaxy->record_count * 0xa8] = g_galaxy_route_points[1 + divs.dp.d(sx.q(ebp), edi->r:-4.d) + var_cc].y
00408afe        (&galaxy->route_slots[0].record.map_z)[galaxy->record_count * 0xa8] = 0
00408b10        char var_80[0x80]
00408b10        sprintf(&var_80, "LEVEL %i MISSING", galaxy->record_count)
00408b31        rstrcpy_checked_ascii(&galaxy->route_slots[0].record.detail_text[galaxy->record_count * 0x2a0], &var_80)
00408b55        rstrcpy_checked_ascii(&galaxy->route_slots[0].record.description_text[galaxy->record_count * 0x2a0], &var_80)
00408b61        j_1 += 1
00408b62        galaxy->record_count += 1
00408b68        ebp += 0xa
00408b6d        do while (j_1 s< edi->r:-4.d)
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
