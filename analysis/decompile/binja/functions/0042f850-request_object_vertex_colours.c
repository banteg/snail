/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: request_object_vertex_colours @ 0x42f850 */

0042f864        mesh->vertex_colours = allocate_tracked_memory(mesh->vertex_count << 4, "Object Vertex Colours List")
0042f86d        int32_t i = 0
0042f871        if (mesh->vertex_count s<= 0)
0042f871        return 
0042f874        int32_t* eax_4 = nullptr
0042f87e        i += 1
0042f87f        *(eax_4 + mesh->vertex_colours) = 0x3f800000
0042f885        *(&mesh->vertex_colours->g + eax_4) = 0x3f800000
0042f88c        *(&mesh->vertex_colours->b + eax_4) = 0x3f800000
0042f893        eax_4 = &eax_4[4]
0042f898        do while (i s< mesh->vertex_count)
0042f89c        return
