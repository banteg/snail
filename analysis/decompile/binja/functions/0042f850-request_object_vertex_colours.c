/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: request_object_vertex_colours @ 0x42f850 */

0042f864        object->vertex_colours = allocate_tracked_memory(object->vertex_count << 4, "Object Vertex Colours List")
0042f86d        int32_t vertex_index = 0
0042f871        if (object->vertex_count s<= 0)
0042f871        return
0042f874        int32_t colour_byte_offset = 0
0042f87e        vertex_index += 1
0042f87f        *(colour_byte_offset + object->vertex_colours) = 0x3f800000
0042f885        *(&object->vertex_colours->g + colour_byte_offset) = 0x3f800000
0042f88c        *(&object->vertex_colours->b + colour_byte_offset) = 0x3f800000
0042f893        colour_byte_offset += 0x10
0042f898        do while (vertex_index s< object->vertex_count)
0042f89c        return
