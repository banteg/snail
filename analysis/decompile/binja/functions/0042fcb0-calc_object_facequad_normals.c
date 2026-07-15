/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: calc_object_facequad_normals @ 0x42fcb0 */

0042fcb9        request_object_facequad_normals(object)
0042fcca        float* pointer = allocate_tracked_memory(object->vertex_count << 2, "Normal Tally")
0042fcd4        int32_t ecx_1 = object->vertex_count << 2
0042fcea        __builtin_memset(__builtin_memset(pointer, 0, ecx_1 & 0xfffffffc), 0, ecx_1 & 3)
0042fcef        float* edi_2 = nullptr
0042fcf3        int32_t var_68 = 0
0042fcf7        if (object->facequad_count s> 0)
0042fcfd        int32_t var_64_1 = 0
00430171        bool cond:2_1
0042fd04        struct Vec3* vertices = object->vertices
0042fd07        void* eax_4 = object->facequads + edi_2
0042fd09        int32_t edx_1 = 0
0042fd0b        edx_1.w = *(eax_4 + 2)
0042fd12        float* ebp_1 = &vertices[edx_1]
0042fd15        int32_t edx_3 = 0
0042fd17        edx_3.w = *(eax_4 + 4)
0042fd1b        int32_t edx_4 = edx_3 * 3
0042fd24        void* edx_5 = vertices + (edx_4 << 2)
0042fd3f        struct Vec3 lhs
0042fd3f        lhs.x = fconvert.s(fconvert.t(*(vertices + (edx_4 << 2))) - fconvert.t(*ebp_1))
0042fd47        lhs.y = fconvert.s(fconvert.t(*(edx_5 + 4)) - fconvert.t(ebp_1[1]))
0042fd53        lhs.z = fconvert.s(fconvert.t(*(edx_5 + 8)) - fconvert.t(ebp_1[2]))
0042fd57        int32_t edx_9 = 0
0042fd59        edx_9.w = *(eax_4 + 2)
0042fd60        float* ebp_2 = &vertices[edx_9]
0042fd63        int32_t edx_11 = 0
0042fd65        edx_11.w = *(eax_4 + 6)
0042fd69        int32_t eax_5 = edx_11 * 3
0042fd72        void* ecx_5 = vertices + (eax_5 << 2)
0042fd91        struct Vec3 rhs
0042fd91        rhs.x = fconvert.s(fconvert.t(*(vertices + (eax_5 << 2))) - fconvert.t(*ebp_2))
0042fd95        rhs.y = fconvert.s(fconvert.t(*(ecx_5 + 4)) - fconvert.t(ebp_2[1]))
0042fdaf        rhs.z = fconvert.s(fconvert.t(*(ecx_5 + 8)) - fconvert.t(ebp_2[2]))
0042fdb3        struct Vec3 var_54
0042fdb3        cross_vectors(&var_54, &lhs, &rhs)
0042fdbc        normalize_vector(&var_54)
0042fdcc        float* eax_8 = object->facequad_normals + var_64_1
0042fdd0        *eax_8 = var_54.x
0042fdd6        eax_8[1] = var_54.y
0042fddd        eax_8[2] = var_54.z
0042fde0        struct ObjectFaceQuad* facequads = object->facequads
0042fde6        void* eax_9 = facequads + edi_2
0042fdec        struct Vec3 var_60
0042fdec        if ((*(facequads + edi_2) & 0x80) == 0)
0042fdf2        struct Vec3* vertices_1 = object->vertices
0042fdf5        int32_t edx_15 = 0
0042fdf7        edx_15.w = *(eax_9 + 2)
0042fdfe        float* ebp_3 = &vertices_1[edx_15]
0042fe01        int32_t edx_17 = 0
0042fe03        edx_17.w = *(eax_9 + 6)
0042fe07        int32_t edx_18 = edx_17 * 3
0042fe10        void* edx_19 = vertices_1 + (edx_18 << 2)
0042fe2b        lhs.x = fconvert.s(fconvert.t(*(vertices_1 + (edx_18 << 2))) - fconvert.t(*ebp_3))
0042fe33        lhs.y = fconvert.s(fconvert.t(*(edx_19 + 4)) - fconvert.t(ebp_3[1]))
0042fe3f        lhs.z = fconvert.s(fconvert.t(*(edx_19 + 8)) - fconvert.t(ebp_3[2]))
0042fe43        int32_t edx_23 = 0
0042fe45        edx_23.w = *(eax_9 + 2)
0042fe4c        float* ebp_4 = &vertices_1[edx_23]
0042fe4f        int32_t edx_25 = 0
0042fe51        edx_25.w = *(eax_9 + 8)
0042fe55        int32_t eax_10 = edx_25 * 3
0042fe5e        void* ecx_12 = vertices_1 + (eax_10 << 2)
0042fe7d        rhs.x = fconvert.s(fconvert.t(*(vertices_1 + (eax_10 << 2))) - fconvert.t(*ebp_4))
0042fe81        rhs.y = fconvert.s(fconvert.t(*(ecx_12 + 4)) - fconvert.t(ebp_4[1]))
0042fe9b        rhs.z = fconvert.s(fconvert.t(*(ecx_12 + 8)) - fconvert.t(ebp_4[2]))
0042fe9f        cross_vectors(&var_60, &lhs, &rhs)
0042fea8        normalize_vector(&var_60)
0042feb6        int32_t* edx_27 = object->facequad_normals + var_64_1 + 0xc
0042febe        *edx_27 = var_60.x
0042fec4        edx_27[1] = var_60.y
0042fecb        edx_27[2] = var_60.z
0042fed1        char* ecx_19 = object->facequads + edi_2
0042fed6        if ((*ecx_19 & 0x80) == 0)
0042fedc        int32_t eax_15 = 0
0042fede        eax_15.b = ecx_19[2]
0042fede        eax_15:1.b = ecx_19[3]
0042fee6        int32_t edx_28 = eax_15 * 3
0042fee9        struct Vec3* vertex_normals = object->vertex_normals
0042feef        float* eax_16 = vertex_normals + (edx_28 << 2)
0042fef2        *eax_16 = fconvert.s(fconvert.t(var_60.x) + fconvert.t(*(vertex_normals + (edx_28 << 2))))
0042fefb        eax_16[1] = fconvert.s(fconvert.t(var_60.y) + fconvert.t(eax_16[1]))
0042ff05        eax_16[2] = fconvert.s(fconvert.t(var_60.z) + fconvert.t(eax_16[2]))
0042ff0b        int32_t eax_17 = 0
0042ff11        eax_17.w = *(&object->facequads->vertex_1 + edi_2)
0042ff16        int32_t edx_29 = eax_17 * 3
0042ff19        struct Vec3* vertex_normals_1 = object->vertex_normals
0042ff1f        float* eax_18 = vertex_normals_1 + (edx_29 << 2)
0042ff22        *eax_18 = fconvert.s(fconvert.t(var_60.x) + fconvert.t(*(vertex_normals_1 + (edx_29 << 2))))
0042ff2b        eax_18[1] = fconvert.s(fconvert.t(var_60.y) + fconvert.t(eax_18[1]))
0042ff35        eax_18[2] = fconvert.s(fconvert.t(var_60.z) + fconvert.t(eax_18[2]))
0042ff3b        int32_t eax_19 = 0
0042ff41        eax_19.w = *(&object->facequads->vertex_2 + edi_2)
0042ff46        int32_t edx_30 = eax_19 * 3
0042ff49        struct Vec3* vertex_normals_2 = object->vertex_normals
0042ff4f        float* eax_20 = vertex_normals_2 + (edx_30 << 2)
0042ff52        *eax_20 = fconvert.s(fconvert.t(var_60.x) + fconvert.t(*(vertex_normals_2 + (edx_30 << 2))))
0042ff5b        eax_20[1] = fconvert.s(fconvert.t(var_60.y) + fconvert.t(eax_20[1]))
0042ff65        eax_20[2] = fconvert.s(fconvert.t(var_60.z) + fconvert.t(eax_20[2]))
0042ff6b        int32_t eax_21 = 0
0042ff71        eax_21.w = *(&object->facequads->vertex_3 + edi_2)
0042ff76        int32_t edx_31 = eax_21 * 3
0042ff79        struct Vec3* vertex_normals_3 = object->vertex_normals
0042ff7f        float* eax_22 = vertex_normals_3 + (edx_31 << 2)
0042ff82        int32_t edx_32 = 0
0042ff84        *eax_22 = fconvert.s(fconvert.t(var_60.x) + fconvert.t(*(vertex_normals_3 + (edx_31 << 2))))
0042ff8d        eax_22[1] = fconvert.s(fconvert.t(var_60.y) + fconvert.t(eax_22[1]))
0042ff97        eax_22[2] = fconvert.s(fconvert.t(var_60.z) + fconvert.t(eax_22[2]))
0042ff9d        edx_32.w = *(&object->facequads->vertex_0 + edi_2)
0042ffa2        int32_t ecx_24 = 0
0042ffb0        pointer[edx_32] = fconvert.s(fconvert.t(pointer[edx_32]) + fconvert.t(1f))
0042ffb5        ecx_24.w = *(&object->facequads->vertex_1 + edi_2)
0042ffc6        pointer[ecx_24] = fconvert.s(fconvert.t(pointer[ecx_24]) + fconvert.t(1f))
0042ffcb        int32_t eax_26 = 0
0042ffcd        eax_26.w = *(&object->facequads->vertex_2 + edi_2)
0042ffde        pointer[eax_26] = fconvert.s(fconvert.t(pointer[eax_26]) + fconvert.t(1f))
0042ffe3        int32_t edx_34 = 0
0042ffe5        edx_34.w = *(&object->facequads->vertex_3 + edi_2)
0042fff6        pointer[edx_34] = fconvert.s(fconvert.t(pointer[edx_34]) + fconvert.t(1f))
0042fffb        int32_t eax_29 = 0
00430001        eax_29.w = *(&object->facequads->vertex_0 + edi_2)
00430006        int32_t edx_35 = eax_29 * 3
00430009        struct Vec3* vertex_normals_4 = object->vertex_normals
0043000f        float* eax_30 = vertex_normals_4 + (edx_35 << 2)
00430012        *eax_30 = fconvert.s(fconvert.t(var_54.x) + fconvert.t(*(vertex_normals_4 + (edx_35 << 2))))
0043001b        eax_30[1] = fconvert.s(fconvert.t(var_54.y) + fconvert.t(eax_30[1]))
00430025        eax_30[2] = fconvert.s(fconvert.t(var_54.z) + fconvert.t(eax_30[2]))
0043002b        int32_t eax_31 = 0
00430031        eax_31.w = *(&object->facequads->vertex_1 + edi_2)
00430036        int32_t edx_36 = eax_31 * 3
00430039        struct Vec3* vertex_normals_5 = object->vertex_normals
0043003f        float* eax_32 = vertex_normals_5 + (edx_36 << 2)
00430042        *eax_32 = fconvert.s(fconvert.t(var_54.x) + fconvert.t(*(vertex_normals_5 + (edx_36 << 2))))
0043004b        eax_32[1] = fconvert.s(fconvert.t(var_54.y) + fconvert.t(eax_32[1]))
00430055        eax_32[2] = fconvert.s(fconvert.t(var_54.z) + fconvert.t(eax_32[2]))
0043005b        int32_t eax_33 = 0
00430061        eax_33.w = *(&object->facequads->vertex_2 + edi_2)
00430066        int32_t edx_37 = eax_33 * 3
00430069        struct Vec3* vertex_normals_6 = object->vertex_normals
0043006f        float* eax_34 = vertex_normals_6 + (edx_37 << 2)
00430072        *eax_34 = fconvert.s(fconvert.t(var_54.x) + fconvert.t(*(vertex_normals_6 + (edx_37 << 2))))
0043007b        eax_34[1] = fconvert.s(fconvert.t(var_54.y) + fconvert.t(eax_34[1]))
00430085        eax_34[2] = fconvert.s(fconvert.t(var_54.z) + fconvert.t(eax_34[2]))
0043008b        int32_t eax_35 = 0
00430091        eax_35.w = *(&object->facequads->vertex_3 + edi_2)
00430096        int32_t edx_38 = eax_35 * 3
00430099        struct Vec3* vertex_normals_7 = object->vertex_normals
0043009f        float* eax_36 = vertex_normals_7 + (edx_38 << 2)
004300a2        int32_t edx_39 = 0
004300a4        *eax_36 = fconvert.s(fconvert.t(var_54.x) + fconvert.t(*(vertex_normals_7 + (edx_38 << 2))))
004300ad        eax_36[1] = fconvert.s(fconvert.t(var_54.y) + fconvert.t(eax_36[1]))
004300b7        eax_36[2] = fconvert.s(fconvert.t(var_54.z) + fconvert.t(eax_36[2]))
004300bd        edx_39.w = *(&object->facequads->vertex_0 + edi_2)
004300c2        int32_t ecx_31 = 0
004300d0        pointer[edx_39] = fconvert.s(fconvert.t(pointer[edx_39]) + fconvert.t(2.0999999f))
004300d5        ecx_31.w = *(&object->facequads->vertex_1 + edi_2)
004300e6        pointer[ecx_31] = fconvert.s(fconvert.t(pointer[ecx_31]) + fconvert.t(2.0999999f))
004300eb        int32_t eax_40 = 0
004300ed        eax_40.w = *(&object->facequads->vertex_2 + edi_2)
004300fe        pointer[eax_40] = fconvert.s(fconvert.t(pointer[eax_40]) + fconvert.t(2.0999999f))
00430103        int32_t edx_41 = 0
00430105        edx_41.w = *(&object->facequads->vertex_3 + edi_2)
00430116        int32_t edx_42 = 0
00430118        pointer[edx_41] = fconvert.s(fconvert.t(pointer[edx_41]) + fconvert.t(2.0999999f))
0043011d        int32_t vertex_count = object->vertex_count
00430120        void* eax_44 = object->facequads + edi_2
00430122        edx_42.w = *(eax_44 + 2)
00430128        if (edx_42 s> vertex_count)
0043014d        report_errorf("Invalid Face Vertex Index")
0043012a        int32_t edx_43 = 0
0043012c        edx_43.w = *(eax_44 + 4)
00430132        if (edx_43 s> vertex_count)
0043014d        report_errorf("Invalid Face Vertex Index")
00430134        int32_t edx_44 = 0
00430136        edx_44.w = *(eax_44 + 6)
0043013c        if (edx_44 s> vertex_count)
0043014d        report_errorf("Invalid Face Vertex Index")
0043013e        int32_t edx_45 = 0
00430140        edx_45.w = *(eax_44 + 8)
00430146        if (edx_45 s> vertex_count)
0043014d        report_errorf("Invalid Face Vertex Index")
00430164        edi_2 = &edi_2[0xc]
00430167        cond:2_1 = var_68 + 1 s< object->facequad_count
00430169        var_68 += 1
0043016d        var_64_1 += 0x18
00430171        do while (cond:2_1)
00430177        edi_2 = nullptr
0043017c        int32_t var_68_1 = 0
00430182        if (object->vertex_count s> 0)
00430188        float* pointer_1 = pointer
0043020e        bool cond:1_1
0043018a        struct Vec3* vertex_normals_8 = object->vertex_normals
0043018f        long double x87_r7_93 = fconvert.t(*pointer_1)
00430195        float* eax_49 = edi_2 + vertex_normals_8
0043019b        *eax_49 = fconvert.s(fconvert.t(*(edi_2 + vertex_normals_8)) / x87_r7_93)
004301a2        eax_49[1] = fconvert.s(fconvert.t(eax_49[1]) / x87_r7_93)
004301aa        eax_49[2] = fconvert.s(fconvert.t(eax_49[2]) / x87_r7_93)
004301b4        normalize_vector(edi_2 + object->vertex_normals)
004301bc        pointer_1 = &pointer_1[1]
004301bf        int32_t* eax_52 = object->vertex_normals + edi_2
004301c1        edi_2 = &edi_2[3]
004301df        float var_8_2 = fconvert.s(fconvert.t(eax_52[1]) * fconvert.t(-1f))
004301e6        long double x87_r7_102 = fconvert.t(eax_52[2]) * fconvert.t(-1f)
004301f0        *eax_52 = fconvert.s(fconvert.t(*eax_52) * fconvert.t(-1f))
004301f2        eax_52[1] = var_8_2
004301fd        eax_52[2] = fconvert.s(x87_r7_102)
00430208        cond:1_1 = var_68_1 + 1 s< object->vertex_count
0043020a        var_68_1 += 1
0043020e        do while (cond:1_1)
00430215        free_tracked_memory(pointer)
00430224        return
