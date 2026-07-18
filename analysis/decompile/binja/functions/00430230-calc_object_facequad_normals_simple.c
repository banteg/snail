/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: calc_object_facequad_normals_simple @ 0x430230 */

00430237        request_object_facequad_normals(object)
0043023c        int32_t facequad_count = object->facequad_count
0043023f        int32_t ebp = 0
00430243        int32_t facequad_count_1 = 0
00430247        if (facequad_count s> 0)
0043024f        char* ebx_1 = nullptr
00430254        struct Vec3* vertices = object->vertices
00430257        void* eax_1 = object->facequads + ebx_1
00430259        int32_t edx_1 = 0
0043025b        edx_1.w = *(eax_1 + 2)
00430262        float* edi_1 = &vertices[edx_1]
00430265        int32_t edx_3 = 0
00430267        edx_3.w = *(eax_1 + 4)
0043026b        int32_t edx_4 = edx_3 * 3
00430273        void* edx_5 = vertices + (edx_4 << 2)
0043028e        struct Vec3 lhs
0043028e        lhs.x = fconvert.s(fconvert.t(*(vertices + (edx_4 << 2))) - fconvert.t(*edi_1))
00430296        lhs.y = fconvert.s(fconvert.t(*(edx_5 + 4)) - fconvert.t(edi_1[1]))
004302a2        lhs.z = fconvert.s(fconvert.t(*(edx_5 + 8)) - fconvert.t(edi_1[2]))
004302a6        int32_t edx_9 = 0
004302a8        edx_9.w = *(eax_1 + 2)
004302af        float* edi_2 = &vertices[edx_9]
004302b2        int32_t edx_11 = 0
004302b4        edx_11.w = *(eax_1 + 6)
004302b8        int32_t eax_2 = edx_11 * 3
004302c0        void* eax_3 = vertices + (eax_2 << 2)
004302df        struct Vec3 rhs
004302df        rhs.x = fconvert.s(fconvert.t(*(vertices + (eax_2 << 2))) - fconvert.t(*edi_2))
004302e3        rhs.y = fconvert.s(fconvert.t(*(eax_3 + 4)) - fconvert.t(edi_2[1]))
004302fd        rhs.z = fconvert.s(fconvert.t(*(eax_3 + 8)) - fconvert.t(edi_2[2]))
00430301        struct Vec3 var_24
00430301        cross_vectors(&var_24, &lhs, &rhs)
0043030a        normalize_vector(&var_24)
00430316        float* eax_6 = object->facequad_normals + ebp
0043031a        *eax_6 = var_24.x
00430320        eax_6[1] = var_24.y
00430327        eax_6[2] = var_24.z
0043032a        struct ObjectFaceQuad* facequads = object->facequads
00430330        void* eax_7 = ebx_1 + facequads
00430336        if ((*(ebx_1 + facequads) & 0x80) == 0)
0043033c        struct Vec3* vertices_1 = object->vertices
0043033f        int32_t ecx_6 = 0
00430341        ecx_6.w = *(eax_7 + 2)
00430348        float* edx_14 = &vertices_1[ecx_6]
0043034b        int32_t ecx_8 = 0
0043034d        ecx_8.w = *(eax_7 + 8)
00430351        int32_t eax_8 = ecx_8 * 3
00430359        void* eax_9 = vertices_1 + (eax_8 << 2)
00430378        rhs.x = fconvert.s(fconvert.t(*(vertices_1 + (eax_8 << 2))) - fconvert.t(*edx_14))
0043037c        rhs.y = fconvert.s(fconvert.t(*(eax_9 + 4)) - fconvert.t(edx_14[1]))
00430396        rhs.z = fconvert.s(fconvert.t(*(eax_9 + 8)) - fconvert.t(edx_14[2]))
0043039a        struct Vec3 var_c
0043039a        cross_vectors(&var_c, &lhs, &rhs)
004303a3        normalize_vector(&var_c)
004303a8        struct Vec3* facequad_normals = object->facequad_normals
004303b5        *(facequad_normals + ebp + 0xc) = var_c.x
004303b9        float y = var_c.y
004303bd        *(facequad_normals + ebp + 0x10) = y.b
004303bd        *(facequad_normals + ebp + 0x11) = y:1.b
004303bd        *(facequad_normals + ebp + 0x12) = y:2.b
004303bd        *(facequad_normals + ebp + 0x13) = y:3.b
004303c4        *(facequad_normals + ebp + 0x14) = var_c.z
004303ce        facequad_count = facequad_count_1 + 1
004303cf        ebx_1 = &ebx_1[0x30]
004303d2        ebp += 0x18
004303d7        facequad_count_1 = facequad_count
004303db        do while (facequad_count s< object->facequad_count)
004303e8        return facequad_count
