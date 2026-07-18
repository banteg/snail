/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_x_mesh @ 0x405640 */

0040564a        void* buffer = get_archive_data_base()
0040565f        char* var_250
0040565f        char* var_24c
0040565f        char path[0x100]
0040565f        if (is_archive_index_loaded() == 0)
00405688        char* mesh_path_2 = mesh_path
00405689        var_24c = "X/%s"
00405692        var_250 = &path
00405661        char* mesh_path_3 = mesh_path
00405663        int32_t i = 0xffffffff
00405668        char* mesh_path_1 = mesh_path
00405669        while (i != 0)
00405669        bool cond:0_1 = 0 != *mesh_path_3
00405669        mesh_path_3 = &mesh_path_3[1]
00405669        i -= 1
00405669        if (not(cond:0_1))
00405669        break
00405673        if (mesh_path[not.d(i) - 2] == 0x32)
00405680        var_24c = "X/%s"
00405685        var_250 = &path
00405675        var_24c = "X/%s2"
00405692        var_250 = &path
00405693        sprintf(var_250, var_24c)
004056a6        int32_t out_size
004056a6        load_file_bytes_from_archive_or_fs(&path, buffer, &out_size)
004056b5        *(out_size + buffer - 2) = 0
004056ba        char* eax_2 = find_case_insensitive_substring("Frame ", buffer)
004056ca        if (eax_2 == 0)
004056d6        report_errorf("No 'Frame ' Data in %s", &path)
004056e8        return
004056f1        char* eax_3 = find_case_insensitive_substring("Mesh ", eax_2)
004056f9        char* var_218 = eax_3
004056ff        if (eax_3 == 0)
0040570b        report_errorf("No 'VertexDuplicationIndices 'Data in %s", &path)
00405710        eax_3 = var_218
00405728        var_218 = find_case_insensitive_substring("{", eax_3)
0040572c        char* cursor_2 = find_case_insensitive_substring("Mesh ", eax_2)
00405734        char* cursor = cursor_2
0040573a        if (cursor_2 == 0)
00405746        report_errorf("No 'Mesh 'Data in %s", &path)
0040574b        cursor_2 = cursor
00405763        cursor = find_case_insensitive_substring("{", cursor_2)
00405767        char* eax_6 = find_case_insensitive_substring("MeshMaterialList ", eax_2)
0040576f        char* var_21c = eax_6
00405775        if (eax_6 == 0)
00405781        report_errorf("No 'MeshMaterialList 'Data in %s", &path)
00405786        eax_6 = var_21c
0040579c        var_21c = find_case_insensitive_substring("{", eax_6)
004057a1        parse_next_signed_int(&var_21c)
004057ab        int16_t facequad_count_3 = parse_next_signed_int(&var_21c)
004057b7        int16_t vertex_count_2 = parse_next_signed_int(&var_218)
004057c5        int32_t vertex_count = sx.d(vertex_count_2)
004057d2        if (vertex_count != parse_next_signed_int(&cursor))
004057de        report_errorf("Mesh vertices count does not match vertext duplicate vertices count in %s", &path)
004057eb        parse_next_signed_int(&var_218)
004057f6        char* cursor_3 = find_case_insensitive_substring("MeshTextureCoords ", eax_2)
004057fe        char* cursor_1 = cursor_3
00405804        if (cursor_3 == 0)
00405810        report_errorf("No 'Mesh 'Data in %s", &path)
00405815        cursor_3 = cursor_1
00405827        cursor_1 = find_case_insensitive_substring("{", cursor_3)
0040583a        if (vertex_count != parse_next_signed_int(&cursor_1))
00405846        report_errorf("Mesh texture coords number does not match mesh vertext count in %s", &path)
00405855        int32_t facequad_count = sx.d(facequad_count_3)
0040585b        int32_t facequad_count_2 = facequad_count
0040585f        request_object_facequads(object, facequad_count)
00405867        request_object_vertices(object, vertex_count)
00405879        void* pointer = allocate_tracked_memory(vertex_count << 2, "Mesh vertex remap")
0040588f        float* pointer_1 = allocate_tracked_memory(vertex_count << 3, "Mesh texture coords")
0040589b        if (vertex_count s> 0)
0040589d        float* pointer_3 = pointer_1
0040589f        int32_t vertex_count_1 = vertex_count
004058cb        bool cond:2_1
004058ad        *pointer_3 = fconvert.s(parse_next_float32(&cursor_1))
004058b9        pointer_3[1] = fconvert.s(parse_next_float32(&cursor_1))
004058c3        pointer_3 = &pointer_3[2]
004058c6        cond:2_1 = vertex_count_1 != 1
004058c7        vertex_count_1 -= 1
004058cb        do while (cond:2_1)
004058cd        facequad_count = facequad_count_2
004058d7        if (vertex_count_2 s> 0)
004058d9        float* ebx_1 = nullptr
00405914        int32_t i_1
004058ed        *(ebx_1 + object->vertices) = fconvert.s(parse_next_float32(&cursor))
004058fd        *(&object->vertices->y + ebx_1) = fconvert.s(parse_next_float32(&cursor))
0040590c        *(&object->vertices->z + ebx_1) = fconvert.s(parse_next_float32(&cursor))
00405910        ebx_1 = &ebx_1[3]
00405913        i_1 = vertex_count
00405913        vertex_count -= 1
00405914        do while (i_1 != 1)
00405916        facequad_count = facequad_count_2
00405929        if (facequad_count != parse_next_signed_int(&cursor))
00405935        report_errorf("Mesh face count does not match material face count in %s", &path)
0040593f        if (facequad_count s> 0)
00405945        int16_t* esi_1 = nullptr
00405947        int32_t facequad_count_1 = facequad_count
00405a7e        bool cond:6_1
00405953        *(esi_1 + object->facequads) = 0
00405959        int32_t eax_16 = parse_next_signed_int(&cursor)
00405965        int32_t eax_17 = parse_next_signed_int(&cursor)
00405973        int32_t eax_18 = parse_next_signed_int(&cursor)
00405981        int32_t eax_19 = parse_next_signed_int(&cursor)
0040598c        int32_t var_220_1 = eax_19
00405990        int32_t ebx_3
00405990        if (eax_16 != 4)
004059a7        struct ObjectFaceQuad* facequads = object->facequads
004059aa        ebx_3 = 0
004059ac        *(esi_1 + facequads) |= 0x80
0040599c        ebx_3 = parse_next_signed_int(&cursor)
0040599e        eax_19 = var_220_1
004059c7        *(&object->facequads->uv[2] + esi_1) = pointer_1[eax_17 * 2]
004059d6        *(&object->facequads->uv[2].v + esi_1) = pointer_1[eax_17 * 2 + 1]
004059e5        *(&object->facequads->uv[1] + esi_1) = pointer_1[eax_18 * 2]
004059f4        *(&object->facequads->uv[1].v + esi_1) = pointer_1[eax_18 * 2 + 1]
004059ff        *(&object->facequads->uv + esi_1) = pointer_1[eax_19 * 2]
00405a0a        *(&object->facequads->uv[0].v + esi_1) = pointer_1[eax_19 * 2 + 1]
00405a15        *(&object->facequads->uv[3] + esi_1) = pointer_1[ebx_3 * 2]
00405a25        *(&object->facequads->uv[3].v + esi_1) = pointer_1[ebx_3 * 2 + 1]
00405a31        esi_1 = &esi_1[0x18]
00405a34        *(esi_1 + object->facequads - 0x24) = get_or_create_texture_ref(&g_texture_refs, "X/snail-turbo.tga", 0, 0)
00405a40        int32_t* eax_24 = *(esi_1 + object->facequads - 0x24)
00405a44        int32_t edx_16 = *eax_24
00405a46        edx_16:1.b |= 0x10
00405a49        *eax_24 = edx_16
00405a4e        *(esi_1 + object->facequads - 0x2a) = eax_17.w
00405a5b        *(esi_1 + object->facequads - 0x2c) = eax_18.w
00405a68        *(esi_1 + object->facequads - 0x2e) = var_220_1.w
00405a70        *(esi_1 + object->facequads - 0x28) = ebx_3.w
00405a79        cond:6_1 = facequad_count_1 != 1
00405a7a        facequad_count_1 -= 1
00405a7e        do while (cond:6_1)
00405a84        facequad_count = facequad_count_2
00405a92        object->flags |= OBJECT_FLAG_DISABLE_CULLING
00405a95        free_tracked_memory(pointer_1)
00405a9f        free_tracked_memory(pointer)
00405aae        char* eax_30 = find_case_insensitive_substring("MeshMaterialList", eax_2)
00405ab6        char* var_22c = eax_30
00405abc        if (eax_30 == 0)
00405ac8        report_errorf("No MeshMaterialList { in %s", &path)
00405ada        return
00405aec        var_22c = find_case_insensitive_substring("{", eax_30)
00405af1        int32_t eax_32 = parse_next_signed_int(&var_22c)
00405b01        int32_t i_5 = parse_next_signed_int(&var_22c)
00405b0f        if (i_5 != facequad_count)
00405b1b        report_errorf("No MeshMaterialList face number is not equal to Mesh face number in %s", &path)
00405b2d        return
00405b3d        struct TextureRef** pointer_2 = allocate_tracked_memory(eax_32 << 2, "Direct X Materiallist")
00405b46        char* esi_3 = var_22c
00405b4d        int32_t ebp_1 = 0
00405b55        if (eax_32 s> 0)
00405b5b        struct TextureRef** pointer_4 = pointer_2
00405b63        char* eax_33 = find_case_insensitive_substring("TextureFilename ", esi_3)
00405b6d        if (eax_33 != 0)
00405bba        esi_3 = &find_case_insensitive_substring(""", eax_33)[1]
00405bbb        char texture_path = 0x58
00405bc3        char var_ff_1 = 0x2f
00405bcb        void var_fe
00405bcb        char* eax_36 = &var_fe
00405bd2        char i_2 = *esi_3
00405bd7        while (i_2 != 0x2e)
00405bd9        *eax_36 = i_2
00405bdb        i_2 = esi_3[1]
00405bde        eax_36 = &eax_36[1]
00405bdf        esi_3 = &esi_3[1]
00405be5        *eax_36 = 0x2e
00405bed        eax_36[1] = 0x74
00405bf6        eax_36[2] = 0x67
00405bfa        eax_36[3] = 0x61
00405bfd        eax_36[4] = 0
00405c09        struct TextureRef* eax_40 = get_or_create_texture_ref(&g_texture_refs, &texture_path, 0, 0)
00405c0e        *pointer_4 = eax_40
00405c10        enum TextureRefFlags flags = eax_40->flags
00405c12        flags:1.b |= 0x10
00405c15        eax_40->flags = flags
00405c20        if ((options_flags.b & 2) != 0)
00405c22        struct TextureRef* eax_42 = *pointer_4
00405c24        enum TextureRefFlags flags_1 = eax_42->flags
00405c26        flags_1:1.b |= 0x80
00405c29        eax_42->flags = flags_1
00405b77        if ((options_flags.b & 2) == 0)
00405b84        report_warningf("No TextureFilename for Material %i in %s", ebp_1, &path)
00405b9f        *pointer_4 = get_or_create_texture_ref(&g_texture_refs, "Sprites/debug.tga", 0, 0)
00405ba1        esi_3 = var_22c
00405c2f        ebp_1 += 1
00405c30        pointer_4 = &pointer_4[1]
00405c35        do while (ebp_1 s< eax_32)
00405c3b        int32_t i_4 = i_5
00405c41        if (i_4 s> 0)
00405c43        int32_t esi_5 = 0
00405c67        int32_t i_3
00405c5c        esi_5 += 0x30
00405c62        i_3 = i_4
00405c62        i_4 -= 1
00405c63        *(esi_5 + object->facequads - 0x24) = pointer_2[sx.d(parse_next_signed_int(&var_22c))]
00405c67        do while (i_3 != 1)
00405c6e        free_tracked_memory(pointer_2)
00405c80        return
