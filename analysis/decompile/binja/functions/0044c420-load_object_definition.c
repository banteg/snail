/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_object_definition @ 0x44c420 */

0044c429        char* buffer = get_archive_data_base()
0044c445        char var_100[0x100]
0044c445        sprintf(&var_100, "%s/_Object.txt", arg1)
0044c458        int32_t out_size
0044c458        load_file_bytes_from_archive_or_fs(&var_100, buffer, &out_size)
0044c461        int32_t facequad_count = 0
0044c463        char* result = buffer
0044c468        buffer[out_size - 2] = 0
0044c46d        char out = 0
0044c471        char* var_238 = result
0044c477        int32_t vertex_count = 0
0044c479        int32_t facequad_count_1 = 0
0044c47f        int32_t vertex_count_1 = 0
0044c483        if (*buffer != 0)
0044c491        char ecx_1 = *result
0044c496        if (ecx_1 == 0x2a)
0044c857        result = &result[1]
0044c858        var_238 = result
0044c85f        do while (*result != 0xa)
0044c861        result = &result[1]
0044c862        var_238 = result
0044c49f        if (ecx_1 != 0x5b)
0044c837        skip_to_next_line(&var_238)
0044c4b5        char* cursor
0044c4b5        if (strings_equal_case_insensitive(result, "[VERTEX START]") == 0)
0044c5cc        if (strings_equal_case_insensitive(var_238, "[FACEQUAD START]") != 0)
0044c5d7        skip_to_next_line(&var_238)
0044c5dc        char* cursor_2 = var_238
0044c5e6        cursor = cursor_2
0044c5f4        if (strings_equal_case_insensitive(cursor_2, "[FACEQUAD END]") == 0)
0044c615        bool i
0044c5fa        facequad_count += 1
0044c5fc        skip_to_next_line(&cursor)
0044c60b        i = strings_equal_case_insensitive(cursor, "[FACEQUAD END]")
0044c615        do while (i == 0)
0044c617        facequad_count_1 = facequad_count
0044c61e        request_object_facequads(arg2, facequad_count)
0044c637        if (strings_equal_case_insensitive(var_238, "[FACEQUAD END]") == 0)
0044c824        bool i_1
0044c646        cursor = var_238
0044c64a        int32_t eax_12 = parse_next_int32(&cursor)
0044c656        int16_t eax_13 = parse_next_int32(&cursor)
0044c662        int16_t eax_14 = parse_next_int32(&cursor)
0044c66e        int16_t eax_15 = parse_next_int32(&cursor)
0044c67c        int16_t eax_16 = parse_next_int32(&cursor)
0044c68f        float var_230_2 = fconvert.s(parse_next_float32(&cursor))
0044c69d        float var_220_1 = fconvert.s(parse_next_float32(&cursor))
0044c6ab        float var_214_1 = fconvert.s(parse_next_float32(&cursor))
0044c6b9        float var_208_1 = fconvert.s(parse_next_float32(&cursor))
0044c6c7        float var_20c_1 = fconvert.s(parse_next_float32(&cursor))
0044c6d5        float var_21c_1 = fconvert.s(parse_next_float32(&cursor))
0044c6e3        float var_218_1 = fconvert.s(parse_next_float32(&cursor))
0044c6f1        float var_210_1 = fconvert.s(parse_next_float32(&cursor))
0044c702        char** eax_17
0044c702        int32_t edx_5
0044c702        eax_17, edx_5 = parse_next_space_delimited_token(&cursor, &out)
0044c714        append_c_string(eax_17, edx_5, &out, &out, ".tga")
0044c72c        void texture_path
0044c72c        char* eax_18
0044c72c        int32_t edx_7
0044c72c        eax_18, edx_7 = copy_c_string(&texture_path, arg1)
0044c750        append_c_string(&texture_path, &out, append_c_string(eax_18, edx_7, &texture_path, &texture_path, "/"), &texture_path, &out)
0044c777        arg2->facequads[eax_12].texture_ref = get_or_create_texture_ref(&g_texture_refs, &texture_path, nullptr, 0)
0044c780        skip_to_next_line(&var_238)
0044c791        arg2->facequads[eax_12]..header_word = 0
0044c79a        arg2->facequads[eax_12].vertex_0 = eax_13
0044c7a7        arg2->facequads[eax_12].vertex_1 = eax_14
0044c7af        arg2->facequads[eax_12].vertex_2 = eax_15
0044c7bc        arg2->facequads[eax_12].vertex_3 = eax_16
0044c7c4        arg2->facequads[eax_12].uv[0].u = fconvert.s(fconvert.t(var_230_2))
0044c7cf        arg2->facequads[eax_12].uv[0].v = fconvert.s(fconvert.t(var_220_1))
0044c7da        arg2->facequads[eax_12].uv[1].u = fconvert.s(fconvert.t(var_214_1))
0044c7e5        arg2->facequads[eax_12].uv[1].v = fconvert.s(fconvert.t(var_208_1))
0044c7f0        arg2->facequads[eax_12].uv[2].u = fconvert.s(fconvert.t(var_20c_1))
0044c7fb        arg2->facequads[eax_12].uv[2].v = fconvert.s(fconvert.t(var_21c_1))
0044c806        arg2->facequads[eax_12].uv[3].u = fconvert.s(fconvert.t(var_218_1))
0044c811        arg2->facequads[eax_12].uv[3].v = fconvert.s(fconvert.t(var_210_1))
0044c81a        i_1 = strings_equal_case_insensitive(var_238, "[FACEQUAD END]")
0044c824        do while (i_1 == 0)
0044c82a        facequad_count = facequad_count_1
0044c82e        vertex_count = vertex_count_1
0044c837        skip_to_next_line(&var_238)
0044c4c0        skip_to_next_line(&var_238)
0044c4c5        char* cursor_1 = var_238
0044c4cf        cursor = cursor_1
0044c4dd        if (strings_equal_case_insensitive(cursor_1, "[VERTEX END]") == 0)
0044c4fe        bool i_2
0044c4e3        vertex_count += 1
0044c4e5        skip_to_next_line(&cursor)
0044c4f4        i_2 = strings_equal_case_insensitive(cursor, "[VERTEX END]")
0044c4fe        do while (i_2 == 0)
0044c500        vertex_count_1 = vertex_count
0044c507        request_object_vertices(arg2, vertex_count)
0044c520        if (strings_equal_case_insensitive(var_238, "[VERTEX END]") == 0)
0044c5a8        bool i_3
0044c52f        cursor = var_238
0044c533        int32_t eax_5 = parse_next_int32(&cursor)
0044c544        float var_230_1 = fconvert.s(parse_next_float32(&cursor))
0044c552        float var_22c_1 = fconvert.s(parse_next_float32(&cursor))
0044c560        float var_234_1 = fconvert.s(parse_next_float32(&cursor))
0044c569        skip_to_next_line(&var_238)
0044c580        arg2->vertices[eax_5 * 3] = fconvert.s(fconvert.t(var_230_1))
0044c58a        arg2->vertices[eax_5].y = fconvert.s(fconvert.t(var_22c_1))
0044c595        arg2->vertices[eax_5].z = fconvert.s(fconvert.t(var_234_1))
0044c59e        i_3 = strings_equal_case_insensitive(var_238, "[VERTEX END]")
0044c5a8        do while (i_3 == 0)
0044c837        skip_to_next_line(&var_238)
0044c83f        result = var_238
0044c846        do while (*result != 0)
0044c856        return result
