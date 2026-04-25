/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_x_mesh @ 0x405640 */

0040564a        char* eax = get_archive_data_base()
0040565f        char* var_250
0040565f        char* var_24c
0040565f        char var_200[0x100]
0040565f        if (is_archive_index_loaded() == 0)
00405688        char* mesh_path_2 = mesh_path
00405689        var_24c = "X/%s"
00405692        var_250 = &var_200
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
00405685        var_250 = &var_200
00405675        var_24c = "X/%s2"
00405692        var_250 = &var_200
00405693        sub_48b32c(var_250, var_24c)
004056a6        int32_t var_204
004056a6        load_file_bytes_from_archive_or_fs(&var_200, eax, &var_204)
004056b5        eax[var_204 - 2] = 0
004056ba        char* eax_3 = find_case_insensitive_substring("Frame ", eax)
004056ca        if (eax_3 == 0)
004056d0        char (* var_248_1)[0x100] = &var_200
004056d6        report_errorf("No 'Frame ' Data in %s")
004056e8        return 0
004056f1        char* eax_4 = find_case_insensitive_substring("Mesh ", eax_3)
004056f9        char* var_218 = eax_4
004056ff        if (eax_4 == 0)
00405705        char (* var_248_3)[0x100] = &var_200
0040570b        report_errorf("No 'VertexDuplicationIndices 'Data in %s")
00405710        eax_4 = var_218
00405728        var_218 = find_case_insensitive_substring("{", eax_4)
0040572c        char* cursor_2 = find_case_insensitive_substring("Mesh ", eax_3)
00405734        char* cursor = cursor_2
0040573a        if (cursor_2 == 0)
00405740        char (* var_248_5)[0x100] = &var_200
00405746        report_errorf("No 'Mesh 'Data in %s")
0040574b        cursor_2 = cursor
00405763        cursor = find_case_insensitive_substring("{", cursor_2)
00405767        char* eax_7 = find_case_insensitive_substring("MeshMaterialList ", eax_3)
0040576f        char* var_21c = eax_7
00405775        if (eax_7 == 0)
0040577b        char (* var_248_7)[0x100] = &var_200
00405781        report_errorf("No 'MeshMaterialList 'Data in %s")
00405786        eax_7 = var_21c
0040579c        var_21c = find_case_insensitive_substring("{", eax_7)
004057a1        parse_next_signed_int(&var_21c)
004057ab        int16_t facequad_count_3 = parse_next_signed_int(&var_21c)
004057b7        int16_t vertex_count_2 = parse_next_signed_int(&var_218)
004057c5        int32_t vertex_count = sx.d(vertex_count_2)
004057d2        if (vertex_count != parse_next_signed_int(&cursor))
004057d8        char (* var_248_9)[0x100] = &var_200
004057de        report_errorf("Mesh vertices count does not match vertext duplicate vertices count in %s")
004057eb        parse_next_signed_int(&var_218)
004057f6        char* cursor_3 = find_case_insensitive_substring("MeshTextureCoords ", eax_3)
004057fe        char* cursor_1 = cursor_3
00405804        if (cursor_3 == 0)
0040580a        char (* var_248_11)[0x100] = &var_200
00405810        report_errorf("No 'Mesh 'Data in %s")
00405815        cursor_3 = cursor_1
00405827        cursor_1 = find_case_insensitive_substring("{", cursor_3)
0040583a        if (vertex_count != parse_next_signed_int(&cursor_1))
00405840        char (* var_248_13)[0x100] = &var_200
00405846        report_errorf("Mesh texture coords number does not match mesh vertext count in %s")
00405855        int32_t facequad_count = sx.d(facequad_count_3)
0040585b        int32_t facequad_count_2 = facequad_count
0040585f        request_object_facequads(mesh, facequad_count)
00405867        request_object_vertices(mesh, vertex_count)
00405879        void* eax_12 = allocate_tracked_memory(vertex_count << 2, "Mesh vertex remap")
0040588f        float* eax_14 = allocate_tracked_memory(vertex_count << 3, "Mesh texture coords")
0040589b        if (vertex_count s> 0)
0040589d        float* ebx_1 = eax_14
0040589f        int32_t vertex_count_1 = vertex_count
004058cb        bool cond:2_1
004058ad        *ebx_1 = fconvert.s(parse_next_float32(&cursor_1))
004058b9        ebx_1[1] = fconvert.s(parse_next_float32(&cursor_1))
004058c3        ebx_1 = &ebx_1[2]
004058c6        cond:2_1 = vertex_count_1 != 1
004058c7        vertex_count_1 -= 1
004058cb        do while (cond:2_1)
004058cd        facequad_count = facequad_count_2
004058d7        if (vertex_count_2 s> 0)
004058d9        float* ebx_2 = nullptr
00405914        int32_t i_1
004058ed        *(ebx_2 + mesh->vertices) = fconvert.s(parse_next_float32(&cursor))
004058fd        *(&mesh->vertices->y + ebx_2) = fconvert.s(parse_next_float32(&cursor))
0040590c        *(&mesh->vertices->z + ebx_2) = fconvert.s(parse_next_float32(&cursor))
00405910        ebx_2 = &ebx_2[3]
00405913        i_1 = vertex_count
00405913        vertex_count -= 1
00405914        do while (i_1 != 1)
00405916        facequad_count = facequad_count_2
00405929        if (facequad_count != parse_next_signed_int(&cursor))
0040592f        char (* var_248_19)[0x100] = &var_200
00405935        report_errorf("Mesh face count does not match material face count in %s")
0040593f        if (facequad_count s> 0)
00405945        int16_t* esi_1 = nullptr
00405947        int32_t facequad_count_1 = facequad_count
00405a7e        bool cond:6_1
00405953        *(esi_1 + mesh->facequads) = 0
00405959        int32_t eax_19 = parse_next_signed_int(&cursor)
00405965        int32_t eax_20 = parse_next_signed_int(&cursor)
00405973        int32_t eax_21 = parse_next_signed_int(&cursor)
00405981        int32_t eax_22 = parse_next_signed_int(&cursor)
0040598c        int32_t var_220_1 = eax_22
00405990        int32_t ebx_4
00405990        if (eax_19 != 4)
004059a7        struct ObjectFaceQuad* facequads = mesh->facequads
004059aa        ebx_4 = 0
004059ac        *(esi_1 + facequads) |= 0x80
0040599c        ebx_4 = parse_next_signed_int(&cursor)
0040599e        eax_22 = var_220_1
004059c7        *(&mesh->facequads->u2 + esi_1) = eax_14[eax_20 * 2]
004059d6        *(&mesh->facequads->v2 + esi_1) = eax_14[eax_20 * 2 + 1]
004059e5        *(&mesh->facequads->u1 + esi_1) = eax_14[eax_21 * 2]
004059f4        *(&mesh->facequads->v1 + esi_1) = eax_14[eax_21 * 2 + 1]
004059ff        *(&mesh->facequads->u0 + esi_1) = eax_14[eax_22 * 2]
00405a0a        *(&mesh->facequads->v0 + esi_1) = eax_14[eax_22 * 2 + 1]
00405a15        *(&mesh->facequads->u3 + esi_1) = eax_14[ebx_4 * 2]
00405a25        *(&mesh->facequads->v3 + esi_1) = eax_14[ebx_4 * 2 + 1]
00405a31        esi_1 = &esi_1[0x18]
00405a34        *(esi_1 + mesh->facequads - 0x24) = get_or_create_texture_ref(&data_4b7790, "X/snail-turbo.tga", 0, 0)
00405a3b        struct ObjectFaceQuad* ecx_14
00405a3b        ecx_14.w = eax_20.w
00405a40        int32_t* eax_27 = *(esi_1 + mesh->facequads - 0x24)
00405a46        int32_t edx_16
00405a46        edx_16:1.b = (*eax_27):1.b | 0x10
00405a49        *eax_27 = edx_16
00405a4e        *(esi_1 + mesh->facequads - 0x2a) = ecx_14.w
00405a56        struct ObjectFaceQuad* eax_28
00405a56        eax_28.w = eax_21.w
00405a5b        *(esi_1 + mesh->facequads - 0x2c) = eax_28.w
00405a63        struct ObjectFaceQuad* edx_17
00405a63        edx_17.w = var_220_1.w
00405a68        *(esi_1 + mesh->facequads - 0x2e) = edx_17.w
00405a70        *(esi_1 + mesh->facequads - 0x28) = ebx_4.w
00405a79        cond:6_1 = facequad_count_1 != 1
00405a7a        facequad_count_1 -= 1
00405a7e        do while (cond:6_1)
00405a84        facequad_count = facequad_count_2
00405a92        mesh->flags |= PATH_TEMPLATE_STRIP_MESH_FLAG_IMPORTED_X_MESH
00405a95        free_tracked_memory(eax_14)
00405a9f        free_tracked_memory(eax_12)
00405aae        char* eax_32 = find_case_insensitive_substring("MeshMaterialList", eax_3)
00405ab6        char* var_22c = eax_32
00405abc        if (eax_32 == 0)
00405ac2        char (* var_248_23)[0x100] = &var_200
00405ac8        report_errorf("No MeshMaterialList { in %s")
00405ada        return 0
00405aec        var_22c = find_case_insensitive_substring("{", eax_32)
00405af1        int32_t eax_34 = parse_next_signed_int(&var_22c)
00405b01        int32_t i_5 = parse_next_signed_int(&var_22c)
00405b0f        if (i_5 != facequad_count)
00405b15        char (* var_248_25)[0x100] = &var_200
00405b1b        report_errorf("No MeshMaterialList face number is not equal to Mesh face number in %s")
00405b2d        return 0
00405b3d        int32_t* eax_35 = allocate_tracked_memory(eax_34 << 2, "Direct X Materiallist")
00405b46        char* esi_3 = var_22c
00405b4d        int32_t ebp_1 = 0
00405b55        if (eax_34 s> 0)
00405b5b        int32_t* ebx_5 = eax_35
00405b63        char* eax_36 = find_case_insensitive_substring("TextureFilename ", esi_3)
00405b6d        if (eax_36 != 0)
00405bba        esi_3 = &find_case_insensitive_substring(""", eax_36)[1]
00405bbb        char texture_path = 0x58
00405bc3        char var_ff_1 = 0x2f
00405bcb        void var_fe
00405bcb        char* eax_39 = &var_fe
00405bd2        char i_2 = *esi_3
00405bd7        while (i_2 != 0x2e)
00405bd9        *eax_39 = i_2
00405bdb        i_2 = esi_3[1]
00405bde        eax_39 = &eax_39[1]
00405bdf        esi_3 = &esi_3[1]
00405be5        *eax_39 = 0x2e
00405bed        eax_39[1] = 0x74
00405bf6        eax_39[2] = 0x67
00405bfa        eax_39[3] = 0x61
00405bfd        eax_39[4] = 0
00405c09        struct TextureRef* eax_43 = get_or_create_texture_ref(&data_4b7790, &texture_path, 0, 0)
00405c0e        *ebx_5 = eax_43
00405c12        uint32_t ecx_21
00405c12        ecx_21:1.b = eax_43->flags:1.b | 0x10
00405c15        eax_43->flags = ecx_21
00405c17        eax_43.b = options_flags
00405c20        if ((eax_43.b & 2) != 0)
00405c22        int32_t* eax_44 = *ebx_5
00405c26        int32_t ecx_22
00405c26        ecx_22:1.b = (*eax_44):1.b | 0x80
00405c29        *eax_44 = ecx_22
00405b77        if ((options_flags & 2) == 0)
00405b7d        char (* var_248_27)[0x100] = &var_200
00405b7e        int32_t var_24c_9 = ebp_1
00405b84        report_warningf("No TextureFilename for Material %i in %s")
00405b9f        *ebx_5 = get_or_create_texture_ref(&data_4b7790, "Sprites/debug.tga", 0, 0)
00405ba1        esi_3 = var_22c
00405c2f        ebp_1 += 1
00405c30        ebx_5 = &ebx_5[1]
00405c35        do while (ebp_1 s< eax_34)
00405c3b        int32_t i_4 = i_5
00405c41        if (i_4 s> 0)
00405c43        int32_t esi_5 = 0
00405c67        int32_t i_3
00405c5c        esi_5 += 0x30
00405c62        i_3 = i_4
00405c62        i_4 -= 1
00405c63        *(esi_5 + mesh->facequads - 0x24) = eax_35[sx.d(parse_next_signed_int(&var_22c))]
00405c67        do while (i_3 != 1)
00405c80        return free_tracked_memory(eax_35)
