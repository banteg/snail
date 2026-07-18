/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_landscape_script_by_name @ 0x4182f0 */

00418308        char* script_name_1 = script_name
00418311        void path
00418311        sprintf(&path, "Backgrounds/%s")
0041831f        int32_t i = 0
00418323        if (manager->script_count s> 0)
00418325        char (* ebp_1)[0x80] = &manager->scripts[0].name
00418337        if (strings_equal_case_insensitive_path(ebp_1, script_name) != 0)
00418392        return i
0041833f        i += 1
00418340        ebp_1 = &(*ebp_1)[0x124]
00418348        do while (i s< manager->script_count)
00418354        void* eax_3 = load_file_bytes(&path, nullptr)
00418360        if (eax_3 == 0)
0041836f        report_errorf("Landscape.Cannot load %s", &path)
00418383        return 0
004183aa        rstrcpy_checked_ascii(&manager->scripts[manager->script_count].name, script_name)
004183b5        char* cursor_1 = find_case_insensitive_substring("ID:", eax_3)
004183bd        char* cursor = cursor_1
004183c3        if (cursor_1 != 0)
00418402        cursor = find_case_insensitive_substring(":", cursor_1)
0041841b        manager->scripts[manager->script_count].id = parse_next_signed_int(&cursor)
004183d2        report_errorf("Landscape. Cannot find ID: %s", &path)
004183e6        manager->scripts[manager->script_count].id = 0
00418428        char* cursor_2 = find_case_insensitive_substring("Fog:", eax_3)
00418430        cursor = cursor_2
00418436        if (cursor_2 != 0)
00418475        cursor = find_case_insensitive_substring(":", cursor_2)
004184a2        manager->scripts[manager->script_count].fog_color.r = fconvert.s(float.t(parse_next_signed_int(&cursor)) * fconvert.t(0.00392156886f))
004184cd        manager->scripts[manager->script_count].fog_color.g = fconvert.s(float.t(parse_next_signed_int(&cursor)) * fconvert.t(0.00392156886f))
004184f6        manager->scripts[manager->script_count].fog_color.b = fconvert.s(float.t(parse_next_signed_int(&cursor)) * fconvert.t(0.00392156886f))
00418445        report_errorf("Landscape. Cannot find Fog: %s", &path)
00418460        set_color_black(&manager->scripts[manager->script_count].fog_color)
00418503        char* cursor_3 = find_case_insensitive_substring("Picture:", eax_3)
0041850b        cursor = cursor_3
00418511        if (cursor_3 != 0)
00418538        char* cursor_4 = &find_case_insensitive_substring(":", cursor_3)[1]
00418539        cursor = cursor_4
0041853d        void var_400
0041853d        char* edx_7 = &var_400
00418544        char i_1 = *cursor_4
00418549        while (i_1 != 0x2e)
0041854b        *edx_7 = i_1
0041854d        edx_7 = &edx_7[1]
0041854e        cursor_4 = &cursor_4[1]
0041854f        cursor = cursor_4
00418553        i_1 = *cursor_4
0041855a        int32_t script_count = manager->script_count
00418560        *edx_7 = 0
0041856d        void* var_71c_11 = &var_400
0041857e        sprintf(&manager->scripts[script_count].backdrop_texture_path, "Backgrounds/%s.tga")
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
00418655        char* eax_35 = &texture_path_1
0041865c        if (texture_path_1 != 0x2e)
00418665        char i_2
0041865e        i_2 = eax_35[1]
00418661        eax_35 = &eax_35[1]
00418665        do while (i_2 != 0x2e)
00418667        bool cond:2_1 = texture_path == 0x2e
00418672        __builtin_strncpy(eax_35, "_A.tga", 7)
0041868a        char* eax_36 = &texture_path
0041868e        if (not(cond:2_1))
00418690        eax_36 = &eax_36[1]
00418694        do while (*eax_36 != 0x2e)
00418696        __builtin_strncpy(eax_36, "_B.tga", 7)
004186d4        register_sprite_texture(&texture_path_1, manager->scripts[manager->script_count].backdrop_texture_id, 0x400)
004186fd        register_sprite_texture(&texture_path, manager->scripts[manager->script_count].backdrop_texture_id + 1, 0x400)
004185e3        register_sprite_texture(&manager->scripts[0].backdrop_texture_path[edx_11 << 2], (&manager->scripts[0].backdrop_texture_id)[edx_11], 0x400)
004185f4        manager->scripts[manager->script_count].split_backdrop_texture_pair = 0
00418709        manager->script_count
00418520        report_errorf("Landscape. Cannot find Picture: in %s", &path)
00418730        char* cursor_5 = find_case_insensitive_substring("Landscape:", eax_3)
00418738        cursor = cursor_5
0041873e        if (cursor_5 != 0)
00418768        char* cursor_6 = &find_case_insensitive_substring(":", cursor_5)[1]
00418769        cursor = cursor_6
0041876d        char i_3 = *cursor_6
00418774        if (i_3 == 0x20 || i_3 s< 0x20)
004187d5        manager->scripts[manager->script_count].object_index = 0xffffffff
00418779        char mesh_name[0x200]
00418779        char (* ecx_24)[0x200] = &mesh_name
00418780        while (i_3 != 0x2e)
00418782        *ecx_24 = i_3
00418784        ecx_24 = &(*ecx_24)[1]
00418785        cursor_6 = &cursor_6[1]
00418786        cursor = cursor_6
0041878a        i_3 = *cursor_6
00418791        struct GameRoot* game_base_1 = g_game_base
00418796        *ecx_24 = 0x2e
004187a2        (*ecx_24)[1] = 0x78
004187a5        (*ecx_24)[2] = 0
004187c0        manager->scripts[manager->script_count].object_index = load_or_reuse_cached_x_mesh(&game_base_1->directx_loader, &mesh_name)
0041874d        report_errorf("Landscape. Cannot find Landscape: in %s", &path)
004187e6        char* cursor_7 = find_case_insensitive_substring("Distort:", eax_3)
004187ee        cursor = cursor_7
004187f4        if (cursor_7 != 0)
0041881e        cursor = &find_case_insensitive_substring(":", cursor_7)[1]
00418836        manager->scripts[manager->script_count].distort = fconvert.s(parse_next_float32(&cursor))
00418803        report_errorf("Landscape. Cannot find Distort: in %s", &path)
0041884a        manager->script_count += 1
00418869        return manager->script_count - 1
