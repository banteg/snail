/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: get_or_create_texture_ref @ 0x44e810 */

0044e816        int32_t i = 0
0044e81f        if (texture_list->count == texture_list->capacity)
0044e826        report_errorf("Too many Texture References - Increase TextureList.Init(MAX) in g0.cpp")
0044e83e        if ((arg4:1.b & 8) == 0 && texture_list->count s> 0)
0044e840        char (* ebx_1)[0x80] = &texture_list->entries[0].name
0044e84f        if (strings_equal_case_insensitive(ebx_1, texture_path) != 0)
0044e8f1        return &(&texture_list->entries)[i]
0044e857        i += 1
0044e858        ebx_1 = &(*ebx_1)[0xa4]
0044e860        do while (i s< texture_list->count)
0044e870        copy_c_string(&texture_list->entries[texture_list->count].name, texture_path)
0044e875        int32_t count = texture_list->count
0044e881        texture_list->entries[count].slot_index = count
0044e890        (&texture_list->entries)[texture_list->count][0].flags = 0
0044e8a0        (&texture_list->entries)[texture_list->count][0].flags = 0x400
0044e8b4        texture_list->entries[texture_list->count].texture_ref = arg3
0044e8c3        texture_list->entries[texture_list->count].mip_levels = 1
0044e8ce        int32_t count_1 = texture_list->count
0044e8d7        texture_list->count = count_1 + 1
0044e8e0        return &(&texture_list->entries)[count_1]
