/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: calc_object_facequad_normals @ 0x42fcb0 */

0042fcb9        request_object_facequad_normals(object)
0042fcca        float* allocated_normal_tally = allocate_tracked_memory(object->vertex_count << 2, "Normal Tally")
0042fcd4        int32_t ecx_1 = object->vertex_count << 2
0042fcea        __builtin_memset(__builtin_memset(allocated_normal_tally, 0, ecx_1 & 0xfffffffc), 0, ecx_1 & 3)
0042fcef        int32_t geometry_byte_offset = 0
0042fcf3        int32_t face_index = 0
0042fcf7        if (object->facequad_count s> 0)
0042fcfd        int32_t normal_byte_offset = 0
00430171        bool cond:2_1
0042fd04        struct Vec3* vertices = object->vertices
0042fd07        struct ObjectFaceQuad* primary_face = object->facequads + geometry_byte_offset
0042fd09        int32_t edx_1 = 0
0042fd0b        edx_1.w = primary_face->vertex_0
0042fd12        struct Vec3* primary_vertex_0_for_lhs = &vertices[edx_1]
0042fd15        int32_t edx_3 = 0
0042fd17        edx_3.w = primary_face->vertex_1
0042fd1b        int32_t edx_4 = edx_3 * 3
0042fd24        struct Vec3* primary_vertex_1 = vertices + (edx_4 << 2)
0042fd3f        struct Vec3 lhs
0042fd3f        lhs.x = fconvert.s(fconvert.t(*(vertices + (edx_4 << 2))) - fconvert.t(primary_vertex_0_for_lhs->x))
0042fd47        lhs.y = fconvert.s(fconvert.t(primary_vertex_1->y) - fconvert.t(primary_vertex_0_for_lhs->y))
0042fd53        lhs.z = fconvert.s(fconvert.t(primary_vertex_1->z) - fconvert.t(primary_vertex_0_for_lhs->z))
0042fd57        int32_t edx_8 = 0
0042fd59        edx_8.w = primary_face->vertex_0
0042fd60        struct Vec3* primary_vertex_0_for_rhs = &vertices[edx_8]
0042fd63        int32_t edx_10 = 0
0042fd65        edx_10.w = primary_face->vertex_2
0042fd69        int32_t eax_4 = edx_10 * 3
0042fd72        struct Vec3* primary_vertex_2 = vertices + (eax_4 << 2)
0042fd91        struct Vec3 rhs
0042fd91        rhs.x = fconvert.s(fconvert.t(*(vertices + (eax_4 << 2))) - fconvert.t(primary_vertex_0_for_rhs->x))
0042fd95        rhs.y = fconvert.s(fconvert.t(primary_vertex_2->y) - fconvert.t(primary_vertex_0_for_rhs->y))
0042fdaf        rhs.z = fconvert.s(fconvert.t(primary_vertex_2->z) - fconvert.t(primary_vertex_0_for_rhs->z))
0042fdb3        struct Vec3 face_normal
0042fdb3        cross_vectors(&face_normal, &lhs, &rhs)
0042fdbc        normalize_vector(&face_normal)
0042fdcc        struct Vec3* output_face_normal = object->facequad_normals + normal_byte_offset
0042fdd0        output_face_normal->x = face_normal.x
0042fdd6        output_face_normal->y = face_normal.y
0042fddd        output_face_normal->z = face_normal.z
0042fde0        struct ObjectFaceQuad* facequads = object->facequads
0042fde6        struct ObjectFaceQuad* quad_face = facequads + geometry_byte_offset
0042fdec        struct Vec3 quad_normal
0042fdec        if ((*(facequads + geometry_byte_offset) & 0x80) == 0)
0042fdf2        struct Vec3* vertices_1 = object->vertices
0042fdf5        int32_t edx_14 = 0
0042fdf7        edx_14.w = quad_face->vertex_0
0042fdfe        struct Vec3* quad_vertex_0_for_lhs = &vertices_1[edx_14]
0042fe01        int32_t edx_16 = 0
0042fe03        edx_16.w = quad_face->vertex_2
0042fe07        int32_t edx_17 = edx_16 * 3
0042fe10        struct Vec3* quad_vertex_2 = vertices_1 + (edx_17 << 2)
0042fe2b        lhs.x = fconvert.s(fconvert.t(*(vertices_1 + (edx_17 << 2))) - fconvert.t(quad_vertex_0_for_lhs->x))
0042fe33        lhs.y = fconvert.s(fconvert.t(quad_vertex_2->y) - fconvert.t(quad_vertex_0_for_lhs->y))
0042fe3f        lhs.z = fconvert.s(fconvert.t(quad_vertex_2->z) - fconvert.t(quad_vertex_0_for_lhs->z))
0042fe43        int32_t edx_21 = 0
0042fe45        edx_21.w = quad_face->vertex_0
0042fe4c        struct Vec3* quad_vertex_0_for_rhs = &vertices_1[edx_21]
0042fe4f        int32_t edx_23 = 0
0042fe51        edx_23.w = quad_face->vertex_3
0042fe55        int32_t eax_7 = edx_23 * 3
0042fe5e        struct Vec3* quad_vertex_3 = vertices_1 + (eax_7 << 2)
0042fe7d        rhs.x = fconvert.s(fconvert.t(*(vertices_1 + (eax_7 << 2))) - fconvert.t(quad_vertex_0_for_rhs->x))
0042fe81        rhs.y = fconvert.s(fconvert.t(quad_vertex_3->y) - fconvert.t(quad_vertex_0_for_rhs->y))
0042fe9b        rhs.z = fconvert.s(fconvert.t(quad_vertex_3->z) - fconvert.t(quad_vertex_0_for_rhs->z))
0042fe9f        cross_vectors(&quad_normal, &lhs, &rhs)
0042fea8        normalize_vector(&quad_normal)
0042feb6        struct Vec3* output_quad_normal = object->facequad_normals + normal_byte_offset + 0xc
0042febe        output_quad_normal->x = quad_normal.x
0042fec4        output_quad_normal->y = quad_normal.y
0042fecb        output_quad_normal->z = quad_normal.z
0042fed1        struct ObjectFaceQuad* accumulation_face = object->facequads + geometry_byte_offset
0042fed6        if ((accumulation_face->.header_word.b & 0x80) == 0)
0042fedc        int32_t eax_12 = 0
0042fede        eax_12.b = accumulation_face->vertex_0.b
0042fede        eax_12:1.b = accumulation_face->vertex_0:1.b
0042fee6        int32_t edx_25 = eax_12 * 3
0042fee9        struct Vec3* vertex_normals = object->vertex_normals
0042feef        struct Vec3* quad_vertex_0_normal = vertex_normals + (edx_25 << 2)
0042fef2        quad_vertex_0_normal->x = fconvert.s(fconvert.t(quad_normal.x) + fconvert.t(*(vertex_normals + (edx_25 << 2))))
0042fefb        quad_vertex_0_normal->y = fconvert.s(fconvert.t(quad_normal.y) + fconvert.t(quad_vertex_0_normal->y))
0042ff05        quad_vertex_0_normal->z = fconvert.s(fconvert.t(quad_normal.z) + fconvert.t(quad_vertex_0_normal->z))
0042ff0b        int32_t eax_13 = 0
0042ff11        eax_13.w = *(&object->facequads->vertex_1 + geometry_byte_offset)
0042ff16        int32_t edx_26 = eax_13 * 3
0042ff19        struct Vec3* vertex_normals_1 = object->vertex_normals
0042ff1f        struct Vec3* quad_vertex_1_normal = vertex_normals_1 + (edx_26 << 2)
0042ff22        quad_vertex_1_normal->x = fconvert.s(fconvert.t(quad_normal.x) + fconvert.t(*(vertex_normals_1 + (edx_26 << 2))))
0042ff2b        quad_vertex_1_normal->y = fconvert.s(fconvert.t(quad_normal.y) + fconvert.t(quad_vertex_1_normal->y))
0042ff35        quad_vertex_1_normal->z = fconvert.s(fconvert.t(quad_normal.z) + fconvert.t(quad_vertex_1_normal->z))
0042ff3b        int32_t eax_14 = 0
0042ff41        eax_14.w = *(&object->facequads->vertex_2 + geometry_byte_offset)
0042ff46        int32_t edx_27 = eax_14 * 3
0042ff49        struct Vec3* vertex_normals_2 = object->vertex_normals
0042ff4f        struct Vec3* quad_vertex_2_normal = vertex_normals_2 + (edx_27 << 2)
0042ff52        quad_vertex_2_normal->x = fconvert.s(fconvert.t(quad_normal.x) + fconvert.t(*(vertex_normals_2 + (edx_27 << 2))))
0042ff5b        quad_vertex_2_normal->y = fconvert.s(fconvert.t(quad_normal.y) + fconvert.t(quad_vertex_2_normal->y))
0042ff65        quad_vertex_2_normal->z = fconvert.s(fconvert.t(quad_normal.z) + fconvert.t(quad_vertex_2_normal->z))
0042ff6b        int32_t eax_15 = 0
0042ff71        eax_15.w = *(&object->facequads->vertex_3 + geometry_byte_offset)
0042ff76        int32_t edx_28 = eax_15 * 3
0042ff79        struct Vec3* vertex_normals_3 = object->vertex_normals
0042ff7f        struct Vec3* quad_vertex_3_normal = vertex_normals_3 + (edx_28 << 2)
0042ff82        int32_t edx_29 = 0
0042ff84        quad_vertex_3_normal->x = fconvert.s(fconvert.t(quad_normal.x) + fconvert.t(*(vertex_normals_3 + (edx_28 << 2))))
0042ff8d        quad_vertex_3_normal->y = fconvert.s(fconvert.t(quad_normal.y) + fconvert.t(quad_vertex_3_normal->y))
0042ff97        quad_vertex_3_normal->z = fconvert.s(fconvert.t(quad_normal.z) + fconvert.t(quad_vertex_3_normal->z))
0042ff9d        edx_29.w = *(&object->facequads->vertex_0 + geometry_byte_offset)
0042ffa2        int32_t ecx_21 = 0
0042ffb0        allocated_normal_tally[edx_29] = fconvert.s(fconvert.t(allocated_normal_tally[edx_29]) + fconvert.t(1f))
0042ffb5        ecx_21.w = *(&object->facequads->vertex_1 + geometry_byte_offset)
0042ffc6        allocated_normal_tally[ecx_21] = fconvert.s(fconvert.t(allocated_normal_tally[ecx_21]) + fconvert.t(1f))
0042ffcb        int32_t eax_19 = 0
0042ffcd        eax_19.w = *(&object->facequads->vertex_2 + geometry_byte_offset)
0042ffde        allocated_normal_tally[eax_19] = fconvert.s(fconvert.t(allocated_normal_tally[eax_19]) + fconvert.t(1f))
0042ffe3        int32_t edx_31 = 0
0042ffe5        edx_31.w = *(&object->facequads->vertex_3 + geometry_byte_offset)
0042fff6        allocated_normal_tally[edx_31] = fconvert.s(fconvert.t(allocated_normal_tally[edx_31]) + fconvert.t(1f))
0042fffb        int32_t eax_22 = 0
00430001        eax_22.w = *(&object->facequads->vertex_0 + geometry_byte_offset)
00430006        int32_t edx_32 = eax_22 * 3
00430009        struct Vec3* vertex_normals_4 = object->vertex_normals
0043000f        struct Vec3* primary_vertex_0_normal = vertex_normals_4 + (edx_32 << 2)
00430012        primary_vertex_0_normal->x = fconvert.s(fconvert.t(face_normal.x) + fconvert.t(*(vertex_normals_4 + (edx_32 << 2))))
0043001b        primary_vertex_0_normal->y = fconvert.s(fconvert.t(face_normal.y) + fconvert.t(primary_vertex_0_normal->y))
00430025        primary_vertex_0_normal->z = fconvert.s(fconvert.t(face_normal.z) + fconvert.t(primary_vertex_0_normal->z))
0043002b        int32_t eax_23 = 0
00430031        eax_23.w = *(&object->facequads->vertex_1 + geometry_byte_offset)
00430036        int32_t edx_33 = eax_23 * 3
00430039        struct Vec3* vertex_normals_5 = object->vertex_normals
0043003f        struct Vec3* primary_vertex_1_normal = vertex_normals_5 + (edx_33 << 2)
00430042        primary_vertex_1_normal->x = fconvert.s(fconvert.t(face_normal.x) + fconvert.t(*(vertex_normals_5 + (edx_33 << 2))))
0043004b        primary_vertex_1_normal->y = fconvert.s(fconvert.t(face_normal.y) + fconvert.t(primary_vertex_1_normal->y))
00430055        primary_vertex_1_normal->z = fconvert.s(fconvert.t(face_normal.z) + fconvert.t(primary_vertex_1_normal->z))
0043005b        int32_t eax_24 = 0
00430061        eax_24.w = *(&object->facequads->vertex_2 + geometry_byte_offset)
00430066        int32_t edx_34 = eax_24 * 3
00430069        struct Vec3* vertex_normals_6 = object->vertex_normals
0043006f        struct Vec3* primary_vertex_2_normal = vertex_normals_6 + (edx_34 << 2)
00430072        primary_vertex_2_normal->x = fconvert.s(fconvert.t(face_normal.x) + fconvert.t(*(vertex_normals_6 + (edx_34 << 2))))
0043007b        primary_vertex_2_normal->y = fconvert.s(fconvert.t(face_normal.y) + fconvert.t(primary_vertex_2_normal->y))
00430085        primary_vertex_2_normal->z = fconvert.s(fconvert.t(face_normal.z) + fconvert.t(primary_vertex_2_normal->z))
0043008b        int32_t eax_25 = 0
00430091        eax_25.w = *(&object->facequads->vertex_3 + geometry_byte_offset)
00430096        int32_t edx_35 = eax_25 * 3
00430099        struct Vec3* vertex_normals_7 = object->vertex_normals
0043009f        struct Vec3* primary_vertex_3_normal = vertex_normals_7 + (edx_35 << 2)
004300a2        int32_t edx_36 = 0
004300a4        primary_vertex_3_normal->x = fconvert.s(fconvert.t(face_normal.x) + fconvert.t(*(vertex_normals_7 + (edx_35 << 2))))
004300ad        primary_vertex_3_normal->y = fconvert.s(fconvert.t(face_normal.y) + fconvert.t(primary_vertex_3_normal->y))
004300b7        primary_vertex_3_normal->z = fconvert.s(fconvert.t(face_normal.z) + fconvert.t(primary_vertex_3_normal->z))
004300bd        edx_36.w = *(&object->facequads->vertex_0 + geometry_byte_offset)
004300c2        int32_t ecx_28 = 0
004300d0        allocated_normal_tally[edx_36] = fconvert.s(fconvert.t(allocated_normal_tally[edx_36]) + fconvert.t(2.0999999f))
004300d5        ecx_28.w = *(&object->facequads->vertex_1 + geometry_byte_offset)
004300e6        allocated_normal_tally[ecx_28] = fconvert.s(fconvert.t(allocated_normal_tally[ecx_28]) + fconvert.t(2.0999999f))
004300eb        int32_t eax_29 = 0
004300ed        eax_29.w = *(&object->facequads->vertex_2 + geometry_byte_offset)
004300fe        allocated_normal_tally[eax_29] = fconvert.s(fconvert.t(allocated_normal_tally[eax_29]) + fconvert.t(2.0999999f))
00430103        int32_t edx_38 = 0
00430105        edx_38.w = *(&object->facequads->vertex_3 + geometry_byte_offset)
00430116        int32_t edx_39 = 0
00430118        allocated_normal_tally[edx_38] = fconvert.s(fconvert.t(allocated_normal_tally[edx_38]) + fconvert.t(2.0999999f))
0043011d        int32_t vertex_count = object->vertex_count
00430120        struct ObjectFaceQuad* validation_face = object->facequads + geometry_byte_offset
00430122        edx_39.w = validation_face->vertex_0
00430128        if (edx_39 s> vertex_count)
0043014d        report_errorf("Invalid Face Vertex Index")
0043012a        int32_t edx_40 = 0
0043012c        edx_40.w = validation_face->vertex_1
00430132        if (edx_40 s> vertex_count)
0043014d        report_errorf("Invalid Face Vertex Index")
00430134        int32_t edx_41 = 0
00430136        edx_41.w = validation_face->vertex_2
0043013c        if (edx_41 s> vertex_count)
0043014d        report_errorf("Invalid Face Vertex Index")
0043013e        int32_t edx_42 = 0
00430140        edx_42.w = validation_face->vertex_3
00430146        if (edx_42 s> vertex_count)
0043014d        report_errorf("Invalid Face Vertex Index")
00430164        geometry_byte_offset += 0x30
00430167        cond:2_1 = face_index + 1 s< object->facequad_count
00430169        face_index += 1
0043016d        normal_byte_offset += 0x18
00430171        do while (cond:2_1)
00430177        geometry_byte_offset = 0
0043017c        int32_t vertex_index = 0
00430182        if (object->vertex_count s> 0)
00430188        float* normal_tally_cursor = allocated_normal_tally
0043020e        bool cond:1_1
0043018a        struct Vec3* vertex_normals_8 = object->vertex_normals
0043018f        long double x87_r7_93 = fconvert.t(*normal_tally_cursor)
00430195        struct Vec3* averaged_normal = geometry_byte_offset + vertex_normals_8
0043019b        averaged_normal->x = fconvert.s(fconvert.t(*(geometry_byte_offset + vertex_normals_8)) / x87_r7_93)
004301a2        averaged_normal->y = fconvert.s(fconvert.t(averaged_normal->y) / x87_r7_93)
004301aa        averaged_normal->z = fconvert.s(fconvert.t(averaged_normal->z) / x87_r7_93)
004301b4        normalize_vector(geometry_byte_offset + object->vertex_normals)
004301bc        normal_tally_cursor = &normal_tally_cursor[1]
004301bf        struct Vec3* inverted_normal = object->vertex_normals + geometry_byte_offset
004301c1        geometry_byte_offset += 0xc
004301df        float var_8_2 = fconvert.s(fconvert.t(inverted_normal->y) * fconvert.t(-1f))
004301e6        long double x87_r7_102 = fconvert.t(inverted_normal->z) * fconvert.t(-1f)
004301f0        inverted_normal->x = fconvert.s(fconvert.t(inverted_normal->x) * fconvert.t(-1f))
004301f2        inverted_normal->y = var_8_2
004301fd        inverted_normal->z = fconvert.s(x87_r7_102)
00430208        cond:1_1 = vertex_index + 1 s< object->vertex_count
0043020a        vertex_index += 1
0043020e        do while (cond:1_1)
00430215        free_tracked_memory(allocated_normal_tally)
00430224        return
