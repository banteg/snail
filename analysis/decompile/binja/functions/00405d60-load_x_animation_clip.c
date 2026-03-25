/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_x_animation_clip @ 0x405d60 */

00405d6a        int32_t edi = arg2
00405d78        int32_t var_1a8 = edi
00405d81        void var_100
00405d81        sub_48b32c(&var_100, "%s")
00405d9a        char* mesh_path_1 = &var_100
00405da3        char* mesh_path_2 = &find_case_insensitive_substring("-", &var_100)[1]
00405daa        mesh_path_1 = mesh_path_2
00405db6        char* mesh_path_3 = &find_case_insensitive_substring("-", mesh_path_2)[1]
00405db7        mesh_path_1 = mesh_path_3
00405dbb        *mesh_path_3 = 0x2a
00405dc2        char* mesh_path_4 = &mesh_path_1[1]
00405dc3        mesh_path_1 = mesh_path_4
00405dc7        *mesh_path_4 = 0x2e
00405dce        char* mesh_path_5 = &mesh_path_1[1]
00405dcf        mesh_path_1 = mesh_path_5
00405dd3        *mesh_path_5 = 0x78
00405ddb        mesh_path_1 = &mesh_path_1[1]
00405de6        if (is_archive_index_loaded() != 0)
00405dec        *mesh_path_1 = 0x32
00405df4        mesh_path_1 = &mesh_path_1[1]
00405e08        *mesh_path_1 = 0
00405e10        mesh_path_1 = &mesh_path_1[1]
00405e1f        int32_t var_188
00405e1f        enumerate_matching_archive_or_fs_entries("X", &var_100, &var_188, &data_4b2f50)
00405e31        void* eax_8 = allocate_tracked_memory(var_188 << 7, "Anim Key frame bods")
00405e36        int32_t ecx_3 = var_188
00405e3d        int32_t ebp = 0
00405e45        arg1[0x1782] = 0
00405e4f        if (ecx_3 s> 0)
00405e51        char* mesh_path = &data_4b2f50
00405e56        int32_t* edi_1 = eax_8 + 0x7c
00405e67        set_bod_object(&edi_1[-0x1f], add_object_to_list(0x4b7648))
00405e75        load_x_mesh(mesh_path, edi_1[-0x16], 0)
00405e80        mesh_path_1 = mesh_path
00405e89        char* mesh_path_6 = &find_case_insensitive_substring("-", mesh_path)[1]
00405e90        mesh_path_1 = mesh_path_6
00405e9a        mesh_path_1 = &find_case_insensitive_substring("-", mesh_path_6)[1]
00405eab        *edi_1 = sub_44e710(&mesh_path_1)
00405ead        ecx_3 = var_188
00405eb1        ebp += 1
00405eb2        mesh_path = &mesh_path[0x80]
00405eb8        edi_1 = &edi_1[0x20]
00405ec0        do while (ebp s< ecx_3)
00405ec2        edi = arg2
00405ec9        int32_t var_1a8_3 = ecx_3
00405ed0        clean_duplicate_vertices(&arg1[0x1782])
00405ee6        load_x_mesh(&data_4b2f50, arg3, 0)
00405eed        request_object_vertices_copy(arg3)
00405ef5        int32_t var_1a8_4 = edi
00405f01        arg3->flags |= 0x800000
00405f09        void var_180
00405f09        sub_48b32c(&var_180, "Anim:%s")
00405f16        char* eax_14 = find_case_insensitive_substring(&var_180, *arg1)
00405f22        float var_18c
00405f22        int32_t edi_2
00405f22        if (eax_14 == 0)
00406004        int32_t var_1a8_12 = edi
0040600a        report_errorf("Did not find Anim:%s in _Animation.txt. Using defaults")
00406016        var_18c = 0.0166666675f
0040601e        edi_2 = eax_8 | 1
00405f2e        char* eax_15 = find_case_insensitive_substring("AnimEnd:", eax_14)
00405f3a        if (eax_15 == 0)
00405f3c        int32_t var_1a8_6 = edi
00405f42        report_errorf("Cannot find AnimEnd: for %s \n")
00405f54        return 0
00405f57        char ecx_11 = *eax_15
00405f63        *eax_15 = 0
00405f66        char* mesh_path_7 = find_case_insensitive_substring("Duration:", eax_14)
00405f6e        mesh_path_1 = mesh_path_7
00405f74        if (mesh_path_7 == 0)
00405fa5        var_18c = 0.0166666675f
00405f87        mesh_path_1 = &find_case_insensitive_substring(":", mesh_path_7)[1]
00405f9f        var_18c = fconvert.s(fconvert.t(1f) / (parse_next_float32(&mesh_path_1) * fconvert.t(60f)))
00405fb3        edi_2 = 0
00405fb5        char* mesh_path_8 = find_case_insensitive_substring("Mode:Loop", eax_14)
00405fbd        mesh_path_1 = mesh_path_8
00405fc3        if (mesh_path_8 != 0)
00405fc5        edi_2 = 1
00405fd0        char* mesh_path_9 = find_case_insensitive_substring("Mode:Once", eax_14)
00405fd8        mesh_path_1 = mesh_path_9
00405fde        if (mesh_path_9 != 0)
00405fe0        edi_2 |= 4
00405fe9        char* mesh_path_10 = find_case_insensitive_substring("Mode:Pingpong", eax_14)
00405ff1        mesh_path_1 = mesh_path_10
00405ff7        if (mesh_path_10 != 0)
00405ff9        edi_2 |= 2
00405ffc        mesh_path_10.b = ecx_11
00406000        *eax_15 = mesh_path_10.b
00406021        int32_t eax_18 = var_188
00406028        if (eax_18 == 1)
0040602a        var_18c = 1f
0040604f        return request_object_animation(arg3, eax_18, eax_8, var_18c, edi_2.w)
