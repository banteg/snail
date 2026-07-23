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
004305df        int32_t i_1 = 0
004305e9        struct Vec3 rhs
004305e9        if (object_edge_build_count_1 s<= 0)
004306a3        label_4306a3:
004306a3        g_object_edge_build_edges[object_edge_build_count_1].flags = 1
004306b7        g_object_edge_build_edges[g_object_edge_build_count].vertex_a = vertex_a
004306cb        g_object_edge_build_edges[g_object_edge_build_count].vertex_b = vertex_b
004306dc        g_object_edge_build_edges[g_object_edge_build_count].normal_a = normal_index_1
004306ed        g_object_edge_build_edges[g_object_edge_build_count].normal_b = 0
004306f5        struct Vec3* vertices_1 = object->vertices
004306f8        struct Vec3* new_edge_vertex_a = &vertices_1[vertex_a]
004306fb        int32_t ecx_3 = vertex_b * 3
00430703        struct Vec3* new_edge_vertex_b = vertices_1 + (ecx_3 << 2)
00430706        rhs.x = fconvert.s(fconvert.t(*(vertices_1 + (ecx_3 << 2))) - fconvert.t(new_edge_vertex_a->x))
00430714        rhs.y = fconvert.s(fconvert.t(new_edge_vertex_b->y) - fconvert.t(new_edge_vertex_a->y))
00430722        struct Vec3 direction
00430722        direction.x = rhs.x
00430726        direction.y = rhs.y
0043072a        rhs.z = fconvert.s(fconvert.t(new_edge_vertex_b->z) - fconvert.t(new_edge_vertex_a->z))
00430732        direction.z = rhs.z
0043074c        g_object_edge_build_edges[g_object_edge_build_count].length = fconvert.s(normalize_vector(&direction))
0043075e        struct Vec3* output_direction = &g_object_edge_build_edges[g_object_edge_build_count].direction
00430766        output_direction->x = direction.x
0043076c        output_direction->y = direction.y
00430773        output_direction->z = direction.z
0043077c        g_object_edge_build_count += 1
0043077c        return
004305ef        struct Vec3* vertices = object->vertices
004305f5        struct Vec3* eax_3 = &vertices[vertex_b]
00430601        int32_t* edge_vertex_b_cursor = &g_object_edge_build_edges->vertex_b
00430604        while (true)
00430607        int32_t eax_6 = edge_vertex_b_cursor[-1] * 3
0043060a        long double x87_r7_1 = fconvert.t(*(vertices + (eax_6 << 2)))
0043060d        struct Vec3* existing_vertex_a = vertices + (eax_6 << 2)
00430614        long double temp2_1 = fconvert.t(eax_3->x)
00430614        x87_r7_1 - temp2_1
0043061b        if ((((x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00430621        long double x87_r7_2 = fconvert.t(existing_vertex_a->y)
00430624        long double temp3_1 = fconvert.t(eax_3->y)
00430624        x87_r7_2 - temp3_1
0043062c        if ((((x87_r7_2 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp3_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00430632        long double x87_r7_3 = fconvert.t(existing_vertex_a->z)
00430635        long double temp4_1 = fconvert.t(eax_3->z)
00430635        x87_r7_3 - temp4_1
0043063d        if ((((x87_r7_3 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp4_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp4_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00430642        int32_t eax_14 = *edge_vertex_b_cursor * 3
00430645        long double x87_r7_4 = fconvert.t(*(vertices + (eax_14 << 2)))
00430648        struct Vec3* existing_vertex_b = vertices + (eax_14 << 2)
0043064b        int32_t eax_15 = vertex_a * 3
0043064e        long double temp5_1 = fconvert.t(*(vertices + (eax_15 << 2)))
0043064e        x87_r7_4 - temp5_1
00430651        struct Vec3* candidate_vertex_a = vertices + (eax_15 << 2)
00430659        if ((((x87_r7_4 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp5_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp5_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
0043065b        long double x87_r7_5 = fconvert.t(existing_vertex_b->y)
0043065e        long double temp6_1 = fconvert.t(candidate_vertex_a->y)
0043065e        x87_r7_5 - temp6_1
00430666        if ((((x87_r7_5 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp6_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp6_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00430668        long double x87_r7_6 = fconvert.t(existing_vertex_b->z)
0043066b        long double temp7_1 = fconvert.t(candidate_vertex_a->z)
0043066b        x87_r7_6 - temp7_1
00430673        if ((((x87_r7_6 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp7_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp7_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
0043078b        int32_t i = i_1
0043078f        struct ObjectToonEdge* object_edge_build_edges_2 = g_object_edge_build_edges
0043079b        int32_t flags = object_edge_build_edges_2[i].flags
004307a0        if ((flags.b & 1) != 0)
004307a2        flags.b &= 0xfe
004307a4        object_edge_build_edges_2[i].flags = flags
004307a7        struct ObjectToonEdge* object_edge_build_edges_1 = g_object_edge_build_edges
004307b2        object_edge_build_edges_1[i].flags |= 2
004307c3        g_object_edge_build_edges[i].normal_b = normal_index
004307cb        if ((object->flags.b & 4) == 0)
004307cd        struct ObjectToonEdge* object_edge_build_edges_4 = g_object_edge_build_edges
004307d3        struct Vec3* facequad_normals = object->facequad_normals
004307dd        struct Vec3* face_normal_a = &facequad_normals[object_edge_build_edges_4[i].normal_a]
004307e0        int32_t edi_1
004307e0        edi_1.b = face_normal_a->x.b
004307e0        edi_1:1.b = face_normal_a->x:1.b
004307e0        edi_1:2.b = face_normal_a->x:2.b
004307e0        edi_1:3.b = face_normal_a->x:3.b
004307e2        struct Vec3 lhs
004307e2        lhs.x = edi_1
004307e6        int32_t edi_2
004307e6        edi_2.b = face_normal_a->y.b
004307e6        edi_2:1.b = face_normal_a->y:1.b
004307e6        edi_2:2.b = face_normal_a->y:2.b
004307e6        edi_2:3.b = face_normal_a->y:3.b
004307e9        lhs.y = edi_2
004307f0        lhs.z = face_normal_a->z
004307fb        struct Vec3* face_normal_b = &facequad_normals[object_edge_build_edges_4[i].normal_b]
00430800        rhs.x = face_normal_b->x
0043080c        rhs.y = face_normal_b->y
0043081c        rhs.z = face_normal_b->z
00430820        struct Vec3 normal_cross
00430820        cross_vectors(&normal_cross, &lhs, &rhs)
00430829        long double st0_2 = vector_magnitude(&normal_cross)
0043082e        long double temp8_1 = fconvert.t(0.0500000007f)
0043082e        st0_2 - temp8_1
00430839        long double st0_3
00430839        long double temp9_1
00430839        if ((((st0_2 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(st0_2, temp8_1) ? 1 : 0) << 0xa | (st0_2 == temp8_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00430849        st0_3 = dot_vector(&normal_cross, &g_object_edge_build_edges[i].direction)
0043084e        temp9_1 = fconvert.t(0.00200000009f)
0043084e        st0_3 - temp9_1
00430859        if ((((st0_2 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(st0_2, temp8_1) ? 1 : 0) << 0xa | (st0_2 == temp8_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0 || (((st0_3 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(st0_3, temp9_1) ? 1 : 0) << 0xa | (st0_3 == temp9_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00430868        if (i s< g_object_edge_build_count - 1)
0043086a        int32_t shift_byte_offset = i * 0x24
0043086c        struct ObjectToonEdge* object_edge_build_edges_3 = g_object_edge_build_edges
00430872        i += 1
00430873        struct ObjectToonEdge* shift_source_edge = shift_byte_offset + object_edge_build_edges_3 + 0x24
00430877        struct ObjectToonEdge* shift_destination_edge = shift_byte_offset + object_edge_build_edges_3
0043087f        shift_byte_offset += 0x24
00430882        __builtin_memcpy(shift_destination_edge, shift_source_edge, 0x24)
0043088d        do while (i s< g_object_edge_build_count - 1)
00430898        g_object_edge_build_count -= 1
004308a1        return
004307a0        break
00430679        object_edge_build_count_1 = g_object_edge_build_count
00430683        edge_vertex_b_cursor = &edge_vertex_b_cursor[9]
00430687        bool cond:0_1 = i_1 + 1 s< object_edge_build_count_1
00430689        i_1 += 1
0043068d        if (not(cond:0_1))
00430693        normal_index_1 = normal_index
00430697        goto label_4306a3
00430788        return
