/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_direct3d_renderer @ 0x4129c0 */

004129c5        initialize_direct3d_renderer_defaults(&g_direct3d_renderer)
004129d1        initialize_d3d8_device(&g_direct3d_renderer, 0)
004129e7        g_direct3d_renderer.renderer_state = create_object_vertex_buffer_resource(&g_direct3d_renderer, 8, 0x142)
004129ec        struct ObjectRenderBuffers* eax_1
004129ec        eax_1.b = 1
004129ee        return 1
