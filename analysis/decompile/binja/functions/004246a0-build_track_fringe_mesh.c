/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: build_track_fringe_mesh @ 0x4246a0 */

004246b7        set_bod_object(arg1 + 0x60, add_object_to_list(0x4b7648))
004246cd        void var_10
004246cd        int32_t* eax_1 = get_track_skirt_color(data_4df904 + 0x74618, &var_10)
004246da        struct PathTemplateStripMesh* mesh = *(arg1 + 0x84)
004246e0        *(arg1 + 0x88) = *eax_1
004246e5        *(arg1 + 0x8c) = eax_1[1]
004246eb        *(arg1 + 0x90) = eax_1[2]
004246f1        *(arg1 + 0x94) = eax_1[3]
004246f7        enum PathTemplateStripMeshFlags ebp_1 = mesh->flags | 0x100040
004246fd        mesh->_pad_14[0] = 5
004246fd        mesh->_pad_14[1] = 0
004246fd        mesh->_pad_14[2] = 0
004246fd        mesh->_pad_14[3] = 0
00424704        mesh->flags = ebp_1
00424714        request_object_vertices(mesh, (*(arg1 + 0x44) << 2) + 4)
00424721        request_object_facequads(mesh, *(arg1 + 0x44) << 1)
00424729        struct ObjectFaceQuad* facequads = mesh->facequads
00424735        int32_t var_68 = 0
0042473d        if (*(arg1 + 0x44) s>= 0)
00424743        void* __offset(Vec3, 0x14) esi_1 = mesh->vertices + 0x14
004249da        bool cond:2_1
00424746        int32_t eax_5
00424746        eax_5.b = *(arg1 + 0x3c)
0042474b        int32_t var_64_1
0042474b        int32_t var_60_1
0042474b        int32_t eax_6
0042474b        int32_t ecx_9
0042474b        int32_t edx_2
0042474b        if (eax_5.b == 0)
00424767        eax_6 = *(arg1 + 0x54)
0042476a        ecx_9 = 0
0042476c        edx_2 = 1
00424771        var_60_1 = eax_6
00424778        var_64_1 = eax_6 - 1
0042474d        eax_6 = *(arg1 + 0x54)
00424750        var_64_1 = 1
00424758        ecx_9 = eax_6
0042475a        var_60_1 = 0
00424762        edx_2 = eax_6 - 1
0042477d        struct Vec3* ebx_1 = esi_1 - 0x14
00424790        int32_t* edx_4 = *(*(arg1 + 0x24) + 0x38) + ((eax_6 + 1) * var_68 + edx_2) * 0xc
00424797        ebx_1->x = *edx_4
0042479c        ebx_1->y = edx_4[1]
004247a5        ebx_1->z = edx_4[2]
004247be        int32_t* eax_18 = *(*(arg1 + 0x24) + 0x38) + ((*(arg1 + 0x54) + 1) * var_68 + ecx_9) * 0xc
004247c3        (esi_1 - 0x14)->__offset(0xc).d = *eax_18
004247c8        (esi_1 - 0x14)->__offset(0x10).d = eax_18[1]
004247ce        (esi_1 - 0x14)->__offset(0x14).d = eax_18[2]
004247f1        struct Vec3 vector
004247f1        vector.x = fconvert.s(fconvert.t((esi_1 - 0x14)->__offset(0xc).d) - fconvert.t(ebx_1->x))
004247f9        vector.y = fconvert.s(fconvert.t((esi_1 - 0x14)->__offset(0x10).d) - fconvert.t((esi_1 - 0x14)->y))
00424805        vector.z = fconvert.s(fconvert.t((esi_1 - 0x14)->__offset(0x14).d) - fconvert.t((esi_1 - 0x14)->z))
00424809        normalize_vector(&vector)
00424824        float* ecx_14 = ebx_1
0042484d        float var_3c_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(vector.y) * fconvert.t(0.400000006f))) + fconvert.t((esi_1 - 0x14)->__offset(0x10).d))
00424855        long double x87_r7_15 = fconvert.t(fconvert.s(fconvert.t(vector.z) * fconvert.t(0.400000006f))) + fconvert.t((esi_1 - 0x14)->__offset(0x14).d)
0042485b        *ecx_14 = fconvert.s(fconvert.t(vector.x) * fconvert.t(0.400000006f) + fconvert.t((esi_1 - 0x14)->__offset(0xc).d))
0042485d        ecx_14[1] = var_3c_1
00424868        ecx_14[2] = fconvert.s(x87_r7_15)
00424883        int32_t* eax_27 = *(*(arg1 + 0x24) + 0x38) + ((*(arg1 + 0x54) + 1) * var_68 + var_64_1) * 0xc
0042488a        (esi_1 - 0x14)->__offset(0x18).d = *eax_27
0042488f        (esi_1 - 0x14)->__offset(0x1c).d = eax_27[1]
00424899        (esi_1 - 0x14)->__offset(0x20).d = eax_27[2]
004248b3        int32_t* edx_17 = *(*(arg1 + 0x24) + 0x38) + ((*(arg1 + 0x54) + 1) * var_68 + var_60_1) * 0xc
004248b8        (esi_1 - 0x14)->__offset(0x24).d = *edx_17
004248bd        (esi_1 - 0x14)->__offset(0x28).d = edx_17[1]
004248c3        (esi_1 - 0x14)->__offset(0x2c).d = edx_17[2]
004248e8        vector.x = fconvert.s(fconvert.t((esi_1 - 0x14)->__offset(0x24).d) - fconvert.t((esi_1 - 0x14)->__offset(0x18).d))
004248ec        vector.y = fconvert.s(fconvert.t((esi_1 - 0x14)->__offset(0x28).d) - fconvert.t((esi_1 - 0x14)->__offset(0x1c).d))
004248fc        vector.z = fconvert.s(fconvert.t((esi_1 - 0x14)->__offset(0x2c).d) - fconvert.t((esi_1 - 0x14)->__offset(0x20).d))
00424900        normalize_vector(&vector)
0042493f        float var_24_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(vector.y) * fconvert.t(0.400000006f))) + fconvert.t((esi_1 - 0x14)->__offset(0x28).d))
00424947        long double x87_r7_30 = fconvert.t(fconvert.s(fconvert.t(vector.z) * fconvert.t(0.400000006f))) + fconvert.t((esi_1 - 0x14)->__offset(0x2c).d)
0042494e        (esi_1 - 0x14)->__offset(0x18).d = fconvert.s(fconvert.t(vector.x) * fconvert.t(0.400000006f) + fconvert.t((esi_1 - 0x14)->__offset(0x24).d))
00424951        (esi_1 - 0x14)->__offset(0x1c).d = var_24_1
00424958        long double x87_r7_31 = fconvert.t(arg3)
0042495f        long double temp1_1 = fconvert.t(-1f)
0042495f        x87_r7_31 - temp1_1
00424969        (esi_1 - 0x14)->__offset(0x20).d = fconvert.s(x87_r7_30)
0042496c        float eax_38
0042496c        eax_38.w = (x87_r7_31 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_31, temp1_1) ? 1 : 0) << 0xa | (x87_r7_31 == temp1_1 ? 1 : 0) << 0xe
00424971        if ((eax_38:1.b & 0x40) == 0)
00424995        long double x87_r7_33 = fconvert.t(arg3)
0042499c        long double temp2_1 = fconvert.t(1f)
0042499c        x87_r7_33 - temp2_1
004249a2        eax_38.w = (x87_r7_33 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_33, temp2_1) ? 1 : 0) << 0xa | (x87_r7_33 == temp2_1 ? 1 : 0) << 0xe
004249a7        if ((eax_38:1.b & 0x40) != 0)
004249a9        int32_t i_5 = 4
004249c7        int32_t i
004249ae        long double x87_r7_34 = fconvert.t(ebx_1->x)
004249b0        long double temp4_1 = fconvert.t(0f)
004249b0        x87_r7_34 - temp4_1
004249b6        eax_38.w = (x87_r7_34 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_34, temp4_1) ? 1 : 0) << 0xa | (x87_r7_34 == temp4_1 ? 1 : 0) << 0xe
004249bb        if ((eax_38:1.b & 1) != 0)
004249bd        ebx_1->x = 0
004249c3        ebx_1 = &ebx_1[1]
004249c6        i = i_5
004249c6        i_5 -= 1
004249c7        do while (i != 1)
00424973        int32_t i_4 = 4
00424991        int32_t i_1
00424978        long double x87_r7_32 = fconvert.t(ebx_1->x)
0042497a        long double temp3_1 = fconvert.t(0f)
0042497a        x87_r7_32 - temp3_1
00424980        eax_38.w = (x87_r7_32 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_32, temp3_1) ? 1 : 0) << 0xa | (x87_r7_32 == temp3_1 ? 1 : 0) << 0xe
00424985        if ((eax_38:1.b & 0x41) == 0)
00424987        ebx_1->x = 0
0042498d        ebx_1 = &ebx_1[1]
00424990        i_1 = i_4
00424990        i_4 -= 1
00424991        do while (i_1 != 1)
004249d1        esi_1 += 0x30
004249d4        cond:2_1 = var_68 + 1 s<= *(arg1 + 0x44)
004249d6        var_68 += 1
004249da        do while (cond:2_1)
004249e0        int32_t i_2 = *(arg1 + 0x44)
004249e3        int32_t i_3 = 0
004249ed        if (i_2 s> 0)
004249fc        uint16_t* esi_2 = &facequads->vertex_index_a
00424a16        (esi_2 - 2)->texture_ref = get_or_create_texture_ref(&data_4b7790, arg2, 0, 0)
00424a1b        uint16_t ebp_6 = (i_3 << 2).w
00424a31        (esi_2 - 2)->vertex_index_a = ebp_6 + 5
00424a34        (esi_2 - 2)->vertex_index_b = (i_3 << 2).w + 4
00424a3b        (esi_2 - 2)->vertex_index_c = ebp_6
00424a3f        (esi_2 - 2)->vertex_index_d = ebp_6 + 1
00424a48        (esi_2 - 2)->v3 = 0f
00424a4b        (esi_2 - 2)->u0 = 0.5f
00424a4e        (esi_2 - 2)->v0 = 0f
00424a51        __builtin_memcpy(&esi_2[0xb], "\x00\x00\x00\x3f\x00\x00\x80\x3f\x00\x00\x00\x3f\x00\x00\x80\x3f\x00\x00\x00\x3f", 0x14)
00424a6e        (esi_2 - 2)->__offset(0x3c).d = get_or_create_texture_ref(&data_4b7790, arg2, 0, 0)
00424a77        (esi_2 - 2)->__offset(0x32).w = ebp_6 + 6
00424a7e        (esi_2 - 2)->__offset(0x34).w = ebp_6 + 7
00424a85        (esi_2 - 2)->__offset(0x36).w = ebp_6 + 3
00424a89        (esi_2 - 2)->__offset(0x38).w = ebp_6 + 2
00424a92        (esi_2 - 2)->__offset(0x58).d = 0x3f000000
00424a95        (esi_2 - 2)->__offset(0x5c).d = 0x3f800000
00424a98        (esi_2 - 2)->__offset(0x40).d = 0x3f000000
00424a9b        (esi_2 - 2)->__offset(0x44).d = 0x3f800000
00424aa0        (esi_2 - 2)->__offset(0x48).d = 0x3f000000
00424aa3        (esi_2 - 2)->__offset(0x4c).d = 0
00424aa6        (esi_2 - 2)->__offset(0x50).d = 0x3f000000
00424aa9        (esi_2 - 2)->__offset(0x54).d = 0
00424ab3        i_2 = i_3 + 1
00424ab4        esi_2 = &esi_2[0x30]
00424ab9        i_3 = i_2
00424abd        do while (i_2 s< *(arg1 + 0x44))
00424aca        return i_2
