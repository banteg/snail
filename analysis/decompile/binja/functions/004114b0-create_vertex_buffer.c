/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: create_vertex_buffer @ 0x4114b0 */

004114bd        factory->buffers[factory->count].fvf = fvf
004114c4        int32_t vertex_count_1
004114c4        if (fvf == 2)
00411534        struct Direct3DDevice8* device_2 = g_direct3d_renderer.device
00411559        vertex_count_1 = device_2->vtbl->CreateVertexBuffer(device_2, vertex_count * 0xc, 8, 2, 1, factory + (factory->count + 1) * 0xc)
004114cb        if (fvf == 0x102)
00411506        struct Direct3DDevice8* device_1 = g_direct3d_renderer.device
0041152e        vertex_count_1 = device_1->vtbl->CreateVertexBuffer(device_1, vertex_count * 0x14, 8, 0x102, 1, factory + (factory->count + 1) * 0xc)
004114d0        if (fvf != 0x142)
0041155d        vertex_count_1 = vertex_count
004114d8        struct Direct3DDevice8* device = g_direct3d_renderer.device
00411500        vertex_count_1 = device->vtbl->CreateVertexBuffer(device, vertex_count * 0x18, 8, 0x142, 1, factory + (factory->count + 1) * 0xc)
00411563        if (vertex_count_1 != 0)
0041156a        report_errorf("Vertex Buffer Request fail")
00411578        if (vertex_count_1 == 0x8876017c)
0041157a        char* var_c_4 = "\tOut of video memory\n"
00411587        if (vertex_count_1 == 0x8007000e)
00411589        var_c_4 = "\tOut of memory\n"
00411596        if (vertex_count_1 == 0x8876086c)
00411598        var_c_4 = "\tInvalid call\n"
004115a7        int32_t edx_5 = factory->count + 1
004115aa        factory->count = edx_5
004115b1        if (edx_5 != 0xbb8)
004115cb        return factory + edx_5 * 0xc - 8
004115b8        report_errorf("DX_VERTEXBUFFER_MAX Overflow")
004115c0        while (true)
