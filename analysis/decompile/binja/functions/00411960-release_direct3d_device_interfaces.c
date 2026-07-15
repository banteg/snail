/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: release_direct3d_device_interfaces @ 0x411960 */

00411963        struct Direct3DDevice8* device = renderer->device
0041196b        if (device != 0)
00411970        device->vtbl->Release(device)
00411973        renderer->device = nullptr
0041197d        struct Direct3D8* d3d = renderer->d3d
00411985        if (d3d != 0)
0041198a        d3d->vtbl->Release(d3d)
0041198d        renderer->d3d = nullptr
00411998        return
