/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: present_backbuffer @ 0x413520 */

00413520        struct Direct3DDevice8* device = g_direct3d_renderer.device
00413533        return device->vtbl->Present(device, nullptr, nullptr, 0, nullptr)
