/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_x_animation_clip @ 0x405d60 */

00405d6a        char* mesh_name_1 = mesh_name
00405d78        char* mesh_name_2 = mesh_name_1
00405d81        void pattern
00405d81        sprintf(&pattern, "%s")
00405d9a        char* cursor = &pattern
00405da3        char* cursor_1 = &find_case_insensitive_substring("-", &pattern)[1]
00405daa        cursor = cursor_1
00405db6        char* cursor_2 = &find_case_insensitive_substring("-", cursor_1)[1]
00405db7        cursor = cursor_2
00405dbb        *cursor_2 = 0x2a
00405dc2        char* cursor_3 = &cursor[1]
00405dc3        cursor = cursor_3
00405dc7        *cursor_3 = 0x2e
00405dce        char* cursor_4 = &cursor[1]
00405dcf        cursor = cursor_4
00405dd3        *cursor_4 = 0x78
00405ddb        cursor = &cursor[1]
00405de6        if (is_archive_index_loaded() != 0)
00405dec        *cursor = 0x32
00405df4        cursor = &cursor[1]
00405e08        *cursor = 0
00405e10        cursor = &cursor[1]
00405e1f        int32_t out_count
00405e1f        enumerate_matching_archive_or_fs_entries("X", &pattern, &out_count, &data_4b2f50)
00405e31        struct XAnimationKeyframe* keyframes = allocate_tracked_memory(out_count << 7, "Anim Key frame bods")
00405e36        int32_t unused = out_count
00405e3d        int32_t ebp = 0
00405e45        loader->duplicate_vertices.active_count = 0
00405e4f        if (unused s> 0)
00405e51        char* mesh_path = &data_4b2f50
00405e56        int32_t* edi = &keyframes->frame_number
00405e67        set_bod_object(&edi[-0x1f], add_object_to_list(&g_object_list))
00405e75        load_x_mesh(loader, mesh_path, edi[-0x16], 0)
00405e80        cursor = mesh_path
00405e89        char* cursor_5 = &find_case_insensitive_substring("-", mesh_path)[1]
00405e90        cursor = cursor_5
00405e9a        cursor = &find_case_insensitive_substring("-", cursor_5)[1]
00405eab        *edi = parse_next_signed_int(&cursor)
00405ead        unused = out_count
00405eb1        ebp += 1
00405eb2        mesh_path = &mesh_path[0x80]
00405eb8        edi = &edi[0x20]
00405ec0        do while (ebp s< unused)
00405ec2        mesh_name_1 = mesh_name
00405ed0        clean_duplicate_vertices(&loader->duplicate_vertices, unused)
00405ee6        load_x_mesh(loader, &data_4b2f50, object, 0)
00405eed        request_object_vertices_copy(object)
00405ef5        char* mesh_name_3 = mesh_name_1
00405f01        object->flags |= &data_800000
00405f09        void var_180
00405f09        sprintf(&var_180, "Anim:%s")
00405f16        char* eax_13 = find_case_insensitive_substring(&var_180, loader->animation_bytes)
00405f22        float progress_step
00405f22        int32_t flags
00405f22        if (eax_13 == 0)
0040600a        report_errorf("Did not find Anim:%s in _Animation.txt. Using defaults", mesh_name_1)
00406016        progress_step = 0.0166666675f
0040601e        flags = keyframes | 1
00405f2e        char* eax_14 = find_case_insensitive_substring("AnimEnd:", eax_13)
00405f3a        if (eax_14 == 0)
00405f42        report_errorf("Cannot find AnimEnd: for %s \n", mesh_name_1)
00405f54        return
00405f57        char ecx_11 = *eax_14
00405f63        *eax_14 = 0
00405f66        char* cursor_6 = find_case_insensitive_substring("Duration:", eax_13)
00405f6e        cursor = cursor_6
00405f74        if (cursor_6 == 0)
00405fa5        progress_step = 0.0166666675f
00405f87        cursor = &find_case_insensitive_substring(":", cursor_6)[1]
00405f9f        progress_step = fconvert.s(fconvert.t(1f) / (parse_next_float32(&cursor) * fconvert.t(60f)))
00405fb3        flags = 0
00405fb5        char* cursor_7 = find_case_insensitive_substring("Mode:Loop", eax_13)
00405fbd        cursor = cursor_7
00405fc3        if (cursor_7 != 0)
00405fc5        flags = 1
00405fd0        char* cursor_8 = find_case_insensitive_substring("Mode:Once", eax_13)
00405fd8        cursor = cursor_8
00405fde        if (cursor_8 != 0)
00405fe0        flags |= 4
00405fe9        char* cursor_9 = find_case_insensitive_substring("Mode:Pingpong", eax_13)
00405ff1        cursor = cursor_9
00405ff7        if (cursor_9 != 0)
00405ff9        flags |= 2
00406000        *eax_14 = ecx_11
00406021        int32_t keyframe_count = out_count
00406028        if (keyframe_count == 1)
0040602a        progress_step = 1f
00406040        request_object_animation(object, keyframe_count, keyframes, progress_step, flags)
0040604f        return
