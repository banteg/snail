/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: add_object_edge @ 0x4305a0 */

004305a5        int32_t normal_index_1 = normal_index
004305bb        long double st0 = vector_magnitude(&object->facequad_normals[normal_index_1])
004305c0        long double temp1 = fconvert.t(0.899999976f)
004305c0        st0 - temp1
004305cb        if ((((st0 < temp1 ? 1 : 0) << 8 | (is_unordered.t(st0, temp1) ? 1 : 0) << 0xa | (st0 == temp1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004305cb        return
004305d1        int32_t object_edge_build_count_1 = g_object_edge_build_count
004305d7        int32_t vertex_b_1 = vertex_b
004305df        int32_t i_1 = 0
004305e9        struct Vec3 rhs
004305e9        if (object_edge_build_count_1 s<= 0)
004306a3        label_4306a3:
004306a3        *(g_object_edge_build_edges + object_edge_build_count_1 * 0x24) = 1
004306b7        *(g_object_edge_build_edges + g_object_edge_build_count * 0x24 + 4) = vertex_a
004306cb        *(g_object_edge_build_edges + g_object_edge_build_count * 0x24 + 8) = vertex_b_1
004306dc        *(g_object_edge_build_edges + g_object_edge_build_count * 0x24 + 0xc) = normal_index_1
004306ed        *(g_object_edge_build_edges + g_object_edge_build_count * 0x24 + 0x10) = 0
004306f5        struct Vec3* vertices_1 = object->vertices
004306f8        float* eax_28 = &vertices_1[vertex_a]
004306fb        int32_t ecx_4 = vertex_b_1 * 3
00430703        void* ecx_5 = vertices_1 + (ecx_4 << 2)
00430706        rhs.x = fconvert.s(fconvert.t(*(vertices_1 + (ecx_4 << 2))) - fconvert.t(*eax_28))
00430714        rhs.y = fconvert.s(fconvert.t(*(ecx_5 + 4)) - fconvert.t(eax_28[1]))
00430722        struct Vec3 vector
00430722        vector.x = rhs.x
00430726        vector.y = rhs.y
0043072a        rhs.z = fconvert.s(fconvert.t(*(ecx_5 + 8)) - fconvert.t(eax_28[2]))
00430732        vector.z = rhs.z
0043074c        *(g_object_edge_build_edges + g_object_edge_build_count * 0x24 + 0x20) = fconvert.s(normalize_vector(&vector))
0043075e        float* eax_33 = g_object_edge_build_edges + g_object_edge_build_count * 0x24 + 0x14
00430766        *eax_33 = vector.x
0043076c        eax_33[1] = vector.y
00430773        eax_33[2] = vector.z
0043077c        g_object_edge_build_count += 1
0043077c        return
004305ef        struct Vec3* vertices = object->vertices
004305f8        vertex_b = &vertices[vertex_b_1]
00430601        int32_t* ebp = g_object_edge_build_edges + 8
00430604        while (true)
00430607        int32_t eax_6 = ebp[-1] * 3
0043060a        long double x87_r7_1 = fconvert.t(*(vertices + (eax_6 << 2)))
0043060d        void* edi_1 = vertices + (eax_6 << 2)
00430614        long double temp2_1 = fconvert.t(*vertex_b)
00430614        x87_r7_1 - temp2_1
0043061b        if ((((x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00430621        long double x87_r7_2 = fconvert.t(*(edi_1 + 4))
00430624        long double temp3_1 = fconvert.t(*(vertex_b + 4))
00430624        x87_r7_2 - temp3_1
0043062c        if ((((x87_r7_2 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp3_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00430632        long double x87_r7_3 = fconvert.t(*(edi_1 + 8))
00430635        long double temp4_1 = fconvert.t(*(vertex_b + 8))
00430635        x87_r7_3 - temp4_1
0043063d        if ((((x87_r7_3 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp4_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp4_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00430642        int32_t eax_14 = *ebp * 3
00430645        long double x87_r7_4 = fconvert.t(*(vertices + (eax_14 << 2)))
00430648        void* edi_2 = vertices + (eax_14 << 2)
0043064b        int32_t eax_15 = vertex_a * 3
0043064e        long double temp5_1 = fconvert.t(*(vertices + (eax_15 << 2)))
0043064e        x87_r7_4 - temp5_1
00430651        void* ebx_1 = vertices + (eax_15 << 2)
00430659        if ((((x87_r7_4 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp5_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp5_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
0043065b        long double x87_r7_5 = fconvert.t(*(edi_2 + 4))
0043065e        long double temp6_1 = fconvert.t(*(ebx_1 + 4))
0043065e        x87_r7_5 - temp6_1
00430666        if ((((x87_r7_5 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp6_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp6_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00430668        long double x87_r7_6 = fconvert.t(*(edi_2 + 8))
0043066b        long double temp7_1 = fconvert.t(*(ebx_1 + 8))
0043066b        x87_r7_6 - temp7_1
00430673        if ((((x87_r7_6 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp7_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp7_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
0043078b        int32_t i = i_1
0043078f        int32_t object_edge_build_edges_2 = g_object_edge_build_edges
00430798        int32_t esi_2 = i * 0x24
0043079b        int32_t eax_36 = *(esi_2 + object_edge_build_edges_2)
004307a0        if ((eax_36.b & 1) != 0)
004307a2        eax_36.b &= 0xfe
004307a4        *(esi_2 + object_edge_build_edges_2) = eax_36
004307a7        int32_t object_edge_build_edges_1 = g_object_edge_build_edges
004307b2        *(esi_2 + object_edge_build_edges_1) |= 2
004307c3        *(esi_2 + g_object_edge_build_edges + 0x10) = normal_index
004307cb        if ((object->flags.b & 4) == 0)
004307cd        int32_t object_edge_build_edges_4 = g_object_edge_build_edges
004307d3        struct Vec3* facequad_normals = object->facequad_normals
004307dd        char* ecx_14 = &facequad_normals[*(esi_2 + object_edge_build_edges_4 + 0xc)]
004307e0        int32_t edi_3
004307e0        edi_3.b = *ecx_14
004307e0        edi_3:1.b = ecx_14[1]
004307e0        edi_3:2.b = ecx_14[2]
004307e0        edi_3:3.b = ecx_14[3]
004307e2        struct Vec3 lhs
004307e2        lhs.x = edi_3
004307e6        int32_t edi_4
004307e6        edi_4.b = ecx_14[4]
004307e6        edi_4:1.b = ecx_14[5]
004307e6        edi_4:2.b = ecx_14[6]
004307e6        edi_4:3.b = ecx_14[7]
004307e9        lhs.y = edi_4
004307f0        lhs.z = *(ecx_14 + 8)
004307fb        int32_t* eax_38 = &facequad_normals[*(esi_2 + object_edge_build_edges_4 + 0x10)]
00430800        rhs.x = *eax_38
0043080c        rhs.y = eax_38[1]
0043081c        rhs.z = eax_38[2]
00430820        struct Vec3 var_c
00430820        cross_vectors(&var_c, &lhs, &rhs)
00430829        long double st0_2 = vector_magnitude(&var_c)
0043082e        long double temp8_1 = fconvert.t(0.0500000007f)
0043082e        st0_2 - temp8_1
00430839        long double st0_3
00430839        long double temp9_1
00430839        if ((((st0_2 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(st0_2, temp8_1) ? 1 : 0) << 0xa | (st0_2 == temp8_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00430849        st0_3 = dot_vector(&var_c, esi_2 + g_object_edge_build_edges + 0x14)
0043084e        temp9_1 = fconvert.t(0.00200000009f)
0043084e        st0_3 - temp9_1
00430859        if ((((st0_2 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(st0_2, temp8_1) ? 1 : 0) << 0xa | (st0_2 == temp8_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0 || (((st0_3 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(st0_3, temp9_1) ? 1 : 0) << 0xa | (st0_3 == temp9_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00430868        if (i s< g_object_edge_build_count - 1)
0043086a        int32_t eax_45 = esi_2
0043086c        int32_t object_edge_build_edges_3 = g_object_edge_build_edges
00430872        i += 1
00430873        int32_t esi_3 = eax_45 + object_edge_build_edges_3 + 0x24
00430877        int32_t edi_5 = eax_45 + object_edge_build_edges_3
0043087f        eax_45 += 0x24
00430882        __builtin_memcpy(edi_5, esi_3, 0x24)
0043088d        do while (i s< g_object_edge_build_count - 1)
00430898        g_object_edge_build_count -= 1
004308a1        return
004307a0        break
00430679        object_edge_build_count_1 = g_object_edge_build_count
00430683        ebp = &ebp[9]
00430687        bool cond:0_1 = i_1 + 1 s< object_edge_build_count_1
00430689        i_1 += 1
0043068d        if (not(cond:0_1))
00430693        normal_index_1 = normal_index
00430697        goto label_4306a3
00430788        return
