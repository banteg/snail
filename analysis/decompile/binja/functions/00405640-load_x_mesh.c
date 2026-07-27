/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_x_mesh @ 0x405640 */

0040564a        char* eax = get_archive_data_base()
0040565f        char* buffer
0040565f        char* format
0040565f        char* mesh_path_1
0040565f        char mesh_file_path[0x100]
0040565f        if (is_archive_index_loaded() == 0)
00405688        mesh_path_1 = mesh_path
00405689        format = "X/%s"
00405692        buffer = &mesh_file_path
00405661        char* mesh_path_2 = mesh_path
00405663        int32_t i = 0xffffffff
00405668        mesh_path_1 = mesh_path
00405669        while (i != 0)
00405669        bool cond:0_1 = 0 != *mesh_path_2
00405669        mesh_path_2 = &mesh_path_2[1]
00405669        i -= 1
00405669        if (not(cond:0_1))
00405669        break
00405673        if (mesh_path[not.d(i) - 2] == 0x32)
00405680        format = "X/%s"
00405685        buffer = &mesh_file_path
00405675        format = "X/%s2"
00405692        buffer = &mesh_file_path
00405693        sprintf(buffer, format, mesh_path_1)
004056a6        int32_t byte_count
004056a6        load_file_bytes_from_archive_or_fs(&mesh_file_path, eax, &byte_count)
004056b5        eax[byte_count - 2] = 0
004056ba        char* searched = find_case_insensitive_substring("Frame ", eax)
004056ca        if (searched == 0)
004056d6        report_errorf("No 'Frame ' Data in %s", &mesh_file_path)
004056e8        return
004056f1        char* searched_1 = find_case_insensitive_substring("Mesh ", searched)
004056f9        char* duplicate_cursor = searched_1
004056ff        if (searched_1 == 0)
0040570b        report_errorf("No 'VertexDuplicationIndices 'Data in %s", &mesh_file_path)
00405710        searched_1 = duplicate_cursor
00405728        duplicate_cursor = find_case_insensitive_substring("{", searched_1)
0040572c        char* searched_2 = find_case_insensitive_substring("Mesh ", searched)
00405734        char* mesh_cursor = searched_2
0040573a        if (searched_2 == 0)
00405746        report_errorf("No 'Mesh 'Data in %s", &mesh_file_path)
0040574b        searched_2 = mesh_cursor
00405763        mesh_cursor = find_case_insensitive_substring("{", searched_2)
00405767        char* searched_3 = find_case_insensitive_substring("MeshMaterialList ", searched)
0040576f        char* material_header_cursor = searched_3
00405775        if (searched_3 == 0)
00405781        report_errorf("No 'MeshMaterialList 'Data in %s", &mesh_file_path)
00405786        searched_3 = material_header_cursor
0040579c        material_header_cursor = find_case_insensitive_substring("{", searched_3)
004057a1        parse_next_signed_int(&material_header_cursor)
004057ab        int16_t facequad_count_3 = parse_next_signed_int(&material_header_cursor)
004057b7        int16_t vertex_count_2 = parse_next_signed_int(&duplicate_cursor)
004057c5        int32_t vertex_count = sx.d(vertex_count_2)
004057d2        if (vertex_count != parse_next_signed_int(&mesh_cursor))
004057de        report_errorf("Mesh vertices count does not match vertext duplicate vertices count in %s", &mesh_file_path)
004057eb        parse_next_signed_int(&duplicate_cursor)
004057f6        char* searched_4 = find_case_insensitive_substring("MeshTextureCoords ", searched)
004057fe        char* texcoord_cursor = searched_4
00405804        if (searched_4 == 0)
00405810        report_errorf("No 'Mesh 'Data in %s", &mesh_file_path)
00405815        searched_4 = texcoord_cursor
00405827        texcoord_cursor = find_case_insensitive_substring("{", searched_4)
0040583a        if (vertex_count != parse_next_signed_int(&texcoord_cursor))
00405846        report_errorf("Mesh texture coords number does not match mesh vertext count in %s", &mesh_file_path)
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
004058ad        *pointer_3 = fconvert.s(parse_next_float32(&texcoord_cursor))
004058b9        pointer_3[1] = fconvert.s(parse_next_float32(&texcoord_cursor))
004058c3        pointer_3 = &pointer_3[2]
004058c6        cond:2_1 = vertex_count_1 != 1
004058c7        vertex_count_1 -= 1
004058cb        do while (cond:2_1)
004058cd        facequad_count = facequad_count_2
004058d7        if (vertex_count_2 s> 0)
004058d9        float* ebx_1 = nullptr
00405914        int32_t i_1
004058ed        *(ebx_1 + object->vertices) = fconvert.s(parse_next_float32(&mesh_cursor))
004058fd        *(&object->vertices->y + ebx_1) = fconvert.s(parse_next_float32(&mesh_cursor))
0040590c        *(&object->vertices->z + ebx_1) = fconvert.s(parse_next_float32(&mesh_cursor))
00405910        ebx_1 = &ebx_1[3]
00405913        i_1 = vertex_count
00405913        vertex_count -= 1
00405914        do while (i_1 != 1)
00405916        facequad_count = facequad_count_2
00405929        if (facequad_count != parse_next_signed_int(&mesh_cursor))
00405935        report_errorf("Mesh face count does not match material face count in %s", &mesh_file_path)
0040593f        if (facequad_count s> 0)
00405945        int16_t* esi_1 = nullptr
00405947        int32_t facequad_count_1 = facequad_count
00405a7e        bool cond:6_1
00405953        *(esi_1 + object->facequads) = 0
00405959        int32_t eax_14 = parse_next_signed_int(&mesh_cursor)
00405965        int32_t eax_15 = parse_next_signed_int(&mesh_cursor)
00405973        int32_t eax_16 = parse_next_signed_int(&mesh_cursor)
00405981        int32_t eax_17 = parse_next_signed_int(&mesh_cursor)
0040598c        int32_t var_220_1 = eax_17
00405990        int32_t ebx_3
00405990        if (eax_14 != 4)
004059a7        struct ObjectFaceQuad* facequads = object->facequads
004059aa        ebx_3 = 0
004059ac        *(esi_1 + facequads) |= 0x80
0040599c        ebx_3 = parse_next_signed_int(&mesh_cursor)
0040599e        eax_17 = var_220_1
004059c7        *(&object->facequads->uv[2] + esi_1) = pointer_1[eax_15 * 2]
004059d6        *(&object->facequads->uv[2].v + esi_1) = pointer_1[eax_15 * 2 + 1]
004059e5        *(&object->facequads->uv[1] + esi_1) = pointer_1[eax_16 * 2]
004059f4        *(&object->facequads->uv[1].v + esi_1) = pointer_1[eax_16 * 2 + 1]
004059ff        *(&object->facequads->uv + esi_1) = pointer_1[eax_17 * 2]
00405a0a        *(&object->facequads->uv[0].v + esi_1) = pointer_1[eax_17 * 2 + 1]
00405a15        *(&object->facequads->uv[3] + esi_1) = pointer_1[ebx_3 * 2]
00405a25        *(&object->facequads->uv[3].v + esi_1) = pointer_1[ebx_3 * 2 + 1]
00405a31        esi_1 = &esi_1[0x18]
00405a34        *(esi_1 + object->facequads - 0x24) = get_or_create_texture_ref(&g_texture_refs, "X/snail-turbo.tga", nullptr, 0)
00405a40        int32_t* eax_22 = *(esi_1 + object->facequads - 0x24)
00405a44        int32_t edx_16 = *eax_22
00405a46        edx_16:1.b |= 0x10
00405a49        *eax_22 = edx_16
00405a4e        *(esi_1 + object->facequads - 0x2a) = eax_15.w
00405a5b        *(esi_1 + object->facequads - 0x2c) = eax_16.w
00405a68        *(esi_1 + object->facequads - 0x2e) = var_220_1.w
00405a70        *(esi_1 + object->facequads - 0x28) = ebx_3.w
00405a79        cond:6_1 = facequad_count_1 != 1
00405a7a        facequad_count_1 -= 1
00405a7e        do while (cond:6_1)
00405a84        facequad_count = facequad_count_2
00405a92        object->flags |= OBJECT_FLAG_DISABLE_CULLING
00405a95        free_tracked_memory(pointer_1)
00405a9f        free_tracked_memory(pointer)
00405aae        char* searched_5 = find_case_insensitive_substring("MeshMaterialList", searched)
00405ab6        char* material_cursor = searched_5
00405abc        if (searched_5 == 0)
00405ac8        report_errorf("No MeshMaterialList { in %s", &mesh_file_path)
00405ada        return
00405aec        material_cursor = find_case_insensitive_substring("{", searched_5)
00405af1        int32_t eax_29 = parse_next_signed_int(&material_cursor)
00405b01        int32_t i_5 = parse_next_signed_int(&material_cursor)
00405b0f        if (i_5 != facequad_count)
00405b1b        report_errorf("No MeshMaterialList face number is not equal to Mesh face number in %s", &mesh_file_path)
00405b2d        return
00405b3d        struct TextureRef** pointer_2 = allocate_tracked_memory(eax_29 << 2, "Direct X Materiallist")
00405b46        char* searched_7 = material_cursor
00405b4d        int32_t ebp_1 = 0
00405b55        if (eax_29 s> 0)
00405b5b        struct TextureRef** pointer_4 = pointer_2
00405b63        char* searched_6 = find_case_insensitive_substring("TextureFilename ", searched_7)
00405b6d        if (searched_6 != 0)
00405bba        searched_7 = &find_case_insensitive_substring(""", searched_6)[1]
00405bbb        char texture_path[0x100]
00405bbb        __builtin_strncpy(&texture_path, "X/", 2)
00405bcb        char* eax_32 = &texture_path[2]
00405bd2        char i_2 = *searched_7
00405bd7        while (i_2 != 0x2e)
00405bd9        *eax_32 = i_2
00405bdb        i_2 = searched_7[1]
00405bde        eax_32 = &eax_32[1]
00405bdf        searched_7 = &searched_7[1]
00405be5        *eax_32 = 0x2e
00405bed        eax_32[1] = 0x74
00405bf6        eax_32[2] = 0x67
00405bfa        eax_32[3] = 0x61
00405bfd        eax_32[4] = 0
00405c09        struct TextureRef* eax_36 = get_or_create_texture_ref(&g_texture_refs, &texture_path, nullptr, 0)
00405c0e        *pointer_4 = eax_36
00405c10        enum TextureRefFlags flags = eax_36->flags
00405c12        flags:1.b |= 0x10
00405c15        eax_36->flags = flags
00405c20        if ((options_flags.b & 2) != 0)
00405c22        struct TextureRef* eax_38 = *pointer_4
00405c24        enum TextureRefFlags flags_1 = eax_38->flags
00405c26        flags_1:1.b |= 0x80
00405c29        eax_38->flags = flags_1
00405b77        if ((options_flags.b & 2) == 0)
00405b84        report_warningf("No TextureFilename for Material %i in %s", ebp_1, &mesh_file_path)
00405b9f        *pointer_4 = get_or_create_texture_ref(&g_texture_refs, "Sprites/debug.tga", nullptr, 0)
00405ba1        searched_7 = material_cursor
00405c2f        ebp_1 += 1
00405c30        pointer_4 = &pointer_4[1]
00405c35        do while (ebp_1 s< eax_29)
00405c3b        int32_t i_4 = i_5
00405c41        if (i_4 s> 0)
00405c43        int32_t esi_4 = 0
00405c67        int32_t i_3
00405c5c        esi_4 += 0x30
00405c62        i_3 = i_4
00405c62        i_4 -= 1
00405c63        *(esi_4 + object->facequads - 0x24) = pointer_2[sx.d(parse_next_signed_int(&material_cursor))]
00405c67        do while (i_3 != 1)
00405c6e        free_tracked_memory(pointer_2)
00405c80        return
