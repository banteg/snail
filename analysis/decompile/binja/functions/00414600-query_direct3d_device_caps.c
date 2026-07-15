/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: query_direct3d_device_caps @ 0x414600 */

00414603        struct Direct3D8* d3d = renderer->d3d
00414617        d3d->vtbl->GetDeviceCaps(d3d, 0, 1, &renderer->device_caps)
00414640        return
