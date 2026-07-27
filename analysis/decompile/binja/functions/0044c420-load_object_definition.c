/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_object_definition @ 0x44c420 */

0044c429        char* buffer = get_archive_data_base()
0044c445        char object_file_path[0x100]
0044c445        sprintf(&object_file_path, "%s/_Object.txt", path)
0044c458        int32_t byte_count
0044c458        load_file_bytes_from_archive_or_fs(&object_file_path, buffer, &byte_count)
0044c461        int32_t facequad_count = 0
0044c463        char* left = buffer
0044c468        buffer[byte_count - 2] = 0
0044c46d        char texture_name[0x80]
0044c46d        texture_name[0] = 0
0044c471        char* cursor = left
0044c477        int32_t vertex_count = 0
0044c479        int32_t facequad_count_1 = 0
0044c47f        int32_t vertex_count_1 = 0
0044c483        if (*buffer == 0)
0044c483        return
0044c491        char ecx_1 = *left
0044c496        if (ecx_1 == 0x2a)
0044c857        left = &left[1]
0044c858        cursor = left
0044c85f        do while (*left != 0xa)
0044c861        left = &left[1]
0044c862        cursor = left
0044c49f        if (ecx_1 != 0x5b)
0044c837        skip_to_next_line(&cursor)
0044c4b5        char* line_cursor
0044c4b5        if (strings_equal_case_insensitive(left, "[VERTEX START]") == 0)
0044c5cc        if (strings_equal_case_insensitive(cursor, "[FACEQUAD START]") != 0)
0044c5d7        skip_to_next_line(&cursor)
0044c5dc        char* left_2 = cursor
0044c5e6        line_cursor = left_2
0044c5f4        if (strings_equal_case_insensitive(left_2, "[FACEQUAD END]") == 0)
0044c615        bool i
0044c5fa        facequad_count += 1
0044c5fc        skip_to_next_line(&line_cursor)
0044c60b        i = strings_equal_case_insensitive(line_cursor, "[FACEQUAD END]")
0044c615        do while (i == 0)
0044c617        facequad_count_1 = facequad_count
0044c61e        request_object_facequads(object, facequad_count)
0044c637        if (strings_equal_case_insensitive(cursor, "[FACEQUAD END]") == 0)
0044c824        bool i_1
0044c646        line_cursor = cursor
0044c64a        int32_t eax_12 = parse_next_int32(&line_cursor)
0044c656        int16_t eax_13 = parse_next_int32(&line_cursor)
0044c662        int16_t eax_14 = parse_next_int32(&line_cursor)
0044c66e        int16_t eax_15 = parse_next_int32(&line_cursor)
0044c67c        int16_t eax_16 = parse_next_int32(&line_cursor)
0044c68f        float var_230_2 = fconvert.s(parse_next_float32(&line_cursor))
0044c69d        float var_220_1 = fconvert.s(parse_next_float32(&line_cursor))
0044c6ab        float var_214_1 = fconvert.s(parse_next_float32(&line_cursor))
0044c6b9        float var_208_1 = fconvert.s(parse_next_float32(&line_cursor))
0044c6c7        float var_20c_1 = fconvert.s(parse_next_float32(&line_cursor))
0044c6d5        float var_21c_1 = fconvert.s(parse_next_float32(&line_cursor))
0044c6e3        float var_218_1 = fconvert.s(parse_next_float32(&line_cursor))
0044c6f1        float var_210_1 = fconvert.s(parse_next_float32(&line_cursor))
0044c702        parse_next_space_delimited_token(&line_cursor, &texture_name)
0044c714        append_c_string(&texture_name, ".tga")
0044c72c        char texture_path[0x80]
0044c72c        copy_c_string(&texture_path, path)
0044c73e        append_c_string(&texture_path, "/")
0044c750        append_c_string(&texture_path, &texture_name)
0044c777        object->facequads[eax_12].texture_ref = get_or_create_texture_ref(&g_texture_refs, &texture_path, nullptr, 0)
0044c780        skip_to_next_line(&cursor)
0044c791        object->facequads[eax_12]..header_word = 0
0044c79a        object->facequads[eax_12].vertex_0 = eax_13
0044c7a7        object->facequads[eax_12].vertex_1 = eax_14
0044c7af        object->facequads[eax_12].vertex_2 = eax_15
0044c7bc        object->facequads[eax_12].vertex_3 = eax_16
0044c7c4        object->facequads[eax_12].uv[0].u = fconvert.s(fconvert.t(var_230_2))
0044c7cf        object->facequads[eax_12].uv[0].v = fconvert.s(fconvert.t(var_220_1))
0044c7da        object->facequads[eax_12].uv[1].u = fconvert.s(fconvert.t(var_214_1))
0044c7e5        object->facequads[eax_12].uv[1].v = fconvert.s(fconvert.t(var_208_1))
0044c7f0        object->facequads[eax_12].uv[2].u = fconvert.s(fconvert.t(var_20c_1))
0044c7fb        object->facequads[eax_12].uv[2].v = fconvert.s(fconvert.t(var_21c_1))
0044c806        object->facequads[eax_12].uv[3].u = fconvert.s(fconvert.t(var_218_1))
0044c811        object->facequads[eax_12].uv[3].v = fconvert.s(fconvert.t(var_210_1))
0044c81a        i_1 = strings_equal_case_insensitive(cursor, "[FACEQUAD END]")
0044c824        do while (i_1 == 0)
0044c82a        facequad_count = facequad_count_1
0044c82e        vertex_count = vertex_count_1
0044c837        skip_to_next_line(&cursor)
0044c4c0        skip_to_next_line(&cursor)
0044c4c5        char* left_1 = cursor
0044c4cf        line_cursor = left_1
0044c4dd        if (strings_equal_case_insensitive(left_1, "[VERTEX END]") == 0)
0044c4fe        bool i_2
0044c4e3        vertex_count += 1
0044c4e5        skip_to_next_line(&line_cursor)
0044c4f4        i_2 = strings_equal_case_insensitive(line_cursor, "[VERTEX END]")
0044c4fe        do while (i_2 == 0)
0044c500        vertex_count_1 = vertex_count
0044c507        request_object_vertices(object, vertex_count)
0044c520        if (strings_equal_case_insensitive(cursor, "[VERTEX END]") == 0)
0044c5a8        bool i_3
0044c52f        line_cursor = cursor
0044c533        int32_t eax_5 = parse_next_int32(&line_cursor)
0044c544        float var_230_1 = fconvert.s(parse_next_float32(&line_cursor))
0044c552        float var_22c_1 = fconvert.s(parse_next_float32(&line_cursor))
0044c560        float var_234_1 = fconvert.s(parse_next_float32(&line_cursor))
0044c569        skip_to_next_line(&cursor)
0044c580        object->vertices[eax_5].x = fconvert.s(fconvert.t(var_230_1))
0044c58a        object->vertices[eax_5].y = fconvert.s(fconvert.t(var_22c_1))
0044c595        object->vertices[eax_5].z = fconvert.s(fconvert.t(var_234_1))
0044c59e        i_3 = strings_equal_case_insensitive(cursor, "[VERTEX END]")
0044c5a8        do while (i_3 == 0)
0044c837        skip_to_next_line(&cursor)
0044c83f        left = cursor
0044c846        do while (*left != 0)
0044c856        return
