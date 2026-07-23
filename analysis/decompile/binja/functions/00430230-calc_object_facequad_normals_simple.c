/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: calc_object_facequad_normals_simple @ 0x430230 */

00430237        request_object_facequad_normals(object)
0043023c        int32_t facequad_count = object->facequad_count
0043023f        int32_t normal_byte_offset = 0
00430243        int32_t face_index = 0
00430247        if (facequad_count s> 0)
0043024f        int32_t face_byte_offset = 0
00430254        struct Vec3* vertices = object->vertices
00430257        struct ObjectFaceQuad* face = object->facequads + face_byte_offset
00430259        int32_t edx_1 = 0
0043025b        edx_1.w = face->vertex_0
00430262        struct Vec3* vertex_0_for_lhs = &vertices[edx_1]
00430265        int32_t edx_3 = 0
00430267        edx_3.w = face->vertex_1
0043026b        int32_t edx_4 = edx_3 * 3
00430273        struct Vec3* vertex_1 = vertices + (edx_4 << 2)
0043028e        struct Vec3 lhs
0043028e        lhs.x = fconvert.s(fconvert.t(*(vertices + (edx_4 << 2))) - fconvert.t(vertex_0_for_lhs->x))
00430296        lhs.y = fconvert.s(fconvert.t(vertex_1->y) - fconvert.t(vertex_0_for_lhs->y))
004302a2        lhs.z = fconvert.s(fconvert.t(vertex_1->z) - fconvert.t(vertex_0_for_lhs->z))
004302a6        int32_t edx_8 = 0
004302a8        edx_8.w = face->vertex_0
004302af        struct Vec3* vertex_0_for_rhs = &vertices[edx_8]
004302b2        int32_t edx_10 = 0
004302b4        edx_10.w = face->vertex_2
004302b8        int32_t eax_1 = edx_10 * 3
004302c0        struct Vec3* vertex_2 = vertices + (eax_1 << 2)
004302df        struct Vec3 rhs
004302df        rhs.x = fconvert.s(fconvert.t(*(vertices + (eax_1 << 2))) - fconvert.t(vertex_0_for_rhs->x))
004302e3        rhs.y = fconvert.s(fconvert.t(vertex_2->y) - fconvert.t(vertex_0_for_rhs->y))
004302fd        rhs.z = fconvert.s(fconvert.t(vertex_2->z) - fconvert.t(vertex_0_for_rhs->z))
00430301        struct Vec3 normal_a
00430301        cross_vectors(&normal_a, &lhs, &rhs)
0043030a        normalize_vector(&normal_a)
00430316        struct Vec3* output_normal_a = object->facequad_normals + normal_byte_offset
0043031a        output_normal_a->x = normal_a.x
00430320        output_normal_a->y = normal_a.y
00430327        output_normal_a->z = normal_a.z
0043032a        struct ObjectFaceQuad* facequads = object->facequads
00430330        struct ObjectFaceQuad* quad_face = face_byte_offset + facequads
00430336        if ((*(face_byte_offset + facequads) & 0x80) == 0)
0043033c        struct Vec3* vertices_1 = object->vertices
0043033f        int32_t ecx_6 = 0
00430341        ecx_6.w = quad_face->vertex_0
00430348        struct Vec3* vertex_0_for_quad = &vertices_1[ecx_6]
0043034b        int32_t ecx_8 = 0
0043034d        ecx_8.w = quad_face->vertex_3
00430351        int32_t eax_4 = ecx_8 * 3
00430359        struct Vec3* vertex_3 = vertices_1 + (eax_4 << 2)
00430378        rhs.x = fconvert.s(fconvert.t(*(vertices_1 + (eax_4 << 2))) - fconvert.t(vertex_0_for_quad->x))
0043037c        rhs.y = fconvert.s(fconvert.t(vertex_3->y) - fconvert.t(vertex_0_for_quad->y))
00430396        rhs.z = fconvert.s(fconvert.t(vertex_3->z) - fconvert.t(vertex_0_for_quad->z))
0043039a        struct Vec3 normal_b
0043039a        cross_vectors(&normal_b, &lhs, &rhs)
004303a3        normalize_vector(&normal_b)
004303a8        struct Vec3* facequad_normals = object->facequad_normals
004303b5        *(facequad_normals + normal_byte_offset + 0xc) = normal_b.x
004303b9        float y = normal_b.y
004303bd        (facequad_normals + normal_byte_offset + 0xc)->y.b = y.b
004303bd        (facequad_normals + normal_byte_offset + 0xc)->y:1.b = y:1.b
004303bd        (facequad_normals + normal_byte_offset + 0xc)->y:2.b = y:2.b
004303bd        (facequad_normals + normal_byte_offset + 0xc)->y:3.b = y:3.b
004303c4        (facequad_normals + normal_byte_offset + 0xc)->z = normal_b.z
004303ce        facequad_count = face_index + 1
004303cf        face_byte_offset += 0x30
004303d2        normal_byte_offset += 0x18
004303d7        face_index = facequad_count
004303db        do while (facequad_count s< object->facequad_count)
004303e8        return facequad_count
