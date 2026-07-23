/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_x_animation_clip @ 0x405d60 */

00405d6a        char* mesh_name_1 = mesh_name
00405d81        char path_pattern[0x100]
00405d81        sprintf(&path_pattern, "%s", mesh_name_1)
00405d9a        char* cursor = &path_pattern
00405da3        char* cursor_1 = &find_case_insensitive_substring("-", &path_pattern)[1]
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
00405e1f        int32_t keyframe_count
00405e1f        enumerate_matching_archive_or_fs_entries("X", &path_pattern, &keyframe_count, &data_4b2f50)
00405e31        struct XAnimationKeyframe* allocated_keyframes = allocate_tracked_memory(keyframe_count << 7, "Anim Key frame bods")
00405e36        int32_t loop_keyframe_count = keyframe_count
00405e3d        int32_t keyframe_index = 0
00405e45        loader->duplicate_vertices.active_count = 0
00405e4f        if (loop_keyframe_count s> 0)
00405e51        char* mesh_path = &data_4b2f50
00405e56        int32_t* frame_number_cursor = &allocated_keyframes->frame_number
00405e67        set_bod_object(&frame_number_cursor[-0x1f], add_object_to_list(&g_object_list))
00405e75        load_x_mesh(loader, mesh_path, frame_number_cursor[-0x16], 0)
00405e80        cursor = mesh_path
00405e89        char* cursor_5 = &find_case_insensitive_substring("-", mesh_path)[1]
00405e90        cursor = cursor_5
00405e9a        cursor = &find_case_insensitive_substring("-", cursor_5)[1]
00405eab        *frame_number_cursor = parse_next_signed_int(&cursor)
00405ead        loop_keyframe_count = keyframe_count
00405eb1        keyframe_index += 1
00405eb2        mesh_path = &mesh_path[0x80]
00405eb8        frame_number_cursor = &frame_number_cursor[0x20]
00405ec0        do while (keyframe_index s< loop_keyframe_count)
00405ec2        mesh_name_1 = mesh_name
00405ed0        clean_duplicate_vertices(&loader->duplicate_vertices, loop_keyframe_count)
00405ee6        load_x_mesh(loader, &data_4b2f50, object, 0)
00405eed        request_object_vertices_copy(object)
00405f01        object->flags |= &data_800000
00405f09        char animation_tag[0x80]
00405f09        sprintf(&animation_tag, "Anim:%s", mesh_name_1)
00405f1b        char* animation_block = find_case_insensitive_substring(&animation_tag, loader->animation_bytes)
00405f22        float progress_step
00405f22        int32_t mode_flags
00405f22        if (animation_block == 0)
0040600a        report_errorf("Did not find Anim:%s in _Animation.txt. Using defaults", mesh_name_1)
00406016        progress_step = 0.0166666675f
0040601e        mode_flags = allocated_keyframes | 1
00405f33        char* animation_end = find_case_insensitive_substring("AnimEnd:", animation_block)
00405f3a        if (animation_end == 0)
00405f42        report_errorf("Cannot find AnimEnd: for %s \n", mesh_name_1)
00405f54        return
00405f57        char ecx_11 = *animation_end
00405f63        *animation_end = 0
00405f66        char* cursor_6 = find_case_insensitive_substring("Duration:", animation_block)
00405f6e        cursor = cursor_6
00405f74        if (cursor_6 == 0)
00405fa5        progress_step = 0.0166666675f
00405f87        cursor = &find_case_insensitive_substring(":", cursor_6)[1]
00405f9f        progress_step = fconvert.s(fconvert.t(1f) / (parse_next_float32(&cursor) * fconvert.t(60f)))
00405fb3        mode_flags = 0
00405fb5        char* cursor_7 = find_case_insensitive_substring("Mode:Loop", animation_block)
00405fbd        cursor = cursor_7
00405fc3        if (cursor_7 != 0)
00405fc5        mode_flags = 1
00405fd0        char* cursor_8 = find_case_insensitive_substring("Mode:Once", animation_block)
00405fd8        cursor = cursor_8
00405fde        if (cursor_8 != 0)
00405fe0        mode_flags |= 4
00405fe9        char* cursor_9 = find_case_insensitive_substring("Mode:Pingpong", animation_block)
00405ff1        cursor = cursor_9
00405ff7        if (cursor_9 != 0)
00405ff9        mode_flags |= 2
00406000        *animation_end = ecx_11
00406021        int32_t keyframe_count_1 = keyframe_count
00406028        if (keyframe_count_1 == 1)
0040602a        progress_step = 1f
00406040        request_object_animation(object, keyframe_count_1, allocated_keyframes, progress_step, mode_flags)
0040604f        return
