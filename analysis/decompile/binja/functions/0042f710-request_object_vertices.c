/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: request_object_vertices @ 0x42f710 */

0042f71e        if (vertex_count s> 0x10000)
0042f725        report_errorf("Too many Vertices")
0042f72d        int32_t vertex_count_1 = object->vertex_count
0042f736        if (vertex_count_1 s> 0 && vertex_count_1 s< vertex_count)
0042f73d        report_errorf("Reallocation of Vertices impending\n")
0042f746        free_tracked_memory(object->vertices)
0042f74e        object->vertex_count = 0
0042f75a        if (object->vertex_count != 0)
0042f75a        return
0042f768        object->vertex_count = vertex_count
0042f775        object->vertices = allocate_tracked_memory(vertex_count * 0xc, "Object Vertex List")
0042f778        request_object_vertex_colours(object)
0042f77f        return
