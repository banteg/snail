/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* export: isolated copy with manifest symbols applied */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: begin_sprite_depth_render_state @ 0x413540 */

00413543        struct Direct3DDevice8* device = g_direct3d_renderer.device
00413558        struct TransformMatrix matrix
00413558        __builtin_memset(&matrix.position, 0, 0xc)
00413560        matrix.basis_forward_w = 0
00413568        matrix.basis_forward.y = 0
00413570        matrix.basis_forward.x = 0
00413578        matrix.basis_up_w = 0
00413580        matrix.basis_up.z = 0
00413588        matrix.basis_up.x = 0
00413590        matrix.basis_right_w = 0
00413598        matrix.basis_right.z = 0
004135a0        matrix.basis_right.y = 0
004135a8        matrix.position_w = 0x3f800000
004135b0        matrix.basis_forward.z = 0x3f800000
004135b8        matrix.basis_up.y = 0x3f800000
004135c0        matrix.basis_right.x = 0x3f800000
004135d2        device->vtbl->GetTransform(device, 2, &data_503178)
004135d8        struct Direct3DDevice8* device_1 = g_direct3d_renderer.device
004135e7        device_1->vtbl->SetTransform(device_1, 2, &matrix)
004135ed        struct Direct3DDevice8* device_2 = g_direct3d_renderer.device
004135ff        device_2->vtbl->SetTransform(device_2, 0x100, &matrix)
00413605        struct Direct3DDevice8* device_3 = g_direct3d_renderer.device
00413613        device_3->vtbl->SetTextureStageState(device_3, 0, 0xd, 3)
00413619        struct Direct3DDevice8* device_4 = g_direct3d_renderer.device
00413627        device_4->vtbl->SetTextureStageState(device_4, 0, 0xe, 3)
0041362d        struct Direct3DDevice8* device_5 = g_direct3d_renderer.device
00413644        return device_5->vtbl->SetTextureStageState(device_5, 0, 0x18, 0)
