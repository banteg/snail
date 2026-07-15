/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: calc_object_edges @ 0x4308b0 */

004308b0        struct Object* object_1 = object
004308b8        if ((object->flags.b & 1) == 0)
004308b8        return
004308c0        struct ObjectFaceQuad* facequads = object->facequads
004308c9        void* object_edge_build_edges_1 = get_archive_data_base()
004308cb        int32_t object_edge_build_count_1 = 0
004308cd        g_object_edge_build_edges = object_edge_build_edges_1
004308d3        g_object_edge_build_count = 0
004308dc        object_1 = nullptr
004308e2        if (object->facequad_count s> 0)
004308e8        int32_t normal_index = 0
004308ea        int32_t vertex_b = 0
004308ec        int32_t vertex_a_2 = 0
004308ee        vertex_b.w = facequads->vertex_1
004308f2        vertex_a_2.w = facequads->vertex_0
004308fb        add_object_edge(object, vertex_a_2, vertex_b, normal_index)
00430900        int32_t vertex_b_4 = 0
00430902        int32_t vertex_a = 0
00430904        vertex_b_4.w = facequads->vertex_0
00430908        vertex_a.w = facequads->vertex_2
00430911        add_object_edge(object, vertex_a, vertex_b_4, normal_index)
00430916        int32_t vertex_b_2 = 0
00430918        int32_t vertex_a_4 = 0
0043091a        vertex_b_2.w = facequads->vertex_2
0043091e        vertex_a_4.w = facequads->vertex_1
00430927        add_object_edge(object, vertex_a_4, vertex_b_2, normal_index)
0043092f        if ((facequads->.header_word.b & 0x80) == 0)
00430931        int32_t vertex_b_1 = 0
00430936        vertex_b_1.w = facequads->vertex_2
0043093a        int32_t vertex_a_3 = 0
0043093c        vertex_a_3.w = facequads->vertex_0
00430945        add_object_edge(object, vertex_a_3, vertex_b_1, normal_index + 1)
0043094a        int32_t vertex_b_5 = 0
0043094c        int32_t vertex_a_1 = 0
0043094e        vertex_b_5.w = facequads->vertex_0
00430952        vertex_a_1.w = facequads->vertex_3
0043095b        add_object_edge(object, vertex_a_1, vertex_b_5, normal_index + 1)
00430960        int32_t vertex_b_3 = 0
00430962        int32_t vertex_a_5 = 0
00430964        vertex_b_3.w = facequads->vertex_3
00430968        vertex_a_5.w = facequads->vertex_2
00430971        add_object_edge(object, vertex_a_5, vertex_b_3, normal_index + 1)
0043097d        facequads = &facequads[1]
00430981        normal_index += 2
00430986        object_1 = &object_1->_pad_00[1]
0043098a        do while (&object_1->_pad_00[1] s< object->facequad_count)
00430990        object_edge_build_edges_1 = g_object_edge_build_edges
00430996        object_edge_build_count_1 = g_object_edge_build_count
004309a2        if (((object->flags).w:1.b & 0x80) != 0)
004309a4        int32_t i_1 = 0
004309a8        if (object_edge_build_count_1 s> 0)
004309aa        struct Object* object_2 = nullptr
004309ac        object_1 = nullptr
004309b4        if ((*(object_2 + object_edge_build_edges_1) & 1) != 0)
004309b9        int32_t i = i_1
004309bd        if (i_1 s< object_edge_build_count_1 - 1)
004309ca        i += 1
004309cb        __builtin_memcpy(object_edge_build_edges_1 + object_2, &object_2->_pad_1c[8] + object_edge_build_edges_1, 0x24)
004309cd        object_edge_build_count_1 = g_object_edge_build_count
004309d3        object_edge_build_edges_1 = g_object_edge_build_edges
004309d9        object_2 = &object_2->_pad_1c[8]
004309e1        do while (i s< object_edge_build_count_1 - 1)
004309e3        object_2 = object_1
004309e7        object_edge_build_count_1 -= 1
004309e8        i_1 -= 1
004309e9        g_object_edge_build_count = object_edge_build_count_1
004309ef        object_2 -= 0x24
004309f2        i_1 += 1
004309f3        object_2 = &object_2->_pad_1c[8]
004309f8        object_1 = object_2
004309fc        do while (i_1 s< object_edge_build_count_1)
00430a01        request_object_edges(object, object_edge_build_count_1)
00430a17        int32_t ecx_9 = g_object_edge_build_count * 0x24
00430a1f        int32_t esi_5
00430a1f        int32_t edi_3
00430a1f        edi_3, esi_5 = __builtin_memcpy(object->edges, g_object_edge_build_edges, ecx_9 & 0xfffffffc)
00430a26        __builtin_memcpy(edi_3, esi_5, ecx_9 & 3)
00430a2d        return
