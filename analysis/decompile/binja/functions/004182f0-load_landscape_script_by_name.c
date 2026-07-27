/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_landscape_script_by_name @ 0x4182f0 */

00418311        char var_600[0x200]
00418311        sprintf(&var_600, "Backgrounds/%s", script_name)
0041831f        int32_t i = 0
00418323        if (manager->script_count s> 0)
00418325        char (* ebp_1)[0x80] = &manager->scripts[0].name
00418337        if (strings_equal_case_insensitive_path(ebp_1, script_name) != 0)
00418392        return i
0041833f        i += 1
00418340        ebp_1 = &(*ebp_1)[0x124]
00418348        do while (i s< manager->script_count)
00418354        char* searched = load_file_bytes(&var_600, nullptr)
00418360        if (searched == 0)
0041836f        report_errorf("Landscape.Cannot load %s", &var_600)
00418383        return 0
004183aa        rstrcpy_checked_ascii(&manager->scripts[manager->script_count].name, script_name)
004183b5        char* searched_1 = find_case_insensitive_substring("ID:", searched)
004183bd        char* cursor = searched_1
004183c3        if (searched_1 != 0)
00418402        cursor = find_case_insensitive_substring(":", searched_1)
0041841b        manager->scripts[manager->script_count].id = parse_next_signed_int(&cursor)
004183d2        report_errorf("Landscape. Cannot find ID: %s", &var_600)
004183e6        manager->scripts[manager->script_count].id = 0
00418428        char* searched_2 = find_case_insensitive_substring("Fog:", searched)
00418430        cursor = searched_2
00418436        if (searched_2 != 0)
00418475        cursor = find_case_insensitive_substring(":", searched_2)
004184a2        manager->scripts[manager->script_count].fog_color.r = fconvert.s(float.t(parse_next_signed_int(&cursor)) * fconvert.t(0.00392156886f))
004184cd        manager->scripts[manager->script_count].fog_color.g = fconvert.s(float.t(parse_next_signed_int(&cursor)) * fconvert.t(0.00392156886f))
004184f6        manager->scripts[manager->script_count].fog_color.b = fconvert.s(float.t(parse_next_signed_int(&cursor)) * fconvert.t(0.00392156886f))
00418445        report_errorf("Landscape. Cannot find Fog: %s", &var_600)
00418460        set_color_black(&manager->scripts[manager->script_count].fog_color)
00418503        char* searched_3 = find_case_insensitive_substring("Picture:", searched)
0041850b        cursor = searched_3
00418511        if (searched_3 != 0)
00418538        char* cursor_1 = &find_case_insensitive_substring(":", searched_3)[1]
00418539        cursor = cursor_1
0041853d        void var_400
0041853d        char* edx_7 = &var_400
00418544        char i_1 = *cursor_1
00418549        while (i_1 != 0x2e)
0041854b        *edx_7 = i_1
0041854d        edx_7 = &edx_7[1]
0041854e        cursor_1 = &cursor_1[1]
0041854f        cursor = cursor_1
00418553        i_1 = *cursor_1
0041855a        int32_t script_count = manager->script_count
00418560        *edx_7 = 0
0041857e        sprintf(&manager->scripts[script_count].backdrop_texture_path, "Backgrounds/%s.tga", &var_400)
00418583        int32_t script_count_1 = manager->script_count
00418595        manager->scripts[script_count_1].backdrop_texture_id = script_count_1 * 2 + 6
004185b8        bool cond:0_1 = archive_or_file_exists(&manager->scripts[manager->script_count].backdrop_texture_path, 0) == 0
004185c3        int32_t edx_11 = manager->script_count * 0x49
004185c6        if (cond:0_1)
00418601        (&manager->scripts[0].split_backdrop_texture_pair)[edx_11 << 2] = 1
00418625        char texture_path_1
00418625        rstrcpy_checked_ascii(&texture_path_1, &manager->scripts[manager->script_count].backdrop_texture_path)
00418643        char texture_path
00418643        rstrcpy_checked_ascii(&texture_path, &manager->scripts[manager->script_count].backdrop_texture_path)
00418655        char* eax_34 = &texture_path_1
0041865c        if (texture_path_1 != 0x2e)
00418665        char i_2
0041865e        i_2 = eax_34[1]
00418661        eax_34 = &eax_34[1]
00418665        do while (i_2 != 0x2e)
00418667        bool cond:2_1 = texture_path == 0x2e
00418672        __builtin_strncpy(eax_34, "_A.tga", 7)
0041868a        char* eax_35 = &texture_path
0041868e        if (not(cond:2_1))
00418690        eax_35 = &eax_35[1]
00418694        do while (*eax_35 != 0x2e)
00418696        __builtin_strncpy(eax_35, "_B.tga", 7)
004186d4        register_sprite_texture(&g_sprite_manager, &texture_path_1, manager->scripts[manager->script_count].backdrop_texture_id, 0x400)
004186fd        register_sprite_texture(&g_sprite_manager, &texture_path, manager->scripts[manager->script_count].backdrop_texture_id + 1, 0x400)
004185e3        register_sprite_texture(&g_sprite_manager, &manager->scripts[0].backdrop_texture_path[edx_11 << 2], (&manager->scripts[0].backdrop_texture_id)[edx_11], 0x400)
004185f4        manager->scripts[manager->script_count].split_backdrop_texture_pair = 0
00418709        manager->script_count
00418520        report_errorf("Landscape. Cannot find Picture: in %s", &var_600)
00418730        char* searched_4 = find_case_insensitive_substring("Landscape:", searched)
00418738        cursor = searched_4
0041873e        if (searched_4 != 0)
00418768        char* cursor_2 = &find_case_insensitive_substring(":", searched_4)[1]
00418769        cursor = cursor_2
0041876d        char i_3 = *cursor_2
00418774        if (i_3 == 0x20 || i_3 s< 0x20)
004187d5        manager->scripts[manager->script_count].object_index = 0xffffffff
00418779        char mesh_name[0x200]
00418779        char (* ecx_21)[0x200] = &mesh_name
00418780        while (i_3 != 0x2e)
00418782        *ecx_21 = i_3
00418784        ecx_21 = &(*ecx_21)[1]
00418785        cursor_2 = &cursor_2[1]
00418786        cursor = cursor_2
0041878a        i_3 = *cursor_2
00418791        struct GameRoot* game_base_1 = g_game_base
00418796        *ecx_21 = 0x2e
004187a2        (*ecx_21)[1] = 0x78
004187a5        (*ecx_21)[2] = 0
004187c0        manager->scripts[manager->script_count].object_index = load_or_reuse_cached_x_mesh(&game_base_1->directx_loader, &mesh_name)
0041874d        report_errorf("Landscape. Cannot find Landscape: in %s", &var_600)
004187e6        char* searched_5 = find_case_insensitive_substring("Distort:", searched)
004187ee        cursor = searched_5
004187f4        if (searched_5 != 0)
0041881e        cursor = &find_case_insensitive_substring(":", searched_5)[1]
00418836        manager->scripts[manager->script_count].distort = fconvert.s(parse_next_float32(&cursor))
00418803        report_errorf("Landscape. Cannot find Distort: in %s", &var_600)
0041884a        manager->script_count += 1
00418869        return manager->script_count - 1
