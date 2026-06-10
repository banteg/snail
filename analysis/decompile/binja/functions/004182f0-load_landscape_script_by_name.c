/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_landscape_script_by_name @ 0x4182f0 */

004182fe        char* ebx = arg2
00418308        char* var_71c = ebx
00418311        char var_600[0x200]
00418311        sub_48b32c(&var_600, "Backgrounds/%s")
0041831f        int32_t i = 0
00418323        if (*(arg1 + 0x5a0) s> 0)
00418325        char* ebp_1 = arg1 + 0x5a8
00418337        if (sub_44e6c0(ebp_1, ebx) != 0)
00418392        return i
0041833f        i += 1
00418340        ebp_1 = &ebp_1[0x124]
00418348        do while (i s< *(arg1 + 0x5a0))
00418354        char* eax_3 = load_file_bytes(&var_600, nullptr)
00418360        if (eax_3 == 0)
0041836f        report_errorf("Landscape.Cannot load %s", &var_600)
00418383        return 0
004183aa        rstrcpy_checked_ascii(arg1 + *(arg1 + 0x5a0) * 0x124 + 0x5a8, ebx)
004183b5        char* cursor_1 = find_case_insensitive_substring("ID:", eax_3)
004183bd        char* cursor = cursor_1
004183c3        if (cursor_1 != 0)
00418402        cursor = find_case_insensitive_substring(":", cursor_1)
0041841b        *(arg1 + *(arg1 + 0x5a0) * 0x124 + 0x5a4) = parse_next_signed_int(&cursor)
004183d2        report_errorf("Landscape. Cannot find ID: %s", &var_600)
004183e6        *(arg1 + *(arg1 + 0x5a0) * 0x124 + 0x5a4) = 0
00418428        char* cursor_2 = find_case_insensitive_substring("Fog:", eax_3)
00418430        cursor = cursor_2
00418436        if (cursor_2 != 0)
00418475        cursor = find_case_insensitive_substring(":", cursor_2)
004184a2        *(arg1 + *(arg1 + 0x5a0) * 0x124 + 0x6b4) = fconvert.s(float.t(parse_next_signed_int(&cursor)) * fconvert.t(0.00392156886f))
004184cd        *(arg1 + *(arg1 + 0x5a0) * 0x124 + 0x6b8) = fconvert.s(float.t(parse_next_signed_int(&cursor)) * fconvert.t(0.00392156886f))
004184f6        *(arg1 + *(arg1 + 0x5a0) * 0x124 + 0x6bc) = fconvert.s(float.t(parse_next_signed_int(&cursor)) * fconvert.t(0.00392156886f))
00418445        report_errorf("Landscape. Cannot find Fog: %s", &var_600)
00418460        set_color_black()
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
0041855a        int32_t eax_21 = *(arg1 + 0x5a0)
00418560        *edx_7 = 0
0041856d        void* var_71c_12 = &var_400
0041857e        sub_48b32c(arg1 + eax_21 * 0x124 + 0x62d, "Backgrounds/%s.tga")
00418583        int32_t eax_23 = *(arg1 + 0x5a0)
00418595        *(arg1 + eax_23 * 0x124 + 0x628) = eax_23 * 2 + 6
004185b8        bool cond:0_1 = archive_or_file_exists(arg1 + *(arg1 + 0x5a0) * 0x124 + 0x62d, 0) == 0
004185c3        int32_t edx_11 = *(arg1 + 0x5a0) * 0x49
004185c6        if (cond:0_1)
00418601        *(arg1 + (edx_11 << 2) + 0x62c) = 1
00418625        char var_680
00418625        rstrcpy_checked_ascii(&var_680, arg1 + *(arg1 + 0x5a0) * 0x124 + 0x62d)
00418643        char var_700
00418643        rstrcpy_checked_ascii(&var_700, arg1 + *(arg1 + 0x5a0) * 0x124 + 0x62d)
00418655        char* eax_37 = &var_680
0041865c        if (var_680 != 0x2e)
00418665        char i_2
0041865e        i_2 = eax_37[1]
00418661        eax_37 = &eax_37[1]
00418665        do while (i_2 != 0x2e)
00418667        bool cond:2_1 = var_700 == 0x2e
00418672        __builtin_strncpy(eax_37, "_A.tga", 7)
0041868a        char* eax_38 = &var_700
0041868e        if (not(cond:2_1))
00418690        eax_38 = &eax_38[1]
00418694        do while (*eax_38 != 0x2e)
00418696        __builtin_strncpy(eax_38, "_B.tga", 7)
004186d4        register_sprite_texture(&var_680, *(arg1 + *(arg1 + 0x5a0) * 0x124 + 0x628), 0x400)
004186fd        register_sprite_texture(&var_700, *(arg1 + *(arg1 + 0x5a0) * 0x124 + 0x628) + 1, 0x400)
00418702        ebx = arg2
004185e3        register_sprite_texture(arg1 + (edx_11 << 2) + 0x62d, *(arg1 + (edx_11 << 2) + 0x628), 0x400)
004185f4        *(arg1 + *(arg1 + 0x5a0) * 0x124 + 0x62c) = 0
0041871c        void* var_71c_14 = arg1 + *(arg1 + 0x5a0) * 0x124 + 0x62d
0041871d        char* var_720_8 = "Loading backdrop texture %s"
00418520        report_errorf("Landscape. Cannot find Picture: in %s", &var_600)
00418730        char* cursor_5 = find_case_insensitive_substring("Landscape:", eax_3)
00418738        cursor = cursor_5
0041873e        if (cursor_5 != 0)
00418768        char* cursor_6 = &find_case_insensitive_substring(":", cursor_5)[1]
00418769        cursor = cursor_6
0041876d        char i_3 = *cursor_6
00418774        if (i_3 == 0x20 || i_3 s< 0x20)
004187d5        *(arg1 + *(arg1 + 0x5a0) * 0x124 + 0x6b0) = 0xffffffff
00418779        void var_200
00418779        char* ecx_22 = &var_200
00418780        while (i_3 != 0x2e)
00418782        *ecx_22 = i_3
00418784        ecx_22 = &ecx_22[1]
00418785        cursor_6 = &cursor_6[1]
00418786        cursor = cursor_6
0041878a        i_3 = *cursor_6
00418791        void* eax_46 = data_4df904
00418796        *ecx_22 = 0x2e
004187a2        ecx_22[1] = 0x78
004187a5        ecx_22[2] = 0
004187c0        *(arg1 + *(arg1 + 0x5a0) * 0x124 + 0x6b0) = load_or_reuse_cached_x_mesh(eax_46 + 0x48e00, &var_200)
0041874d        report_errorf("Landscape. Cannot find Landscape: in %s", &var_600)
004187e6        char* cursor_7 = find_case_insensitive_substring("Distort:", eax_3)
004187ee        cursor = cursor_7
004187f4        if (cursor_7 != 0)
0041881e        cursor = &find_case_insensitive_substring(":", cursor_7)[1]
00418822        parse_next_float32(&cursor)
00418822        unimplemented  {call 0x431f20}
00418836        *(arg1 + *(arg1 + 0x5a0) * 0x124 + 0x6c4) = fconvert.s(unimplemented  {fstp dword [esi+edx*4+0x6c4], st0})
00418836        unimplemented  {fstp dword [esi+edx*4+0x6c4], st0}
00418803        report_errorf("Landscape. Cannot find Distort: in %s", &var_600)
00418843        char* var_71c_22 = ebx
00418845        char* var_720_9 = "Landscape: %s imported\n"
0041884a        *(arg1 + 0x5a0) += 1
00418869        return *(arg1 + 0x5a0) - 1
