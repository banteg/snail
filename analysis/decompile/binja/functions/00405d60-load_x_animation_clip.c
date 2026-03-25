/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_x_animation_clip @ 0x405d60 */

00405d6a        int32_t edi = arg2
00405d78        int32_t var_1a8 = edi
00405d81        void var_100
00405d81        sub_48b32c(&var_100, "%s")
00405d9a        char* var_194 = &var_100
00405da3        char* eax_1 = &find_case_insensitive_substring("-", &var_100)[1]
00405daa        var_194 = eax_1
00405db6        char* eax_3 = &find_case_insensitive_substring("-", eax_1)[1]
00405db7        var_194 = eax_3
00405dbb        *eax_3 = 0x2a
00405dc2        char* eax_5 = &var_194[1]
00405dc3        var_194 = eax_5
00405dc7        *eax_5 = 0x2e
00405dce        char* eax_7 = &var_194[1]
00405dcf        var_194 = eax_7
00405dd3        *eax_7 = 0x78
00405ddb        var_194 = &var_194[1]
00405de6        if (is_archive_index_loaded() != 0)
00405dec        *var_194 = 0x32
00405df4        var_194 = &var_194[1]
00405e08        *var_194 = 0
00405e10        var_194 = &var_194[1]
00405e1f        int32_t var_188
00405e1f        enumerate_matching_archive_or_fs_entries("X", &var_100, &var_188, &data_4b2f50)
00405e31        void* eax_12 = allocate_tracked_memory(var_188 << 7, "Anim Key frame bods")
00405e36        int32_t ecx_3 = var_188
00405e3d        int32_t ebp = 0
00405e45        arg1[0x1782] = 0
00405e4f        if (ecx_3 s> 0)
00405e51        char* esi_1 = &data_4b2f50
00405e56        int32_t* edi_1 = eax_12 + 0x7c
00405e67        set_bod_object(&edi_1[-0x1f], add_object_to_list(0x4b7648))
00405e75        load_x_mesh(esi_1, edi_1[-0x16], 0)
00405e80        var_194 = esi_1
00405e89        char* eax_15 = &find_case_insensitive_substring("-", esi_1)[1]
00405e90        var_194 = eax_15
00405e9a        var_194 = &find_case_insensitive_substring("-", eax_15)[1]
00405eab        *edi_1 = sub_44e710(&var_194)
00405ead        ecx_3 = var_188
00405eb1        ebp += 1
00405eb2        esi_1 = &esi_1[0x80]
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
00405f16        char* eax_19 = find_case_insensitive_substring(&var_180, *arg1)
00405f22        float var_18c
00405f22        int32_t edi_2
00405f22        if (eax_19 == 0)
00406004        int32_t var_1a8_12 = edi
0040600a        report_errorf("Did not find Anim:%s in _Animation.txt. Using defaults")
00406016        var_18c = 0.0166666675f
0040601e        edi_2 = eax_12 | 1
00405f2e        char* eax_20 = find_case_insensitive_substring("AnimEnd:", eax_19)
00405f3a        if (eax_20 == 0)
00405f3c        int32_t var_1a8_6 = edi
00405f42        report_errorf("Cannot find AnimEnd: for %s \n")
00405f54        return 0
00405f57        char ecx_11 = *eax_20
00405f63        *eax_20 = 0
00405f66        char* eax_21 = find_case_insensitive_substring("Duration:", eax_19)
00405f6e        var_194 = eax_21
00405f74        if (eax_21 == 0)
00405fa5        var_18c = 0.0166666675f
00405f87        var_194 = &find_case_insensitive_substring(":", eax_21)[1]
00405f9f        var_18c = fconvert.s(fconvert.t(1f) / (parse_next_float32(&var_194) * fconvert.t(60f)))
00405fb3        edi_2 = 0
00405fb5        char* eax_24 = find_case_insensitive_substring("Mode:Loop", eax_19)
00405fbd        var_194 = eax_24
00405fc3        if (eax_24 != 0)
00405fc5        edi_2 = 1
00405fd0        char* eax_25 = find_case_insensitive_substring("Mode:Once", eax_19)
00405fd8        var_194 = eax_25
00405fde        if (eax_25 != 0)
00405fe0        edi_2 |= 4
00405fe9        char* eax_26 = find_case_insensitive_substring("Mode:Pingpong", eax_19)
00405ff1        var_194 = eax_26
00405ff7        if (eax_26 != 0)
00405ff9        edi_2 |= 2
00405ffc        eax_26.b = ecx_11
00406000        *eax_20 = eax_26.b
00406021        int32_t eax_27 = var_188
00406028        if (eax_27 == 1)
0040602a        var_18c = 1f
0040604f        return request_object_animation(arg3, eax_27, eax_12, var_18c, edi_2.w)
