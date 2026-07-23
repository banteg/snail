/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: calc_object_edges @ 0x4308b0 */

004308b0        struct Object* object_1 = object
004308b8        if ((object->flags.b & 1) == 0)
004308b8        return
004308c0        struct ObjectFaceQuad* face_cursor = object->facequads
004308c9        struct ObjectToonEdge* build_edges = get_archive_data_base()
004308cb        int32_t edge_count = 0
004308cd        g_object_edge_build_edges = build_edges
004308d3        g_object_edge_build_count = 0
004308dc        int32_t face_index = 0
004308e2        if (object->facequad_count s> 0)
004308e8        int32_t normal_index = 0
0043098a        bool cond:0_1
004308ea        int32_t vertex_b = 0
004308ec        int32_t vertex_a_2 = 0
004308ee        vertex_b.w = face_cursor->vertex_1
004308f2        vertex_a_2.w = face_cursor->vertex_0
004308fb        add_object_edge(object, vertex_a_2, vertex_b, normal_index)
00430900        int32_t vertex_b_4 = 0
00430902        int32_t vertex_a = 0
00430904        vertex_b_4.w = face_cursor->vertex_0
00430908        vertex_a.w = face_cursor->vertex_2
00430911        add_object_edge(object, vertex_a, vertex_b_4, normal_index)
00430916        int32_t vertex_b_2 = 0
00430918        int32_t vertex_a_4 = 0
0043091a        vertex_b_2.w = face_cursor->vertex_2
0043091e        vertex_a_4.w = face_cursor->vertex_1
00430927        add_object_edge(object, vertex_a_4, vertex_b_2, normal_index)
0043092f        if ((face_cursor->.header_word.b & 0x80) == 0)
00430931        int32_t vertex_b_1 = 0
00430936        vertex_b_1.w = face_cursor->vertex_2
0043093a        int32_t vertex_a_3 = 0
0043093c        vertex_a_3.w = face_cursor->vertex_0
00430945        add_object_edge(object, vertex_a_3, vertex_b_1, normal_index + 1)
0043094a        int32_t vertex_b_5 = 0
0043094c        int32_t vertex_a_1 = 0
0043094e        vertex_b_5.w = face_cursor->vertex_0
00430952        vertex_a_1.w = face_cursor->vertex_3
0043095b        add_object_edge(object, vertex_a_1, vertex_b_5, normal_index + 1)
00430960        int32_t vertex_b_3 = 0
00430962        int32_t vertex_a_5 = 0
00430964        vertex_b_3.w = face_cursor->vertex_3
00430968        vertex_a_5.w = face_cursor->vertex_2
00430971        add_object_edge(object, vertex_a_5, vertex_b_3, normal_index + 1)
0043097d        face_cursor = &face_cursor[1]
00430981        normal_index += 2
00430984        cond:0_1 = face_index + 1 s< object->facequad_count
00430986        face_index += 1
0043098a        do while (cond:0_1)
00430990        build_edges = g_object_edge_build_edges
00430996        edge_count = g_object_edge_build_count
004309a2        if (((object->flags).w:1.b & 0x80) != 0)
004309a4        int32_t edge_index = 0
004309a8        if (edge_count s> 0)
004309aa        int32_t edge_byte_offset = 0
004309ac        int32_t edge_byte_offset_spill = 0
004309b4        if ((*(edge_byte_offset + build_edges) & 1) != 0)
004309b9        int32_t shift_index = edge_index
004309bd        if (edge_index s< edge_count - 1)
004309ca        shift_index += 1
004309cb        __builtin_memcpy(build_edges + edge_byte_offset, edge_byte_offset + build_edges + 0x24, 0x24)
004309cd        edge_count = g_object_edge_build_count
004309d3        build_edges = g_object_edge_build_edges
004309d9        edge_byte_offset += 0x24
004309e1        do while (shift_index s< edge_count - 1)
004309e3        edge_byte_offset = edge_byte_offset_spill
004309e7        edge_count -= 1
004309e8        edge_index -= 1
004309e9        g_object_edge_build_count = edge_count
004309ef        edge_byte_offset -= 0x24
004309f2        edge_index += 1
004309f3        edge_byte_offset += 0x24
004309f8        edge_byte_offset_spill = edge_byte_offset
004309fc        do while (edge_index s< edge_count)
00430a01        request_object_edges(object, edge_count)
00430a17        int32_t edge_byte_count = g_object_edge_build_count * 0x24
00430a1f        uint8_t* copy_source_tail
00430a1f        uint8_t* copy_destination_tail
00430a1f        copy_destination_tail, copy_source_tail = __builtin_memcpy(object->edges, g_object_edge_build_edges, edge_byte_count & 0xfffffffc)
00430a26        __builtin_memcpy(copy_destination_tail, copy_source_tail, edge_byte_count & 3)
00430a2d        return
