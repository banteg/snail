/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: direct3d_renderer_set_cull_mode @ 0x411700 */

00411706        struct Direct3DDevice8* device = renderer->device
0041170c        if (cull_front == 0)
0041172b        return device->vtbl->SetRenderState(device, 0x16, 1)
0041171b        return device->vtbl->SetRenderState(device, 0x16, 3)
