/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: create_index_buffer @ 0x4115d0 */

004115d3        struct Direct3DDevice8* device = g_direct3d_renderer.device
004115f0        int32_t eax = device->vtbl->CreateIndexBuffer(device, index_count * 2, 0x28, 0x65, 1, &factory->buffers[factory->count])
004115f7        int32_t ecx_2 = factory->count + 1
004115fa        factory->count = ecx_2
00411601        if (ecx_2 == 0xbb8)
00411608        report_errorf("Too many Index Buffers, Increase DX_INDEXBUFFER_MAX in GDX.h")
00411612        if (eax != 0)
00411619        report_errorf("Vertex Buffer Request fail")
00411628        return factory + (factory->count << 2)
